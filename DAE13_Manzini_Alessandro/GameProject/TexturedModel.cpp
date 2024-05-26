#include "pch.h"
#include "TexturedModel.h"
#include "Texture2D.h"
#include "utils.h"

TexturedModel::TexturedModel( const Point2f& position )
	: m_Location{ position }
	, m_TextureFlashing{}
{
}

Vector2f TexturedModel::GetLocation( ) const
{
	return m_Location;
}

void TexturedModel::DrawTextureOutline( ) const
{
	utils::SetColor( Color4f{ 1.f, 1.f, 1.f, 1.f } );
	utils::DrawRect( m_Location.ToPoint2f( ), GetTextureWidth( ), GetTextureHeight( ) );
}

void TexturedModel::Draw( const TextureInfo& textureInfo ) const
{
	if ( textureInfo.pTexture )
	{
		textureInfo.pTexture->Draw( m_Location.ToPoint2f( ), textureInfo.flipX, textureInfo.flipY, m_TextureFlashing );
	}
}

void TexturedModel::Draw( Texture2D const* pTexture ) const
{
	pTexture->Draw( m_Location.ToPoint2f( ) );
}
