#pragma once
#include "PlatformManager.h"
#include <vector>
#include <list>
class Camera;
class ResourcesLinker;
class Cuphead;
class NonInterractableProp;
class Projectile;

class StageManager final
{
public:
	explicit StageManager( Camera* pCamera, ResourcesLinker* pResourcesLinker );
	StageManager( const StageManager& other ) = delete;
	~StageManager();

	void Start( );
	void Pause( );

	void Update( float elapsedSec );
	
	void KeyPressEvent( const SDL_KeyboardEvent& e );

	Cuphead const* GetPlayer( ) const;
	const std::list<Projectile*>& GetProjectiles( ) const;

	const std::vector<NonInterractableProp>& GetBackgroundProps( ) const;
	const std::vector<NonInterractableProp>& GetFrontgroundProps( ) const;

	static void PushProjectile( Projectile* pProjectile );

	StageManager& operator=( const StageManager& rhs ) = delete;

private:
	enum class BackgroundScope;

	Camera* m_pCamera;
	ResourcesLinker* m_pResourcesLinker;

	PlatformManager m_PlatformManager;

	bool m_IsHalted;
	bool m_IsCameraFixed;

#pragma region gameUnits
	Cuphead* m_pPlayer;
	std::vector<NonInterractableProp> m_BackgroundProps;
	std::vector<NonInterractableProp> m_FrontgroundProps;

	static std::list<Projectile*> sm_pProjectiles;

#pragma endregion

	void Initialize( );
	void InitializeProps( );
	void InitializeEntities( );
	void CreateNIP( BackgroundScope scope, const std::string& uid, const Point2f& position, float scale = 1.f  );

	void UpdateBackground( float elapsedSec );
	void UpdateEntities( float elapsedSec );
	void UpdateProjectiles( float elapsedSec );

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
