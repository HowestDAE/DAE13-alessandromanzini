#pragma once
#include <vector>
#include <unordered_map>
#include "Weapon.h"
class TextureManager;
class SpriteManager;
class CompositeSpriteManager;
class Cuphead;
class NonInterractableProp;
class Projectile;

class ResourcesLinker final
{
public:
	ResourcesLinker( );
	ResourcesLinker( const ResourcesLinker& other ) = delete;
	~ResourcesLinker( );

	void LinkTexture( Cuphead* pPlayer ); // not const because of lazy loading
	void LinkTexture( NonInterractableProp& nip, const std::string& uid ) const;
	void LinkTexture( Projectile* pProjectile ); // not const because of lazy loading

	ResourcesLinker& operator=( const ResourcesLinker& rhs ) = delete;

private:
#pragma region background
	std::unordered_map<std::string, TextureManager*> m_pBackgroundTextures;

#pragma endregion background

#pragma region entities
	// Cuphead
	SpriteManager* m_pCupheadIdle;

	SpriteManager* m_pCupheadRunLoop;
	SpriteManager* m_pCupheadRunBegin;
	SpriteManager* m_pCupheadRunEnd;
	CompositeSpriteManager* m_pCupheadRun;

	SpriteManager* m_pCupheadDuckLoop;
	SpriteManager* m_pCupheadDuckBegin;
	SpriteManager* m_pCupheadDuckEnd;
	CompositeSpriteManager* m_pCupheadDuck;

	SpriteManager* m_pCupheadJump;

	SpriteManager* m_pCupheadDashGroundLoop;
	SpriteManager* m_pCupheadDashGroundBegin;
	SpriteManager* m_pCupheadDashGroundEnd;
	CompositeSpriteManager* m_pCupheadDashGround;

	SpriteManager* m_pCupheadDashAirLoop;
	SpriteManager* m_pCupheadDashAirBegin;
	SpriteManager* m_pCupheadDashAirEnd;
	CompositeSpriteManager* m_pCupheadDashAir;

#pragma endregion entities

#pragma region weapons
	std::vector<SpriteManager*> m_pProjectileSprites;

#pragma endregion weapons

	void InitializeTextures( );
	void InitializeEntities( );
	void InitializeBackgroundProps( );

	void ReleaseTextures( );
	void ReleaseEntities( );
	void ReleaseBackgroundProps( );
	void ReleaseProjectiles( );
};

