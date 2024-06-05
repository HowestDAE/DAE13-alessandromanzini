#include "pch.h"
#include "WinningScreenManager.h"
#include "ResourcesLinker.h"
#include "Pattern.h"
#include "Sprite.h"
#include "string_manip.cpp"
#include "SoundManager.h"

WinningScreenManager::WinningScreenManager( const std::string& fontPath, const Rectf& viewport )
	: ScreenManager( viewport )
	, m_TimeText{ Point2f{ 610.f, 400.f }, "0.00", fontPath, smk_LargeTextSize, smk_ActiveColor }
	, m_CoinsText{ Point2f{ 610.f, 350.f }, "0/0", fontPath, smk_LargeTextSize, smk_ActiveColor }
	, m_GradeText{ Point2f{ 610.f, 170.f }, "D", fontPath, smk_LargeTextSize, smk_ActiveColor }

	, m_CupheadText{ Point2f{ 300.f, 80.f }, "CUPHEAD", fontPath, smk_MediumTextSize, smk_ActiveColor }
	, m_ContinueText{ Point2f{ 1050.f, 50.f }, "Press ENTER to continue...", fontPath, smk_SmallTextSize, smk_ActiveColor }

	, m_BackgroundAngle{}
	, mk_BackgroundRotationSpeed{ 10.f }

	, m_ReturnToTitleScreen{}
{
}

void WinningScreenManager::Draw( ) const
{
	const Point2f middlePoint{ mk_ViewPort.width / 2.f, mk_ViewPort.height / 2.f };
	m_pBackgroundPattern->Draw( middlePoint, m_BackgroundAngle, true );
	m_pBoardPattern->Draw( Point2f{ 500.f, 60.f } );

	m_pResultsSprite->Draw( Point2f{ middlePoint.x - m_pResultsSprite->GetWidth( ) / 2.f, 545.f } );
	m_pCupheadSprite->Draw( Point2f{ 150.f, 100.f } );

	m_TimeText.Draw( false );
	m_CoinsText.Draw( false );
	m_GradeText.Draw( false );

	m_CupheadText.Draw( );
	m_ContinueText.Draw( );

	m_pIrisTransition->Draw( Point2f{ 0.f, 0.f } );
}

void WinningScreenManager::Update( float elapsedSec )
{
	m_pResultsSprite->Update( elapsedSec );
	m_pCupheadSprite->Update( elapsedSec );

	m_pIrisTransition->Update( elapsedSec );

	m_BackgroundAngle += mk_BackgroundRotationSpeed * elapsedSec;
}

void WinningScreenManager::Initialize( )
{
	m_ReturnToTitleScreen = false;
	SoundManager::Loop( "victory_tune" );
}

void WinningScreenManager::SetStatistics( const GameStats& gameStats )
{
	m_TimeText.SetText( fillString( "TIME", stringifyTime( gameStats.time ), '.', 30 ) );
	m_CoinsText.SetText( fillString( "GOLD COINS", std::to_string( gameStats.collectedCoins ) + "/" + std::to_string( gameStats.totalCoins ), '.', 21 ) );
	m_GradeText.SetText( fillString( "GRADE", gameStats.grade, '.', 28 ) );
}

bool WinningScreenManager::GetReturnToTileScreen( ) const
{
	return m_ReturnToTitleScreen;
}

void WinningScreenManager::KeyDownEvent( const SDL_KeyboardEvent& e )
{
	switch ( e.keysym.sym )
	{
	case SDLK_RETURN:
		SoundManager::Loop( "victory_tune", true );
		m_ReturnToTitleScreen = true;
		break;
	}
}

void WinningScreenManager::LinkTexture( ResourcesLinker* pResourcesLinker )
{
	m_pBackgroundPattern = pResourcesLinker->GetPattern( "winscreen_bg" );
	m_pBoardPattern = pResourcesLinker->GetPattern( "winscreen_board" );

	m_pResultsSprite = pResourcesLinker->GetSprite( "winscreen_results" );
	m_pCupheadSprite = pResourcesLinker->GetSprite( "winscreen_cuphead" );

	m_pIrisTransition = pResourcesLinker->GetSprite( "iris_transition" );
}
