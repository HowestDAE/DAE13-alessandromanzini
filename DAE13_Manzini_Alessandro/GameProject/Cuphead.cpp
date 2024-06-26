#include "pch.h"
#include "Cuphead.h"
#include "Constants.h"
#include "SoundManager.h"
#include "ResourcesLinker.h"
#include "Texture2D.h"
#include "Sprite.h"
#include "PlatformManager.h"
#include "HUDManager.h"
#include "utils.h"
#include <iostream>

Cuphead::Cuphead(const Point2f& position, HUDManager* pHUDManager )
	: Entity( position, Constants::sk_CupheadStartingHP, 0 ) 
	, m_pHUDManager{ pHUDManager }
	, m_WeaponManager{}
	, m_MovementManager{}
	, m_IsInvincible{ false }
	, m_IFramesElapsedTime{}
	, m_LockControls{}
	, m_StandingCollisionManager{ std::vector<CollisionCircle>{ CollisionCircle{ 45.f, 30.f, 30.f, CollisionType::forceHit }, CollisionCircle{ 45.f, 75.f, 30.f, CollisionType::forceHit } }, &m_Location }
	, m_DuckingCollisionManager{ std::vector<CollisionCircle>{ CollisionCircle{ 45.f, 30.f, 30.f, CollisionType::forceHit } }, &m_Location }
	, m_ReversedStandingCollisionManager{ std::vector<CollisionCircle>{ CollisionCircle{ 45.f, 60.f, 30.f, CollisionType::forceHit }, CollisionCircle{ 45.f, 105.f, 30.f, CollisionType::forceHit } }, &m_Location }
	, m_ReversedDuckingCollisionManager{ std::vector<CollisionCircle>{ CollisionCircle{ 45.f, 105.f, 30.f, CollisionType::forceHit } }, &m_Location }
{
	m_Velocity = Vector2f{ 0.f, 0.f };
	SetCollisionManager( &m_StandingCollisionManager );
	InitializeQueues( 2 );
}

void Cuphead::Draw( ) const
{
	// Player should be drawn on top of projectiles
	if ( !m_TextureFlashing )
	{
		Entity::Draw( 0 );
	}
	Entity::Draw( 1 );
}

void Cuphead::DrawProjectiles( ) const
{
	m_WeaponManager.Draw( );
}

void Cuphead::Update( float elapsedSec )
{
	// Entity updates loads textures, so it must be first
	Entity::Update( elapsedSec );

	UpdateMovement( elapsedSec );
	UpdateWeapons( elapsedSec );
	UpdateIFrames( elapsedSec );

	UpdateHUDManager( );
}

void Cuphead::KeyPressEvent( const SDL_KeyboardEvent& e )
{
	if ( !m_LockControls )
	{
		m_MovementManager.KeyPressEvent( e );
	}
}

bool Cuphead::CheckCollision( PlatformManager const* pPlatformManager )
{
	if ( !GetIsAlive( ) ) return false;

	Vector2f displacement{}, cameraDisplacement{};
	const bool platformCollision{ pPlatformManager->CheckCollision( this, displacement ) },
		cameraCollision{ pPlatformManager->CheckCameraBoundsCollision( this, displacement ) };
	const bool collision{ platformCollision || cameraCollision };
	{
		// Platform Collision
		if ( displacement.y )
		{
			const float speedThreshold{ 300.f };
			if ( abs( m_Velocity.y ) > speedThreshold )
			{
				QueueTexture( m_pJumpDustSprite, false, 1 );
			}

			m_Velocity.y = 0;
			m_MovementManager.PlatformCollisionFeedback( );
		}

		m_Location += displacement + cameraDisplacement;
	}

	{
		// Bounds Collision
		if ( pPlatformManager->CheckVerticalBounds( this ) )
		{
			const int outOfBoundsDamage{ 1 };
			Hit( outOfBoundsDamage );
			//m_Velocity.Set( 0.f, 0.f );
			m_MovementManager.VerticalBoundsCollisionFeedback( );
		}
	}

	return collision;
}

bool Cuphead::CheckCollision( CollidableEntity& other )
{
	if ( !GetIsAlive( ) ) return false;

	const bool playerCollision{ CollidableEntity::CheckCollision( other ) };

	if ( other.GetIsPink( ) )
	{
		if ( playerCollision && m_MovementManager.GetIsParrying( ) )
		{
			m_MovementManager.ParryCollisionFeedback( );
			// other.die()
			// weaponManager.increaseEx
		}
	}
	else
	{
		m_WeaponManager.CheckCollision( other );
	}
	
	return playerCollision;
}

