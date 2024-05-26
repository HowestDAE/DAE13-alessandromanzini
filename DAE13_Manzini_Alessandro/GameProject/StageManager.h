#pragma once
#include "PlatformManager.h"
#include "HUDManager.h"
#include "Camera.h"
#include <vector>
#include <list>
class ResourcesLinker;
class Cuphead;
class Toyduck;
class Card;
class Entity;
class NonInterractableProp;
class Projectile;

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

#pragma region gameUnits
	Cuphead* m_pPlayer;
	Toyduck* m_pToyduck;
	std::vector<Card*> m_pCards;
	std::vector<NonInterractableProp> m_BackgroundProps;
	std::vector<NonInterractableProp> m_FrontgroundProps;

	std::vector<Entity*> m_pEntities;

#pragma endregion

	void Initialize( );
	void InitializeProps( const std::string& propsCsvPath );
	void InitializeEntities( );
	void InitializeHUD( );
	void CreateNIP( BackgroundScope scope, const std::string& uid, const Point2f& position, float scale = 1.f  );

	void LoadLevelStartAnimation( );

	void Pause( ) noexcept;

	void UpdateBackground( float elapsedSec );
	void UpdateEntities( float elapsedSec );

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
