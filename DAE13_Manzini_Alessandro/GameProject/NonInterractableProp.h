#pragma once
#include "TexturedModel.h"
#include "vector"
#include "Vector2f.h"
class ResourcesLinker;
class Texture2D;

class NonInterractableProp final
	: public TexturedModel
{
public:
	explicit NonInterractableProp( int depth, const Point2f& position, const std::string& uid, float scale = 1.f );
	virtual ~NonInterractableProp( ) noexcept = default;

	NonInterractableProp( const NonInterractableProp& other ) = delete;
	NonInterractableProp( NonInterractableProp&& other ) noexcept;
	NonInterractableProp& operator=( const NonInterractableProp& other ) = delete;
	NonInterractableProp& operator=( NonInterractableProp&& other ) = delete;

	int GetDepth() const;

	virtual float GetTextureWidth( ) const override;
	virtual float GetTextureHeight( ) const override;

	virtual void Draw( ) const;
	void Draw( float offsetX ) const;
	virtual void Update( float elapsedSec ) override;

	virtual void LinkTexture( ResourcesLinker* pResourcesLinker ) override;

private:
	const int mk_Depth;
	const std::string mk_Uid;
	const float mk_Scale;

	Texture2D* m_pTexture;

};

