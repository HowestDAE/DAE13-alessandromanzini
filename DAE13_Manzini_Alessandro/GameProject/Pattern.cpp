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
	// giving a height of 0.f draws the entire image, therefore we must return
	const float epsilon{ .0001f };
	if ( percentage <= epsilon )
	{
		return;
	}
	Texture2D::Draw( pos, Rectf{ 0.f, 0.f, GetWidth(), GetHeight() * percentage } );
}

void Pattern::Draw( const Point2f& pos, float rotation, bool pointToCenter ) const
{
	glPushMatrix( );
	{
		glTranslatef( pos.x, pos.y, 0.f );
		glRotatef( rotation, 0.f, 0.f, 1.f );
		Draw( Point2f{ -GetWidth( ) / 2.f, -GetHeight( )/2.f } );
	}
	glPopMatrix( );
}

void Pattern::Update( float elapsedSec )
{
	// No behaviour
}

void Pattern::ForceReady( )
{
	// No behaviour
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
}
