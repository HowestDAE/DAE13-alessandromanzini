#pragma once
#include "Vector2f.h"
class Entity;

class PlatformManager final
{
public:
	PlatformManager( ) = default;

	Vector2f GetDisplacementFromPlatform( Entity* pEntity ) const;

private:
};

