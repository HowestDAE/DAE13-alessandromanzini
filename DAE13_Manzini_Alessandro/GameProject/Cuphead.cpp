#include "pch.h"
#include "Cuphead.h"
#include "TextureManager.h"
#include "SpriteManager.h"
#include "CompositeSpriteManager.h"

Cuphead::Cuphead(const Point2f& position )
	: Entity( position )
	, m_pIdleSprite{}
	, m_pRunSprite{}
	, m_pDuckSprite{}
	, m_pJumpSprite{}
{
	m_Velocity = Vector2f{ 0.f, 0.f };
}

void Cuphead::Draw( ) const
{
	Entity::Draw( );
}

void Cuphead::Update( float elapsedSec )
{
	UpdateMovement( elapsedSec );
	UpdateWeapons( elapsedSec );

	m_pTextureManager->Update( elapsedSec );
}

void Cuphead::KeyPressEvent( const SDL_KeyboardEvent& e )
{
	m_MovementManager.KeyPressEvent( e );
}

void Cuphead::ProcessPlatformCollision( const Vector2f& displacement )
{
	if ( displacement.y )
	{
		m_Velocity.y = 0;
		m_MovementManager.TouchingFloor( );
	}

	Entity::ProcessPlatformCollision( displacement );
}

float Cuphead::GetTextureWidth( ) const
{
	return m_pIdleSprite->GetWidth();
}

bool Cuphead::SelectTexture( MovementManager::AimDirection direction, MovementManager::MovementType movement )
{
	TextureManager* pSelectedTexture{};
	bool flipX{ !m_MovementManager.IsFacingRight() }, flipY{};
	bool isShooting{ m_MovementManager.IsShooting( ) };

	switch ( movement )
	{
	case MovementManager::MovementType::idle:
		pSelectedTexture = m_pIdleSprite;
		break;
	case MovementManager::MovementType::duck:
		pSelectedTexture = isShooting ? m_pDuckSprite : m_pDuckSprite;
		break;
	case MovementManager::MovementType::aim:
		break;
	case MovementManager::MovementType::run:
		pSelectedTexture = isShooting ? m_pRunSprite : m_pRunSprite;
		break;
	case MovementManager::MovementType::jump:
		pSelectedTexture = m_pJumpSprite;
		break;
	case MovementManager::MovementType::parry:
		break;
	case MovementManager::MovementType::dashGround:
		pSelectedTexture = m_pDashGroundSprite;
		break;
	case MovementManager::MovementType::dashAir:
		pSelectedTexture = m_pDashAirSprite;
		break;
	default:
		break;
	}

	return TryQueueTexture( pSelectedTexture, flipX, flipY );
}

void Cuphead::UpdateMovement( float elapsedSec )
{
	m_MovementManager.ProcessMovementData( );

	const MovementManager::AimDirection direction{ m_MovementManager.GetAimDirection( ) };
	const MovementManager::MovementType movement{ m_MovementManager.GetMovementType( ) };

	if ( SelectTexture( direction, movement ) )
	{
		//m_MovementManager.ApplyMovementData( );
	}
	m_MovementManager.UpdateVelocity( m_Velocity, elapsedSec );
	m_Location += m_Velocity * elapsedSec;
}

void Cuphead::UpdateWeapons( float elapsedSec )
{
	m_WeaponManager.Update( elapsedSec );
	if ( m_MovementManager.IsShooting( ) )
	{
		m_WeaponManager.Shoot( m_Location.ToPoint2f( ), 0.f );
	}
}
