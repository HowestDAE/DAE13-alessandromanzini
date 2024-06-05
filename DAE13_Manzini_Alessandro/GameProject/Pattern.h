#pragma once
#include "Texture2D.h"
#include "PatternSettings.h"

class Pattern final
	: public Texture2D
{
public:
	explicit Pattern( Texture const* pTexture, const PatternSettings& patternSettings );
	explicit Pattern( Texture const* pTexture, int repetition = 0 );
	explicit Pattern( Texture const* pTexture, Vector2f offset, int repetition = 0 );
	virtual ~Pattern( ) noexcept = default;

	Pattern( const Pattern& other ) = default;
	Pattern( Pattern&& other ) noexcept = default;
	Pattern& operator=( const Pattern& rhs ) = delete;
	Pattern& operator=( Pattern&& rhs ) = delete;

	virtual void Draw( const Point2f& pos, bool flipX = false, bool flipY = false, bool flash = false ) const override;
	void Draw( const Point2f& pos, float percentage ) const;
	void Draw( const Point2f& pos, float rotation, bool pointToCenter ) const;
	virtual void Update( float elapsedSec ) override;

	virtual void ForceReady( ) override;
	virtual bool GetIsReady( ) const override;
	virtual float GetAnimationTimer( ) const override;

	virtual void Reset( ) override;

private:
	const int mk_Repetition;

};

