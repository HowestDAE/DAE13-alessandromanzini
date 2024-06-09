#include "pch.h"
#include "MovementManager.h"
#include "SoundManager.h"
#include "Constants.h"
#include <iostream>

const float MovementManager::smk_InputDelay{ 0.25f };
const float MovementManager::smk_ToAirborneTime{ 0.17f };

MovementManager::MovementManager( )
	: m_KeysStates{}
	, m_DirectionData{ AimDirection::none, true }
	, m_MovementType{}
	, m_VelocityModifiers{}
	, m_IsTransitioning{}
	, m_IsShooting{}
	, m_IsExMoveRequested{}
	, m_IsExMoving{}
	, m_AimAngle{}
	, m_IsDashing{}
	, m_DashingAccumulatedTime{}
	, m_DashingCooldownAccumulatedTime{}
	, m_IsAirborne{}
	, m_AirborneAccumulatedTime{}
	, m_IsParrying{}
	, m_IsParried{}
	, m_IsGravityReversing{}
	, m_GravityReversingAccumulatedTime{}
	, m_IsGravityReversed{}
	, m_GravityNormal{ -1 } // default Gravity goes down
	, m_IsMoving{}
	, m_IsParryIFraming{}
	, m_ParryIFramingElapsedTime{}
	, m_IsPropelled{}
	, m_IsPropelling{}
	, m_PropelledAccumulatedTime{}
	, m_SwapWeaponsRequested{}
	, m_SwapWeaponsAccumulatedTime{}
{
	m_KeysStates.stopKeyPressed = true;
}

MovementManager::AimDirection MovementManager::GetAimDirection( ) const
{
	return m_DirectionData.direction;
}

MovementManager::MovementType MovementManager::GetMovementType( ) const
{
	return m_MovementType;
}

bool MovementManager::GetIsFacingRight( ) const
{
	return m_DirectionData.facingRight;
}

bool MovementManager::GetIsGravityReversed( ) const
{
	return m_IsGravityReversed;
}

bool MovementManager::GetIsTransitioning( ) const
{
	return m_IsTransitioning;
}

bool MovementManager::GetIsIFraming( ) const
{
	return m_IsParryIFraming;
}

bool MovementManager::GetIsShooting( ) const
{
	return m_IsShooting;
}

bool MovementManager::GetIsExMove( ) const
{
	return m_IsExMoveRequested;
}

float MovementManager::GetAimAngle( ) const
{
	return m_AimAngle;
}

bool MovementManager::GetIsParrying( ) const
{
	return m_IsParrying;
}

bool MovementManager::GetSwapWeapons( ) const
{
	return m_SwapWeaponsRequested;
}

void MovementManager::SetExingState( bool isExing )
{
	m_IsExMoving = isExing;
}

void MovementManager::ToggleGravity( )
{
	m_IsGravityReversing = true;
}

void MovementManager::PlatformCollisionFeedback( )
{
	m_IsAirborne = false;
	m_IsParrying = false;
	m_IsParried = false;
	m_AirborneAccumulatedTime = 0.f;
}

void MovementManager::VerticalBoundsCollisionFeedback( )
{
	if ( !m_IsPropelled )
	{
		m_IsPropelled = true;
		m_IsPropelling = true;
	}
}

void MovementManager::ParryCollisionFeedback( )
{
	m_IsParrying = false;
	m_IsParryIFraming = true;

	SoundManager::Play( "cuphead_parry" );
}

void MovementManager::Update( float elapsedSec )
{
	DefineState( );
	UpdateState( elapsedSec );

	ProcessMovementData( );

	if ( m_AirborneAccumulatedTime >= smk_ToAirborneTime )
	{
		m_IsAirborne = true;
	}
}

