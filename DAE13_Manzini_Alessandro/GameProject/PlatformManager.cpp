#include "pch.h"
#include "PlatformManager.h"
#include "Cuphead.h"
#include "Constants.h"

void PlatformManager::CheckCollision( Cuphead* pCuphead )
{
	const Point2f position{ pCuphead->GetPosition( ) };
	if ( position.y < Constants::sk_CupheadStartingPosition.y )
	{
		pCuphead->ProcessPlatformCollision( Vector2f{ 0.f, Constants::sk_CupheadStartingPosition.y - position.y } );
	}
}
