#include "pch.h"
#include "MovementManager.h"
#include "Constants.h"

const float MovementManager::smk_CupheadJumpSpeed{ 1000.f };
const float MovementManager::smk_CupheadRunSpeed{ 370.f };
const float MovementManager::smk_CupheadDashSpeed{ 700.f };
const float MovementManager::smk_CupheadDashTime{ .3f };
const float MovementManager::smk_CupheadDashCooldownTime{ .5f };

MovementManager::MovementManager( )
	: m_KeysStates{}
	, m_DirectionData{ AimDirection::none, true }
	, m_MovementType{}
	, m_VelocityModifiers{}
	, m_IsShooting{}
	, m_IsDashing{}
	, m_DashingAccumulatedTime{}
	, m_DashingCooldownAccumulatedTime{}
	, m_IsAirborne{}
	, m_AirborneAccumulatedTime{}
	, m_IsGravityReversed{}
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

bool MovementManager::IsFacingRight( ) const
{
	return m_DirectionData.facingRight;
}

bool MovementManager::IsShooting( ) const
{
	return m_IsShooting;
}

void MovementManager::SetGravity( bool isReversed )
{
	m_IsGravityReversed = isReversed;
}

void MovementManager::TouchingFloor( )
{
	m_IsAirborne = false;
	m_AirborneAccumulatedTime = 0.f;
}

void MovementManager::UpdateVelocity( Vector2f& velocity, float elapsedSec )
{
	velocity.x = 0;

	// If cuphead is dashing, put dashing speed in the dashing direction ...
	if ( m_IsDashing )
	{
		// end dash algorithm
		m_DashingAccumulatedTime += elapsedSec;
		if ( m_DashingAccumulatedTime > smk_CupheadDashTime )
		{
			m_IsDashing = false;
			m_DashingAccumulatedTime = 0.f;
			m_DashingCooldownAccumulatedTime = 0.f;
			UpdateVelocity( velocity, elapsedSec );
			return;
		}

		const int direction{ m_DirectionData.facingRight ? 1 : -1 };
		velocity.x = direction * smk_CupheadDashSpeed;

		// store current y velocity when accelerating downwards in modifiers to apply it after dash
		if ( velocity.y < 0.f )
		{
			m_VelocityModifiers.y += velocity.y;
		}
		velocity.y = 0.f;
	}
	// ... else do other basic movements
	else 
	{
		if ( m_IsAirborne )
		{
			m_AirborneAccumulatedTime += elapsedSec;
		}
		if ( m_MovementType != MovementType::duck )
		{
			if ( m_KeysStates.faceRightKeyPressed )
			{
				velocity.x += smk_CupheadRunSpeed;
			}
			if ( m_KeysStates.faceLeftKeyPressed )
			{
				velocity.x -= smk_CupheadRunSpeed;
			}
		}

		velocity.y -= (Constants::sk_GravityPullSpeed * elapsedSec + Constants::sk_GravityPullAcceleration * m_AirborneAccumulatedTime);
		velocity += m_VelocityModifiers;
		m_VelocityModifiers.Set( 0.f, 0.f );
	}

	m_DashingCooldownAccumulatedTime += elapsedSec;
}

void MovementManager::KeyPressEvent( const SDL_KeyboardEvent& e )
{
	const bool pressed{ e.state == SDL_PRESSED };
	switch ( e.keysym.sym )
	{
	case SDLK_UP:
		m_KeysStates.faceUpKeyPressed = pressed;
		break;
	case SDLK_LEFT:
		m_KeysStates.faceLeftKeyPressed = pressed;
		break;
	case SDLK_DOWN:
		m_KeysStates.faceDownKeyPressed = pressed;
		break;
	case SDLK_RIGHT:
		m_KeysStates.faceRightKeyPressed = pressed;
		break;
	case SDLK_SPACE:
		m_KeysStates.jumpKeyChanged = (m_KeysStates.jumpKeyPressed != pressed);
		m_KeysStates.jumpKeyPressed = pressed;
		break;
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
		m_KeysStates.swapWeaponsKeyPressed = pressed;
		break;
	default:
		return;
	}
	m_KeysStates.stopKeyPressed = (m_KeysStates.faceRightKeyPressed == m_KeysStates.faceLeftKeyPressed); // stop when neither or both are pressed
}

void MovementManager::ProcessMovementData( )
{
	DirectionData directionData{ CalculateAimDirection( m_DirectionData ) };
	MovementType movement{ CalculateMovementType( m_MovementType ) };

	m_IsShooting = m_KeysStates.shootKeyPressed;

	directionData.Fix( movement, m_DirectionData );
	if ( movement == MovementType::jump && !m_IsAirborne )
	{
		m_IsAirborne = true;
		m_VelocityModifiers.y += smk_CupheadJumpSpeed;
	}
	else if ( movement == MovementType::dashGround || movement == MovementType::dashAir )
	{
		m_IsDashing = true;
		m_IsShooting = false;
	}

	m_DirectionData = directionData;
	m_MovementType = movement;
}

MovementManager::DirectionData MovementManager::CalculateAimDirection( DirectionData previous )
{
	DirectionData directionData{ previous };
	int mod{};

	if ( m_KeysStates.faceUpKeyPressed )
	{
		mod = 1; // "up" variation is placed 1 position under left/right
	}
	else if ( m_KeysStates.faceDownKeyPressed )
	{
		mod = 2; // "down" variation is placed 1 position under left/right
	}

	if ( m_KeysStates.faceRightKeyPressed )
	{
		directionData.direction = AimDirection::right;
		directionData.facingRight = true;
		
	}
	else if ( m_KeysStates.faceLeftKeyPressed )
	{
		directionData.direction = AimDirection::left;
		directionData.facingRight = false;
	}

	directionData.direction = static_cast<AimDirection>(int( directionData.direction ) + mod); // Direction is casted as offset + variation
	return directionData;
}

MovementManager::MovementType MovementManager::CalculateMovementType( MovementType previous )
{
	MovementType movement{ MovementType::idle }; // By default, set to idle.

	if ( m_IsDashing || (m_KeysStates.dashKeyPressed && m_DashingCooldownAccumulatedTime > smk_CupheadDashCooldownTime) )
	{
		movement = m_IsAirborne ? MovementType::dashAir : MovementType::dashGround;
	}
	else if ( m_IsAirborne || (m_KeysStates.jumpKeyPressed && m_KeysStates.jumpKeyChanged) )
	{
		movement = MovementType::jump;
	}
	else
	{
		if ( m_KeysStates.faceUpKeyPressed )
		{
		}
		else if ( m_KeysStates.faceDownKeyPressed )
		{
			if ( previous != MovementType::run )
			{
				movement = MovementType::duck;
			}
		}

		if ( m_KeysStates.stopKeyPressed )
		{
		}
		else if ( m_KeysStates.faceLeftKeyPressed || m_KeysStates.faceRightKeyPressed )
		{
			if ( movement != MovementType::duck )
			{
				movement = MovementType::run;
			}
		}
	}

	return movement;
}

void MovementManager::DirectionData::Fix( MovementType movement, const DirectionData& previous )
{
	if ( movement == MovementType::duck )
	{
		direction = facingRight ? AimDirection::right : AimDirection::left;
	}
	else if ( movement == MovementType::dashGround || movement == MovementType::dashAir )
	{
		*this = previous;
	}
}
