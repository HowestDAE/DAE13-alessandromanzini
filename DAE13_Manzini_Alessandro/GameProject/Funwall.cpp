#include "pch.h"
#include "Funwall.h"
#include "Constants.h"
#include "StageManager.h"
#include "Sprite.h"
#include "SoundManager.h"
#include "Toycar.h"
#include "Tongue.h"

const float Funwall::smk_LipsSpawnDelay{ 0.675f };
const float Funwall::smk_HitSFXDelay{ 1.3f };
const float Funwall::smk_UhohAttackDelay{ 4.5f };
const float Funwall::smk_UhohCastDelay{ smk_UhohAttackDelay - .65f };
const float Funwall::smk_UhohRecoverDelay{ smk_UhohAttackDelay + 4.f };

const Vector2f Funwall::smk_ToycarBottomSpawnOffset{ 190.f, 140.f };
const Vector2f Funwall::smk_ToycarTopSpawnOffset{ 190.f, 560.f };
const Vector2f Funwall::smk_TongueBottomSpawnOffset{ -850.f, 140.f };
const Vector2f Funwall::smk_TongueTopSpawnOffset{ -850.f, 570.f };

Funwall::Funwall( const Point2f& position, float aggroRadius, float dropRadius, bool tongueVariation )
	: Enemy( position, Constants::sk_FunwallHP, aggroRadius, dropRadius, 1, false, true )
	, m_CollisionManager{ std::vector<CollisionCircle>{ CollisionCircle{ 180.f, 280.f, 150.f }, CollisionCircle{ 180.f, 580.f, 150.f } }, &m_Location }
	, mk_TongueVariation{ tongueVariation }
	, m_Lips{}
	, m_pHonkSprites{}
	, m_pHonkVFXSprites{}
	, m_DeathVFXPosition{}
	, m_HonkCooldownTimes{}
	, m_HasHonked{}
	, m_HitSFXTimer{ smk_HitSFXDelay }
	, m_pUhohSprite{}
	, m_HasCastedUhoh{}
	, m_HasAttackedUhoh{}
	, m_UhohIndex{}
	, m_UhohCooldownTime{ smk_UhohAttackDelay/2.f }
	, m_pUhohEnemies{}
{
	InitializeQueues( 8, 2 );
	SetCollisionManager( &m_CollisionManager );

	StageManager::PushCompositionEntity( &m_Lips[0] );
	StageManager::PushCompositionEntity( &m_Lips[1] );

	InitializeUhOhEntities( aggroRadius, dropRadius );
}

Funwall::~Funwall( ) noexcept
{
	StageManager::PopCompositionEntity( &m_Lips[0] );
	StageManager::PopCompositionEntity( &m_Lips[1] );
	StageManager::PopCompositionEntity( m_pUhohEnemies[0] );
	StageManager::PopCompositionEntity( m_pUhohEnemies[1] );

	for ( int i{}; i < smk_SidesCount; ++i )
	{
		delete m_pUhohEnemies[i];
	}
}

void Funwall::Draw( ) const
{
	m_pUhohEnemies[m_UhohIndex]->Draw( );

	for ( int i{}; i < smk_SidesCount; ++i )
	{
		m_Lips[i].Draw( );
	}

	Enemy::Draw( );

	if( !GetIsAlive( ) )
	{
		m_pDeathVFXSprite->Draw( m_DeathVFXPosition );
	}
}

void Funwall::DrawBackside( ) const
{
	Enemy::DrawBackside( );
	m_pUhohEnemies[m_UhohIndex]->DrawBackside( );
}

void Funwall::Update( float elapsedSec )
{
	for ( int i{}; i < smk_SidesCount; ++i )
	{
		m_Lips[i].Update( elapsedSec );
	}

	m_pUhohEnemies[m_UhohIndex]->Update( elapsedSec );

	m_HitSFXTimer += elapsedSec;
}

void Funwall::Update( float elapsedSec, const Vector2f& targetLocation )
{
	if ( !GetIsAggro( ) ) return;

	Enemy::Update( elapsedSec );
	Update( elapsedSec );

	if ( GetIsAlive( ) )
	{
		UpdateHonkAttack( elapsedSec, targetLocation );
		UpdateUhohAttack( elapsedSec );
	}
	else
	{
		m_pDeathVFXSprite->Update( elapsedSec );

		if ( m_pDeathVFXSprite->GetIsReady( ) )
		{
			RandomizeDeathVFX( );
		}
	}
}

