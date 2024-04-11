#include "pch.h"
#include "TextureManager.h"
#include "Texture.h"
#include "Vector2f.h"

TextureManager::TextureManager( const Vector2f& offset )
	: mk_Offset{ offset }
{
}

void TextureManager::Draw( const Texture* pTexture, const Point2f& pos, const Rectf& srcRect, bool flipX, bool flipY ) const
{
	pTexture->Draw( pos + mk_Offset, srcRect, flipX, flipY );
}

Vector2f TextureManager::GetOffset( ) const
{
	return mk_Offset;
}
