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
	bool GetIsGravityReversed( ) const;

	bool GetIsTransitioning( ) const;
	bool GetIsIFraming( ) const;

	bool GetIsShooting( ) const;
	bool GetIsExMove( ) const;

	float GetAimAngle( ) const;

	bool GetIsParrying( ) const;

	bool GetSwapWeapons( ) const;

	void SetExingState( bool isExing );
	void ToggleGravity( );

	void PlatformCollisionFeedback( );
	void VerticalBoundsCollisionFeedback( );
	void ParryCollisionFeedback( );

	void Update( float elapsedSec );
	void UpdateVelocity( Vector2f& velocity, float elapsedSec );

	void KeyPressEvent( const SDL_KeyboardEvent& e );

	void Reset( );

private:
	const static float smk_InputDelay;

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
	bool m_IsExMoveRequested;
	bool m_IsExMoving;
	float m_AimAngle;

	bool m_IsDashing;
	float m_DashingAccumulatedTime;
	float m_DashingCooldownAccumulatedTime;

	bool m_IsAirborne;
	float m_AirborneAccumulatedTime;
	const static float smk_ToAirborneTime;

	bool m_IsParrying;
	bool m_IsParried;

	bool m_IsMoving;

	bool m_IsGravityReversing;
	float m_GravityReversingAccumulatedTime;
	bool m_IsGravityReversed;
	Vector2f m_VelocityModifiers;
	int m_GravityNormal;

	bool m_IsParryIFraming;
	float m_ParryIFramingElapsedTime;

	bool m_IsPropelled;
	bool m_IsPropelling;
	float m_PropelledAccumulatedTime;

	bool m_SwapWeaponsRequested;
	float m_SwapWeaponsAccumulatedTime;

	void DefineState( );
	void UpdateState( float elapsedSec );

	void ProcessMovementData( );

	DirectionData CalculateAimDirection( ) const;
	MovementType CalculateMovementType( ) const;
	float CalculateAimAngle( ) const;
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
	duck,
	exGround,
	exAir
};
