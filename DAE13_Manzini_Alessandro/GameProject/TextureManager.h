#pragma once
#include <Vector2f.h>
class Texture;

class TextureManager
{
public:
	explicit TextureManager( const Vector2f& offset = {} );
	TextureManager( const TextureManager& other ) = delete;
	virtual ~TextureManager( ) = default;
	
	virtual void Draw( const Point2f& pos, bool flipX = false, bool flipY = false ) const = 0;
	virtual void Update( float elapsedSec ) = 0;

	Vector2f GetOffset( ) const;
	virtual float GetWidth( ) const = 0;
	virtual float GetHeight( ) const = 0;

	virtual void ForceReady( ) = 0;		
	// By default, texture is ready.
	virtual bool GetIsReady( ) const = 0;	
	// By default, texture has no animation timer.
	virtual float GetAnimationTimer( ) const = 0;

	virtual void Reset( ) = 0;

	TextureManager& operator=( const TextureManager& rhs ) = delete;

protected:
	void Draw( const Texture* pTexture, const Point2f& pos, const Rectf& srcRect, bool flipX, bool flipY ) const;
	
private:
	const Vector2f mk_Offset;
};

