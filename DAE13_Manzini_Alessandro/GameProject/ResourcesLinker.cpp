#include "pch.h"
#include "ResourcesLinker.h"
#include "Texture.h"
#include "Texture2D.h"
#include "Pattern.h"
#include "Sprite.h"
#include "VectorSprite.h"
#include "CSVReader.h"
#include "Constants.h"
#include <exception>
#include <stdexcept>

ResourcesLinker::ResourcesLinker( )
	: m_pTextures{}
	, m_pInstantiatedTextures{}
	, m_pScreenFXTextures{}
	, m_TextureTypeMap{}
	, m_SpriteSettingsMap{}
	, m_PatternSettingsMap{}
{
	InitializeTextures( );
}

ResourcesLinker::~ResourcesLinker( )
{
	ReleaseTextures( );
}

Texture2D* ResourcesLinker::GetTexture( const std::string& uid )
{
	Texture2D* pTexture{};

	switch ( m_TextureTypeMap[uid] )
	{
	case TextureType::pattern:
		pTexture = new Pattern( m_pTextures[uid], m_PatternSettingsMap[uid] );
		break;
	case TextureType::sprite:
		pTexture = new Sprite( m_pTextures[uid], m_pTextures[uid + "_flash"], m_SpriteSettingsMap[uid] );
		break;
	default:
		break;
	}
	m_pInstantiatedTextures.push_back( pTexture );
	return pTexture;
}

Sprite* ResourcesLinker::GetSprite( const std::string& uid )
{
	return static_cast<Sprite*>( GetTexture( uid ) );
}

Pattern* ResourcesLinker::GetPattern( const std::string& uid )
{
	return static_cast<Pattern*>( GetTexture( uid ) );
}

VectorSprite* ResourcesLinker::GetScreenFXTexture( )
{
	VectorSprite* pTexture{ new VectorSprite( m_pScreenFXTextures, Constants::sk_ScreenFXFrameDelay ) };

	m_pInstantiatedTextures.push_back( pTexture );

	return pTexture;
}

void ResourcesLinker::ClearInstantiated( )
{
	for ( Texture2D* pTexture : m_pInstantiatedTextures )
	{
		delete pTexture;
	}
	m_pInstantiatedTextures.clear( );
}

void ResourcesLinker::InitializeTextures( )
{
	InitializeEntities( );
	InitializeBackgroundProps( );
	//InitializeScreens( );

	//FillSettingsMap( );
}

void ResourcesLinker::InitializeEntities( )
{
	// Cuphead
	LoadTexturesFromFile( "csv/resources/cuphead/cuphead_textures.csv", true );
	LoadSpriteSettingsFromFile( "csv/resources/cuphead/cuphead_sprite_settings.csv" );

	// HUD
	LoadTexturesFromFile( "csv/resources/hud/hud_textures.csv", true );
	LoadSpriteSettingsFromFile( "csv/resources/hud/hud_sprite_settings.csv" );

	// Weapons
	LoadTexturesFromFile( "csv/resources/weapons/peashooter_textures.csv", true );
	LoadSpriteSettingsFromFile( "csv/resources/weapons/peashooter_sprite_settings.csv" );

	// -- ENEMIES --
	// Card
	LoadTexturesFromFile( "csv/resources/enemies/card/card_textures.csv", true );
	LoadSpriteSettingsFromFile( "csv/resources/enemies/card/card_sprite_settings.csv" );

	// Toyduck
	LoadTexturesFromFile( "csv/resources/enemies/toyduck/toyduck_textures.csv", true );
	LoadSpriteSettingsFromFile( "csv/resources/enemies/toyduck/toyduck_sprite_settings.csv" );
}

void ResourcesLinker::InitializeBackgroundProps( )
{

	// part 1
	LoadTexturesFromFile( "csv/resources/background/bg_part1_textures.csv" );
	LoadPatternSettingsFromFile( "csv/resources/background/bg_part1_pattern_settings.csv" );
	LoadSpriteSettingsFromFile( "csv/resources/background/bg_part1_sprite_settings.csv" );
}

