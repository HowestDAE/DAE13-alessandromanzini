#include "pch.h"
#include "Toyduck.h"
#include "Constants.h"
#include "Sprite.h"
#include "utils.h"

Toyduck::Toyduck( const Point2f& position )
	: Entity( position, Constants::sk_ToyduckStartingHP )
	, m_pIdleSprite{}
	, m_pBacktireSprite{}
	, m_CollisionManager{ std::vector<CollisionCircle>{ CollisionCircle{ 180.f, 130.f, 70.f, false }, CollisionCircle{ 130.f, 250.f, 60.f } }, &m_Location}
{
	m_Velocity.Set( -Constants::sk_ToyduckSpeed, 0.f );
	SetCollisionManager( &m_CollisionManager );
}

void Toyduck::Draw( ) const
{
	m_pBacktireSprite->Draw( m_Location.ToPoint2f( ) );
	Entity::Draw( );

	//DrawTextureOutline( );
	DrawCollision( );
}

void Toyduck::Update( float elapsedSec )
{
	m_pIdleSprite->Update( elapsedSec );
	m_pBacktireSprite->Update( elapsedSec );

	m_Location += m_Velocity * elapsedSec;

	Entity::UpdateHitFlashing( elapsedSec, Constants::sk_DefaultFlashDuration );
}

void Toyduck::LinkTexture( ResourcesLinker* pResourcesLinker )
{
	m_pIdleSprite = pResourcesLinker->GetSprite( "toyduck_idle" );
	m_pBacktireSprite = pResourcesLinker->GetSprite( "toyduck_backtire" );

	m_TextureInfo.pTexture = m_pIdleSprite;
}
