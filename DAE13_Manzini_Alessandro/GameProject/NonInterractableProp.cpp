#include "pch.h"
#include "NonInterractableProp.h"
#include "TextureManager.h"

NonInterractableProp::NonInterractableProp( int depth, const Point2f& position, float scale )
	: TexturedModel( position )
	, mk_Depth{ depth }
	, mk_Scale{ scale }
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
		glScalef( mk_Scale, mk_Scale, 0.f );

		glTranslated( offsetX, 0, 0 );

		TexturedModel::Draw( );
	}
	glPopMatrix( );
}

void NonInterractableProp::Update( float elapsedSec )
{
	m_pTextureManager->Update( elapsedSec );
}
