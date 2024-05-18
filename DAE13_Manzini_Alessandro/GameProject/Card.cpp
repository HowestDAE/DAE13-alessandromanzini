#include "pch.h"
#include "Card.h"
#include "Texture2D.h"
#include "Sprite.h"

Card::Card( const Point2f& position )
	: Entity( position, 1, 0 )
	, m_pIdleSprite{}
	, m_pSpinSprite{}
	, m_pStarsSprite{}
	, m_CollisionManager{ CollisionCircle{ 55.f, 60.f, 35.f, CollisionType::noHit }, &m_Location }
{
	SetCollisionManager( &m_CollisionManager );
	InitializeQueues( 2 );
}

void Card::Draw( ) const
{
	Entity::Draw( );
}

void Card::Update( float elapsedSec )
{
	Entity::Update( elapsedSec );
}

void Card::LinkTexture( ResourcesLinker* pResourcesLinker )
{
	m_pIdleSprite = pResourcesLinker->GetSprite( "card_idle" );
	m_pSpinSprite = pResourcesLinker->GetSprite( "card_spin" );
	m_pStarsSprite = pResourcesLinker->GetSprite( "card_stars" );
	
	QueueTexture( 0, m_pIdleSprite );
	QueueTexture( 1, m_pStarsSprite );
}
