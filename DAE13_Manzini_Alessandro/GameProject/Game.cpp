#include "pch.h"
#include "Game.h"
#include "iostream"
#include "Texture2D.h"
#include "VectorSprite.h"

Game::Game( const Window& window ) 
	: BaseGame{ window }
	, m_GameState{ GameState::title }
	, m_pStageManager{}
{
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	m_pResourcesLinker = new ResourcesLinker( );
	m_pCamera = new Camera( GetViewPort( ) );

	m_pTitleScreenManager = new TitleScreenManager( GetViewPort( ) );
	m_pTitleScreenManager->LinkTexture( m_pResourcesLinker );

	//m_pScreenFXTexture = m_pResourcesLinker->GetScreenFXTexture( );
}

void Game::InitializeGameResources( )
{
	m_pStageManager = new StageManager( m_pCamera, m_pResourcesLinker ); // Association1 + Aggregation
	m_pCamera->SetStageManager( m_pStageManager ); // Association2
}

void Game::Cleanup( )
{
	CleanupGameResources( true );

	delete m_pResourcesLinker;
	delete m_pCamera;

	delete m_pTitleScreenManager;

	m_pResourcesLinker = nullptr;
	m_pCamera = nullptr;

	m_pTitleScreenManager = nullptr;
}

void Game::CleanupGameResources( bool deepClean )
{
	m_pResourcesLinker->ClearInstantiated( );
	if ( !deepClean )
	{
		m_pTitleScreenManager->LinkTexture( m_pResourcesLinker );
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
		m_pTitleScreenManager->Update( elapsedSec );
		ProcessTitleManagerState( );
		break;
	case GameState::stage:
		m_pStageManager->Update( elapsedSec );
		m_pCamera->Update( elapsedSec );
		break;
	}

	//m_pScreenFXTexture->Update( elapsedSec );
}

void Game::Draw( ) const
{
	switch ( m_GameState )
	{
	case GameState::title:
		m_pTitleScreenManager->Draw( );
		break;
	//case GameState::starting:
	case GameState::stage:
		m_pCamera->Draw( );
		if ( m_pStageManager->GetIsHalted( ) )
		{
			m_pTitleScreenManager->Draw( TitleScreenManager::TitleOptions::controls );
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
		m_pTitleScreenManager->KeyDownEvent( e );
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

void Game::ProcessTitleManagerState( )
{
	TitleScreenManager::TitleOptions option;
	if ( m_pTitleScreenManager->IsOptionSelected( option ) )
	{
		switch ( option )
		{
		case TitleScreenManager::TitleOptions::start:
			StartGame( );
			m_pTitleScreenManager->Clear( );
			break;
		case TitleScreenManager::TitleOptions::exit:
			m_pTitleScreenManager->Clear( );
			break;
		default:
			break;
		}
	}
}
