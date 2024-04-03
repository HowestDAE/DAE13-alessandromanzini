#pragma once
#include "Vector2f.h"
#include "KeysState.h"

class MovementManager final
{
public:
	MovementManager( );

	enum class AimDirection;
	enum class MovementType;

	AimDirection GetAimDirection( ) const;
	MovementType GetMovementType( ) const;

	void SetGravity( bool isDefault );

	void UpdateVelocity( Vector2f& velocity );

	void KeyPressEvent( const SDL_KeyboardEvent& e );
	void CalculateMovementData( );

private:
	KeysState m_KeysStates;

	AimDirection m_Direction;
	MovementType m_MovementType;

	bool m_IsAirborne;
	bool m_IsGravityReversed;

	const Vector2f mk_BaseVelocity;
	const Vector2f mk_BaseJumpVelocity;
	Vector2f m_VelocityModifiers; // One Time Modifiers
};

enum class MovementManager::AimDirection
{
	none,
	up,
	down,
	right,
	rightup,
	rightdown,
	left,
	leftup,
	leftdown
};

enum class MovementManager::MovementType
{
	idle,
	aim,
	run,
	jump,
	parry,
	dash,
	duck
};
