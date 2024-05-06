#include "pch.h"
#include "Texture2D.h"
#include "Texture.h"
#include "Vector2f.h"

Texture2D::Texture2D( Texture const* pTexture, const Vector2f& offset )
	: mk_pTexture{ pTexture }
	, mk_Offset{ offset }
{
}

void Texture2D::Draw( Texture const* pTexture, const Point2f& pos, const Rectf& srcRect, bool flipX, bool flipY ) const
{
	pTexture->Draw( pos + mk_Offset, srcRect, flipX, flipY );
}

void Texture2D::Draw( ) const
{
	Texture2D::Draw( mk_pTexture, Point2f{ 0.f, 0.f }, Rectf{} );
}

void Texture2D::Draw( const Point2f& pos, const Rectf& srcRect, bool flipX, bool flipY ) const
{
	Texture2D::Draw( mk_pTexture, pos, srcRect, flipX, flipY );
}

Vector2f Texture2D::GetOffset( ) const
{
	return mk_Offset;
}

float Texture2D::GetWidth( ) const
{
	return mk_pTexture->GetWidth();
}

float Texture2D::GetHeight( ) const
{
	return mk_pTexture->GetHeight();
}