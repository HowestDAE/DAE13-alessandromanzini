#include "pch.h"
#include "NonInterractableProp.h"
#include "Texture2D.h"
#include "Sprite.h"
#include "ResourcesLinker.h"

NonInterractableProp::NonInterractableProp( int depth, const Point2f& position, const std::string& uid, float scale, bool animated )
	: TexturedModel( position )
	, mk_Depth{ depth }
	, mk_Uid{ uid }
	, mk_Scale{ scale }
	, mk_IsAnimated{ animated }
{
}

int NonInterractableProp::GetDepth( ) const
{
	return mk_Depth;
}

void NonInterractableProp::Draw( float offsetX ) const
{
	glPushMatrix( );
	{
		/*glScalef( mk_Scale, mk_Scale, 0.f );*/

		glTranslated( offsetX, 0, 0 );

		TexturedModel::Draw( );
	}
	glPopMatrix( );
}

void NonInterractableProp::Update( float elapsedSec )
{
	m_TextureInfo.pTexture->Update( elapsedSec );
}

void NonInterractableProp::LinkTexture( ResourcesLinker* pResourcesLinker )
{
	Texture2D* pTexture{};

	if ( mk_IsAnimated )
	{
		pTexture = pResourcesLinker->GetSprite( mk_Uid );
	}
	else
	{
		pTexture = pResourcesLinker->GetTexture( mk_Uid );
	}

	m_TextureInfo.pTexture = pTexture;
}
