#include "pch.h"
#include "Game.h"
#include "iostream"
#include "Texture2D.h"
#include "VectorSprite.h"

Game::Game( const Window& window ) 
	: BaseGame{ window }
	, m_GameState{ GameState::title }
	, m_ResourcesLinker{}
	, m_Camera{ GetViewPort( ) }
	, m_pStageManager{}
	, m_TitleScreenManager{ GetViewPort( ) }
	, m_pScreenFXTexture{}
{
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	m_TitleScreenManager.LinkTexture( &m_ResourcesLinker );

	//m_pScreenFXTexture = m_pResourcesLinker->GetScreenFXTexture( );
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
		m_TitleScreenManager.Update( elapsedSec );
		ProcessTitleManagerState( );
		break;
	case GameState::stage:
		if ( m_pStageManager->GetRequestTitleScreen( ) )
		{
			TerminateGame( );
			return;
		}
		m_pStageManager->Update( elapsedSec );
		m_Camera.Update( elapsedSec );
		break;
	}

	//m_pScreenFXTexture->Update( elapsedSec );
}

void Game::Draw( ) const
{
	switch ( m_GameState )
	{
	case GameState::title:
		m_TitleScreenManager.Draw( );
		break;
	//case GameState::starting:
	case GameState::stage:
		m_Camera.Draw( );
		if ( m_pStageManager->GetIsHalted( ) )
		{
			m_TitleScreenManager.Draw( TitleScreenManager::TitleOptions::controls );
		}
		break;
	}

	//m_pScreenFXTexture->Draw( GetViewPort() );
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
	std::cout << e.x << " " << e.y << std::endl;
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
	m_GameState = GameState::title;

	CleanupGameResources( );
	m_Camera.Reset( );
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
			break;
		default:
			break;
		}
	}
}
