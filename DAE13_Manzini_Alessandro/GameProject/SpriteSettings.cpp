#include "pch.h"
#include "SpriteSettings.h"

SpriteSettings::SpriteSettings( )
	: SpriteSettings( 0, 0, 0.f )
{
}

SpriteSettings::SpriteSettings( int rows, int cols, float frameDelay, bool boomerang, const Vector2f& offset, bool mustComplete )
	: m_Rows{ rows }
	, m_Cols{ cols }
	, m_FrameDelay{ frameDelay }
	, m_Boomerang{ boomerang }
	, m_Offset{ offset }
	, m_MustComplete{ mustComplete }
{
}

int SpriteSettings::GetRows( ) const
{
	return m_Rows;
}

int SpriteSettings::GetCols( ) const
{
	return m_Cols;
}

float SpriteSettings::GetFrameDelay( ) const
{
	return m_FrameDelay;
}

bool SpriteSettings::GetBoomerang( ) const
{
	return m_Boomerang;
}

Vector2f SpriteSettings::GetOffset( ) const
{
	return m_Offset;
}

bool SpriteSettings::GetMustComplete( ) const
{
	return m_MustComplete;
}

