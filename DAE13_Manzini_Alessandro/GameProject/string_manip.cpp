// https://stackoverflow.com/questions/216823/how-to-trim-a-stdstring
#include "pch.h"
#include <algorithm> 
#include <cctype>
#include <locale>
#include <sstream>
#include <iomanip>

// trim from start (in place)
inline void ltrim( std::string& s )
{
    s.erase( s.begin( ), std::find_if( s.begin( ), s.end( ), []( unsigned char ch )
        {
            return !std::isspace( ch );
        } ) );
}

// trim from end (in place)
inline void rtrim( std::string& s )
{
    s.erase( std::find_if( s.rbegin( ), s.rend( ), []( unsigned char ch )
        {
            return !std::isspace( ch );
        } ).base( ), s.end( ) );
}

inline void trim( std::string& s )
{
    rtrim( s );
    ltrim( s );
}

inline std::string fillString( const std::string& label, const std::string& value, char fillChar = '.', int totalLength = 20 )
{
    std::ostringstream oss;
    int fillLength = totalLength - static_cast<int>( label.length( ) ) - static_cast<int>( value.length( ) );

    if ( fillLength < 0 )
    {
        fillLength = 0;
    }

    oss << label << std::setw( fillLength ) << std::setfill( fillChar ) << "" << value;
    return oss.str( );
}

inline std::string stringifyTime( float totalTime )
{
    int minutes{ int( totalTime / 60 ) };
    int seconds{ int( totalTime ) % 60 };
    std::ostringstream oss;

    oss << std::setw( 2 ) << std::setfill( '0' ) << minutes << ":" << std::setw( 2 ) << std::setfill( '0' ) << seconds;
    return oss.str( );
}