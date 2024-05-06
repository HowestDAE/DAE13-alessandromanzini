#include "pch.h"
#include "Cuphead.h"
#include "Constants.h"
#include "ResourcesLinker.h"
#include "Texture2D.h"
#include "Sprite.h"
#include "PlatformManager.h"
#include "HUDManager.h"
#include "utils.h"
#include "iostream"

Cuphead::Cuphead(const Point2f& position, HUDManager* pHUDManager )
	: Entity( position, Constants::sk_CupheadStartingHP, 0 ) 
	, m_pHUDManager{ pHUDManager }
	, m_IsInvincible{ false }
	, m_IFramesElapsedTime{}
	, m_pIdleSprite{}
	, m_pRunSprite{}
	, m_pDuckSprite{}
	, m_pDuckShootSprite{}
	, m_pJumpSprite{}
	, m_pDashGroundSprite{}
	, m_pDashAirSprite{}
	, m_pShootStraightSprite{}
	, m_pShootDiagonalupSprite{}
	, m_pShootDownSprite{}
	, m_pAimUpSprite{}
	, m_pAimStraightSprite{}
	, m_pAimDiagonaldownSprite{}
	, m_pRunShootStraightSprite{}
	, m_pRunShootDiagonalupSprite{}
	, m_pParrySprite{}
	, m_StandingCollisionManager{ std::vector<CollisionCircle>{ CollisionCircle{ 45.f, 30.f, 30.f }, CollisionCircle{ 45.f, 75.f, 30.f } }, &m_Location }
	, m_DuckingCollisionManager{ std::vector<CollisionCircle>{ CollisionCircle{ 45.f, 30.f, 30.f } }, &m_Location }
{
	m_Velocity = Vector2f{ 0.f, 0.f };
}

void Cuphead::Draw( ) const
{
	m_WeaponManager.Draw( );
	if ( !m_TextureFlashing )
	{
		Entity::Draw( );
	}
	DrawCollision( );
	/*{
		const Point2f point{ (m_Location + m_MidTranslationVector).ToPoint2f( ) };
		const Point2f wallPos{ point + m_ShootingTranslationVector };
		utils::DrawRect( point.x - 5.f, point.y - 5.f, 10.f, 10.f );
		utils::DrawRect( wallPos.x, wallPos.y - 7.f, 5.f, 14.f );
	}*/
}

void Cuphead::Update( float elapsedSec )
{
	m_TextureInfo.pTexture->Update( elapsedSec );
	Entity::Update( elapsedSec );

	UpdateMovement( elapsedSec );
	UpdateWeapons( elapsedSec );
	UpdateIFrames( elapsedSec );

	UpdateHUDManager( );
}

void Cuphead::KeyPressEvent( const SDL_KeyboardEvent& e )
{
	m_MovementManager.KeyPressEvent( e );
}

void Cuphead::CheckCollision( PlatformManager const* pPlatformManager )
{
	const Vector2f displacement{ pPlatformManager->GetDisplacementFromPlatform( this ) };

	if ( displacement.y )
	{
		m_Velocity.y = 0;
		m_MovementManager.TouchingFloor( );
	}

	m_Location += displacement;
}

void Cuphead::CheckCollision( CollidableEntity& other )
{
	CollidableEntity::CheckCollision( other );
	m_WeaponManager.CheckCollision( other );
}

void Cuphead::Hit( int damage )
{
	if ( !m_IsInvincible )
	{
		Entity::Hit( damage );

		m_pHitSprite->Reset( );
		QueueTexture( m_pHitSprite, true );

		if ( !GetIsAlive( ) )
		{
			Kill( );
			return;
		}

		m_IsInvincible = true;
		m_IFramesElapsedTime = 0.f;
	}
}

float Cuphead::GetTextureWidth( ) const
{
	return m_pIdleSprite->GetWidth();
}

