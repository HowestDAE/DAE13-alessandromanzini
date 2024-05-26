#pragma once
class Texture2D;

struct TextureInfo final
{
public:
	TextureInfo( );
	explicit TextureInfo( Texture2D* pTexture, bool flipX, bool flipY );

	Texture2D* pTexture;
	bool flipX;
	bool flipY;

};

