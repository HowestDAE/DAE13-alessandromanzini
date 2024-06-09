#pragma once
#include <vector>
#include <unordered_map>
#include "Weapon.h"
class ResourcesLinker;
class Texture2D;
class Pattern;

class HUDManager final
{
public:
	HUDManager( );

	void Draw( ) const;
	void Update( float elapsedSec );

	void SetHP( int hp );
	void SetEx( int count, float progress );

	void SwapWeapon( Weapon::WeaponType weaponType );

	void LinkTexture( ResourcesLinker* pResourceLinker );

private:
	std::vector<Texture2D*> m_pHPTextures;
	int m_HPIndex;

	const static float smk_WeaponIconTransitionTime;
	const static float smk_WeaponIconHoldTime;
	std::unordered_map<Weapon::WeaponType, Pattern*> m_pWeaponIconPatterns;
	bool m_SwappingWeapon;
	int m_TransitionNormal;
	float m_WeaponIconTransitionAccumulatedTime;
	Point2f m_WeaponIconPosition;
	Weapon::WeaponType m_TargetWeaponType;
	
	Pattern* m_pExcardFaceupPattern;
	Pattern* m_pExcardFacedownPattern;
	int m_ExCount;
	float m_ExProgress;

	void UpdateWeaponIconTransition( float elapsedSec );
};

