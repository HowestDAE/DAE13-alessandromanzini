#pragma once
#include "vector"
#include "CollisionCircle.h"

class Constants
{
public:
	static const float sk_ScreenFXFrameDelay;

	static const Point2f sk_HUD_HP_Position;
	static const Point2f sk_HUD_Excards_Position;

	static const Point2f sk_CupheadStartingPosition;

	static const int sk_CupheadStartingHP;
	static const float sk_CupheadIFramesDuration;

	static const float sk_CupheadRunSpeed;
	static const float sk_CupheadJumpSpeed;
	static const float sk_CupheadDashSpeed;
	static const float sk_CupheadDashTime;
	static const float sk_CupheadDashCooldownTime;
	static const float sk_CupheadExPushBackSpeed;
	static const float sk_CupheadGhostSpeed;

	static const int sk_ExMovesLimit;

	static const int sk_ToyduckStartingHP;
	static const float sk_ToyduckSpeed;

	static const int sk_ToycarStartingHP;
	static const float sk_ToycarSpeed;

	static const float sk_GravityPullSpeed;
	static const float sk_GravityPullAcceleration;

	static const float sk_ProjectileSpeed;

	static const int sk_PeashooterCount;
	static const int sk_PeashooterDamage;
	static const float sk_PeashooterRange;
	static const float sk_PeashooterExProgressPerHit;

	static const int sk_PeashooterExCount;
	static const int sk_PeashooterExHP;
	static const int sk_PeashooterExDamage;
	static const float sk_PeashooterExRange;

	static const int sk_SpreadCount;
	static const int sk_SpreadDamage;
	static const float sk_SpreadRange;
	static const float sk_SpreadExProgressPerHit;

	static const int sk_SpreadExCount;
	static const int sk_SpreadExHP;
	static const int sk_SpreadExDamage;
	static const float sk_SpreadExRange;

	static const float sk_CupheadFlashDuration;
	static const float sk_DefaultFlashDuration;
};

