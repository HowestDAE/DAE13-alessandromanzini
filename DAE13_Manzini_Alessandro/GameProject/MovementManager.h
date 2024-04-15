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
	bool IsFacingRight( ) const;
	bool IsShooting( ) const;

	void SetGravity( bool isDefault );
	void TouchingFloor( );

	void UpdateVelocity( Vector2f& velocity, float elapsedSec );

	void KeyPressEvent( const SDL_KeyboardEvent& e );
	void ProcessMovementData( );

private:
	struct DirectionData
	{
		AimDirection direction;
		bool facingRight;
	};

	KeysState m_KeysStates;

	DirectionData m_DirectionData;
	MovementType m_MovementType;

	bool m_IsShooting;

	bool m_IsDashing;
	float m_DashingAccumulatedTime;
	float m_DashingCooldownAccumulatedTime;

	bool m_IsAirborne;
	float m_AirborneAccumulatedTime;

	bool m_IsGravityReversed;
	Vector2f m_VelocityModifiers;

	DirectionData CalculateAimDirection( ) const;
	MovementType CalculateMovementType( ) const;
	void SetMovementType( MovementType movement );
	void SetDirectionData( DirectionData data, MovementType movement );
};

enum class MovementManager::AimDirection
{
	none,
	up,
	down,
	straight,
	diagonalup,
	diagonaldown
};

enum class MovementManager::MovementType
{
	idle,
	aim,
	run,
	jump,
	parry,
	dashGround,
	dashAir,
	duck
};