void Cuphead::LinkTexture( ResourcesLinker* pResourcesLinker )
{
	m_pIdleSprite = pResourcesLinker->GetSprite("cuphead_idle" );
	m_pRunSprite = pResourcesLinker->GetSprite( "cuphead_run" );
	m_pDuckBeginSprite = pResourcesLinker->GetSprite( "cuphead_duck_begin" );
	m_pDuckSprite = pResourcesLinker->GetSprite( "cuphead_duck" );
	m_pDuckShootSprite = pResourcesLinker->GetSprite( "cuphead_duckshoot" );
	m_pJumpSprite = pResourcesLinker->GetSprite( "cuphead_jump" );
	m_pParrySprite = pResourcesLinker->GetSprite( "cuphead_parry" );
	m_pDashGroundSprite = pResourcesLinker->GetSprite( "cuphead_dash_ground" );
	m_pDashAirSprite = pResourcesLinker->GetSprite( "cuphead_dash_air" );
	m_pShootStraightSprite = pResourcesLinker->GetSprite( "cuphead_shoot_straight" );
	m_pShootDiagonalupSprite = pResourcesLinker->GetSprite( "cuphead_shoot_diagonalup" );
	m_pShootDiagonaldownSprite = pResourcesLinker->GetSprite( "cuphead_shoot_diagonaldown" );
	m_pShootDownSprite = pResourcesLinker->GetSprite( "cuphead_shoot_down" );
	m_pShootUpSprite = pResourcesLinker->GetSprite( "cuphead_shoot_up" );
	m_pAimUpSprite = pResourcesLinker->GetSprite( "cuphead_aim_up" );
	m_pAimDownSprite = pResourcesLinker->GetSprite( "cuphead_aim_down" );
	m_pAimStraightSprite = pResourcesLinker->GetSprite( "cuphead_aim_straight" );
	m_pAimDiagonaldownSprite = pResourcesLinker->GetSprite( "cuphead_aim_diagonaldown" );
	m_pAimDiagonalupSprite = pResourcesLinker->GetSprite( "cuphead_aim_diagonalup" );
	m_pRunShootStraightSprite = pResourcesLinker->GetSprite( "cuphead_runshoot_straight" );
	m_pRunShootDiagonalupSprite = pResourcesLinker->GetSprite( "cuphead_runshoot_diagonalup" );
	m_pHitSprite = pResourcesLinker->GetSprite( "cuphead_hit" );
	m_pGhostSprite = pResourcesLinker->GetSprite( "cuphead_ghost" );

	m_TextureInfo.pTexture = m_pIdleSprite;
	
	m_WeaponManager.LinkTexture( pResourcesLinker );
}

void Cuphead::UpdateMovement( float elapsedSec )
{
	if ( true || GetIsAlive( ) )
	{
		m_MovementManager.Update( elapsedSec );
		m_MovementManager.UpdateVelocity( m_Velocity, elapsedSec );
		SelectTexture( );
	}
	m_Location += m_Velocity * elapsedSec;
}

void Cuphead::UpdateWeapons( float elapsedSec )
{
	m_WeaponManager.Update( elapsedSec );
	if ( m_MovementManager.GetIsShooting( ) )
	{
		const float textureWidthHalved{ GetTextureWidth() / 2.f };
		const float radius{ textureWidthHalved / 2.f };

		const Point2f relativeOrigin{ textureWidthHalved + m_TextureInfo.pTexture->GetOffset( ).x, GetTextureHeight( ) / 2.f };
		Point2f origin{ relativeOrigin + m_Location };
		float rotation{};

		// Get "facing right" angle
		switch ( m_MovementManager.GetAimDirection( ) )
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
		if ( !m_MovementManager.GetIsFacingRight( ) )
		{
			rotation = 180 - rotation;
		}
		else
		{
			const float rightOffset{ 40.f };
			origin.x += rightOffset;
		}

		if ( m_MovementManager.GetMovementType( ) == MovementManager::MovementType::duck )
		{
			const float heightOffset{ 18.f };
			origin.y -= heightOffset;
		}

		m_WeaponManager.Shoot( origin, radius, rotation );
	}
}

void Cuphead::UpdateIFrames( float elapsedSec )
{
	if ( m_IsInvincible )
	{
		Entity::UpdateHitFlashing( elapsedSec, Constants::sk_CupheadFlashDuration, true );
		
		m_IFramesElapsedTime += elapsedSec;
		if ( m_IFramesElapsedTime >= Constants::sk_CupheadIFramesDuration )
		{
			m_IsInvincible = false;
			m_TextureFlashing = false;
		}
	}
}

void Cuphead::UpdateHUDManager( )
{
	m_pHUDManager->SetHP( m_HP );
}

