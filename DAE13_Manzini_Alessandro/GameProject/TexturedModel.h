#pragma once
#include "ResourcesLinker.h"
#include "TextureInfo.h"
#include "Vector2f.h"
class Texture2D;

class TexturedModel
{
public:
	TexturedModel( const Point2f& position );

	Vector2f GetLocation( ) const;

	float GetTextureWidth( ) const;
	float GetTextureHeight( ) const;

	virtual void Draw( ) const;
	virtual void Update( float elapsedSec ) = 0;

	void DrawTextureOutline( ) const;

	virtual void LinkTexture( ResourcesLinker* pResourceLinker ) = 0;

protected:
	Vector2f m_Location;
	TextureInfo m_TextureInfo;

};

