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
	Pattern( const Pattern& other ) = delete;
	virtual ~Pattern( ) override = default;

	virtual void Draw( const Point2f& pos, bool flipX = false, bool flipY = false, bool flash = false ) const override;
	virtual void Update( float elapsedSec ) override;

	virtual void ForceReady( ) override;
	virtual bool GetIsReady( ) const override;
	virtual float GetAnimationTimer( ) const override;

	virtual void Reset( ) override;

	Pattern& operator=( const Pattern& rhs ) = delete;

private:
	const int mk_Repetition;

};

