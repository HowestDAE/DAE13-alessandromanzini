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

		void Fix( MovementType movement, const DirectionData& previous );
	};

	static const float smk_CupheadRunSpeed;
	static const float smk_CupheadJumpSpeed;
	static const float smk_CupheadDashSpeed;
	static const float smk_CupheadDashTime;
	static const float smk_CupheadDashCooldownTime;

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

	DirectionData CalculateAimDirection( DirectionData previous );
	MovementType CalculateMovementType( MovementType previous );
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
	dashGround,
	dashAir,
	duck
};
