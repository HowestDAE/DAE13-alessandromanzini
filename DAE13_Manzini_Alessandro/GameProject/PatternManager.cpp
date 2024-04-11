#include "pch.h"
#include "PatternManager.h"
#include "Texture.h"

PatternManager::PatternManager( const std::string& patternPath, int repetition )
	: PatternManager(patternPath, Vector2f{}, repetition )
{
}

PatternManager::PatternManager( const std::string& patternPath, Vector2f offset, int repetition )
	: TextureManager( offset )
	, mk_Repetition{ repetition }
{
	m_pTexture = new Texture( patternPath );
}

PatternManager::~PatternManager( )
{
	delete m_pTexture;
}

void PatternManager::Draw( const Point2f& pos, bool flipX, bool flipY ) const
{
	for ( int i{}; i < mk_Repetition + 1; ++i ) // Draw at least once (if repetition = 0, i < 1)
	{
		const Vector2f adjustesLocationVector{ GetWidth( ) * i, 0.f };
		TextureManager::Draw( m_pTexture, pos + adjustesLocationVector, Rectf{}, flipX, flipY );
	}
}

void PatternManager::Update( float elapsedSec )
{
	// No behaviour
	return;
}

float PatternManager::GetWidth( ) const
{
	return m_pTexture->GetWidth();
}

float PatternManager::GetHeight( ) const
{
	return m_pTexture->GetHeight( );
}

void PatternManager::ForceReady( )
{
	// No behaviour
	return;
}

bool PatternManager::GetIsReady( ) const
{
	return true;
}

float PatternManager::GetAnimationTimer( ) const
{
	return 0.0f;
}

void PatternManager::Reset( )
{
	// No behaviour
	return;
}
