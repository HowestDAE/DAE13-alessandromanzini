#pragma once
#include "Vector2f.h"

enum class CollisionType
{
	defaultHit, // gets and generates hits between other default circles.
	noHit,		// doesn't hit default circles.
	forceHit,	// can hit noHit circles.
	hollow		// creates a collision with everybody but disables hits.
};

struct CollisionCircle final
{
	CollisionCircle( );
	explicit CollisionCircle( Point2f center, float radius, CollisionType collisionType = CollisionType::defaultHit );
	explicit CollisionCircle( float x, float y, float radius, CollisionType collisionType = CollisionType::defaultHit );

	bool IsCollisionCompatible( const CollisionCircle& other ) const;

	Circlef circle;
	CollisionType collisionType;
};

CollisionCircle operator+( const CollisionCircle& lhs, const Vector2f& rhs );
