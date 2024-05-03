#pragma once
#include "TexturedModel.h"
#include "vector"
#include "Vector2f.h"
class ResourcesLinker;
class Texture2D;

class NonInterractableProp final
	: public TexturedModel
{
#pragma once
public:
	explicit NonInterractableProp( int depth, const Point2f& position, const std::string& uid, float scale = 1.f, bool animated = false );

	int GetDepth() const;

	virtual void Draw( float offsetX ) const;

	virtual void Update( float elapsedSec ) override;

	virtual void LinkTexture( ResourcesLinker* pResourcesLinker ) override;

private:
	const int mk_Depth;
	const std::string mk_Uid;
	const float mk_Scale;

	const bool mk_IsAnimated;
};

