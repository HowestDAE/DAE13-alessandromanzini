#include "pch.h"
#include "Pattern.h"
#include "Texture.h"

Pattern::Pattern( Texture const* pTexture, const PatternSettings& patternSettings )
	: Pattern( pTexture, patternSettings.GetOffset(), patternSettings.GetRepetition() )
{
}

Pattern::Pattern( Texture const* pTexture, int repetition )
	: Pattern( pTexture, Vector2f{}, repetition )
{
}

Pattern::Pattern( Texture const* pTexture, Vector2f offset, int repetition )
	: Texture2D( pTexture, offset )
	, mk_Repetition{ repetition }
{
}

void Pattern::Draw( const Point2f& pos, bool flipX, bool flipY, bool flash ) const
{
	for ( int i{}; i < mk_Repetition + 1; ++i ) // Draw at least once (if repetition = 0, i < 1)
	{
		const Vector2f adjustesLocationVector{ GetWidth( ) * i, 0.f };
		Texture2D::Draw( pos + adjustesLocationVector, Rectf{}, flipX, flipY );
	}
}

void Pattern::Draw( const Point2f& pos, float percentage ) const
{
	const float epsilon{ .0001f };
	if ( percentage <= epsilon )
	{
		return;
	}
	Texture2D::Draw( pos, Rectf{ 0.f, 0.f, GetWidth(), GetHeight() * percentage } );
}

void Pattern::Update( float elapsedSec )
{
	// No behaviour
	return;
}

void Pattern::ForceReady( )
{
	// No behaviour
	return;
}

bool Pattern::GetIsReady( ) const
{
	return true;
}

float Pattern::GetAnimationTimer( ) const
{
	return 0.0f;
}

void Pattern::Reset( )
{
	// No behaviour
	return;
}
