#include "pch.h"
#include "TextureInfo.h"
#include "Texture2D.h"

TextureInfo::TextureInfo( )
	: TextureInfo( nullptr, false, false )
{
}

TextureInfo::TextureInfo( Texture2D* pTexture, bool flipX, bool flipY )
	: pTexture{ pTexture }
	, flipX{ flipX }
	, flipY{ flipY }
{
}