bool Funwall::CompareAggroDistance( const Vector2f& targetLocation )
{
	for ( int i{}; i < smk_SidesCount; ++i )
	{
		m_pUhohEnemies[i]->CompareAggroDistance( targetLocation );
	}
	return Enemy::CompareAggroDistance( targetLocation );
}

void Funwall::AggroEvent( )
{
	for ( int i{}; i < smk_SidesCount; ++i )
	{
		RandomizeHonk( i );
	}
}

void Funwall::LinkTexture( ResourcesLinker* pResourcesLinker )
{
	m_pBoilSprite = pResourcesLinker->GetSprite( "funwall_boil" );
	m_pEyeIdleSprite = pResourcesLinker->GetSprite( "funwall_eye_idle" );
	m_pEyeHitSprite = pResourcesLinker->GetSprite( "funwall_eye_hit" );

	m_pHonkSprites[0] = pResourcesLinker->GetSprite( "funwall_honk_bottom" );
	m_pHonkSprites[1] = pResourcesLinker->GetSprite( "funwall_honk_top" );
	m_pHonkVFXSprites[0] = pResourcesLinker->GetSprite( "funwall_honk_bottom_vfx" );
	m_pHonkVFXSprites[1] = pResourcesLinker->GetSprite( "funwall_honk_top_vfx" );

	m_pOpeningSprite[0] = pResourcesLinker->GetSprite( "funwall_mouth_opening_bottom" );
	m_pOpenSprite[0] = pResourcesLinker->GetSprite( "funwall_mouth_open_bottom" );
	m_pClosingSprite[0] = pResourcesLinker->GetSprite( "funwall_mouth_closing_bottom" );
	m_pOpeningSprite[1] = pResourcesLinker->GetSprite( "funwall_mouth_opening_top" );
	m_pOpenSprite[1] = pResourcesLinker->GetSprite( "funwall_mouth_open_top" );
	m_pClosingSprite[1] = pResourcesLinker->GetSprite( "funwall_mouth_closing_top" );

	m_pMouthCoverSprite[0] = pResourcesLinker->GetSprite( "funwall_mouth_cover_bottom" );
	m_pMouthCoverSprite[1] = pResourcesLinker->GetSprite( "funwall_mouth_cover_top" );

	m_pDeathSprite = pResourcesLinker->GetSprite( "funwall_death" );
	m_pDeathCoverSprite = pResourcesLinker->GetSprite( "funwall_death_cover" );
	m_pDeathVFXSprite = pResourcesLinker->GetSprite( "funwall_death_vfx" );

	QueueTexture( 0, m_pBoilSprite );
	QueueTexture( 1, m_pEyeIdleSprite );

	for ( int i{}; i < smk_SidesCount; ++i )
	{
		m_Lips[i].LinkTexture( pResourcesLinker );
		m_pUhohEnemies[i]->LinkTexture( pResourcesLinker );
	}
}

void Funwall::InitializeUhOhEntities( float aggroRadius, float dropRadius )
{
	if ( mk_TongueVariation )
	{
		m_pUhohEnemies[0] = new Tongue( (m_Location + smk_TongueBottomSpawnOffset).ToPoint2f(), dropRadius, dropRadius );
		m_pUhohEnemies[1] = new Tongue( (m_Location + smk_TongueTopSpawnOffset).ToPoint2f( ), dropRadius, dropRadius, true );
	}
	else
	{
		const Point2f outOfBounds{ -10000.f, -10000.f };
		m_pUhohEnemies[0] = new Toycar( (m_Location + smk_ToycarBottomSpawnOffset).ToPoint2f( ), dropRadius, dropRadius, 2 );
		m_pUhohEnemies[1] = new Toycar( (m_Location + smk_ToycarTopSpawnOffset).ToPoint2f( ), dropRadius, dropRadius, 2, true );
		m_pUhohEnemies[0]->Reset( outOfBounds );
		m_pUhohEnemies[1]->Reset( outOfBounds );
	}

	StageManager::PushCompositionEntity( m_pUhohEnemies[0] );
	StageManager::PushCompositionEntity( m_pUhohEnemies[1] );
}

