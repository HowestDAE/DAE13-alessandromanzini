#pragma once
#include "PlatformManager.h"
#include "HUDManager.h"
#include "Camera.h"
#include "GameStats.h"
#include <vector>
#include <list>
class ResourcesLinker;
class Cuphead;
class Toyduck;
class Entity;
class Enemy;
class Card;
class Coin;
class NonInterractableProp;
class Projectile;
class CSVReader;

class StageManager final
{
public:
	explicit StageManager( Camera* pCamera, ResourcesLinker* pResourcesLinker );
	~StageManager() noexcept;

	StageManager( const StageManager& other ) = delete;
	StageManager( StageManager&& other ) = delete;
	StageManager& operator=( const StageManager& rhs ) = delete;
	StageManager& operator=( StageManager&& rhs ) = delete;

	void Start( ) noexcept;

	void Update( float elapsedSec );
	
	void KeyPressEvent( const SDL_KeyboardEvent& e );

	bool GetIsHalted( ) const;
	bool GetRequestTitleScreen( ) const;
	bool GetRequestWinScreen( GameStats& gameStats ) const;

	float GetScreenOpacity( ) const;

	const std::vector<NonInterractableProp>& GetBackgroundProps( ) const;
	const std::vector<NonInterractableProp>& GetFrontgroundProps( ) const;

	PlatformManager const* GetPlatformManager( ) const;
	HUDManager const* GetHUDManager( ) const;

	Cuphead const* GetPlayer( ) const;
	const std::vector<Entity*>& GetEntities( ) const;

	static void PushCompositionEntity( Entity* pEntity );
	static void PopCompositionEntity( Entity* pEntity );

private:
	enum class BackgroundScope;

	Camera* m_pCamera;
	ResourcesLinker* m_pResourcesLinker;

	PlatformManager m_PlatformManager;
	HUDManager m_HUDManager;

	bool m_IsHalted;
	bool m_IsCameraFixed;

	float m_TotalElapsedTime;

	static const float smk_RequestTitleScreenDelay;
	float m_RequestTitleScreenElapsedTime;
	bool m_RequestingTitleScreen;
	bool m_RequestTitleScreen;

	static const float smk_RequestWinScreenDelay;
	float m_RequestWinScreenElapsedTime;
	bool m_RequestingWinScreen;
	bool m_RequestWinScreen;

	bool m_DeathScreenLoaded;

	bool m_IntroPlayed;

	int m_CollectedCoinsCount;

	std::vector<NonInterractableProp> m_BackgroundProps;
	std::vector<NonInterractableProp> m_FrontgroundProps;

	Cuphead* m_pPlayer;
	Enemy const* mk_pLockedEnemy;

	std::vector<Entity*> m_pEntities;
	std::vector<Enemy*> m_pEnemies;
	std::vector<Entity*> m_pCards;
	std::vector<Entity*> m_pCoins;

	static std::vector<Entity*> sm_pCompositionEntities;

	void Initialize( );
	void InitializeProps( const std::string& propsCsvPath );
	void InitializeEntities( const std::string& enemiesCsvPath, const std::string& cardsCsvPath, const std::string& coinsCsvPath );
	void InitializeHUD( );
	void InitializeSounds( const std::string& soundsCsvPath );

	void LoadLevelStartAnimation( );
	void LoadPlayerDeathAnimation( );
	void LoadLevelWinAnimation( );
	void LoadEntitiesFromFile( const std::string& csvPath, std::vector<Entity*>& pEntities );
	void LoadEnemiesFromFile( const std::string& csvPath, std::vector<Enemy*>& pEnemies );

	void CreateNIP( BackgroundScope scope, const std::string& uid, const Point2f& position, float scale = 1.f  );
	Entity* CreateEntity( const CSVReader& reader );

	void Pause( ) noexcept;

	void UpdateBackground( float elapsedSec );
	void UpdateEntities( float elapsedSec );
	void CheckScreenRequests( float elapsedSec );

	void CheckCollisions( );
	void CheckPlayerCollisions( );
	void CheckEntitiesCollisions( );
	void CheckPlayerState( ); // loads player death is player is not alive

	void LockCamera( const Point2f& centerPoint );
	void UnlockCamera( );

	void CollectCoin( ) noexcept;

	bool GetIsGameOver( ) const;

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
