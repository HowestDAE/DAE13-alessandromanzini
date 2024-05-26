#pragma once
#include "PlatformManager.h"
#include "HUDManager.h"
#include "Camera.h"
#include <vector>
#include <list>
class ResourcesLinker;
class Cuphead;
class Toyduck;
class Entity;
class Enemy;
class Card;
class NonInterractableProp;
class Projectile;
class CSVReader;

class StageManager final
{
public:
	explicit StageManager( Camera* pCamera, ResourcesLinker* pResourcesLinker );
	~StageManager();

	StageManager( const StageManager& other ) = delete;
	StageManager( StageManager&& other ) = delete;
	StageManager& operator=( const StageManager& rhs ) = delete;
	StageManager& operator=( StageManager&& rhs ) = delete;

	void Start( ) noexcept;

	void Update( float elapsedSec );
	
	void KeyPressEvent( const SDL_KeyboardEvent& e );

	bool GetIsHalted( ) const;
	bool GetRequestTitleScreen( ) const;

	const std::vector<NonInterractableProp>& GetBackgroundProps( ) const;
	const std::vector<NonInterractableProp>& GetFrontgroundProps( ) const;

	PlatformManager const* GetPlatformManager( ) const;
	HUDManager const* GetHUDManager( ) const;

	Cuphead const* GetPlayer( ) const;
	const std::vector<Entity*>& GetEntities( ) const;

private:
	enum class BackgroundScope;

	Camera* m_pCamera;
	ResourcesLinker* m_pResourcesLinker;

	PlatformManager m_PlatformManager;
	HUDManager m_HUDManager;

	bool m_IsHalted;
	bool m_IsCameraFixed;

	static const float smk_RequestTitleScreenDelay;
	float m_RequestTitleScreenElapsedTime;
	bool m_RequestingTitleScreen;
	bool m_RequestTitleScreen;

#pragma region gameUnits
	std::vector<NonInterractableProp> m_BackgroundProps;
	std::vector<NonInterractableProp> m_FrontgroundProps;

	Cuphead* m_pPlayer;

	std::vector<Entity*> m_pEntities;
	std::vector<Enemy*> m_pEnemies;
	std::vector<Entity*> m_pCards;

#pragma endregion

	void Initialize( );
	void InitializeProps( const std::string& propsCsvPath );
	void InitializeEntities( );
	void InitializeHUD( );

	void LoadLevelStartAnimation( );
	void LoadEntitiesFromFile( const std::string& csvPath, std::vector<Entity*>& pEntities );
	void LoadEnemiesFromFile( const std::string& csvPath, std::vector<Enemy*>& pEnemies );
	void CreateNIP( BackgroundScope scope, const std::string& uid, const Point2f& position, float scale = 1.f  );
	Entity* CreateEntity( const CSVReader& reader );

	void Pause( ) noexcept;

	void UpdateBackground( float elapsedSec );
	void UpdateEntities( float elapsedSec );
	void CheckRequestTitleScreen( float elapsedSec );

	void CheckCollisions( );

	void LockCamera( const Point2f& centerPoint );
	void UnlockCamera( );

};

enum class StageManager::BackgroundScope
{
	frontground1 = -3,
	frontground2,
	frontground3,
	midground1 = 0,
	midground2,
	background1,
	background2,
	background3,
	background4,
	background5
};
