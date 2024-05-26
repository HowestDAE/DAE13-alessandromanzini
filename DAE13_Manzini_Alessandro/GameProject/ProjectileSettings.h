#pragma once
#include "CollisionCircle.h"

struct ProjectileSettings final
{
	int initialCount;
	int hp;
	int damage;
	float speed; 
	float range; 
	CollisionCircle collisionCircle;
};

