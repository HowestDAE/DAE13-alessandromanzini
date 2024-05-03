#pragma once
#include "Vector2f.h"

struct CollisionCircle
{
	CollisionCircle( );
	explicit CollisionCircle( Point2f center, float radius, bool canHit = true );
	explicit CollisionCircle( float x, float y, float radius, bool canHit = true );

	Circlef circle;
	bool canHit;
};

CollisionCircle operator+( const CollisionCircle& lhs, const Vector2f& rhs );
