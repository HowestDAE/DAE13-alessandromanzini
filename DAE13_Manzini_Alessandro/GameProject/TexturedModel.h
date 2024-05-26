#pragma once
#include "ResourcesLinker.h"
#include "TextureInfo.h"
#include "Vector2f.h"
class Texture2D;

class TexturedModel
{
public:
	TexturedModel( const Point2f& position );
	virtual ~TexturedModel( ) noexcept = default;

	TexturedModel( const TexturedModel& other ) = delete;
	TexturedModel( TexturedModel&& other ) = delete;
	TexturedModel& operator=( const TexturedModel& rhs ) = delete;
	TexturedModel& operator=( TexturedModel&& rhs ) = delete;

	Vector2f GetLocation( ) const;

	virtual float GetTextureWidth( ) const = 0;
	virtual float GetTextureHeight( ) const = 0;

	virtual void Draw( ) const = 0;
	virtual void Update( float elapsedSec ) = 0;

	void DrawTextureOutline( ) const;

	virtual void LinkTexture( ResourcesLinker* pResourceLinker ) = 0;

protected:
	Vector2f m_Location;
	bool m_TextureFlashing;

	void Draw( const TextureInfo& textureInfo ) const;
	void Draw( Texture2D const* pTexture ) const;

};

