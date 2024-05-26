#pragma once
#include <Vector2f.h>

class PatternSettings final
{
public:
	PatternSettings( );
	explicit PatternSettings( const Vector2f& offset, int repetition = 0 );
	explicit PatternSettings( int repetition );

	Vector2f GetOffset( ) const;
	int GetRepetition( ) const;

private:
	Vector2f m_Offset;
	int m_Repetition;
};