void Cuphead::SelectTexture( )
{
	Texture2D* pSelectedTexture{};
	const MovementManager::AimDirection direction{ m_MovementManager.GetAimDirection() };
	const MovementManager::MovementType movement{ m_MovementManager.GetMovementType() };
	const bool flipX{ !m_MovementManager.GetIsFacingRight() }, flipY{};
	const bool isShooting{ m_MovementManager.GetIsShooting( ) };
	const bool isTransitioning{ m_MovementManager.GetIsTransitioning( ) };

	SetCollisionManager( &m_StandingCollisionManager );
	switch ( movement )
	{
	case MovementManager::MovementType::idle:
		SelectIdle( );
		break;
	case MovementManager::MovementType::duck:
		SelectDuck( isShooting, isTransitioning );
		SetCollisionManager( &m_DuckingCollisionManager );
		break;
	case MovementManager::MovementType::aim:
		SelectAim( isShooting, direction );
		break;
	case MovementManager::MovementType::run:
		SelectRun( isShooting, direction );
		break;
	case MovementManager::MovementType::jump:
		SelectJump( );
		break;
	case MovementManager::MovementType::parry:
		SelectParry( );
		break;
	case MovementManager::MovementType::dashGround:
		SelectDashGround( );
		break;
	case MovementManager::MovementType::dashAir:
		SelectDashAir( );
		break;
	}
}

void Cuphead::SelectIdle( )
{
	QueueTexture( m_pIdleSprite );
}

void Cuphead::SelectDuck( bool isShooting, bool isTransitioning )
{
	Texture2D* pTexture;

	if ( isShooting )
	{
		pTexture = m_pDuckShootSprite;
	}
	else
	{
		pTexture = m_pDuckSprite;
	}

	if ( isTransitioning )
	{
		m_pDuckBeginSprite->Reset( );
		QueueTexture( m_pDuckBeginSprite );
	}
	QueueTexture( pTexture );
}

void Cuphead::SelectAim( bool isShooting, MovementManager::AimDirection direction )
{
	Texture2D* pTexture{};
	switch ( direction )
	{
	case MovementManager::AimDirection::up:
		pTexture = isShooting ? m_pShootUpSprite : m_pAimUpSprite;
		break;
	case MovementManager::AimDirection::down:
		pTexture = isShooting ? m_pShootDownSprite : m_pAimDownSprite;
		break;
	case MovementManager::AimDirection::straight:
		pTexture = isShooting ? m_pShootStraightSprite : m_pAimStraightSprite;
		break;
	case MovementManager::AimDirection::diagonalup:
		pTexture = isShooting ? m_pShootDiagonalupSprite : m_pAimDiagonalupSprite;
		break;
	case MovementManager::AimDirection::diagonaldown:
		pTexture = isShooting ? m_pShootDiagonaldownSprite : m_pAimDiagonaldownSprite;
		break;
	default:
		pTexture = m_pAimStraightSprite;
		break;
	}
	QueueTexture( pTexture );
}

void Cuphead::SelectRun( bool isShooting, MovementManager::AimDirection direction )
{
	Texture2D* pTexture;

	if ( isShooting )
	{
		if ( direction == MovementManager::AimDirection::diagonalup )
		{
			pTexture = m_pRunShootDiagonalupSprite;
		}
		else
		{
			pTexture = m_pRunShootStraightSprite;
		}
	}
	else
	{
		pTexture = m_pRunSprite;
	}

	QueueTexture( pTexture );
}

void Cuphead::SelectJump( )
{
	QueueTexture( m_pJumpSprite );
}

void Cuphead::SelectParry( )
{
	QueueTexture( m_pParrySprite );
}

void Cuphead::SelectDashGround( )
{
	QueueTexture( m_pDashGroundSprite );
}

void Cuphead::SelectDashAir( )
{
	QueueTexture( m_pDashAirSprite );
}

void Cuphead::QueueTexture( Texture2D* pTexture, bool priority )
{
	const bool flipX{ !m_MovementManager.GetIsFacingRight( ) }, flipY{};
	m_AnimationQueue.Enqueue( TextureInfo{ pTexture, flipX, flipY }, priority );
}

void Cuphead::Kill( )
{
	QueueTexture( m_pGhostSprite );
	m_TextureFlashing = false;
	m_Velocity.Set( 0.f, Constants::sk_CupheadGhostSpeed );
}
