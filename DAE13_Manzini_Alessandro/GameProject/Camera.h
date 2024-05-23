#pragma once
#include "Vector2f.h"
#include <vector>
class NonInterractableProp;
class StageManager;

class Camera final
{
public:
	explicit Camera( const Rectf& viewPort );

	void SetStageManager( StageManager const* pStageManager );

	void Aim( const Point2f& position, float width=0 );

	void Draw( ) const;
	void Update( float elapsedSec );

private:
	StageManager const* m_pStageManager;

	const Rectf mk_ViewPort;

	static const float smk_CameraMaxSpeed;
	static const float smk_GreenwichMeridian;
	static const float smk_CameraPulsation;
	static const float smk_CameraMovementEpsilon;

	Vector2f m_CameraLocationVector;
	Vector2f m_CameraTranslationVector;
	Vector2f m_AimLocationVector;

	void DrawPlatform( ) const;
	void DrawHUD( ) const;
	void DrawBackground( const std::vector<NonInterractableProp>& props ) const;
	void DrawEntities( ) const;
	void DrawProjectiles( ) const;

	float GetXParallaxRatio( int depth ) const;
};

