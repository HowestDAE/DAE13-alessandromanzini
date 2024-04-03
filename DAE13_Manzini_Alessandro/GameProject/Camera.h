#pragma once
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

private:
	StageManager const* m_pStageManager;

	const Rectf mk_ViewPort;
	Point2f m_CameraTranslationPoint;

	void DrawBackground( const std::vector<NonInterractableProp>& props ) const;
	void DrawEntities( ) const;

	float GetXParallaxRatio( int depth ) const;
};