bool Cuphead::CheckCollision( Card& card )
{
	if ( CollidableEntity::CheckCollision( card ) && m_MovementManager.GetIsParrying( ) )
	{
		m_MovementManager.ParryCollisionFeedback( );
		m_MovementManager.ToggleGravity( );

		card.ParryCollisionFeedback( );
	}
	return false;
}

void Cuphead::Win( ) noexcept
{
	m_Velocity.x = Constants::sk_CupheadRunSpeed;
	m_LockControls = true;
	Entity::QueueTexture( 0, m_pRunSprite ); // manual query to make sure cuphead faces right
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
	m_pJumpDustSprite = pResourcesLinker->GetSprite( "cuphead_jump_dust" );
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
	m_pExAirUpSprite = pResourcesLinker->GetSprite( "cuphead_ex_air_up" );
	m_pExAirStraightSprite = pResourcesLinker->GetSprite( "cuphead_ex_air_straight" );
	m_pExAirDiagonaldownSprite = pResourcesLinker->GetSprite( "cuphead_ex_air_diagonaldown" );
	m_pExAirDiagonalupSprite = pResourcesLinker->GetSprite( "cuphead_ex_air_diagonalup" );
	m_pExAirDownSprite = pResourcesLinker->GetSprite( "cuphead_ex_air_down" );
	m_pRunShootStraightSprite = pResourcesLinker->GetSprite( "cuphead_runshoot_straight" );
	m_pRunShootDiagonalupSprite = pResourcesLinker->GetSprite( "cuphead_runshoot_diagonalup" );
	m_pHitSprite = pResourcesLinker->GetSprite( "cuphead_hit" );
	m_pHitDustSprite = pResourcesLinker->GetSprite( "cuphead_hit_dust" );
	m_pGhostSprite = pResourcesLinker->GetSprite( "cuphead_ghost" );

	SelectIdle( );
	
	m_WeaponManager.LinkTexture( pResourcesLinker );
}

void Cuphead::UpdateMovement( float elapsedSec )
{
	m_MovementManager.SetExingState( m_WeaponManager.GetIsExMoveOngoing( ) );
	if ( !m_LockControls )
	{
		m_MovementManager.Update( elapsedSec );
		m_MovementManager.UpdateVelocity( m_Velocity, elapsedSec );
		SelectTexture( );
	}
	UpdateLocation( elapsedSec );
}

void Cuphead::UpdateWeapons( float elapsedSec )
{
	m_WeaponManager.Update( elapsedSec );
	TryShoot( );

	if ( m_MovementManager.GetSwapWeapons( ) )
	{
		m_WeaponManager.SwapWeapons( );
		m_pHUDManager->SwapWeapon( m_WeaponManager.GetEquippedWeaponType( ) );
	}
}

void Cuphead::UpdateIFrames( float elapsedSec )
{
	if ( m_IsInvincible )
	{
		m_IFramesElapsedTime += elapsedSec;
		if ( m_IFramesElapsedTime >= Constants::sk_CupheadIFramesDuration )
		{
			m_IsInvincible = false;
			m_TextureFlashing = false;
		}
	}
}

void Cuphead::UpdateHUDManager( ) const
{
	m_pHUDManager->SetHP( GetHP( ) );
	m_WeaponManager.UpdateHUDManager( m_pHUDManager );
}

void Cuphead::UpdateHitFlashing( float elapsedSec, float epsilonTime, bool toggle )
{
	if ( m_IsInvincible )
	{
		Entity::UpdateHitFlashing( elapsedSec, Constants::sk_CupheadFlashDuration, true );
	}
}

void Cuphead::Hit( int damage )
{
	if ( !m_IsInvincible && !m_MovementManager.GetIsIFraming() )
	{
		QueueTexture( m_pHitSprite, true );
		QueueTexture( m_pHitDustSprite, true, 1 );
		Entity::Hit( damage );

		if ( GetIsAlive( ) )
		{
			m_IsInvincible = true;
			m_IFramesElapsedTime = 0.f;

			SoundManager::Play( "cuphead_hit" );
		}
	}
}

