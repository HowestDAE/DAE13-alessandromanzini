#include "pch.h"
#include "NonInterractableProp.h"
#include "Texture2D.h"
#include "Sprite.h"
#include "ResourcesLinker.h"

NonInterractableProp::NonInterractableProp( int depth, const Point2f& position, const std::string& uid, float scale )
	: TexturedModel( position )
	, mk_Depth{ depth }
	, mk_Uid{ uid }
	, mk_Scale{ scale }
	, m_pTexture{}
{
}

int NonInterractableProp::GetDepth( ) const
{
	return mk_Depth;
}

float NonInterractableProp::GetTextureWidth( ) const
{
	return m_pTexture->GetWidth( );
}

float NonInterractableProp::GetTextureHeight( ) const
{
	return m_pTexture->GetHeight( );
}

void NonInterractableProp::Draw( ) const
{
	TexturedModel::Draw( m_pTexture );
}

void NonInterractableProp::Draw( float offsetX ) const
{
	glPushMatrix( );
	{
		/*glScalef( mk_Scale, mk_Scale, 0.f );*/

		glTranslated( offsetX, 0, 0 );

		Draw( );
	}
	glPopMatrix( );
}

void NonInterractableProp::Update( float elapsedSec )
{
	m_pTexture->Update( elapsedSec );
}

void NonInterractableProp::LinkTexture( ResourcesLinker* pResourcesLinker )
{
	m_pTexture = pResourcesLinker->GetTexture( mk_Uid );
}
