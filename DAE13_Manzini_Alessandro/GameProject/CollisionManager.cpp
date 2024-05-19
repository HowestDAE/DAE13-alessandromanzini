#include "pch.h"
#include "CollisionManager.h"
#include "utils.h"

CollisionManager::CollisionManager( )
	: m_CollisionCircles{ }
	, m_pDisplacementVector{ }
{
}

CollisionManager::CollisionManager( const std::vector<CollisionCircle>& collisionCircles, Vector2f const* pDisplacement )
	: m_CollisionCircles{ collisionCircles }
	, m_pDisplacementVector{ pDisplacement }
{
}

CollisionManager::CollisionManager( const CollisionCircle& collisionCircle, Vector2f const* pDisplacement )
	: m_CollisionCircles{ std::vector<CollisionCircle>{ collisionCircle } }
	, m_pDisplacementVector{ pDisplacement }
{
}

const std::vector<CollisionCircle>& CollisionManager::GetCollisionCircles( ) const
{
	return m_CollisionCircles;
}

const Vector2f& CollisionManager::GetDisplacementVector( ) const
{
	return *m_pDisplacementVector;
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
				collisionInfo.hollow = (circle1.collisionType == CollisionType::hollow || circle2.collisionType == CollisionType::hollow);
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
		utils::DrawEllipse( Ellipsef{ circle.circle.center + *m_pDisplacementVector, circle.circle.radius, circle.circle.radius } );
	}
}
