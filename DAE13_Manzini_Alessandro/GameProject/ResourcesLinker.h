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

class ResourcesLinker final
{
public:
	ResourcesLinker( );
	ResourcesLinker( const ResourcesLinker& other ) = delete;
	~ResourcesLinker( );

	Texture2D* GetTexture( const std::string& uid );
	Sprite* GetSprite( const std::string& uid );
	Pattern* GetPattern( const std::string& uid );

	VectorSprite* GetScreenFXTexture( );

	void ClearInstantiated( );

	ResourcesLinker& operator=( const ResourcesLinker& rhs ) = delete;

private:
	enum class TextureType;

	std::unordered_map<std::string, Texture*> m_pTextures;
	std::vector<Texture*> m_pScreenFXTextures;
	std::vector<Texture2D*> m_pInstantiatedTextures;

	std::unordered_map<std::string, TextureType> m_TextureTypeMap;
	std::unordered_map<std::string, PatternSettings> m_PatternSettingsMap;
	std::unordered_map<std::string, SpriteSettings> m_SpriteSettingsMap;
	

	void InitializeTextures( );
	void InitializeEntities( );
	void InitializeBackgroundProps( );
	void InitializeScreens( );

	void ReleaseTextures( );

	void LoadTexturesFromFile( const std::string& csvPath, bool flash = false );
	void LoadSpriteSettingsFromFile( const std::string& csvPath );
	void LoadPatternSettingsFromFile( const std::string& csvPath );

	void PushPattern( const std::string& uid, const std::string& path, const PatternSettings& settings = {} );
	void PushSprite( const std::string& uid, const std::string& path, const SpriteSettings& settings );

	void FillSettingsMap( );
};

enum class ResourcesLinker::TextureType
{
	pattern,
	sprite
};
