#include "pch.h"
#include "CollisionCircle.h"

CollisionCircle::CollisionCircle( )
	: CollisionCircle{ Point2f{}, 0.f }
{
}

CollisionCircle::CollisionCircle( Point2f center, float radius, CollisionType collisionType )
	: circle{ center, radius }
	, collisionType{ collisionType }
{
}

CollisionCircle::CollisionCircle( float x, float y, float radius, CollisionType collisionType )
	: CollisionCircle{ Point2f{ x, y }, radius, collisionType }
{
}

bool CollisionCircle::IsCollisionCompatible( const CollisionCircle& other ) const
{
	// Only apply hit if both circles can hit or are forced to hit
	if ( (collisionType == CollisionType::noHit || other.collisionType == CollisionType::noHit)
		&& collisionType != CollisionType::forceHit && other.collisionType != CollisionType::forceHit )
	{
		return false;
	}
	return true;
}

CollisionCircle operator+( const CollisionCircle& lhs, const Vector2f& rhs )
{
	return CollisionCircle{ lhs.circle.center + rhs, lhs.circle.radius, lhs.collisionType };
}
