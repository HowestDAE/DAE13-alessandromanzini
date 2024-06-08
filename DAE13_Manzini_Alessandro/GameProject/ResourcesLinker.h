#pragma once
#include <vector>
#include <unordered_map>
#include "Weapon.h"
#include "PatternSettings.h"
#include "SpriteSettings.h"
class Texture2D;
class Sprite;
class Pattern;
class VectorSprite;
class SoundStream;
class SoundEffect;

class ResourcesLinker final
{
public:
	ResourcesLinker( );
	~ResourcesLinker( );

	ResourcesLinker( const ResourcesLinker& other ) = delete;
	ResourcesLinker( ResourcesLinker&& other ) = delete;
	ResourcesLinker& operator=( const ResourcesLinker& rhs ) = delete;
	ResourcesLinker& operator=( ResourcesLinker&& rhs ) = delete;

	Texture2D* GetTexture( const std::string& uid );
	Sprite* GetSprite( const std::string& uid );
	Pattern* GetPattern( const std::string& uid );

	SoundStream const* GetSoundStream( const std::string& uid ) const;
	SoundEffect* GetSoundEffect( const std::string& uid ) const;
	void ResetSound( ) const;

	VectorSprite* GetScreenFXTexture( );

	static std::string GetFontPath( );
	static std::string GetLightFontPath( );

	void ClearInstantiated( );

private:
	enum class TextureType;

	std::unordered_map<std::string, Texture*> m_pTextures;
	std::vector<Texture*> m_pScreenFXTextures;
	std::vector<Texture2D*> m_pInstantiatedTextures;

	std::unordered_map<std::string, TextureType> m_TextureTypeMap;
	std::unordered_map<std::string, PatternSettings> m_PatternSettingsMap;
	std::unordered_map<std::string, SpriteSettings> m_SpriteSettingsMap;

	std::unordered_map<std::string, SoundStream*> m_pSoundStreams;
	std::unordered_map<std::string, SoundEffect*> m_pSoundEffects;

	void InitializeTextures( );
	void InitializeEntities( );
	void InitializeBackgroundProps( );
	void InitializeScreens( );

	void ReleaseTextures( );

	void LoadTexturesFromFile( const std::string& csvPath, bool flash = false );
	void LoadSpriteSettingsFromFile( const std::string& csvPath );
	void LoadPatternSettingsFromFile( const std::string& csvPath );

	void LoadSoundsFromFile( const std::string& csvPath );

	void PushPattern( const std::string& uid, const std::string& path, const PatternSettings& settings = {} );
	void PushSprite( const std::string& uid, const std::string& path, const SpriteSettings& settings );

	void FillSettingsMap( );
};

enum class ResourcesLinker::TextureType
{
	pattern,
	sprite
};
