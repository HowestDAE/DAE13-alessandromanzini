#pragma once
#include "vector"
#include "CollisionCircle.h"
class Entity;

class PlatformManager final
{
public:
	explicit PlatformManager( const std::string& mapLayoutCsvPath );

	void Draw( ) const;
	void Draw( Entity const* pEntity ) const;
	bool CheckCollision( Entity* pEntity, Vector2f& displacement ) const;

private:
	std::vector<Point2f> m_MapVertices;

	void Raycast( const CollisionCircle& circle, const Vector2f& location, Vector2f& displacement ) const;

};

