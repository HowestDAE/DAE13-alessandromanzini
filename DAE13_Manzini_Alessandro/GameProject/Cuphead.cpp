#include "pch.h"
#include "Cuphead.h"

#include "TextureManager.h"
#include "SpriteManager.h"
#include "WeaponsManager.h"
#include "MovementManager.h"

Cuphead::Cuphead(const Point2f& position )
	: m_pIdleSprite{}
	, m_pRunSprite{}
	, m_FlipTextureX{}
	, m_FlipTextureY{}
{
	m_Velocity = Vector2f{ 0.f, 0.f };
	m_Location = Vector2f{ position };
}

void Cuphead::Draw( ) const
{
	m_pTextureManager->Draw( m_Location.ToPoint2f(), m_FlipTextureX, m_FlipTextureY );
}

void Cuphead::Update( float elapsedSec )
{
	m_MovementManager.CalculateMovementData( );
	m_MovementManager.UpdateVelocity( m_Velocity );
	m_Location += m_Velocity * elapsedSec;

	SelectTexture( );
	m_pTextureManager->Update( elapsedSec );
}

void Cuphead::KeyPressEvent( const SDL_KeyboardEvent& e )
{
	m_MovementManager.KeyPressEvent( e );
}

void Cuphead::SelectTexture( )
{
	MovementManager::AimDirection direction{ m_MovementManager.GetAimDirection( ) };
	MovementManager::MovementType movementType{ m_MovementManager.GetMovementType( ) };

	switch ( movementType )
	{
	case MovementManager::MovementType::idle:
	case MovementManager::MovementType::duck:
		m_pTextureManager = m_pIdleSprite;
		break;
	case MovementManager::MovementType::aim:
		break;
	case MovementManager::MovementType::run:
		m_pTextureManager = m_pRunSprite;
		break;
	case MovementManager::MovementType::jump:
		break;
	case MovementManager::MovementType::parry:
		break;
	case MovementManager::MovementType::dash:
		break;
	default:
		break;
	}

	switch ( direction )
	{
	case MovementManager::AimDirection::right:
	case MovementManager::AimDirection::rightup:
	case MovementManager::AimDirection::rightdown:
		m_FlipTextureX = false;
		break;
	case MovementManager::AimDirection::left:
	case MovementManager::AimDirection::leftup:
	case MovementManager::AimDirection::leftdown:
		m_FlipTextureX = true;
		break;
	default:
		break;
	}
}