void MovementManager::UpdateVelocity( Vector2f& velocity, float elapsedSec )
{
	velocity.x = 0;

	if ( m_IsExMoving )
	{
		velocity.y = 0.f;
		velocity.x += Constants::sk_CupheadExPushBackSpeed * (m_DirectionData.facingRight ? -1 : 1);
	}
	// If cuphead is dashing, put dashing speed in the dashing direction ...
	else if ( m_IsDashing )
	{
		const int direction{ m_DirectionData.facingRight ? 1 : -1 };
		velocity.x = direction * Constants::sk_CupheadDashSpeed;

		// store current y velocity when accelerating downwards in modifiers to apply it after dash
		if ( velocity.y * (-m_GravityNormal) < 0.f )
		{
			m_VelocityModifiers.y += velocity.y;
		}
		velocity.y = 0.f;
	}
	// ... else do other basic movements
	else 
	{
		if ( m_IsPropelling )
		{
			velocity.y = 0.f;
			m_AirborneAccumulatedTime = 0.f;
			m_VelocityModifiers.y += -Constants::sk_CupheadOutOfBoundsSpeed * m_GravityNormal;
			m_IsPropelling = false;
		}
		if ( m_IsMoving )
		{
			if ( m_DirectionData.facingRight )
			{
				velocity.x += Constants::sk_CupheadRunSpeed;
			}
			else
			{
				velocity.x -= Constants::sk_CupheadRunSpeed;
			}
		}

		const float gravityPull{ (Constants::sk_GravityPullSpeed * elapsedSec + Constants::sk_GravityPullAcceleration * m_AirborneAccumulatedTime) };
		velocity.y += ( gravityPull * m_GravityNormal );
		velocity += m_VelocityModifiers;
		m_VelocityModifiers.Set( 0.f, 0.f );
	}
}

void MovementManager::KeyPressEvent( const SDL_KeyboardEvent& e )
{
	const bool pressed{ e.state == SDL_PRESSED };
	switch ( e.keysym.sym )
	{
	case SDLK_UP:
		if ( !m_IsGravityReversed )
		{
			m_KeysStates.faceUpKeyPressed = pressed;
		}
		else
		{
			m_KeysStates.faceDownKeyPressed = pressed;
		}
		break;
	case SDLK_LEFT:
		m_KeysStates.faceLeftKeyPressed = pressed;
		m_KeysStates.faceRightOverride = !pressed;
		break;
	case SDLK_DOWN:
		if ( !m_IsGravityReversed )
		{
			m_KeysStates.faceDownKeyPressed = pressed;
		}
		else
		{
			m_KeysStates.faceUpKeyPressed = pressed;
		}
		break;
	case SDLK_RIGHT:
		m_KeysStates.faceRightKeyPressed = pressed;
		m_KeysStates.faceRightOverride = pressed;
		break;
	case SDLK_SPACE:
		m_KeysStates.jumpKeyChanged = (m_KeysStates.jumpKeyPressed != pressed);
		m_KeysStates.jumpKeyPressed = pressed;
		break;
	case SDLK_z:
	case SDLK_LSHIFT:
		m_KeysStates.dashKeyChanged = (m_KeysStates.dashKeyPressed != pressed);
		m_KeysStates.dashKeyPressed = pressed;
		break;
	case SDLK_a:
		m_KeysStates.shootKeyPressed = pressed;
		break;
	case SDLK_s:
		m_KeysStates.lockKeyPressed = pressed;
		break;
	case SDLK_d:
		m_KeysStates.exMoveKeyPressed = pressed;
		break;
	case SDLK_x:
		m_KeysStates.swapWeaponsKeyChanged = (m_KeysStates.swapWeaponsKeyPressed != pressed);
		m_KeysStates.swapWeaponsKeyPressed = pressed;
		break;
	default:
		return;
	}
	m_KeysStates.stopKeyPressed = (!m_KeysStates.faceRightKeyPressed && !m_KeysStates.faceLeftKeyPressed); // stop when neither or both are pressed
}

