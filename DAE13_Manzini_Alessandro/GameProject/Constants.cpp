#include "pch.h"
#include "Constants.h"

const float Constants::sk_ScreenFXFrameDelay{ .3f };

const Point2f Constants::sk_HUD_HP_Position{ 20.f, 20.f };
const Point2f Constants::sk_HUD_Excards_Position{ 115.f, 20.f };
const Point2f Constants::sk_HUD_WeaponIcon_Position{ 30.f, 45.f };

const Point2f Constants::sk_CupheadStartingPosition{ 285.f, 100.f }; // 285, 100

const int Constants::sk_CupheadStartingHP{ 3 };
const float Constants::sk_CupheadIFramesDuration{ 3.f };

const float Constants::sk_CupheadJumpSpeed{ 1000.f }; // 1000
const float Constants::sk_CupheadRunSpeed{ 370.f }; // 370
const float Constants::sk_CupheadDashSpeed{ 800.f }; // 800
const float Constants::sk_CupheadDashTime{ .3f };
const float Constants::sk_CupheadDashCooldownTime{ .35f };
const float Constants::sk_CupheadExPushBackSpeed{ 275.f };
const float Constants::sk_CupheadGhostSpeed{ 140.f };
const float Constants::sk_CupheadOutOfBoundsSpeed{ 1400.f };
const float Constants::sk_CupheadPropelledCooldownTime{ .25f };
const float Constants::sk_CupheadGravityReversingTime{ .015f };
const float Constants::sk_CupheadParryIFrameTime{ .6f };

const int Constants::sk_ExMovesLimit{ 5 };

const int Constants::sk_ToyduckStartingHP{ 200 };
const float Constants::sk_ToyduckSpeed{ 125.f };

const float Constants::sk_ToycarSpeed{ 270.f };

const int Constants::sk_FunwallHP{ 8000 }; // 8000
const float Constants::sk_LipSpeed{ 400.f };
const float Constants::sk_TongueIntroSpeed{ 1400.f };
const float Constants::sk_TongueOutroSpeed{	1900.f };

const float Constants::sk_StarblasterProjectileSpeed{ 400.f };
const float Constants::sk_StarblasterProjectileRange{ 300.f };

const int Constants::sk_TubaHP{ 500 }; // 8000
const float Constants::sk_TubaDeathSpeed{ 250.f };
const Vector2f Constants::sk_BwaSpeed{ 1100.f, 400.f };

const float Constants::sk_GravityPullSpeed{ 1000.f }; // 1000
const float Constants::sk_GravityPullAcceleration{ 90.f }; // 90

const float Constants::sk_ProjectileSpeed{ 1050.f }; // 1050

const int Constants::sk_PeashooterCount{ 24 };
const int Constants::sk_PeashooterDamage{ 40 }; // 40
const float Constants::sk_PeashooterRange{ 1000.f };
const float Constants::sk_PeashooterExProgressPerHit{ 1.f / 32 }; // 1.f / 32

const int Constants::sk_PeashooterExCount{ 5 };
const int Constants::sk_PeashooterExHP{ 3 };
const int Constants::sk_PeashooterExDamage{ 100 };
const float Constants::sk_PeashooterExRange{ 1000.f };

const int Constants::sk_SpreadCount{ 12 };
const int Constants::sk_SpreadDamage{ 15 };
const float Constants::sk_SpreadRange{ 200.f };
const float Constants::sk_SpreadExProgressPerHit{ 1.f / 64 };

const int Constants::sk_SpreadExCount{ 18 };
const int Constants::sk_SpreadExHP{ 1 };
const int Constants::sk_SpreadExDamage{ 100 };
const float Constants::sk_SpreadExRange{ 400.f };

const float Constants::sk_DefaultFlashDuration{ .08f };
const float Constants::sk_CupheadFlashDuration{ .075f };