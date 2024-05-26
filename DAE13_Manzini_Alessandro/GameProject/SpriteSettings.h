#pragma once
#include <Vector2f.h>
class SpriteSettings final
{
public:
	SpriteSettings( );
	explicit SpriteSettings( int rows, int cols, float frameDelay, bool boomerang = false, const Vector2f& offset = {}, bool mustComplete = false );

	int GetRows( ) const;
	int GetCols( ) const;
	float GetFrameDelay( ) const;
	bool GetBoomerang( ) const;
	Vector2f GetOffset( ) const;
	bool GetMustComplete( ) const;

private:
	int m_Rows;
	int m_Cols;
	float m_FrameDelay;
	bool m_Boomerang;
	Vector2f m_Offset;
	bool m_MustComplete;
};

