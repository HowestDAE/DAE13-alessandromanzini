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

	std::string loopTextureUid;
	std::string deathTextureUid;
	std::string spawnAudioUid;
	std::string hitAudioUid;
};

