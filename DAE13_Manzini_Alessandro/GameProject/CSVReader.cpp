#include "pch.h"
#include "CSVReader.h"
#include "string_manip.cpp"
#include <fstream>
#include <iostream>
#include <cassert>

CSVReader::CSVReader( const std::string& csvPath )
	: m_LabelIndexMap{}
	, m_DataLines{}
	, m_DataIterator{}
{
	LoadDataFromFile( csvPath );
	ExtractHeaders( );

	m_DataIterator = m_DataLines.begin( );
}

const std::string& CSVReader::Get( const std::string& label ) const
{
	return Get( MapLabelToIndex( label ) );
}

const std::string& CSVReader::Get( int index ) const
{
	return m_DataIterator->at( index );
}

int CSVReader::GetInt( const std::string& label ) const
{
	return std::stoi( Get( label ) );
}

int CSVReader::GetInt( int index ) const
{
	return std::stoi( Get( index ) );
}

float CSVReader::GetFloat( const std::string& label ) const
{
	return std::stof( Get( label ) );
}

float CSVReader::GetFloat( int index ) const
{
	return std::stof( Get( index ) );
}

bool CSVReader::GetBoolean( const std::string& label ) const
{
	return GetInt( label );
}

bool CSVReader::GetBoolean( int index ) const
{
	return GetInt( index );
}

int CSVReader::size( ) const
{
	return static_cast<int>( m_DataLines.size( ) );
}

bool CSVReader::next( )
{
	++m_DataIterator;
	return eof( );
}

bool CSVReader::eof( ) const
{
	return m_DataIterator == m_DataLines.end( );
}

void CSVReader::LoadDataFromFile( const std::string& csvPath )
{
	const char csvSeparator{ ';' };
	std::ifstream csv{};
	std::string line;

	int separatorCount{};

	csv.open( csvPath );
	if ( !csv )
	{
		throw std::runtime_error( "Couldn't open file at '" + csvPath + "'." );
	}

	while ( std::getline( csv, line ) ) // while there are lines, keep reading
	{
		if ( !csv.good( ) && !csv.eof( ) )
		{
			throw std::runtime_error( "Error while reading csv file at '" + csvPath + "'.\nrdstate: " + std::to_string(csv.rdstate()) );
		}

		trim( line );
		if ( line.empty( ) ) continue; // avoid blank lines

		int readerPos{};
		int separatorPos;

		std::vector<std::string> dataLine{ size_t( separatorCount ) };
		dataLine.clear( );
		m_DataLines.push_back( std::move( dataLine ) );

		// if separator exists, put its position in separatorPos and do while's body
		while ( (separatorPos = int( line.find( csvSeparator, readerPos ) )) != std::string::npos )
		{
			std::string field{ line.substr( readerPos, separatorPos - readerPos ) };
			trim( field );

			m_DataLines.back( ).push_back( std::move( field ) );

			separatorCount = static_cast<int>( m_DataLines.size( ) );
			readerPos = separatorPos + 1;
		}
	}
}

void CSVReader::ExtractHeaders( )
{
	if ( m_DataLines.size( ) > 0 )
	{
		// First line becomes the "legenda"
		for ( int idx{}; idx < m_DataLines.front( ).size( ); ++idx )
		{
			m_LabelIndexMap.insert( std::pair<std::string, int>( m_DataLines.front( )[idx], idx ) );
		}
		// pop first line from data
		m_DataLines.pop_front( );
	}
}

int CSVReader::MapLabelToIndex( const std::string& label ) const
{
	if ( m_LabelIndexMap.find( label ) == m_LabelIndexMap.end( ) )
	{
		throw std::invalid_argument( "Label '" + label + "' not found. " );
	}
	return m_LabelIndexMap.at( label );
}
