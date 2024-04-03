#include "pch.h"
#include "NonInterractableProp.h"
#include "TextureManager.h"

NonInterractableProp::NonInterractableProp( int depth, const Point2f& position, float scale )
	: mk_Depth{ depth }
	, mk_Scale{ scale }
{
	m_Location = Vector2f{ position };
}

int NonInterractableProp::GetDepth( ) const
{
	return mk_Depth;
}

void NonInterractableProp::Draw( ) const
{
	m_pTextureManager->Draw( m_Location.ToPoint2f( ) );
}

void NonInterractableProp::Draw( float offsetX ) const
{
	glPushMatrix( );
	{
		glScalef( mk_Scale, mk_Scale, 0.f );

		glTranslated( offsetX, 0, 0 );

		Draw( );
	}
	glPopMatrix( );
}

void NonInterractableProp::Update( float elapsedSec )
{
	m_pTextureManager->Update( elapsedSec );
}
