#include "pch.h"
#include "HUDManager.h"
#include "Constants.h"
#include "ResourcesLinker.h"
#include "Texture2D.h"
#include "Pattern.h"

const float HUDManager::smk_WeaponIconTransitionTime{ .15f };
const float HUDManager::smk_WeaponIconHoldTime{ .5f };

HUDManager::HUDManager( )
	: m_pHPTextures{}
	, m_HPIndex{}
	, m_pWeaponIconPatterns{}
	, m_SwappingWeapon{}
	, m_WeaponIconTransitionAccumulatedTime{}
	, m_TransitionNormal{ 1 }
	, m_TargetWeaponType{}
	, m_pExcardFaceupPattern{}
	, m_pExcardFacedownPattern{}
	, m_ExCount{}
	, m_ExProgress{}
{
}

void HUDManager::Draw( ) const
{
	// Weapon icon transition
	const float transitionRatio{ m_WeaponIconTransitionAccumulatedTime / smk_WeaponIconTransitionTime };
	m_pWeaponIconPatterns.at(m_TargetWeaponType)->Draw( Constants::sk_HUD_WeaponIcon_Position, transitionRatio );
		
	// HP
	m_pHPTextures[m_HPIndex]->Draw(Constants::sk_HUD_HP_Position);

	{
		// Ex cards
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

	UpdateWeaponIconTransition( elapsedSec );
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

void HUDManager::SwapWeapon( Weapon::WeaponType weaponType )
{
	m_TargetWeaponType = weaponType;
	m_SwappingWeapon = true;
	m_TransitionNormal = 1;
	m_WeaponIconTransitionAccumulatedTime = 0.f;
}

void HUDManager::LinkTexture( ResourcesLinker* pResourceLinker )
{
	m_pHPTextures.push_back( pResourceLinker->GetTexture( "hud_hp_dead" ) );
	m_pHPTextures.push_back( pResourceLinker->GetTexture( "hud_hp_1" ) );
	m_pHPTextures.push_back( pResourceLinker->GetTexture( "hud_hp_2" ) );
	m_pHPTextures.push_back( pResourceLinker->GetTexture( "hud_hp_3" ) );

	m_pExcardFaceupPattern = pResourceLinker->GetPattern( "excard_faceup" );
	m_pExcardFacedownPattern = pResourceLinker->GetPattern( "excard_facedown" );

	m_pWeaponIconPatterns[Weapon::WeaponType::peashooter] = pResourceLinker->GetPattern( "peashooter_icon" );
	m_pWeaponIconPatterns[Weapon::WeaponType::spread] = pResourceLinker->GetPattern( "spread_icon" );
}

void HUDManager::UpdateWeaponIconTransition( float elapsedSec )
{
	if ( m_SwappingWeapon )
	{
		m_WeaponIconTransitionAccumulatedTime += elapsedSec * m_TransitionNormal;

		if( m_WeaponIconTransitionAccumulatedTime < 0.f )
		{
			m_SwappingWeapon = false;
		}
		else if( m_WeaponIconTransitionAccumulatedTime >= smk_WeaponIconTransitionTime + smk_WeaponIconHoldTime )
		{
			m_TransitionNormal = -1;
		}
	}
}
