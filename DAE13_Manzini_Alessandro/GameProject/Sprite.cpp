#include "pch.h"
#include "Sprite.h"
#include "Texture.h"
#include <iostream>

Sprite::Sprite( Texture const* pTexture, Texture const* pFlashTexture, const SpriteSettings& spriteSettings )
	: Sprite( pTexture, 
		pFlashTexture,
		spriteSettings.GetRows(), 
		spriteSettings.GetCols( ), 
		spriteSettings.GetFrameDelay( ), 
		spriteSettings.GetBoomerang( ), 
		spriteSettings.GetOffset( ),
		spriteSettings.GetMustComplete( ) )
{
}

Sprite::Sprite( Texture const* pTexture, Texture const* pFlashTexture, int rows, int cols, float frameDelay, bool boomerang, const Vector2f& offset, bool mustComplete )
	: Texture2D( pTexture, offset )
	, mk_pFlashTexture{ pFlashTexture }
	, mk_Rows{ rows }
	, mk_Cols{ cols }
	, mk_FrameDelay{ frameDelay }
	, mk_Boomerang{ boomerang }
	, mk_TotalAnimationTime{ rows * cols * frameDelay }
	, mk_MustComplete{ mustComplete }
	, m_NoRepeat{}
	, m_CanDraw{ true }
{
	Reset( );
	m_SourceRect = Rectf{ 0.f, 0.f,
		pTexture->GetWidth( ) / mk_Cols,
		pTexture->GetHeight( ) / mk_Rows
	};
}

void Sprite::Draw( const Point2f& pos, bool flipX, bool flipY, bool flash ) const
{
	if ( m_CanDraw )
	{
		Texture2D::Draw( pos, m_SourceRect, flipX, flipY );

		if ( flash && mk_pFlashTexture )
		{
			Texture2D::Draw( mk_pFlashTexture, pos, m_SourceRect, flipX, flipY );
		}
	}
}

void Sprite::Update( float elapsedSec )
{
	m_AccumulatedTime += elapsedSec;

	if ( m_AccumulatedTime >= mk_FrameDelay )
	{
		m_CurrentFrame += m_Increment;
		m_AccumulatedTime -= mk_FrameDelay;

		if ( m_CurrentFrame >= (mk_Rows * mk_Cols) || m_CurrentFrame < 0 )
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

			m_LastFrameReached = true;
			m_CanDraw = !m_NoRepeat;
		}

		m_SourceRect.left = float( m_CurrentFrame % mk_Cols ) * m_SourceRect.width;
		m_SourceRect.bottom = float( m_CurrentFrame / mk_Cols ) * m_SourceRect.height;
	}
}

void Sprite::Reset( )
{
	m_CurrentFrame = 0;
	m_Increment = 1;

	m_AccumulatedTime = 0.f;
	m_LastFrameReached = false;
	m_CanDraw = true;
}

float Sprite::GetWidth( ) const
{
	return m_SourceRect.width;
}

float Sprite::GetHeight( ) const
{
	return m_SourceRect.height;
}

bool Sprite::GetIsLastFrameReached( ) const
{
	return m_LastFrameReached;
}

void Sprite::ForceReady( )
{
	m_LastFrameReached = true;
}

bool Sprite::GetIsReady( ) const
{
	return !mk_MustComplete || GetIsLastFrameReached();
}

float Sprite::GetAnimationTimer( ) const
{
	return mk_TotalAnimationTime - (m_CurrentFrame * mk_FrameDelay) - m_AccumulatedTime;
}

int Sprite::GetCurrentFrame( ) const
{
	return m_CurrentFrame;
}

void Sprite::SetCurrentFrame( int currentFrame )
{
	m_CurrentFrame = currentFrame;
}

void Sprite::SetNoRepeat( bool noRepeat )
{
	m_NoRepeat = noRepeat;
}

bool Sprite::GetMustComplete( ) const
{
	return mk_MustComplete;
}
