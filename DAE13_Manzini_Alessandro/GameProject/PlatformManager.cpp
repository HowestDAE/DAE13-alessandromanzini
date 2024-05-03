#include "pch.h"
#include "PlatformManager.h"
#include "Entity.h"
#include "Constants.h"

Vector2f PlatformManager::GetDisplacementFromPlatform( Entity* pEntity ) const
{
	const Vector2f location{ pEntity->GetLocation( ) };
	Vector2f displacement{};

	if ( location.y < Constants::sk_CupheadStartingPosition.y )
	{
		displacement = Vector2f{ 0.f, Constants::sk_CupheadStartingPosition.y - location.y };
	}

	return displacement;
}
