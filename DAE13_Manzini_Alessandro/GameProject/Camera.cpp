#include "pch.h"
#include "Camera.h"
#include "StageManager.h"
#include "Cuphead.h"
#include "Toyduck.h"
#include "NonInterractableProp.h"
#include "Projectile.h"
#include <math.h>

// We only want the first fourth of the wave. Thus M_PI_2 instead of 2*M_PI.
const float Camera::smk_CameraMaxSpeed{ 700.f };
const float Camera::smk_GreenwichMeridian{ 100.f };
const float Camera::smk_CameraPulsation{ float(M_PI / 2.) / (smk_GreenwichMeridian) };

const float Camera::smk_CameraMovementEpsilon{ 10.f };

Camera::Camera( const Rectf& viewPort )
	: m_pStageManager{}
	, mk_ViewPort{ viewPort }
	, m_CameraLocationVector{}
	, m_CameraTranslationVector{}
	, m_AimLocationVector{}
{
}

void Camera::SetStageManager( StageManager const* pStageManager )
{
	m_pStageManager = pStageManager;
}

void Camera::Aim( const Point2f& position, float width )
{
	// [position.x - viewport/2] gives the position relative to the actual point. 
	// [+ width/2] makes it relative to the texture.
	const float screenTranslation{ position.x - mk_ViewPort.width / 2 + width / 2 };

	// avoid going off the screen
	m_AimLocationVector.Set( (screenTranslation < 0.f) ? 0.f : screenTranslation, 0.f );

	m_CameraTranslationVector = m_AimLocationVector - m_CameraLocationVector;
}

void Camera::Draw( ) const
{
	glPushMatrix( );
	{
		const float cameraX{ -m_CameraLocationVector.x }, cameraY{ -m_CameraLocationVector.y };
		glTranslatef( cameraX, cameraY, 0.f ); // position camera

		DrawBackground( m_pStageManager->GetBackgroundProps() ); // Draw background, midground
		DrawEntities( );
		DrawProjectiles( );
		DrawBackground( m_pStageManager->GetFrontgroundProps( ) ); // Draw frontground
	}
	glPopMatrix( );
}

void Camera::Update( float elapsedSec )
{
	const float difference{ (m_AimLocationVector - m_CameraLocationVector).SquaredLength() };
	// Apply movement only when difference is greater than epsilon
	if ( difference > smk_CameraMovementEpsilon )
	{
		const float distance{ m_CameraTranslationVector.Length() };
	
		// The wave coefficient will be 1.f if greater than the max distance, but will get lower the closer to the target. 
		const float waveCoefficient{ ( distance < smk_GreenwichMeridian ) ?
			sinf( smk_CameraPulsation * distance ) : 1.f
		};
		const float relativeSpeed{ waveCoefficient * smk_CameraMaxSpeed * elapsedSec };
		m_CameraLocationVector += m_CameraTranslationVector.Normalized( ) * relativeSpeed;
	}
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
	m_pStageManager->GetPlayer()->Draw( );
	m_pStageManager->GetToyduck()->Draw( );
}

void Camera::DrawProjectiles( ) const
{

}

float Camera::GetXParallaxRatio( int depth ) const
{
	float offset{ m_CameraLocationVector.x };
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
