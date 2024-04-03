#include "pch.h"
#include "SpriteManager.h"
#include "Texture.h"

SpriteManager::SpriteManager( const std::string& spritePath, int rows, int cols, float frameDelay, bool boomerang, const Vector2f& offset )
	: TextureManager( offset )
	, mk_Rows{ rows }
	, mk_Cols{ cols }
	, mk_FrameDelay{ frameDelay }
	, mk_Boomerang{ boomerang }
{
	Reset( );

	m_pTexture = new Texture( spritePath );
	m_SourceRect = Rectf{ 0.f, 0.f,
		m_pTexture->GetWidth( ) / mk_Cols,
		m_pTexture->GetHeight( ) / mk_Rows
	};
}

SpriteManager::~SpriteManager( )
{
	delete m_pTexture;
}

void SpriteManager::Draw( const Point2f& pos, bool flipX, bool flipY ) const
{
	TextureManager::Draw( m_pTexture, pos, m_SourceRect, flipX, flipY );
}

void SpriteManager::Update( float elapsedSec )
{
	m_AccumulatedTime += elapsedSec;

	if ( m_AccumulatedTime >= mk_FrameDelay )
	{
		m_CurrentFrame += m_Increment;
		m_AccumulatedTime -= mk_FrameDelay;

		if ( m_CurrentFrame >= (mk_Rows * mk_Cols - 1) || (m_CurrentFrame < 0) )
		{
			if ( mk_Boomerang )
			{
				m_Increment *= -1;
				m_CurrentFrame += m_Increment;
			}
			else
			{
				m_CurrentFrame = 0;
			}
		}

		m_SourceRect.left = float( m_CurrentFrame % mk_Cols ) * m_SourceRect.width;
		m_SourceRect.bottom = float( m_CurrentFrame / mk_Cols ) * m_SourceRect.height;
	}
}

void SpriteManager::Reset( )
{
	m_CurrentFrame = 0;
	m_Increment = 1;
	m_AccumulatedTime = 0;
	//m_IndexOffsetReached = false;
}

float SpriteManager::GetWidth( ) const
{
	return m_SourceRect.width;
}

float SpriteManager::GetHeight( ) const
{
	return m_SourceRect.height;
}