void ResourcesLinker::InitializeScreens( )
{
	// Screen FX
	{
		const int screenFxCount{ 127 };
		const std::string basePath{ "screen/ST_screen_fx/cuphead_screen_fx_" };
		
		m_pScreenFXTextures = std::vector<Texture*>( screenFxCount );

		for ( int i{}; i < screenFxCount; ++i )
		{
			const std::string path{ basePath + (i < 100 ? (i < 10 ? "000" : "00") : "0")};
			m_pScreenFXTextures[i] = new Texture( path + std::to_string( i ) + ".png", false, true );

		}
	}
}

void ResourcesLinker::ReleaseTextures( )
{
	ClearInstantiated( );

	for ( std::pair<const std::string, Texture*>& pair : m_pTextures )
	{
		delete pair.second;
	}
	m_pTextures.clear( );

	for ( Texture* pTexture : m_pScreenFXTextures )
	{
		delete pTexture;
	}
	m_pScreenFXTextures.clear( );
}

void ResourcesLinker::LoadTexturesFromFile( const std::string& csvPath, bool flash )
{
	CSVReader reader{ csvPath };

	while ( !reader.eof( ) )
	{
		const std::string uid{ reader.Get( "label" ) };
		const std::string path{ reader.Get( "path" ) };

		if ( m_pTextures.find( uid ) != m_pTextures.end( ) )
		{
			throw std::invalid_argument( std::string("Texture with uid '" + uid + "' already exists but is being loaded by " + csvPath) );
		}

		m_pTextures[uid] = new Texture( path );
		if ( flash )
		{
			m_pTextures[uid + "_flash"] = new Texture( path, true );
		}

		reader.next( );
	}
}

void ResourcesLinker::LoadSpriteSettingsFromFile( const std::string& csvPath )
{
	CSVReader reader{ csvPath };

	while ( !reader.eof( ) )
	{
		const std::string uid{ reader.Get( "label" ) };

		if ( m_SpriteSettingsMap.find( uid ) != m_SpriteSettingsMap.end( ) )
		{
			throw std::invalid_argument( std::string( "SpriteSettings with uid '" + uid + "' already exists but is being loaded by " + csvPath ) );
		}

		const SpriteSettings settings{ reader.GetInt( "rows" ), reader.GetInt( "cols" ),
			reader.GetFloat( "delay" ), reader.GetBoolean( "boomerang" ),
			Vector2f{ reader.GetFloat( "x" ), reader.GetFloat( "y" ) },
			reader.GetBoolean( "mustcomplete" ) };
		m_SpriteSettingsMap[uid] = settings;
		m_TextureTypeMap[uid] = TextureType::sprite;

		reader.next( );
	}
}

void ResourcesLinker::LoadPatternSettingsFromFile( const std::string& csvPath )
{
	CSVReader reader{ csvPath };

	while ( !reader.eof( ) )
	{
		const std::string uid{ reader.Get( "label" ) };

		if ( m_SpriteSettingsMap.find( uid ) != m_SpriteSettingsMap.end( ) )
		{
			throw std::invalid_argument( std::string( "PatternSettings with uid '" + uid + "' already exists but is being loaded by " + csvPath ) );
		}

		const PatternSettings settings{ reader.GetInt( "repetition" ) };
		m_PatternSettingsMap[uid] = settings;
		m_TextureTypeMap[uid] = TextureType::pattern;

		reader.next( );
	}
}

void ResourcesLinker::PushPattern( const std::string& uid, const std::string& path, const PatternSettings& settings )
{
	m_pTextures[uid] = new Texture( path );
	m_PatternSettingsMap[uid] = settings;
	m_TextureTypeMap[uid] = TextureType::pattern;
}

void ResourcesLinker::PushSprite( const std::string& uid, const std::string& path, const SpriteSettings& settings )
{
	m_pTextures[uid] = new Texture( path );
	m_pTextures[uid + "_flash"] = new Texture( path, true );
	m_SpriteSettingsMap[uid] = settings;
	m_TextureTypeMap[uid] = TextureType::sprite;
}

void ResourcesLinker::FillSettingsMap( )
{
	for ( std::pair<const std::string, Texture*>& pair : m_pTextures )
	{
		// If the settings were not defined, turn into patternSettings
		if ( m_TextureTypeMap.find( pair.first ) == m_TextureTypeMap.end( ) )
		{
			m_PatternSettingsMap[pair.first] = PatternSettings{};
			m_TextureTypeMap[pair.first] = TextureType::pattern;
		}
	}
}
