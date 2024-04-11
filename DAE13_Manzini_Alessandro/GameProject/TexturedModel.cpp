#include "pch.h"
#include "TexturedModel.h"
#include "TextureManager.h"

TexturedModel::TexturedModel( const Point2f& position )
	: m_pTextureManager{ nullptr }
	, m_FlipX{}
	, m_FlipY{}
	, m_Location{ position }
{
}

Point2f TexturedModel::GetPosition( ) const
{
	return m_Location.ToPoint2f();
}

float TexturedModel::GetTextureWidth( ) const
{
	return m_pTextureManager->GetWidth();
}

float TexturedModel::GetTextureHeight( ) const
{
	return m_pTextureManager->GetHeight( );
}

void TexturedModel::Draw( ) const
{
	m_pTextureManager->Draw( m_Location.ToPoint2f( ), m_FlipX, m_FlipY );
}
