#include "pch.h"
#include "CollisionManager.h"
#include "utils.h"

CollisionManager::CollisionManager( )
	: CollisionManager( CollisionCircle{}, nullptr )
{
}

CollisionManager::CollisionManager( const std::vector<CollisionCircle>& collisionCircles, Vector2f const* pDisplacement )
	: m_CollisionCircles{ collisionCircles }
	, mk_pDisplacementVector{ pDisplacement }
{
}

CollisionManager::CollisionManager( const CollisionCircle& collisionCircle, Vector2f const* pDisplacement )
	: CollisionManager( std::vector<CollisionCircle>{ collisionCircle }, pDisplacement )
{
}

const std::vector<CollisionCircle>& CollisionManager::GetCollisionCircles( ) const
{
	return m_CollisionCircles;
}

const Vector2f& CollisionManager::GetDisplacementVector( ) const
{
	return *mk_pDisplacementVector;
}

bool CollisionManager::CheckCollision( const CollisionManager& other, CollisionInfo& collisionInfo ) const
{
	for ( CollisionCircle circle1 : m_CollisionCircles )
	{
		circle1 = circle1 + GetDisplacementVector();

		for ( const CollisionCircle& circle2 : other.GetCollisionCircles( ) )
		{
			if ( utils::IsOverlapping( circle1.circle, (circle2 + other.GetDisplacementVector()).circle ) 
				&& circle1.IsCollisionCompatible(circle2) )
			{
				const bool isHollow = ( circle1.collisionType == CollisionType::hollow
					|| circle2.collisionType == CollisionType::hollow );

				collisionInfo.selfHit = !isHollow;
				collisionInfo.otherHit = !isHollow;

				return true;
			}
		}
	}
	return false;
}

void CollisionManager::Draw( ) const
{
	utils::SetColor( Color4f{ 1.f, 1.f, 1.f, 1.f } );
	for ( const CollisionCircle& circle : m_CollisionCircles )
	{
		utils::DrawEllipse( Ellipsef{ circle.circle.center + *mk_pDisplacementVector, circle.circle.radius, circle.circle.radius } );
	}
}
