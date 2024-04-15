#include "pch.h"
#include "Cuphead.h"
#include "TextureManager.h"
#include "SpriteManager.h"
#include "CompositeSpriteManager.h"
#include "utils.h"
#include "iostream"

Cuphead::Cuphead(const Point2f& position )
	: Entity( position )
	, m_pIdleSprite{}
	, m_pRunSprite{}
	, m_pDuckSprite{}
	, m_pJumpSprite{}
	, m_pDashAirSprite{}
	, m_pDashGroundSprite{}
	, m_pShootStraightSprite{}
	, m_pRunShootStraightSprite{}
	, m_pRunShootDiagonalupSprite{}
{
	m_Velocity = Vector2f{ 0.f, 0.f };
}

void Cuphead::Draw( ) const
{
	m_WeaponManager.Draw( );
	Entity::Draw( );
	/*{
		const Point2f point{ (m_Location + m_MidTranslationVector).ToPoint2f( ) };
		const Point2f wallPos{ point + m_ShootingTranslationVector };
		utils::DrawRect( point.x - 5.f, point.y - 5.f, 10.f, 10.f );
		utils::DrawRect( wallPos.x, wallPos.y - 7.f, 5.f, 14.f );
	}*/
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
		if ( isShooting )
		{
			pSelectedTexture = m_pDuckSprite;
		}
		else
		{
			pSelectedTexture = m_pDuckSprite;
		}
		break;
	case MovementManager::MovementType::aim:
		pSelectedTexture = m_pShootStraightSprite;
		break;
	case MovementManager::MovementType::run:
		if ( isShooting )
		{
			if ( direction == MovementManager::AimDirection::diagonalup )
			{
				pSelectedTexture = m_pRunShootDiagonalupSprite;
			}
			else
			{
				pSelectedTexture = m_pRunShootStraightSprite;
			}
		}
		else
		{
			pSelectedTexture = m_pRunSprite;
		}
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

	m_MovementManager.UpdateVelocity( m_Velocity, elapsedSec );
	m_Location += m_Velocity * elapsedSec;

	if ( SelectTexture( direction, movement ) )
	{
		//m_MovementManager.ApplyMovementData( );
		/*std::cout << "dir: " << int( direction ) << std::endl;
		std::cout << "mov: " << int( movement ) << std::endl << std::endl;*/
	}
}

void Cuphead::UpdateWeapons( float elapsedSec )
{
	m_WeaponManager.Update( elapsedSec );
	if ( m_MovementManager.IsShooting( ) )
	{
		const float textureWidthHalved{ m_pTextureManager->GetWidth( ) / 2.f };
		const Point2f origin{ Point2f{ textureWidthHalved + m_pTextureManager->GetOffset().x, m_pTextureManager->GetHeight( ) / 2.f} + m_Location};
		const float radius{ textureWidthHalved / 2.f };
		float rotation{};

		// Get "facing right" angle
		switch ( m_MovementManager.GetAimDirection() )
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
		if ( !m_MovementManager.IsFacingRight( ) )
		{
			rotation = 180 - rotation;
		}
		
		m_WeaponManager.Shoot( origin, radius, rotation );
	}
}
