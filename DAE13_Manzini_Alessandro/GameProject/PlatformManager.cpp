#include "pch.h"
#include "PlatformManager.h"
#include "Entity.h"
#include "CollisionManager.h"
#include "Constants.h"
#include "utils.h"
#include "CSVReader.h"

PlatformManager::PlatformManager( const std::string& mapLayoutCsvPath )
{
	CSVReader reader{ mapLayoutCsvPath };

	m_MapVertices = std::vector<Point2f>( reader.size( ) );
	m_MapVertices.clear( );
	while ( !reader.eof( ) )
	{
		const Point2f vertex{ reader.GetFloat( "x" ), reader.GetFloat( "y" ) };
		m_MapVertices.push_back( vertex );
		reader.next( );
	}
}

void PlatformManager::Draw( ) const
{
	utils::DrawPolygon( m_MapVertices.data(), m_MapVertices.size(), false );
}

void PlatformManager::Draw( Entity const* pEntity ) const
{
	CollisionManager const* pCollisionManager{ pEntity->GetCollisionManager( ) };
	const Vector2f location{ pEntity->GetLocation( ) };

	for ( const CollisionCircle& circle : pCollisionManager->GetCollisionCircles( ) )
	{
		const Vector2f horizontalOffset{ circle.circle.radius, 0.f };
		const Vector2f verticalOffset{ 0.f, circle.circle.radius };

		const Point2f middlePoint{ circle.circle.center + location };

		utils::DrawLine( middlePoint + horizontalOffset, middlePoint - horizontalOffset );
		utils::DrawLine( middlePoint + verticalOffset, middlePoint - verticalOffset );
	}
}

bool PlatformManager::CheckCollision( Entity* pEntity, Vector2f& displacement ) const
{
	CollisionManager const* pCollisionManager{ pEntity->GetCollisionManager( ) };
	const Vector2f location{ pEntity->GetLocation( ) };

	for ( const CollisionCircle& circle : pCollisionManager->GetCollisionCircles( ) )
	{
		Raycast( circle, location, displacement );

		if ( displacement.x != 0.f || displacement.y != 0.f )
		{
			return true;
		}
	}
	return false;
}

void PlatformManager::Raycast( const CollisionCircle& circle, const Vector2f& location, Vector2f& displacement ) const
{
	utils::HitInfo tempInfo{};

	const Vector2f horizontalOffset{ circle.circle.radius, 0.f };
	const Vector2f verticalOffset{ 0.f, circle.circle.radius };

	const Point2f middlePoint{ circle.circle.center + location };

	// Horizontal displacement
	if ( utils::Raycast( m_MapVertices, middlePoint + horizontalOffset, middlePoint - horizontalOffset, tempInfo ) )
	{
		displacement.x = horizontalOffset.x * tempInfo.normal.x + ( tempInfo.intersectPoint.x - middlePoint.x );
	}

	// Vertical displacement
	if ( utils::Raycast( m_MapVertices, middlePoint + verticalOffset, middlePoint - verticalOffset, tempInfo ) )
	{
		displacement.y = verticalOffset.y * tempInfo.normal.y + (tempInfo.intersectPoint.y - middlePoint.y);
	}
}
