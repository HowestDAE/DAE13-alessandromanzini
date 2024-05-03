#pragma once
#include "vector"
#include "CollisionCircle.h"

class Constants
{
public:
	static const Point2f sk_HUD_HP_Position;

	static const Point2f sk_CupheadStartingPosition;

	static const int sk_CupheadStartingHP;
	static const float sk_CupheadIFramesDuration;

	static const float sk_CupheadRunSpeed;
	static const float sk_CupheadJumpSpeed;
	static const float sk_CupheadDashSpeed;
	static const float sk_CupheadDashTime;
	static const float sk_CupheadDashCooldownTime;

	static const int sk_ToyduckStartingHP;
	static const float sk_ToyduckSpeed;

	static const float sk_GravityPullSpeed;
	static const float sk_GravityPullAcceleration;

	static const float sk_ProjectileSpeed;

	static const int sk_PeashooterCount;
	static const int sk_PeashooterDamage;
	static const float sk_PeashooterRange;

	static const int sk_SpreadCount;
	static const int sk_SpreadDamage;
	static const float sk_SpreadRange;
};

