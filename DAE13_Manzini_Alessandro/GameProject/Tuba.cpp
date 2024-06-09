#include "pch.h"
#include "Tuba.h"
#include "Constants.h"
#include "ResourcesLinker.h"
#include "StageManager.h"
#include "Sprite.h"
#include "SoundManager.h"

const Vector2f Tuba::smk_BwaAttackLocation{ -85.f, 320.f };
const float Tuba::smk_TubaAttackSpeed{ 5.f };
const float Tuba::smk_TubaCastSpeed{ smk_TubaAttackSpeed - 1.3f };

Tuba::Tuba( const Point2f& position, float aggroRadius, float dropRadius )
	: Enemy{ position, Constants::sk_TubaHP, aggroRadius, dropRadius }
	, m_CollisionManager{ std::vector<CollisionCircle>{ CollisionCircle{ 120.f, 330.f, 65.f }, CollisionCircle{ 160.f, 180.f, 100.f } }, &m_Location }
	, m_BwaAttack{ ( m_Location + smk_BwaAttackLocation ).ToPoint2f( ) }
	, m_AttackTimer{}
	, m_HasCasted{}
{
	SetCollisionManager( &m_CollisionManager );
	InitializeQueues( 2, 1 );

	StageManager::PushCompositionEntity( &m_BwaAttack );
}

Tuba::~Tuba( ) noexcept
{
	StageManager::PopCompositionEntity( &m_BwaAttack );
}

void Tuba::DrawBackside( ) const
{
	Entity::DrawBackside( );

	m_BwaAttack.Draw( );
}

void Tuba::Update( float elapsedSec, const Vector2f& targetLocation )
{
	if ( !GetIsAggro( ) ) return;

	Enemy::Update( elapsedSec, targetLocation );

	if ( GetIsAlive( ) )
	{
		m_AttackTimer += elapsedSec;
		if( !m_HasCasted && m_AttackTimer >= smk_TubaCastSpeed )
		{
			QueueTexture( 0, TextureInfo{ m_pAttackSprite }, true );
			QueueTexture( 0, m_pIdleSprite );
			QueueTexture( 1, TextureInfo{ m_pAttackCoverSprite }, true );
			m_HasCasted = true;
		}
		else if( m_AttackTimer >= smk_TubaAttackSpeed )
		{
			m_AttackTimer = 0.f;
			m_HasCasted = false;
			m_BwaAttack.Reset( );
			SoundManager::Play( "tuba_attack" );
		}
	}

	m_BwaAttack.Update( elapsedSec );
}

void Tuba::Kill( )
{
	Enemy::Kill( );
	m_BwaAttack.Kill( );
	
	SoundManager::Play( "tuba_death" );

	ClearQueue( 0 );
	ClearQueue( 1 );
	QueueTexture( 0, TextureInfo{ m_pDeathSprite }, true );
	m_Velocity.Set( 0, -Constants::sk_TubaDeathSpeed );
}

void Tuba::LinkTexture( ResourcesLinker* pResourcesLinker )
{
	m_pIdleSprite = pResourcesLinker->GetSprite( "tuba_idle" );
	m_pAttackSprite = pResourcesLinker->GetSprite( "tuba_attack" );
	m_pAttackCoverSprite = pResourcesLinker->GetSprite( "tuba_attack_cover" );
	m_pDeathSprite = pResourcesLinker->GetSprite( "tuba_death" );

	QueueTexture( 0, m_pIdleSprite );

	m_BwaAttack.LinkTexture( pResourcesLinker );
}
