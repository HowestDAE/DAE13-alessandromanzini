#pragma once
#include "ScreenManager.h"
#include "StringTexture.h"
class ResourcesLinker;
class Texture2D;

class TitleScreenManager final
	: public ScreenManager
{
public:
	enum class TitleOptions;

	explicit TitleScreenManager( const Rectf& bounds );

	virtual void Draw( ) const override;
	void Draw( TitleOptions option ) const;
	virtual void Update( float elapsedSec ) override;

	virtual void KeyDownEvent( const SDL_KeyboardEvent& e ) override;

	bool IsOptionSelected( TitleOptions& option ) const noexcept;
	void Clear( ) noexcept;

	virtual void LinkTexture( ResourcesLinker* pResourcesLinker ) override;

private:
	Texture2D* m_pTitleScreenTexture;
	Texture2D* m_pControlsScreenTexture;

	TitleOptions m_SelectedOption;
	StringTexture m_StartText;
	StringTexture m_ControlsText;
	StringTexture m_ExitText;

	bool m_IsOptionSelected;

	void SelectOption( TitleOptions option );
	void NextOption( ) noexcept;
	void PreviousOption( ) noexcept;
	void SetColor( TitleOptions option, const Color4f& color );

};

enum class TitleScreenManager::TitleOptions
{
	start,
	controls,
	exit
};
