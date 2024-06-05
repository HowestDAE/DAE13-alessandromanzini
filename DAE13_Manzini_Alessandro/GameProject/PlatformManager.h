#pragma once
#include "vector"
#include "CollisionCircle.h"
class CollidableEntity;
class Cuphead;
class Enemy;

class PlatformManager final
{
public:
	explicit PlatformManager( const std::string& mapLayoutCsvPath, const std::string& finishLineLayoutCsvPath, const Rectf& viewPort );

	void Draw( ) const;
	void Draw( CollidableEntity const* pEntity ) const;

	bool CheckCollision( CollidableEntity* pEntity, Vector2f& displacement ) const;
	bool CheckCameraBoundsCollision( CollidableEntity* pEntity, Vector2f& displacement ) const;
	bool CheckVerticalBounds( CollidableEntity* pEntity ) const;
	bool CheckFinishLine( CollidableEntity* pEntity ) const;

	void SetCameraBounds( const Point2f center );
	void DropCameraBounds( );

	Point2f GetCameraPoint( Cuphead* pCuphead ) const;
	Point2f GetCameraPoint( Enemy* pEnemy ) const;

private:
	const Rectf mk_ViewPort;
	std::vector<Point2f> m_MapVertices;
	std::vector<Point2f> m_FinishLineVertices;

	std::vector<Point2f> m_CameraVertices;

	bool CheckVerticesCollision( const std::vector<Point2f>& vertices, CollidableEntity* pEntity, Vector2f& displacement ) const;
	void Raycast( const std::vector<Point2f>& vertices, const CollisionCircle& circle, const Vector2f& location, Vector2f& displacement ) const;

	void LoadVerticesFromFile( const std::string& csvPath, std::vector<Point2f>& pVertices );

};

