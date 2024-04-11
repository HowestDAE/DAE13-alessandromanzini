#pragma once
#include "TextureManager.h"

class PatternManager final
	: public TextureManager
{
public:
	explicit PatternManager( const std::string& patternPath, int repetition = 0 );
	explicit PatternManager( const std::string& patternPath, Vector2f offset, int repetition = 0 );
	PatternManager( const PatternManager& other ) = delete;
	virtual ~PatternManager( ) override;

	virtual void Draw( const Point2f& pos, bool flipX = false, bool flipY = false ) const override;
	virtual void Update( float elapsedSec ) override;

	virtual float GetWidth( ) const override;
	virtual float GetHeight( ) const override;

	virtual void ForceReady( ) override;
	virtual bool GetIsReady( ) const override;
	virtual float GetAnimationTimer( ) const override;

	virtual void Reset( ) override;

	PatternManager& operator=( const PatternManager& rhs ) = delete;

private:
	const int mk_Repetition;

	Texture* m_pTexture;
};

