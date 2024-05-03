#pragma once
#include "vector"
#include "Vector2f.h"
#include "CollisionCircle.h"

class CollisionManager
{
public:
	CollisionManager( );
	explicit CollisionManager( const std::vector<CollisionCircle>& collisionCircles, Vector2f const* pDisplacement );
	explicit CollisionManager( const CollisionCircle& collisionCircle, Vector2f const* pDisplacement );

	const std::vector<CollisionCircle>& GetCollisionCircles( ) const;
	const Vector2f& GetDisplacementVector( ) const;
	bool CheckCollision( const CollisionManager& other ) const;

	void Draw( ) const;

private:
	std::vector<CollisionCircle> m_CollisionCircles;
	Vector2f const* m_pDisplacementVector;
};

