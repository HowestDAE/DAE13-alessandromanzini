#pragma once
#include <vector>
#include <unordered_map>
class TextureManager;
class SpriteManager;
class NonInterractableProp;
class Cuphead;

class ResourcesLinker final
{
public:
	ResourcesLinker( );
	ResourcesLinker( const ResourcesLinker& other ) = delete;
	~ResourcesLinker( );

	void LinkTexture( Cuphead* pPlayer ) const;
	void LinkTexture( NonInterractableProp& nip, const std::string& uid ) const;

	ResourcesLinker& operator=( const ResourcesLinker& rhs ) = delete;

private:
#pragma region background
	std::unordered_map<std::string, TextureManager*> m_pBackgroundTextures;

#pragma endregion background

#pragma region entities
	// Cuphead
	SpriteManager* m_pCupheadIdle;
	SpriteManager* m_pCupheadRun;

#pragma endregion entities

	void InitializeTextures( );
	void InitializeEntities( );
	void InitializeBackgroundProps( );

	void ReleaseTextures( );
	void ReleaseEntities( );
	void ReleaseBackgroundProps( );
};

