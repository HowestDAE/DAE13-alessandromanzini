#pragma once
#include "TexturedModel.h"
#include "vector"
#include "Vector2f.h"

class TextureManager;
class NonInterractableProp final
	: public TexturedModel
{
#pragma once
public:
	explicit NonInterractableProp( int depth, const Point2f& position, float scale = 1.f );

	int GetDepth() const;

	virtual void Draw( float offsetX ) const;

	virtual void Update( float elapsedSec ) override;

	friend void ResourcesLinker::LinkTexture( NonInterractableProp& nip, const std::string& uid ) const;

private:
	const int mk_Depth;
	const float mk_Scale;
};

