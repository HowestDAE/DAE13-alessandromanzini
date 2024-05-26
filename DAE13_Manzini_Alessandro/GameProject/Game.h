#pragma once
#include "BaseGame.h"
#include "ResourcesLinker.h"
#include "Camera.h"
#include "StageManager.h"
#include "TitleScreenManager.h"

enum class GameState;

class Game : public BaseGame
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update( float elapsedSec ) override;
	void Draw( ) const override;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;

private:
	GameState m_GameState;

	ResourcesLinker m_ResourcesLinker;
	Camera m_Camera;
	StageManager* m_pStageManager;

	TitleScreenManager m_TitleScreenManager;

	VectorSprite* m_pScreenFXTexture;

	// FUNCTIONS
	void Initialize();
	void InitializeGameResources( );
	void Cleanup( );
	void CleanupGameResources( bool deepClean = false );
	void ClearBackground( ) const;

	void StartGame( );
	void TerminateGame( );

	void ProcessTitleManagerState( );
};

enum class GameState
{
	title,
	stage,
	success
};