#pragma once
#include "CollisionCircle.h"

struct ProjectileSettings
{
	int initialCount;
	int hp;
	int damage;
	float speed; 
	float range; 
	CollisionCircle collisionCircle;
};

