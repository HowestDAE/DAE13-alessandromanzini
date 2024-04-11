#pragma once
#include "Vector2f.h"
#include "ResourcesLinker.h"
class TextureManager;

class TexturedModel
{
public:
	TexturedModel( const Point2f& position );

	Point2f GetPosition( ) const;

	float GetTextureWidth( ) const;
	float GetTextureHeight( ) const;

	virtual void Draw( ) const;
	virtual void Update( float elapsedSec ) = 0;

protected:
	TextureManager* m_pTextureManager;

	Vector2f m_Location;
	bool m_FlipX;
	bool m_FlipY;
};

