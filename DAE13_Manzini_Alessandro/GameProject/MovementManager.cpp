#include "pch.h"
#include "MovementManager.h"
#include "Constants.h"

MovementManager::MovementManager( )
	: m_KeysStates{}
	, m_Direction{}
	, m_MovementType{}
	, mk_BaseVelocity{ Constants::sk_CupheadSpeed, Constants::sk_GravityPullSpeed }
	, mk_BaseJumpVelocity{ 0, Constants::sk_CupheadSpeed }
	, m_VelocityModifiers{}
	, m_IsAirborne{}
	, m_IsGravityReversed{}
{
	m_KeysStates.stopKeyPressed = true;
}

MovementManager::AimDirection MovementManager::GetAimDirection( ) const
{
	return m_Direction;
}

MovementManager::MovementType MovementManager::GetMovementType( ) const
{
	return m_MovementType;
}

void MovementManager::SetGravity( bool isReversed )
{
	m_IsGravityReversed = isReversed;
}

void MovementManager::UpdateVelocity( Vector2f& velocity )
{
	velocity.x = 0;
	if ( m_KeysStates.faceDownKeyPressed && !m_IsAirborne )
	{

	}
	else
	{
		if ( m_KeysStates.faceRightKeyPressed )
		{
			velocity.x += mk_BaseVelocity.x;
		}
		if ( m_KeysStates.faceLeftKeyPressed )
		{
			velocity.x -= mk_BaseVelocity.x;
		}
	}

	velocity += m_VelocityModifiers;
	m_VelocityModifiers = Vector2f{};

	//velocity.y += mk_BaseVelocity.y;
}

void MovementManager::KeyPressEvent( const SDL_KeyboardEvent& e )
{
	const bool pressed{ e.state == SDL_PRESSED };
	switch ( e.keysym.sym )
	{
	case SDLK_w:
		m_KeysStates.faceUpKeyPressed = pressed;
		break;
	case SDLK_a:
		m_KeysStates.faceLeftKeyPressed = pressed;
		break;
	case SDLK_s:
		m_KeysStates.faceDownKeyPressed = pressed;
		break;
	case SDLK_d:
		m_KeysStates.faceRightKeyPressed = pressed;
		break;
	default:
		return;
	}
	m_KeysStates.stopKeyPressed = (m_KeysStates.faceRightKeyPressed == m_KeysStates.faceLeftKeyPressed); // stop when neither or both are pressed
}

void MovementManager::CalculateMovementData( )
{
	AimDirection direction{ AimDirection::none };
	MovementType movement{ MovementType::run }; // By default, set to run.
	int mod{};

	if ( m_KeysStates.faceUpKeyPressed )
	{
		mod = 1; // "up" variation is placed 1 position under left/right
	}
	else if ( m_KeysStates.faceDownKeyPressed )
	{
		mod = 2; // "down" variation is placed 1 position under left/right
		movement = MovementType::duck;
	}

	if ( m_KeysStates.stopKeyPressed )
	{
		movement = MovementType::idle;
	}
	else if ( m_KeysStates.faceLeftKeyPressed )
	{
		direction = AimDirection::left;	
	}
	else if ( m_KeysStates.faceRightKeyPressed )
	{
		direction = AimDirection::right;
	}

	direction = static_cast<AimDirection>(int( direction ) + mod); // Direction is casted as offset + variation
	
	m_Direction = (direction != AimDirection::none) ? direction : m_Direction; // Discard new direction if enum::none
	m_MovementType = movement;
}