void Cuphead::TryShoot( )
{
	const float textureWidthHalved{ GetTextureWidth( ) / 2.f };
	const float radius{ textureWidthHalved / 2.f };

	const Point2f relativeOrigin{ textureWidthHalved + GetTextureOffset( ).x, GetTextureHeight( ) / 2.f };
	Point2f origin{ relativeOrigin + m_Location };
	float rotation{ m_MovementManager.GetAimAngle( ) };

	if( m_MovementManager.GetIsFacingRight( ) )
	{
		// amount of offset to position the projectiles on the hand
		const float rightOffset{ 40.f };
		origin.x += rightOffset;
	}

	// if cuphead is ducking, lower the projectile height
	if ( m_MovementManager.GetMovementType( ) == MovementManager::MovementType::duck )
	{
		const float heightOffset{ m_MovementManager.GetIsGravityReversed( ) ? -24.f : 18.f };
		origin.y -= heightOffset;
	}

	if ( m_MovementManager.GetIsGravityReversed( ) 
		&& rotation == 0.f )
	{
		const float heightOffset{ 14.f };
		origin.y += heightOffset;
	}

	if ( m_MovementManager.GetIsExMove( ) )
	{
		m_WeaponManager.ShootEX( origin, radius, rotation );
	}
	else if ( m_MovementManager.GetIsShooting( ) )
	{
		m_WeaponManager.Shoot( origin, radius, rotation );
	}
	else
	{
		m_WeaponManager.StopAudioLoop( );
	}
}

void Cuphead::SelectTexture( )
{
	Texture2D* pSelectedTexture{};
	CollisionManager* pCollisionManager{};

	const MovementManager::AimDirection direction{ m_MovementManager.GetAimDirection() };
	const MovementManager::MovementType movement{ m_MovementManager.GetMovementType() };
	const bool flipX{ !m_MovementManager.GetIsFacingRight( ) }, flipY{};
	const bool isShooting{ m_MovementManager.GetIsShooting( ) };
	const bool isExing{ m_WeaponManager.RequireExMoveQueue( ) };
	const bool isTransitioning{ m_MovementManager.GetIsTransitioning( ) };
	const bool isReversed{ m_MovementManager.GetIsGravityReversed( ) };

	if ( isExing )
	{
		SelectExMove( direction );
	}
	else
	{
		pCollisionManager = isReversed ? &m_ReversedStandingCollisionManager : &m_StandingCollisionManager;

		switch ( movement )
		{
		case MovementManager::MovementType::idle:
			SelectIdle( );
			break;
		case MovementManager::MovementType::duck:
			SelectDuck( isShooting, isTransitioning );
			pCollisionManager = isReversed ? &m_ReversedDuckingCollisionManager : &m_DuckingCollisionManager;
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

		SetCollisionManager( pCollisionManager );
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
		//m_pDuckBeginSprite->Reset( );
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

void Cuphead::SelectExMove( MovementManager::AimDirection direction )
{
	Texture2D* pTexture{};
	switch ( direction )
	{
	case MovementManager::AimDirection::up:
		pTexture = m_pExAirUpSprite;
		break;
	case MovementManager::AimDirection::down:
		pTexture = m_pExAirDownSprite;
		break;
	case MovementManager::AimDirection::straight:
		pTexture = m_pExAirStraightSprite;
		break;
	case MovementManager::AimDirection::diagonalup:
		pTexture = m_pExAirDiagonalupSprite;
		break;
	case MovementManager::AimDirection::diagonaldown:
		pTexture = m_pExAirDiagonaldownSprite;
		break;
	default:
		return;
	}
	//pTexture->Reset( );
	QueueTexture( pTexture, true );
}

void Cuphead::QueueTexture( Texture2D* pTexture, bool priority, int index )
{
	const bool flipX{ !m_MovementManager.GetIsFacingRight( ) }, flipY{ m_MovementManager.GetIsGravityReversed() };
	Entity::QueueTexture( index, pTexture, flipX, flipY, priority );
}

void Cuphead::Kill( )
{
	Entity::Kill( );

	m_TextureFlashing = false;
	m_Velocity.Set( 0.f, Constants::sk_CupheadGhostSpeed );

	m_MovementManager.Reset( );
	m_LockControls = true;
	QueueTexture( m_pGhostSprite );

	SoundManager::Play( "cuphead_death" );
}
