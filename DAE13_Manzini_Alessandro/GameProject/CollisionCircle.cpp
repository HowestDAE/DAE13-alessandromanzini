#include "pch.h"
#include "CollisionCircle.h"

CollisionCircle::CollisionCircle( )
	: CollisionCircle{ Point2f{}, 0.f }
{
}

CollisionCircle::CollisionCircle( Point2f center, float radius, bool canHit )
	: circle{ center, radius }
	, canHit{ canHit }
{
}

CollisionCircle::CollisionCircle( float x, float y, float radius, bool canHit )
	: CollisionCircle{ Point2f{ x, y }, radius, canHit }
{
}

CollisionCircle operator+( const CollisionCircle& lhs, const Vector2f& rhs )
{
	return CollisionCircle{ lhs.circle.center + rhs, lhs.circle.radius, lhs.canHit };
}
