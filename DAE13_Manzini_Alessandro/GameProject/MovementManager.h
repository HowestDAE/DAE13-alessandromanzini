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
	bool GetIsFacingRight( ) const;

	bool GetIsTransitioning( ) const;

	bool GetIsShooting( ) const;

	void SetGravity( bool isDefault );
	void TouchingFloor( );

	void Update( float elapsedSec );
	void UpdateVelocity( Vector2f& velocity, float elapsedSec );

	void KeyPressEvent( const SDL_KeyboardEvent& e );

	void Reset( );

private:
	struct DirectionData
	{
		AimDirection direction;
		bool facingRight;
	};

	KeysState m_KeysStates;

	DirectionData m_DirectionData;
	MovementType m_MovementType;

	bool m_IsTransitioning;

	bool m_IsShooting;

	bool m_IsDashing;
	float m_DashingAccumulatedTime;
	float m_DashingCooldownAccumulatedTime;

	bool m_IsAirborne;
	float m_AirborneAccumulatedTime;

	bool m_IsParrying;

	bool m_IsMoving;

	bool m_IsGravityReversed;
	Vector2f m_VelocityModifiers;

	void DefineState( );
	void UpdateState( float elapsedSec );

	void ProcessMovementData( );

	DirectionData CalculateAimDirection( ) const;
	MovementType CalculateMovementType( ) const;
	void AdjustMovementData( DirectionData& data, MovementType& movement );
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
