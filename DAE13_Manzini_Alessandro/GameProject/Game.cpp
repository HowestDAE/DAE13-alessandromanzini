#include "pch.h"
#include "Game.h"
#include "iostream"
#include "GameStats.h"
#include "Texture2D.h"
#include "VectorSprite.h"
#include "SoundManager.h"

Game::Game( const Window& window ) 
	: BaseGame{ window }
	, m_GameState{ GameState::title }
	, m_ResourcesLinker{}
	, m_Camera{ GetViewPort( ) }
	, m_pStageManager{}
	, m_TitleScreenManager{ GetViewPort( ) }
	, m_pWinningScreenManager{}
	, m_pScreenFXTexture{}
{
	Initialize();
	m_pWinningScreenManager->LinkTexture( &m_ResourcesLinker );
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	m_TitleScreenManager.LinkTexture( &m_ResourcesLinker );
	
	SoundManager::LinkResources( &m_ResourcesLinker );

	m_pWinningScreenManager = new WinningScreenManager( m_ResourcesLinker.GetLightFontPath( ), GetViewPort( ) );

	m_pScreenFXTexture = m_ResourcesLinker.GetScreenFXTexture( );
}

void Game::InitializeGameResources( )
{
	m_pStageManager = new StageManager( &m_Camera, &m_ResourcesLinker ); // Association1 + Aggregation
	m_Camera.SetStageManager( m_pStageManager ); // Association2
}

void Game::Cleanup( )
{
	CleanupGameResources( true );
}

void Game::CleanupGameResources( bool deepClean )
{
	m_ResourcesLinker.ClearInstantiated( );
	if ( !deepClean )
	{
		m_TitleScreenManager.LinkTexture( &m_ResourcesLinker );
	}
	else
	{
		delete m_pWinningScreenManager;
	}

	if ( m_pStageManager )
	{
		delete m_pStageManager;
		m_pStageManager = nullptr;
	}
}

void Game::Update( float elapsedSec )
{
	switch ( m_GameState )
	{
	case GameState::title:
		UpdateTitleState( elapsedSec );
		break;

	case GameState::stage:
		UpdateStageState( elapsedSec );
		break;
		
	case GameState::success:
		UpdateSuccessState( elapsedSec );
		break;
	}

	m_pScreenFXTexture->Update( elapsedSec );
}

void Game::Draw( ) const
{
	switch ( m_GameState )
	{
	case GameState::title:
		m_TitleScreenManager.Draw( );
		break;

	case GameState::stage:
		m_Camera.Draw( );
		if ( m_pStageManager->GetIsHalted( ) )
		{
			m_TitleScreenManager.Draw( TitleScreenManager::TitleOptions::controls );
		}
		break;

	case GameState::success:
		m_pWinningScreenManager->Draw( );
		break;
	}

	m_pScreenFXTexture->Draw( GetViewPort() );
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	switch ( m_GameState )
	{
	case GameState::title:
		m_TitleScreenManager.KeyDownEvent( e );
		break;
	case GameState::stage:
		m_pStageManager->KeyPressEvent( e );
		break;
	case GameState::success:
		m_pWinningScreenManager->KeyDownEvent( e );
		break;
	}
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	switch ( m_GameState )
	{
	case GameState::stage:
		m_pStageManager->KeyPressEvent( e );
		break;
	}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	const Point2f cursorPos{ Point2f{ float(e.x), float(e.y) } + m_Camera.GetCameraLocation( ) };
	std::cout << "[GAME] Click event. Camera cursor at (" << cursorPos.x << ", " << cursorPos.y << ")" << std::endl;
	std::cout << "[GAME] Click event. Cursor at (" << e.x << ", " << e.y << ")" << std::endl << std::endl;
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::StartGame( )
{
	m_GameState = GameState::stage;

	InitializeGameResources( );
	m_pStageManager->Start( );
}

void Game::TerminateGame( )
{
	SoundManager::Reset( );

	CleanupGameResources( );
	m_Camera.Reset( );

	m_pScreenFXTexture = m_ResourcesLinker.GetScreenFXTexture( );
}

void Game::UpdateTitleState( float elapsedSec )
{
	m_TitleScreenManager.Update( elapsedSec );
	ProcessTitleManagerState( );
}

void Game::UpdateStageState( float elapsedSec )
{
	if ( m_pStageManager->GetRequestTitleScreen( ) )
	{
		m_GameState = GameState::title;
		TerminateGame( );
		return;
	}

	GameStats gameStats{};
	if ( m_pStageManager->GetRequestWinScreen( gameStats ) )
	{
		m_GameState = GameState::success;
		m_pWinningScreenManager->SetStatistics( gameStats );
		TerminateGame( );
		m_pWinningScreenManager->Initialize( );
		m_pWinningScreenManager->LinkTexture( &m_ResourcesLinker );
		return;
	}

	m_pStageManager->Update( elapsedSec );
	m_Camera.Update( elapsedSec );
}

void Game::UpdateSuccessState( float elapsedSec )
{
	m_pWinningScreenManager->Update( elapsedSec );

	if ( m_pWinningScreenManager->GetReturnToTileScreen( ) )
	{
		m_GameState = GameState::title;
	}
}

void Game::ProcessTitleManagerState( )
{
	TitleScreenManager::TitleOptions option;
	if ( m_TitleScreenManager.IsOptionSelected( option ) )
	{
		switch ( option )
		{
		case TitleScreenManager::TitleOptions::start:
			StartGame( );
			m_TitleScreenManager.Clear( );
			break;
		case TitleScreenManager::TitleOptions::exit:
			m_TitleScreenManager.Clear( );
			RequestQuit( );
			break;
		default:
			break;
		}
	}
}
