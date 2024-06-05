#include "pch.h"
#include "PlatformManager.h"
#include "CollidableEntity.h"
#include "CollisionManager.h"
#include "Cuphead.h"
#include "Enemy.h"
#include "Constants.h"
#include "utils.h"
#include "CSVReader.h"

PlatformManager::PlatformManager( const std::string& mapLayoutCsvPath, const std::string& finishLineLayoutCsvPath, const Rectf& viewPort )
	: mk_ViewPort{ viewPort }
	, m_CameraVertices{}
{
	LoadVerticesFromFile( mapLayoutCsvPath, m_MapVertices );
	LoadVerticesFromFile( finishLineLayoutCsvPath, m_FinishLineVertices );
}

void PlatformManager::Draw( ) const
{
	utils::DrawPolygon( m_MapVertices.data(), m_MapVertices.size(), false );
	utils::DrawPolygon( m_CameraVertices.data(), m_CameraVertices.size(), false );
}

void PlatformManager::Draw( CollidableEntity const* pEntity ) const
{
	CollisionManager const* pCollisionManager{ pEntity->GetCollisionManager( ) };
	const Vector2f location{ pCollisionManager->GetDisplacementVector( ) };

	for ( const CollisionCircle& circle : pCollisionManager->GetCollisionCircles( ) )
	{
		const Vector2f horizontalOffset{ circle.circle.radius, 0.f };
		const Vector2f verticalOffset{ 0.f, circle.circle.radius };

		const Point2f middlePoint{ circle.circle.center + location };

		utils::DrawLine( middlePoint + horizontalOffset, middlePoint - horizontalOffset );
		utils::DrawLine( middlePoint + verticalOffset, middlePoint - verticalOffset );
	}
}

bool PlatformManager::CheckCollision( CollidableEntity* pEntity, Vector2f& displacement ) const
{
	return CheckVerticesCollision( m_MapVertices, pEntity, displacement );
}

bool PlatformManager::CheckCameraBoundsCollision( CollidableEntity* pEntity, Vector2f& displacement ) const
{
	return CheckVerticesCollision( m_CameraVertices, pEntity, displacement );
}

bool PlatformManager::CheckVerticalBounds( CollidableEntity* pEntity ) const
{
	Vector2f location{ pEntity->GetCollisionManager( )->GetDisplacementVector( ) };
	location.y += pEntity->GetCollisionManager( )->GetCollisionCircles( )[0].circle.radius * 2;

	return location.y < 0 || location.y > mk_ViewPort.height;
}

bool PlatformManager::CheckFinishLine( CollidableEntity* pEntity ) const
{
	CollisionManager const* pCollisionManager{ pEntity->GetCollisionManager( ) };
	const Vector2f location{ pCollisionManager->GetDisplacementVector( ) };

	for ( const CollisionCircle& circle : pCollisionManager->GetCollisionCircles( ) )
	{
		if ( utils::IsOverlapping( m_FinishLineVertices, (circle + location).circle ) )
		{
			return true;
		}
	}

	return false;
}

void PlatformManager::SetCameraBounds( const Point2f center )
{
	const float halfScreenWidth{ mk_ViewPort.width / 2.f };
	m_CameraVertices = 
	{ 
		Point2f{ center.x + halfScreenWidth, 0.f }, Point2f{ center.x + halfScreenWidth, mk_ViewPort.height },
		Point2f{ center.x - halfScreenWidth, mk_ViewPort.height }, Point2f{ center.x - halfScreenWidth, 0.f }
	};
}

void PlatformManager::DropCameraBounds( )
{
	m_CameraVertices.clear( );
}

Point2f PlatformManager::GetCameraPoint( Cuphead* pCuphead ) const
{
	return pCuphead->GetLocation( ).ToPoint2f( );
}

Point2f PlatformManager::GetCameraPoint( Enemy* pEnemy ) const
{
	const float defaultEnemyCameraOffset{ 350.f };
	return Point2f{ pEnemy->GetLocation( ).x - mk_ViewPort.width / 2.f + defaultEnemyCameraOffset, 0.f};
}

bool PlatformManager::CheckVerticesCollision( const std::vector<Point2f>& vertices, CollidableEntity* pEntity, Vector2f& displacement ) const
{
	if ( vertices.empty( ) ) return false;

	CollisionManager const* pCollisionManager{ pEntity->GetCollisionManager( ) };
	const Vector2f location{ pCollisionManager->GetDisplacementVector( ) };

	for ( const CollisionCircle& circle : pCollisionManager->GetCollisionCircles( ) )
	{
		Raycast( vertices, circle, location, displacement );

		if ( displacement.x != 0.f || displacement.y != 0.f )
		{
			return true;
		}
	}
	return false;
}

void PlatformManager::Raycast( const std::vector<Point2f>& vertices, const CollisionCircle& circle, const Vector2f& location, Vector2f& displacement ) const
{
	utils::HitInfo tempInfo{};

	const Vector2f horizontalOffset{ circle.circle.radius, 0.f };
	const Vector2f verticalOffset{ 0.f, circle.circle.radius };

	const Point2f middlePoint{ circle.circle.center + location };

	// Horizontal displacement
	if ( utils::Raycast( vertices, middlePoint + horizontalOffset, middlePoint - horizontalOffset, tempInfo ) )
	{
		displacement.x = horizontalOffset.x * tempInfo.normal.x + ( tempInfo.intersectPoint.x - middlePoint.x );
	}

	// Vertical displacement
	if ( utils::Raycast( vertices, middlePoint + verticalOffset, middlePoint - verticalOffset, tempInfo ) )
	{
		displacement.y = verticalOffset.y * tempInfo.normal.y + ( tempInfo.intersectPoint.y - middlePoint.y );
	}
}

void PlatformManager::LoadVerticesFromFile( const std::string& csvPath, std::vector<Point2f>& pVertices )
{
	CSVReader reader{ csvPath };

	pVertices = std::vector<Point2f>( reader.size( ) );
	pVertices.clear( );
	while ( !reader.eof( ) )
	{
		const Point2f vertex{ reader.GetFloat( "x" ), reader.GetFloat( "y" ) };
		pVertices.push_back( vertex );
		reader.next( );
	}
}
