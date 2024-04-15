#include "pch.h"
#include "Toyduck.h"
#include "SpriteManager.h"
#include "Constants.h"

Toyduck::Toyduck( const Point2f& position )
	: Entity( position )
	, m_pIdleSprite{}
	, m_pBacktireSprite{}
{
	m_Velocity.Set( -Constants::sk_ToyduckSpeed, 0.f );
}

void Toyduck::Draw( ) const
{
	m_pBacktireSprite->Draw( m_Location.ToPoint2f( ) );
	m_pIdleSprite->Draw( m_Location.ToPoint2f( ) );
}

void Toyduck::Update( float elapsedSec )
{
	m_pIdleSprite->Update( elapsedSec );
	m_pBacktireSprite->Update( elapsedSec );

	m_Location += m_Velocity * elapsedSec;
}
