#include "pch.h"
#include "ScreenManager.h"

const int ScreenManager::smk_HeadingTextSize{ 30 };
const int ScreenManager::smk_LargeTextSize{ 35 };
const int ScreenManager::smk_MediumTextSize{ 25 };
const int ScreenManager::smk_SmallTextSize{ 20 };
const Color4f ScreenManager::smk_DefaultColor{ 0.48f, 0.48f, 0.44f, 1.f };
const Color4f ScreenManager::smk_ActiveColor{ 1.f, 0.97f, 1.f, 1.f };

ScreenManager::ScreenManager( const Rectf& viewport )
	: mk_ViewPort{ viewport }
{
}
