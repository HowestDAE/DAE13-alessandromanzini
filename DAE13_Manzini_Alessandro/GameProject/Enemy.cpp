#include "pch.h"
#include "Enemy.h"
#include <iostream>

Enemy::Enemy( const Point2f& position, int hp, float aggroRadius, float dropRadius, int contactDamage, bool isPink, bool screenLock )
	: Entity( position, hp, contactDamage, isPink )
	, m_AggroRadius{ powf( aggroRadius, 2 ) }
	, mk_DropRadius{ powf( dropRadius, 2 ) }
	, mk_ScreenLock{ screenLock }
	, mk_StartLocation{ position }
	, m_IsAggro{ false }
{
}

void Enemy::Update( float elapsedSec )
{
	if ( m_IsAggro )
	{
		Entity::Update( elapsedSec );
		UpdateLocation( elapsedSec );
	}
}

void Enemy::Update( float elapsedSec, const Vector2f& targetLocation )
{
	Update( elapsedSec );
}

bool Enemy::CompareAggroDistance( const Vector2f& targetLocation )
{
	const Vector2f selfToTarget{ targetLocation - m_Location };
	const float squaredDistance{ selfToTarget.SquaredLength( ) };

	if ( m_IsAggro )
	{
		if ( squaredDistance > mk_DropRadius )
		{
			// Once activated, the aggro radius extends to the drop radius
			m_AggroRadius = mk_DropRadius;
			m_IsAggro = false;

			DropEvent( );
		}
	}
	else if ( squaredDistance <= m_AggroRadius )
	{
		m_IsAggro = true;

		AggroEvent( );
	}

	return m_IsAggro;
}

void Enemy::Reset( const Point2f& position )
{
	m_Location = Vector2f{ position };
}

void Enemy::Reset( )
{
	m_Location = Vector2f{ mk_StartLocation };
}

bool Enemy::GetIsScreenLock( ) const
{
	return mk_ScreenLock && m_IsAggro && GetIsAlive( );
}

void Enemy::AggroEvent( )
{
}

void Enemy::DropEvent( )
{
}

bool Enemy::GetIsAggro( ) const
{
	return m_IsAggro;
}

bool Enemy::GetIFrameState( ) const
{
	return false;
}
