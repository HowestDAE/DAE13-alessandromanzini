#pragma once
#include "ScreenManager.h"
#include "StringTexture.h"
#include "GameStats.h"
class ResourcesLinker;
class Texture2D;
class Pattern;
class Sprite;

class WinningScreenManager final
	: public ScreenManager
{
public:
	WinningScreenManager( const std::string& fontPath, const Rectf& viewport );

	virtual void Draw( ) const override;
	virtual void Update( float elapsedSec ) override;

	void Initialize( );
	void SetStatistics( const GameStats& gameStats );

	bool GetReturnToTileScreen( ) const;

	virtual void KeyDownEvent( const SDL_KeyboardEvent& e ) override;

	virtual void LinkTexture( ResourcesLinker* pResourcesLinker ) override;

private:
	Pattern* m_pBackgroundPattern;
	Pattern* m_pBoardPattern;

	Sprite* m_pResultsSprite;
	Sprite* m_pCupheadSprite;

	Sprite* m_pIrisTransition;

	StringTexture m_TimeText;
	StringTexture m_CoinsText;
	StringTexture m_GradeText;

	StringTexture m_CupheadText;
	StringTexture m_ContinueText;

	float m_BackgroundAngle;
	const float mk_BackgroundRotationSpeed;

	bool m_ReturnToTitleScreen;

};

