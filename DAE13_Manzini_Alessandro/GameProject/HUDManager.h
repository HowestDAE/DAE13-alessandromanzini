#pragma once
#include "vector"
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

	void LinkTexture( ResourcesLinker* pResourceLinker );

private:
	std::vector<Texture2D*> m_pHPTextures;
	int m_HPIndex;
	
	Pattern* m_pExcardFaceupPattern;
	Pattern* m_pExcardFacedownPattern;
	int m_ExCount;
	float m_ExProgress;
};

