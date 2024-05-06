#include "pch.h"
#include "Constants.h"

const Point2f Constants::sk_HUD_HP_Position{ 20.f, 20.f };

const Point2f Constants::sk_CupheadStartingPosition{ 285.f, 100.f }; // 285, 100

const int Constants::sk_CupheadStartingHP{ 1 };
const float Constants::sk_CupheadIFramesDuration{ 3.f };

const float Constants::sk_CupheadJumpSpeed{ 1000.f }; // 1000
const float Constants::sk_CupheadRunSpeed{ 370.f }; // 370
const float Constants::sk_CupheadDashSpeed{ 800.f }; // 800
const float Constants::sk_CupheadDashTime{ .3f };
const float Constants::sk_CupheadDashCooldownTime{ .5f };
const float Constants::sk_CupheadGhostSpeed{ 200.f };

const int Constants::sk_ToyduckStartingHP{ 200 };
const float Constants::sk_ToyduckSpeed{ 100.f };

const float Constants::sk_GravityPullSpeed{ 1000.f }; // 1000
const float Constants::sk_GravityPullAcceleration{ 90.f }; // 90

const float Constants::sk_ProjectileSpeed{ 1050.f }; // 1050

const int Constants::sk_PeashooterCount{ 24 };
const int Constants::sk_PeashooterDamage{ 40 };
const float Constants::sk_PeashooterRange{ 1000.f };

const int Constants::sk_SpreadCount{ 12 };
const int Constants::sk_SpreadDamage{ 4 };
const float Constants::sk_SpreadRange{ 200.f };

const float Constants::sk_DefaultFlashDuration{ .08f };
const float Constants::sk_CupheadFlashDuration{ .09f };