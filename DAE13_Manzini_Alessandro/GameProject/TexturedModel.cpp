#include "pch.h"
#include "TexturedModel.h"
#include "TextureManager.h"

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
