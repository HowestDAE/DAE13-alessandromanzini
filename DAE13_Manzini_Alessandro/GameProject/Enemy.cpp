#include "pch.h"
#include "Enemy.h"

Enemy::Enemy( const Point2f& position, int hp, float aggroRadius, float dropRadius, int contactDamage, bool isPink, bool screenLock )
	: Entity( position, hp, contactDamage, isPink )
	, mk_AggroRadius{ powf( aggroRadius, 2 ) }
	, mk_DropRadius{ powf( dropRadius, 2 ) }
	, mk_ScreenLock{ screenLock }
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

bool Enemy::CompareAggroDistance( const Vector2f& targetLocation )
{
	const Vector2f selfToTarget{ targetLocation - m_Location };
	const float squaredDistance{ selfToTarget.SquaredLength( ) };

	if ( squaredDistance <= mk_AggroRadius )
	{
		m_IsAggro = true;
	}
	else if ( squaredDistance > mk_DropRadius )
	{
		m_IsAggro = false;
	}

	return m_IsAggro;
}

bool Enemy::GetIsScreenLock( ) const
{
	return mk_ScreenLock;
}
