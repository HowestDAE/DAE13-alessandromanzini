#pragma once
#include <unordered_map>

class CSVReader final
{
public:
	explicit CSVReader( const std::string& csvPath );

	const std::string& Get( const std::string& label ) const;
	const std::string& Get( int index ) const;

	int GetInt( const std::string& label ) const;
	int GetInt( int index ) const;

	float GetFloat( const std::string& label ) const;
	float GetFloat( int index ) const;

	bool GetBoolean( const std::string& label ) const;
	bool GetBoolean( int index ) const;

	int size( ) const;

	bool next( ); 
	bool eof( ) const;

private:
	std::unordered_map<std::string, int> m_LabelIndexMap;

	std::list<std::vector<std::string>> m_DataLines;
	std::list<std::vector<std::string>>::iterator m_DataIterator;

	void LoadDataFromFile( const std::string& csvPath );
	void ExtractHeaders( );

	int MapLabelToIndex( const std::string& label ) const;

};

