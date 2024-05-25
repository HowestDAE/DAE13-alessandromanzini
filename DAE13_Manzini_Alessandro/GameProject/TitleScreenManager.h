#pragma once
#include "StringTexture.h"
class ResourcesLinker;
class Texture2D;

class TitleScreenManager final
{
public:
	enum class TitleOptions;

	explicit TitleScreenManager( const Rectf& bounds );

	void Draw( ) const;
	void Draw( TitleOptions option ) const;
	void Update( float elapsedSec );

	void KeyDownEvent( const SDL_KeyboardEvent& e );

	bool IsOptionSelected( TitleOptions& option ) const noexcept;
	void Clear( ) noexcept;

	void LinkTexture( ResourcesLinker* pResourcesLinker );

private:
	static const int smk_TextSize;
	static const Color4f smk_DefaultColor;
	static const Color4f smk_ActiveColor;

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
