#include "pch.h"
#include "VectorSprite.h"
#include "Texture.h"

VectorSprite::VectorSprite( const std::vector<Texture*>& pTextures, float frameDelay )
	: Texture2D( )
	, mk_pTextures{ pTextures }
	, mk_FrameDelay{ frameDelay }
	, m_CurrentTexture{}
	, m_AccumulatedTime{}
{
}

void VectorSprite::Draw( const Rectf& bounds ) const
{
	mk_pTextures[m_CurrentTexture]->Draw( bounds );
}

void VectorSprite::Draw( const Point2f& pos, bool flipX, bool flipY, bool flash ) const
{
	mk_pTextures[m_CurrentTexture]->Draw( pos );
}

void VectorSprite::Update( float elapsedSec )
{
	m_AccumulatedTime += elapsedSec;

	if ( m_AccumulatedTime >= mk_FrameDelay )
	{
		m_AccumulatedTime -= mk_FrameDelay;
		m_CurrentTexture = ( m_CurrentTexture + 1 ) % mk_pTextures.size( );
	}
}

float VectorSprite::GetWidth( ) const
{
	if ( mk_pTextures.size( ) > 0 )
	{
		return mk_pTextures[0]->GetWidth( );
	}
	return 0.0f;
}

float VectorSprite::GetHeight( ) const
{
	if ( mk_pTextures.size( ) > 0 )
	{
		return mk_pTextures[0]->GetHeight( );
	}
	return 0.0f;
}

void VectorSprite::ForceReady( )
{
}

bool VectorSprite::GetIsReady( ) const
{
	return false;
}

float VectorSprite::GetAnimationTimer( ) const
{
	return m_AccumulatedTime - mk_FrameDelay;
}

void VectorSprite::Reset( )
{
	m_CurrentTexture = 0;
	m_AccumulatedTime = 0.f;
}
