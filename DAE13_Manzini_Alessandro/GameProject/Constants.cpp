#include "pch.h"
#include "Constants.h"

const Point2f Constants::sk_HUD_HP_Position{ 20.f, 20.f };

const Point2f Constants::sk_CupheadStartingPosition{ 285.f, 100.f }; // 285, 100

const std::vector<CollisionCircle> Constants::sk_CupheadDefaultCollisionCircles{ CollisionCircle{ 45.f, 30.f, 30.f }, CollisionCircle{ 45.f, 75.f, 30.f } };
const std::vector<CollisionCircle> Constants::sk_CupheadDuckCollisionCircles{ CollisionCircle{ 45.f, 30.f, 30.f } };
const int Constants::sk_CupheadStartingHP{ 3 };
const float Constants::sk_CupheadIFramesDuration{ 3.f };

const float Constants::sk_CupheadJumpSpeed{ 1000.f }; // 1000
const float Constants::sk_CupheadRunSpeed{ 370.f }; // 370
const float Constants::sk_CupheadDashSpeed{ 800.f }; // 800
const float Constants::sk_CupheadDashTime{ .3f };
const float Constants::sk_CupheadDashCooldownTime{ .5f };

const std::vector<CollisionCircle> Constants::sk_ToyduckCollisionCircles{ CollisionCircle{ 180.f, 130.f, 70.f, false } };
const int Constants::sk_ToyduckStartingHP{ 200 };
const float Constants::sk_ToyduckSpeed{ 100.f };

const float Constants::sk_GravityPullSpeed{ 1000.f }; // 1000
const float Constants::sk_GravityPullAcceleration{ 90.f }; // 90

const float Constants::sk_ProjectileSpeed{ 1050.f }; // 1050

const CollisionCircle Constants::sk_PeashooterCollisionCircle{ 130.f, 0.f, 10.f };
const CollisionCircle Constants::sk_PeashooterExCollisionCircle{};
const int Constants::sk_PeashooterCount{ 24 };
const int Constants::sk_PeashooterDamage{ 10 };
const float Constants::sk_PeashooterRange{ 1000.f };

const CollisionCircle Constants::sk_SpreadCollisionCircle{};
const CollisionCircle Constants::sk_SpreadExCollisionCircle{};
const int Constants::sk_SpreadCount{ 12 };
const int Constants::sk_SpreadDamage{ 4 };
const float Constants::sk_SpreadRange{ 200.f };