void MovementManager::Reset( )
{
	m_IsTransitioning = false;

	m_IsShooting = false;
	m_IsExMoveRequested = false;
	m_IsExMoving = false;
	m_AimAngle = 0.f;

	m_IsDashing = false;
	m_DashingAccumulatedTime = 0.f;
	m_DashingCooldownAccumulatedTime = 0.f;

	m_IsAirborne = false;
	m_AirborneAccumulatedTime = 0.f;

	m_IsParrying = false;
	m_IsParried = false;

	m_IsMoving = false;

	m_IsGravityReversing = false;
	m_IsGravityReversed = false;
	m_GravityNormal = -1;
	m_VelocityModifiers.Set( 0.f, 0.f );

	m_IsParryIFraming = false;
	m_ParryIFramingElapsedTime = 0.f;

	m_IsPropelled = false;
	m_IsPropelling = false;
	m_PropelledAccumulatedTime = 0.f;

	m_SwapWeaponsRequested = false;
	m_SwapWeaponsAccumulatedTime = 0.f;
}

void MovementManager::DefineState( )
{
	if ( !m_IsParrying )
	{
		if ( m_KeysStates.dashKeyPressed && m_KeysStates.dashKeyChanged
			&& m_DashingCooldownAccumulatedTime > Constants::sk_CupheadDashCooldownTime )
		{
			SoundManager::Play( "cuphead_dash" );
			m_IsDashing = true;
		}
	}

	if ( m_KeysStates.jumpKeyPressed && m_KeysStates.jumpKeyChanged )
	{
		m_KeysStates.jumpKeyChanged = false;

		if ( !m_IsAirborne )
		{
			SoundManager::Play( "cuphead_jump" );
			m_VelocityModifiers.y += Constants::sk_CupheadJumpSpeed * ( -m_GravityNormal );
			m_IsAirborne = true;
		}
		else if ( !m_IsParried )
		{
 			m_IsParrying = true;
			m_IsParried = true;
		}
	}

	m_IsMoving = !m_KeysStates.stopKeyPressed;
	m_IsShooting = m_KeysStates.shootKeyPressed;
	m_IsExMoveRequested = m_KeysStates.exMoveKeyPressed;
}

void MovementManager::UpdateState( float elapsedSec )
{
	if ( m_IsDashing )
	{
		m_DashingAccumulatedTime += elapsedSec;
		if ( m_DashingAccumulatedTime > Constants::sk_CupheadDashTime )
		{
			m_IsDashing = false;
			m_DashingAccumulatedTime = 0.f;
			m_DashingCooldownAccumulatedTime = 0.f;
			m_AirborneAccumulatedTime = 0.f;
		}
	}
	else
	{
		m_DashingCooldownAccumulatedTime += elapsedSec;

		m_AirborneAccumulatedTime += elapsedSec;
		/*if ( m_IsAirborne )
		{
			m_AirborneAccumulatedTime += elapsedSec;
		}*/

		if ( m_IsGravityReversing )
		{
			m_GravityReversingAccumulatedTime += elapsedSec;
			if ( m_GravityReversingAccumulatedTime >= Constants::sk_CupheadGravityReversingTime )
			{
				m_IsGravityReversed = !m_IsGravityReversed;
				m_GravityNormal *= -1;

				m_AirborneAccumulatedTime = 0.f;

				m_IsGravityReversing = false;
				m_GravityReversingAccumulatedTime = 0.f;
			}
		}
	}

	if ( m_IsPropelled )
	{
		m_PropelledAccumulatedTime += elapsedSec;

		if ( m_PropelledAccumulatedTime >= Constants::sk_CupheadPropelledCooldownTime )
		{
			m_IsPropelled = false;
			m_PropelledAccumulatedTime = 0.f;
		}
	}

	if ( m_IsParryIFraming )
	{
		m_ParryIFramingElapsedTime += elapsedSec;

		if ( m_ParryIFramingElapsedTime >= Constants::sk_CupheadParryIFrameTime )
		{
			m_IsParryIFraming = false;
			m_ParryIFramingElapsedTime = 0.f;
		}
	}

	m_SwapWeaponsAccumulatedTime += elapsedSec;
	if ( m_KeysStates.swapWeaponsKeyPressed && m_SwapWeaponsAccumulatedTime >= smk_InputDelay )
	{
		m_SwapWeaponsAccumulatedTime = 0.f;
		m_SwapWeaponsRequested = true;
	}
	else
	{
		m_SwapWeaponsRequested = false;
	}
}

