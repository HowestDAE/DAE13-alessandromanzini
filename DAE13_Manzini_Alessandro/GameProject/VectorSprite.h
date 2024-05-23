#pragma once
#include "Texture2D.h"
#include <vector>

class VectorSprite :
    public Texture2D
{
public:
	explicit VectorSprite( const std::vector<Texture*>& textures, float frameDelay );

	void Draw( const Rectf& bounds ) const;
	virtual void Draw( const Point2f& pos, bool flipX = false, bool flipY = false, bool flash = false ) const override;
	virtual void Update( float elapsedSec ) override;

	virtual float GetWidth( ) const override;
	virtual float GetHeight( ) const override;

	virtual void ForceReady( ) override;
	virtual bool GetIsReady( ) const override;
	virtual float GetAnimationTimer( ) const override;

	// Resets animation data
	virtual void Reset( ) override;

private:
	const std::vector<Texture*>& mk_pTextures;
	const float mk_FrameDelay;

	int m_CurrentTexture;
	float m_AccumulatedTime;

};

