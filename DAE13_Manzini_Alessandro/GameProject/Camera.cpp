#include "pch.h"
#include "Camera.h"

#include "StageManager.h"
#include "Cuphead.h"
#include "NonInterractableProp.h"
#include <iostream>

Camera::Camera( const Rectf& viewPort )
	: m_pStageManager{}
	, mk_ViewPort{ viewPort }
	, m_CameraTranslationPoint{}
{
}

void Camera::SetStageManager( StageManager const* pStageManager )
{
	m_pStageManager = pStageManager;
}

void Camera::Aim( const Point2f& position, float width )
{
	const float screenTranslation{ position.x - width / 2 - mk_ViewPort.width / 2  };

	if ( screenTranslation < 0.f )
	{
		m_CameraTranslationPoint = Point2f{ 0.f, 0.f };
	}
	else
	{
		m_CameraTranslationPoint = Point2f{ screenTranslation, 0.f };
	}
}

void Camera::Draw( ) const
{
	glPushMatrix( );
	{
		glTranslatef( -m_CameraTranslationPoint.x, -m_CameraTranslationPoint.y, 0.f ); // center camera on player

		DrawBackground( m_pStageManager->GetBackgroundProps() ); // Draw background, midground
		DrawEntities( );
		DrawBackground( m_pStageManager->GetFrontgroundProps( ) ); // Draw frontground
	}
	glPopMatrix( );
}

void Camera::DrawBackground( const std::vector<NonInterractableProp>& props ) const
{
	for ( const NonInterractableProp& prop : props )
	{
		float offset{ GetXParallaxRatio( prop.GetDepth( ) ) };
		prop.Draw( offset );
	}
}

void Camera::DrawEntities( ) const
{
	const Cuphead* pPlayer = m_pStageManager->GetPlayer( );
	pPlayer->Draw( );
}

float Camera::GetXParallaxRatio( int depth ) const
{
	float offset{ m_CameraTranslationPoint.x };
	switch ( depth )
	{
	case 6: //bg5
		offset *= 0.5f;
		break;
	case 5: //bg4
		offset *= 0.27f;
		break;

	case 4: //bg3
		offset *= 0.21f;
		break;

	case 3: //bg2
		offset *= 0.15f;
		break;

	case 2: //bg1
		offset *= 0.06f;
		break;

	case 1: //mg2
		offset *= 0.02f;
		break;

	case 0: //mg1
		offset *= 0.f;
		break;

	case -1: //fg3
		offset *= -0.2f;
		break;

	case -2: //fg2
		offset *= -0.25f;
		break;

	case -3: //fg1
		offset *= -1.f;
		break;
	}
	return offset;
}