void MovementManager::ProcessMovementData( )
{
	DirectionData directionData{ CalculateAimDirection( ) };
	MovementType movement{ CalculateMovementType( ) };

	AdjustMovementData( directionData, movement );

	m_IsTransitioning = (m_MovementType != movement);

	m_DirectionData = directionData;
	m_MovementType = movement;
	m_AimAngle = CalculateAimAngle( );
}

MovementManager::DirectionData MovementManager::CalculateAimDirection( ) const
{
	DirectionData directionData{ AimDirection::none, m_DirectionData.facingRight };
	int mod{};

	if ( m_KeysStates.faceUpKeyPressed )
	{
		mod = 1; // "diagonalup" variation is placed 1 position under straight
	}
	else if ( m_KeysStates.faceDownKeyPressed )
	{
		mod = 2; // "diagonaldown" variation is placed 1 position under straight
	}

	if ( !m_KeysStates.stopKeyPressed )
	{
		directionData.direction = AimDirection::straight;
		directionData.facingRight = m_KeysStates.faceRightOverride;
	}

	directionData.direction = static_cast<AimDirection>( int( directionData.direction ) + mod ); // Direction is casted as offset + variation
	
	return directionData;
}

MovementManager::MovementType MovementManager::CalculateMovementType( ) const
{
	MovementType movement{ };

	if ( m_IsDashing )
	{
		movement = m_IsAirborne ? MovementType::dashAir : MovementType::dashGround;
	}
	else if ( m_IsParrying )
	{
		movement = MovementType::parry;
	}
	else if ( m_IsAirborne )
	{
		movement = MovementType::jump;
	}
	else if ( m_KeysStates.lockKeyPressed )
	{
		movement = MovementType::aim;
	}
	else if ( m_KeysStates.faceDownKeyPressed )
	{
		movement = MovementType::duck;
	}
	else if ( m_KeysStates.stopKeyPressed )
	{
		movement = MovementType::idle;
	}
	else
	{
		movement = MovementType::run;
	}

	return movement;
}

float MovementManager::CalculateAimAngle( ) const
{
	float rotation{};

	// Get "facing right" angle
	switch ( m_DirectionData.direction )
	{
	case MovementManager::AimDirection::straight:
		rotation = 0.f;
		break;
	case MovementManager::AimDirection::diagonalup:
		rotation = 45.f;
		break;
	case MovementManager::AimDirection::up:
		rotation = 90.f;
		break;
	case MovementManager::AimDirection::down:
		rotation = -90.f;
		break;
	case MovementManager::AimDirection::diagonaldown:
		rotation = -45.f;
		break;
	}

	// Translate to "facing left" angle
	if ( !m_DirectionData.facingRight )
	{
		rotation = 180 - rotation;
	}

	// Translate to gravity change
	if ( m_IsGravityReversed )
	{
		rotation = -rotation;
	}

	return rotation;
}

void MovementManager::AdjustMovementData( DirectionData& data, MovementType& movement ) 
{
	if ( movement == MovementType::dashGround || movement == MovementType::dashAir )
	{
		data = m_DirectionData;
		m_IsShooting = false;
		m_IsExMoveRequested = false;
		m_IsMoving = false;
	}
	else if ( movement == MovementType::idle && m_IsShooting )
	{
		movement = MovementType::aim;

		// only up and straight are allowed and we default to straight
		if ( data.direction != AimDirection::up )
		{
			data.direction = AimDirection::straight;
		}
	}
	else if ( movement == MovementType::run )
	{
		// While running, set everything that is not diagonalup to straight
		if ( data.direction != AimDirection::diagonalup )
		{
			data.direction = AimDirection::straight;
		}
	}
	else if ( movement == MovementType::duck )
	{
		data.direction = AimDirection::straight;
		m_IsMoving = false;
	}
	else if ( movement == MovementType::parry )
	{
		m_IsShooting = false;
		m_IsExMoveRequested = false;
	}
	else if ( movement == MovementType::aim )
	{
		m_IsMoving = false;
	}

	if ( data.direction == AimDirection::none )
	{
		data.direction = AimDirection::straight;
	}
}
