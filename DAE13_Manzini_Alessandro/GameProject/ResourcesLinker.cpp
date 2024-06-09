#include "pch.h"
#include "ResourcesLinker.h"
#include "Texture.h"
#include "Texture2D.h"
#include "Pattern.h"
#include "Sprite.h"
#include "VectorSprite.h"
#include "CSVReader.h"
#include "Constants.h"
#include "SoundStream.h"
#include "SoundEffect.h"
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

SoundStream const* ResourcesLinker::GetSoundStream( const std::string& uid ) const
{
	return m_pSoundStreams.at( uid );
}

SoundEffect* ResourcesLinker::GetSoundEffect( const std::string& uid ) const
{
	return m_pSoundEffects.at( uid );
}

void ResourcesLinker::ResetSound( ) const
{
	for ( std::pair<const std::string, SoundStream*> pair : m_pSoundStreams )
	{
		pair.second->Stop( );
	}

	SoundEffect::StopAll( );
}

VectorSprite* ResourcesLinker::GetScreenFXTexture( )
{
	VectorSprite* pTexture{ new VectorSprite( m_pScreenFXTextures, Constants::sk_ScreenFXFrameDelay ) };

	m_pInstantiatedTextures.push_back( pTexture );

	return pTexture;
}

std::string ResourcesLinker::GetFontPath( )
{
	return std::string( "fonts/F_cuphead_vogue_xbold.otf" );
}

std::string ResourcesLinker::GetLightFontPath( )
{
	return std::string( "fonts/CupheadMemphis-Medium.otf" );
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
	InitializeScreens( );

	LoadSoundsFromFile( "csv/resources/sound/general_sound_settings.csv" );
	LoadSoundsFromFile( "csv/resources/sound/player_sound_settings.csv" );
	LoadSoundsFromFile( "csv/resources/sound/enemies_sound_settings.csv" );
	LoadSoundsFromFile( "csv/level_sound_settings.csv" );

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
	LoadTexturesFromFile( "csv/resources/weapon/weapon_textures.csv", true );
	LoadSpriteSettingsFromFile( "csv/resources/weapon/weapon_sprite_settings.csv" );
	
	// Coins
	LoadTexturesFromFile( "csv/resources/coin/coin_textures.csv" );
	LoadSpriteSettingsFromFile( "csv/resources/coin/coin_sprite_settings.csv" );

	// -- ENEMIES --
	// Card
	LoadTexturesFromFile( "csv/resources/enemy/card/card_textures.csv", true );
	LoadSpriteSettingsFromFile( "csv/resources/enemy/card/card_sprite_settings.csv" );
	
	// Toyduck
	LoadTexturesFromFile( "csv/resources/enemy/toyduck/toyduck_textures.csv", true );
	LoadSpriteSettingsFromFile( "csv/resources/enemy/toyduck/toyduck_sprite_settings.csv" );

	// Toycar
	LoadTexturesFromFile( "csv/resources/enemy/toycar/toycar_textures.csv", true );
	LoadSpriteSettingsFromFile( "csv/resources/enemy/toycar/toycar_sprite_settings.csv" );

	// Funwall
	LoadTexturesFromFile( "csv/resources/enemy/funwall/funwall_textures.csv", true );
	LoadSpriteSettingsFromFile( "csv/resources/enemy/funwall/funwall_sprite_settings.csv" );

	// Starblaster
	LoadTexturesFromFile( "csv/resources/enemy/starblaster/starblaster_textures.csv", true );
	LoadSpriteSettingsFromFile( "csv/resources/enemy/starblaster/starblaster_sprite_settings.csv" );

	// Tuba
	LoadTexturesFromFile( "csv/resources/enemy/tuba/tuba_textures.csv", true );
	LoadSpriteSettingsFromFile( "csv/resources/enemy/tuba/tuba_sprite_settings.csv" );
}

void ResourcesLinker::InitializeBackgroundProps( )
{
	LoadTexturesFromFile( "csv/resources/background/bg_textures.csv" );
	LoadPatternSettingsFromFile( "csv/resources/background/bg_pattern_settings.csv" );
	LoadSpriteSettingsFromFile( "csv/resources/background/bg_sprite_settings.csv" );
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
	LoadTexturesFromFile( "csv/resources/screen/screen_textures.csv" );
	LoadSpriteSettingsFromFile( "csv/resources/screen/screen_sprite_settings.csv" );
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

	for ( std::pair<const std::string, SoundStream*>& pair : m_pSoundStreams )
	{
		delete pair.second;
	}
	m_pSoundStreams.clear( );
	for ( std::pair<const std::string, SoundEffect*>& pair : m_pSoundEffects )
	{
		delete pair.second;
	}
	m_pSoundEffects.clear( );
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

void ResourcesLinker::LoadSoundsFromFile( const std::string& csvPath )
{
	CSVReader reader{ csvPath };

	while ( !reader.eof( ) )
	{
		if ( reader.GetBoolean( "loop" ) )
		{
			SoundStream* pSoundStream{ new SoundStream( reader.Get( "path" ) ) };
			m_pSoundStreams[reader.Get( "label" )] = pSoundStream;

			const int volume{ reader.GetInt( "volume" ) };
			if ( volume != 0 )
			{
				pSoundStream->SetVolume( volume );
			}
		}
		else
		{
			SoundEffect* pSoundEffect{ new SoundEffect( reader.Get( "path" ) ) };
			m_pSoundEffects[reader.Get( "label" )] = pSoundEffect;

			const int volume{ reader.GetInt( "volume" ) };
			if ( volume != 0 )
			{
				pSoundEffect->SetVolume( volume );
			}
		}

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
