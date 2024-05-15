#pragma once
#include "Vector2f.h"

enum class CollisionType
{
	defaultHit,
	noHit,
	forceHit
};

struct CollisionCircle
{
	CollisionCircle( );
	explicit CollisionCircle( Point2f center, float radius, CollisionType collisionType = CollisionType::defaultHit );
	explicit CollisionCircle( float x, float y, float radius, CollisionType collisionType = CollisionType::defaultHit );

	bool IsCollisionCompatible( const CollisionCircle& other ) const;

	Circlef circle;
	CollisionType collisionType;
};

CollisionCircle operator+( const CollisionCircle& lhs, const Vector2f& rhs );
