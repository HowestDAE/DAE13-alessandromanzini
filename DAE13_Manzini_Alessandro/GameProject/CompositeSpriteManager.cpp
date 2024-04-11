#include "pch.h"
#include "CompositeSpriteManager.h"

CompositeSpriteManager::CompositeSpriteManager( SpriteManager* pBegin, SpriteManager* pLoop, SpriteManager* pEnd )
	: m_pBeginSprite{ pBegin }
	, m_pLoopSprite{ pLoop }
	, m_pEndSprite{ pEnd }
	, m_pCurrentSprite{}
{
	Reset( );
}

void CompositeSpriteManager::Draw( const Point2f& pos, bool flipX, bool flipY ) const
{
	m_pCurrentSprite->Draw( pos, flipX, flipY );
}

void CompositeSpriteManager::Update( float elapsedSec )
{
	m_pCurrentSprite->Update( elapsedSec );

	if ( m_Phase != AnimationPhase::loop && m_pCurrentSprite->GetIsReady( ) )
	{
		SetPhase( AnimationPhase( int( m_Phase ) + 1 ) ); // next phase
	}
}

float CompositeSpriteManager::GetWidth( ) const
{
	return m_pCurrentSprite->GetWidth( );
}

float CompositeSpriteManager::GetHeight( ) const
{
	return m_pCurrentSprite->GetHeight( );
}

TextureManager* CompositeSpriteManager::GetLoopSprite( ) const
{
	return m_pLoopSprite;
}

void CompositeSpriteManager::ForceReady( )
{
	if ( m_Phase == AnimationPhase::begin )
	{
		SetPhase( AnimationPhase::over );
	}
	else
	{
		RequestEnd( );
	}
}

bool CompositeSpriteManager::GetIsReady( ) const
{
	return (m_Phase == AnimationPhase::over);
}

float CompositeSpriteManager::GetAnimationTimer( ) const
{
	float timer{};

	switch ( m_Phase )
	{
	case AnimationPhase::begin:
		timer += m_pBeginSprite->GetAnimationTimer( );
	case AnimationPhase::end:
		timer += m_pEndSprite->GetAnimationTimer( );
		break;
	}

	return timer;
}

void CompositeSpriteManager::Reset( )
{
	SetPhase( AnimationPhase::begin );
	
	m_pBeginSprite->Reset( );
	m_pLoopSprite->Reset( );
	m_pEndSprite->Reset( );
}

void CompositeSpriteManager::SetPhase( AnimationPhase phase )
{
	m_Phase = phase;
	switch ( phase )
	{
	case CompositeSpriteManager::AnimationPhase::begin:
		m_pCurrentSprite = m_pBeginSprite;
		break;
	case CompositeSpriteManager::AnimationPhase::loop:
		m_pCurrentSprite = m_pLoopSprite;
		break;
	case CompositeSpriteManager::AnimationPhase::end:
	case CompositeSpriteManager::AnimationPhase::over:
		m_pCurrentSprite = m_pEndSprite;
		break;
	}
}

void CompositeSpriteManager::RequestEnd( )
{
	SetPhase( AnimationPhase::end );
}