void Funwall::UpdateHonkAttack( float elapsedSec, const Vector2f& targetLocation )
{
	const int reservedHonkIndex{ 4 };
	for ( int i{}; i < smk_SidesCount; ++i )
	{
		m_HonkCooldownTimes[i] -= elapsedSec;

		// if time gets to 0, shoot
		if ( m_HonkCooldownTimes[i] <= 0.f )
		{
			QueueTexture( reservedHonkIndex + i * 2 + 1, TextureInfo{ m_pHonkVFXSprites[i] }, true );

			SoundManager::Play( "funwall_kiss" );

			const Vector2f spawnLocation{ m_pHonkSprites[i]->GetOffset( ) + m_Location };
			m_Lips[i].Reset( spawnLocation, targetLocation - spawnLocation );

			RandomizeHonk( i );
			m_HasHonked = false;
		}
		else if ( m_HonkCooldownTimes[i] <= smk_LipsSpawnDelay && !m_HasHonked )
		{
			// if time is about to get to 0, start shoot animation
			QueueTexture( reservedHonkIndex + i * 2, TextureInfo{ m_pHonkSprites[i] }, true );
			m_HasHonked = true;
		}
	}
}

void Funwall::UpdateUhohAttack( float elapsedSec )
{
	m_UhohCooldownTime += elapsedSec;

	if ( m_UhohCooldownTime >= smk_UhohRecoverDelay )
	{
		SoundManager::Play( "funwall_mouth_close" );

		QueueTexture( 0, TextureInfo{ m_pClosingSprite[m_UhohIndex] }, true );
		QueueTexture( 0, m_pBoilSprite );
		ClearQueue( 3 );

		m_UhohCooldownTime = 0.f;
		m_HasCastedUhoh = false;
		m_HasAttackedUhoh = false;
	}
	// if time gets to 0, release enemies
	else if ( !m_HasAttackedUhoh && m_UhohCooldownTime >= smk_UhohAttackDelay )
	{
		// 3 is a dedicated channel for the uhoh attack
		QueueTexture( 3, TextureInfo{ m_pMouthCoverSprite[m_UhohIndex] }, true );

		m_pUhohEnemies[m_UhohIndex]->Reset( );

		m_HasAttackedUhoh = true;
	}
	// if time is before cast delay, open mouth
	else if ( !m_HasCastedUhoh && m_UhohCooldownTime >= smk_UhohCastDelay )
	{		
		m_UhohIndex = (m_UhohIndex + 1) % smk_SidesCount;

		SoundManager::Play( "funwall_mouth_open" );

		QueueTexture( 0, TextureInfo{ m_pOpeningSprite[m_UhohIndex] }, true );
		QueueTexture( 0, m_pOpenSprite[m_UhohIndex] );

		m_HasCastedUhoh = true;
	}
}

void Funwall::Hit( int damage )
{
	Enemy::Hit( damage );
	
	if ( GetIsAlive( ) )
	{
		QueueTexture( 1, TextureInfo{ m_pEyeHitSprite }, true );
		QueueTexture( 1, TextureInfo{ m_pEyeIdleSprite } );

		if( m_HitSFXTimer >= smk_HitSFXDelay )
		{
			SoundManager::Play( "funwall_hit" );
			m_HitSFXTimer = 0.f;
		}
	}
}

void Funwall::RandomizeHonk( int honkIndex )
{
	const float minTime{ 3.f };
	const int variableTime{ 3 };
	m_HonkCooldownTimes[honkIndex] = minTime + float( rand( ) % variableTime );
}

void Funwall::RandomizeDeathVFX( )
{
	const int maxX{ int( GetTextureWidth( ) ) };
	const int maxY{ int( GetTextureHeight( ) ) };

	m_DeathVFXPosition = Point2f{ m_Location.x + float( rand( ) % maxX ), m_Location.y + float( rand( ) % maxY ) };
	m_pDeathVFXSprite->Reset( );
}

void Funwall::Kill( )
{
	Enemy::Kill( );

	QueueTexture( 0, m_pDeathSprite );
	QueueTexture( 2, TextureInfo{ m_pDeathCoverSprite }, true );
	ClearQueue( 1 );
	ClearQueue( 3 );

	SoundManager::Play( "funwall_death" );
	SoundManager::Play( "funwall_explosion" );
	RandomizeDeathVFX( );
}
