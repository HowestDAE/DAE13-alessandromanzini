#include "pch.h"
#include "PatternSettings.h"

PatternSettings::PatternSettings( )
	: PatternSettings( Vector2f{}, 0 )
{
}

PatternSettings::PatternSettings( const Vector2f& offset, int repetition )
	: m_Offset{ offset }
	, m_Repetition{ repetition }
{
}

PatternSettings::PatternSettings( int repetition )
	: PatternSettings( Vector2f{}, repetition )
{
}

Vector2f PatternSettings::GetOffset( ) const
{
	return m_Offset;
}

int PatternSettings::GetRepetition( ) const
{
	return m_Repetition;
}
