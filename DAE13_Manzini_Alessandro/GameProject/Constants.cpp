#include "pch.h"
#include "Constants.h"

const Point2f Constants::sk_CupheadStartingPosition{ 285.f, 100.f }; // 285, 100

const float Constants::sk_CupheadJumpSpeed{ 1000.f };
const float Constants::sk_CupheadRunSpeed{ 370.f }; // 370
const float Constants::sk_CupheadDashSpeed{ 700.f };
const float Constants::sk_CupheadDashTime{ .3f };
const float Constants::sk_CupheadDashCooldownTime{ .5f };

const float Constants::sk_ToyduckSpeed{ 100.f };

const float Constants::sk_GravityPullSpeed{ 1000.f }; // 1000
const float Constants::sk_GravityPullAcceleration{ 90.f }; // 90

const float Constants::sk_ProjectileSpeed{ 1050.f }; // 1050

const int Constants::sk_PeashooterCount{ 24 };
const float Constants::sk_PeashooterDamage{ 10.f };
const float Constants::sk_PeashooterRange{ 1000.f };

const int Constants::sk_SpreadCount{ 12 };
const float Constants::sk_SpreadDamage{ 4.f };
const float Constants::sk_SpreadRange{ 200.f };