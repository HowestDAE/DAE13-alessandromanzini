#pragma once
#include "vector"
class ResourcesLinker;
class Texture2D;

class HUDManager
{
public:
	HUDManager( );

	void Draw( ) const;
	void Update( float elapsedSec );

	void SetHP( int hp );

	void LinkTexture( ResourcesLinker* pResourceLinker );

private:
	std::vector<Texture2D*> m_pHPTextures;
	int m_HPIndex;
};

