#pragma once
#include <Vector2f.h>
class Texture;

class Texture2D
{
public:
	explicit Texture2D( Texture const* pTexture, const Vector2f& offset = {} );
	Texture2D( );
	virtual ~Texture2D( ) = default;

	Texture2D( const Texture2D& other ) = default;
	Texture2D( Texture2D&& other ) noexcept = default;
	Texture2D& operator=( const Texture2D& rhs ) = delete;
	Texture2D& operator=( Texture2D&& rhs ) = delete;

	// public drawing methods
	virtual void Draw( ) const;
	virtual void Draw( const Point2f& pos, bool flipX = false, bool flipY = false, bool flash = false ) const = 0;
	virtual void Update( float elapsedSec ) = 0;

	Vector2f GetOffset( ) const;
	virtual float GetWidth( ) const;
	virtual float GetHeight( ) const;

	virtual void ForceReady( ) = 0;
	virtual bool GetIsReady( ) const = 0;
	virtual float GetAnimationTimer( ) const = 0;

	// Resets animation data
	virtual void Reset( ) = 0;

protected:
	// children drawing methods
	void Draw( Texture const* pTexture, const Point2f& pos, const Rectf& srcRect, bool flipX = false, bool flipY = false ) const;
	void Draw( const Point2f& pos, const Rectf& srcRect, bool flipX = false, bool flipY = false ) const;
	
private:
	const Vector2f mk_Offset;
	Texture const* const mk_pTexture;

};

