#include "pch.h"
#include "TexturedModel.h"
#include "Texture2D.h"
#include "utils.h"

TexturedModel::TexturedModel( const Point2f& position )
	: m_Location{ position }
	, m_TextureInfo{}
	, m_TextureFlashing{}
{
}

Vector2f TexturedModel::GetLocation( ) const
{
	return m_Location;
}

float TexturedModel::GetTextureWidth( ) const
{
	return m_TextureInfo.pTexture->GetWidth();
}

float TexturedModel::GetTextureHeight( ) const
{
	return m_TextureInfo.pTexture->GetHeight( );
}

void TexturedModel::Draw( ) const
{
	m_TextureInfo.pTexture->Draw( m_Location.ToPoint2f( ), m_TextureInfo.flipX, m_TextureInfo.flipY, m_TextureFlashing );
}

void TexturedModel::DrawTextureOutline( ) const
{
	utils::SetColor( Color4f{ 1.f, 1.f, 1.f, 1.f } );
	utils::DrawRect( m_Location.ToPoint2f( ), GetTextureWidth( ), GetTextureHeight( ) );
}
