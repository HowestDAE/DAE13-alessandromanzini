#include "pch.h"
#include "HUDManager.h"
#include "Constants.h"
#include "ResourcesLinker.h"
#include "Texture2D.h"

HUDManager::HUDManager( )
	: m_pHPTextures{}
	, m_HPIndex{}
{
}

void HUDManager::Draw( ) const
{
	m_pHPTextures[m_HPIndex]->Draw(Constants::sk_HUD_HP_Position);
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

void HUDManager::LinkTexture( ResourcesLinker* pResourceLinker )
{
	m_pHPTextures.push_back( pResourceLinker->GetTexture( "hud_hp_dead" ) );
	m_pHPTextures.push_back( pResourceLinker->GetTexture( "hud_hp_1" ) );
	m_pHPTextures.push_back( pResourceLinker->GetTexture( "hud_hp_2" ) );
	m_pHPTextures.push_back( pResourceLinker->GetTexture( "hud_hp_3" ) );
}
