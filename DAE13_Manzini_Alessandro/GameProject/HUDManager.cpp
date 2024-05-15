#include "pch.h"
#include "HUDManager.h"
#include "Constants.h"
#include "ResourcesLinker.h"
#include "Texture2D.h"
#include "Pattern.h"

HUDManager::HUDManager( )
	: m_pHPTextures{}
	, m_HPIndex{}
	, m_pExcardFaceupPattern{}
	, m_pExcardFacedownPattern{}
	, m_ExCount{}
	, m_ExProgress{}
{
}

void HUDManager::Draw( ) const
{
	m_pHPTextures[m_HPIndex]->Draw(Constants::sk_HUD_HP_Position);

	{
		const float margin{ 5.f };
		Vector2f cardsOffset{};
		for ( int i{}; i < m_ExCount; ++i )
		{
			m_pExcardFaceupPattern->Draw( Constants::sk_HUD_Excards_Position + cardsOffset );
			cardsOffset.x += m_pExcardFaceupPattern->GetWidth( ) + margin;
		}
		m_pExcardFacedownPattern->Draw( Constants::sk_HUD_Excards_Position + cardsOffset, m_ExProgress );
	}
}

void HUDManager::Update( float elapsedSec )
{
	m_pHPTextures[m_HPIndex]->Update( elapsedSec );
}

void HUDManager::SetHP( int hp )
{
	const int maxHP{ 3 }, minHP{ 0 };
	if ( hp > maxHP )
	{
		hp = maxHP;
	}
	else if ( hp < minHP )
	{
		hp = minHP;
	}
	m_HPIndex = hp;
}

void HUDManager::SetEx( int count, float progress )
{
	m_ExCount = count;
	m_ExProgress = progress;
}

void HUDManager::LinkTexture( ResourcesLinker* pResourceLinker )
{
	m_pHPTextures.push_back( pResourceLinker->GetTexture( "hud_hp_dead" ) );
	m_pHPTextures.push_back( pResourceLinker->GetTexture( "hud_hp_1" ) );
	m_pHPTextures.push_back( pResourceLinker->GetTexture( "hud_hp_2" ) );
	m_pHPTextures.push_back( pResourceLinker->GetTexture( "hud_hp_3" ) );

	m_pExcardFaceupPattern = pResourceLinker->GetPattern( "excard_faceup" );
	m_pExcardFacedownPattern = pResourceLinker->GetPattern( "excard_facedown" );
}
