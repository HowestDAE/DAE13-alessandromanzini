#include "pch.h"
#include "Game.h"
#include "iostream"

Game::Game( const Window& window ) 
	:BaseGame{ window }
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
	m_pStageManager = new StageManager( m_pCamera, m_pResourcesLinker ); // Association1 + Aggregation
	m_pCamera->SetStageManager( m_pStageManager ); // Association2

	m_pStageManager->Start( );
}

void Game::Cleanup( )
{
	delete m_pResourcesLinker;
	delete m_pCamera;
	delete m_pStageManager;

	m_pResourcesLinker = nullptr;
	m_pCamera = nullptr;
	m_pStageManager = nullptr;
}

void Game::Update( float elapsedSec )
{
	m_pStageManager->Update( elapsedSec );
}

void Game::Draw( ) const
{
	ClearBackground( );

	m_pCamera->Draw( );
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	m_pStageManager->KeyPressEvent( e );
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	m_pStageManager->KeyPressEvent( e );
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
	std::cout << e.x << " " << e.y << std::endl;
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}
