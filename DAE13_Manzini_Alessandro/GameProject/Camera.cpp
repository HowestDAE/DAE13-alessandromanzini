#include "pch.h"
#include "Camera.h"
#include "Constants.h"
#include "StageManager.h"
#include "Projectile.h"
#include "NonInterractableProp.h"
#include "HUDManager.h"
#include "Cuphead.h"
#include "Toyduck.h"
#include <math.h>
#include <utils.h>

// We only want the first fourth of the wave. Thus M_PI_2 instead of 2*M_PI.
const float Camera::smk_CameraMaxSpeed{ 700.f };
const float Camera::smk_GreenwichMeridian{ 100.f };
const float Camera::smk_CameraPulsation{ float(M_PI / 2.) / (smk_GreenwichMeridian) };

const float Camera::smk_CameraMovementEpsilon{ 10.f };

const float Camera::smk_MaxCameraX{ 15260.f };

Camera::Camera( const Rectf& viewPort )
	: mk_pStageManager{}
	, mk_ViewPort{ viewPort }
	, m_CameraLocationVector{ Constants::sk_CupheadStartingPosition }
	, m_CameraTranslationVector{}
	, m_AimLocationVector{}
	, m_ScreenOverlayQueue{}
	, m_ScreenTexture{}
{
}

void Camera::SetStageManager( StageManager const* pStageManager )
{
	mk_pStageManager = pStageManager;
}

void Camera::Aim( const Point2f& position, float width )
{
	// [position.x - viewport/2] gives the position relative to the actual point. 
	// [+ width/2] makes it relative to the texture.
	float screenTranslation{ position.x - mk_ViewPort.width / 2 + width / 2 };

	// avoid going off the screen
	if( screenTranslation > smk_MaxCameraX )
	{
		screenTranslation = smk_MaxCameraX;
	}
	else if( screenTranslation < 0.f )
	{
		screenTranslation = 0.f;
	}

	m_AimLocationVector.Set( screenTranslation, 0.f );
	m_CameraTranslationVector = m_AimLocationVector - m_CameraLocationVector;
}

void Camera::Draw( ) const
{
	glPushMatrix( );
	{
		const float cameraX{ -m_CameraLocationVector.x }, cameraY{ -m_CameraLocationVector.y };
		glTranslatef( cameraX, cameraY, 0.f ); // position camera

		DrawBackground( mk_pStageManager->GetBackgroundProps() ); // Draw background, midground
		DrawEntities( );
		DrawBackground( mk_pStageManager->GetFrontgroundProps( ) ); // Draw frontground
		DrawPlatform( );
	}
	glPopMatrix( );

	DrawHUD( );
	DrawScreenOverlay( );
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

	UpdateScreenOverlay( elapsedSec );
}

void Camera::QueueScreenTexture( Texture2D* pTexture )
{
	m_ScreenOverlayQueue.Enqueue( TextureInfo{ pTexture, false, false } );
}

void Camera::FeedInScreenTexture( )
{
	m_ScreenOverlayQueue.NextAnimation( m_ScreenTexture, true );
}

Rectf Camera::GetViewPort( ) const
{
	return mk_ViewPort;
}

Vector2f Camera::GetCameraLocation( ) const
{
	return m_CameraLocationVector;
}

void Camera::Reset( )
{
	m_CameraLocationVector.Set( 0.f, 0.f );
	m_CameraTranslationVector.Set( 0.f, 0.f );
	m_AimLocationVector.Set( 0.f, 0.f );
	m_ScreenOverlayQueue = AnimationQueue( );
	m_ScreenTexture = TextureInfo( );
}

void Camera::DrawPlatform( ) const
{
	PlatformManager const* pPlatformManager{ mk_pStageManager->GetPlatformManager( ) };
	Cuphead const* pCuphead{ mk_pStageManager->GetPlayer( ) };
	//pPlatformManager->Draw( pCuphead );
}

void Camera::DrawHUD( ) const
{
	const HUDManager* pHUDManager{ mk_pStageManager->GetHUDManager( ) };

	pHUDManager->Draw( );
}

void Camera::DrawScreenOverlay( ) const
{
	if ( m_ScreenTexture.pTexture )
	{
		m_ScreenTexture.pTexture->Draw( Point2f{ 0.f, 0.f } );
	}

	utils::SetColor( Color4f{ 0.f, 0.f, 0.f, mk_pStageManager->GetScreenOpacity( ) } );
	utils::FillRect( mk_ViewPort );
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
	const std::vector<Entity*>& entitites{ mk_pStageManager->GetEntities( ) };
	for ( Entity const* pEntity : entitites )
	{
		pEntity->DrawBackside( );
	}

	mk_pStageManager->GetPlayer()->Draw( );

	for ( Entity const* pEntity : entitites )
	{
		pEntity->Draw( );
	}

	mk_pStageManager->GetPlayer( )->DrawProjectiles( );
}

void Camera::UpdateScreenOverlay( float elapsedSec )
{
	FeedInScreenTexture( );
	if ( m_ScreenTexture.pTexture )
	{
		m_ScreenTexture.pTexture->Update( elapsedSec ); 
	}
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
