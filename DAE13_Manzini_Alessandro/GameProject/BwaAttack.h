#pragma once
#include "Entity.h"
#include "CollisionManager.h"

struct Letter
{
	Sprite* pSprite;
	Point2f position;
};

class BwaAttack final :
    public Entity
{
public:
    explicit BwaAttack( const Point2f& position );

	void Draw( ) const;
	void Update( float elapsedSec );

	virtual bool GetIFrameState( ) const override;

	void Reset( );
	void Kill( );

	void LinkTexture( ResourcesLinker* pResourcesLinker );

private:
	CollisionManager m_CollisionManager;

	const Vector2f m_StartLocation;

	std::vector<Letter> m_Letters;
	int m_VisibleLetterIndex;

	bool m_IsActive;
	float m_Distance;
	float m_TravelTime;

	const static float smk_BwaChangeSpeedTime;
	const static float smk_BwaChangeSpeedDuration;

};
