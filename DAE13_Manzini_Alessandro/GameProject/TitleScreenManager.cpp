#include "pch.h"
#include "TitleScreenManager.h"
#include "ResourcesLinker.h"
#include "Texture2D.h"

TitleScreenManager::TitleScreenManager( const Rectf& bounds )
	: ScreenManager( bounds )
	, m_StartText{ Point2f{ bounds.width/2, 440.f }, "START", ResourcesLinker::GetFontPath(), smk_HeadingTextSize, smk_DefaultColor }
	, m_ControlsText{ Point2f{ bounds.width / 2, 400.f }, "CONTROLS", ResourcesLinker::GetFontPath( ), smk_HeadingTextSize, smk_DefaultColor }
	, m_ExitText{ Point2f{ bounds.width / 2, 360.f }, "EXIT", ResourcesLinker::GetFontPath( ), smk_HeadingTextSize, smk_DefaultColor }
	, m_IsOptionSelected{}
{
	SelectOption( TitleOptions::start );
}	  

void TitleScreenManager::Draw( ) const
{
	m_pTitleScreenTexture->Draw( );

	m_StartText.Draw( );
	m_ControlsText.Draw( );
	m_ExitText.Draw( );

	if ( m_IsOptionSelected )
	{
		Draw( m_SelectedOption );
	}
}

void TitleScreenManager::Draw( TitleOptions option ) const
{
	switch ( option )
	{
	case TitleScreenManager::TitleOptions::start:
		m_pTitleScreenTexture->Draw( );
		break;
	case TitleScreenManager::TitleOptions::controls:
		m_pControlsScreenTexture->Draw( );
		break;
	}
}

void TitleScreenManager::Update( float elapsedSec )
{
}

void TitleScreenManager::KeyDownEvent( const SDL_KeyboardEvent& e )
{
	if( !m_IsOptionSelected )
	{
		switch ( e.keysym.sym )
		{
		case SDLK_UP:
			PreviousOption( );
			break;
		case SDLK_DOWN:
			NextOption( );
			break;
		case SDLK_RETURN:
			m_IsOptionSelected = true;
			break;
		}
	}
	else
	{
		switch ( e.keysym.sym )
		{
		case SDLK_ESCAPE:
		case SDLK_q:
			m_IsOptionSelected = false;
			break;
		}
	}
}

void TitleScreenManager::NextOption( ) noexcept
{
	const int optionsCount{ static_cast<int>( TitleOptions::exit ) + 1 };
	SelectOption( static_cast<TitleOptions>((static_cast<int>(m_SelectedOption) + 1) % optionsCount) );
}

void TitleScreenManager::PreviousOption( ) noexcept
{
	const int option{ static_cast<int>(m_SelectedOption) - 1 };
	if ( option < 0 )
	{
		SelectOption( TitleOptions::exit );
	}
	else
	{
		SelectOption( static_cast<TitleOptions>( option ) );
	}
}

bool TitleScreenManager::IsOptionSelected( TitleOptions& option ) const noexcept
{
	if ( m_IsOptionSelected )
	{
		option = m_SelectedOption;
		return true;
	}
	return false;
}

void TitleScreenManager::Clear( ) noexcept
{
	m_IsOptionSelected = false;
}

void TitleScreenManager::LinkTexture( ResourcesLinker* pResourcesLinker )
{
	m_pTitleScreenTexture = pResourcesLinker->GetTexture( "title_screen" );
	m_pControlsScreenTexture = pResourcesLinker->GetTexture( "controls_screen" );
}

void TitleScreenManager::SelectOption( TitleOptions option )
{
	if ( m_SelectedOption == option ) return;

	SetColor( m_SelectedOption, smk_DefaultColor );
	SetColor( option, smk_ActiveColor );

	m_SelectedOption = option;
}

void TitleScreenManager::SetColor( TitleOptions option, const Color4f& color )
{
	switch ( option )
	{
	case TitleScreenManager::TitleOptions::start:
		m_StartText.SetColor( color );
		break;
	case TitleScreenManager::TitleOptions::controls:
		m_ControlsText.SetColor( color );
		break;
	case TitleScreenManager::TitleOptions::exit:
		m_ExitText.SetColor( color );
		break;
	}
}
