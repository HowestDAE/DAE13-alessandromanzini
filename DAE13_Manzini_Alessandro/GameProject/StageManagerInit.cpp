#include "pch.h"
#include "StageManager.h"

#include "Constants.h"
#include "TextureManager.h"
#include "ResourcesLinker.h"
#include "Cuphead.h"
#include "NonInterractableProp.h"

void StageManager::Initialize( )
{
	InitializeProps( );
	InitializeEntities( );
}

void StageManager::InitializeProps( )
{
	CreateNIP( BackgroundScope::background5, "bg5_bg_loop", Point2f{ 0.f, 0.f } );

	CreateNIP( BackgroundScope::background4, "bg4_curtain_loop", Point2f{ 300.f, 230.f } );

	CreateNIP( BackgroundScope::background3, "bg3_startcurtains", Point2f{ 825.f, 430.f } );
	CreateNIP( BackgroundScope::background3, "bg3_moon", Point2f{ 2150.f, 230.f } );
	CreateNIP( BackgroundScope::background3, "bg3_rocks_loop", Point2f{ 280.f, 180.f } );
	CreateNIP( BackgroundScope::background3, "bg3_cloud1", Point2f{ 2010.f, 480.f } );
	CreateNIP( BackgroundScope::background3, "bg3_cloud2", Point2f{ 4020.f, 435.f } );

	CreateNIP( BackgroundScope::background2, "bg2_rocks_loop", Point2f{ 200.f, 175.f } );
	CreateNIP( BackgroundScope::background2, "bg2_entrance", Point2f{ -30.f, -30.f } );
	CreateNIP( BackgroundScope::background2, "bg2_star1", Point2f{ 1400.f, 410.f } );
	CreateNIP( BackgroundScope::background2, "bg2_star2", Point2f{ 2245.f, 440.f } );
	CreateNIP( BackgroundScope::background2, "bg2_blueplant", Point2f{ 2705.f, 230.f } );
	CreateNIP( BackgroundScope::background2, "bg2_star3", Point2f{ 3000.f, 410.f } );
	CreateNIP( BackgroundScope::background2, "bg2_star1", Point2f{ 4225.f, 430.f } );
	CreateNIP( BackgroundScope::background2, "bg2_star2", Point2f{ 4625.f, 465.f } );

	CreateNIP( BackgroundScope::background1, "bg2_startrock", Point2f{ 800.f, 150.f } );
	CreateNIP( BackgroundScope::background1, "bg1_cloud1", Point2f{ 1262.f, 530.f } );
	CreateNIP( BackgroundScope::background1, "bg1_cloud1", Point2f{ 3500.f, 466.f } );
	CreateNIP( BackgroundScope::background1, "bg1_greyplant", Point2f{ 3590.f, 210.f } );
	CreateNIP( BackgroundScope::background1, "bg1_blueplant", Point2f{ 3890.f, 170.f } );

	CreateNIP( BackgroundScope::midground2, "mg2_mantis", Point2f{ 2035.f, 225.f } );
	CreateNIP( BackgroundScope::midground2, "mg2_craterstart", Point2f{ 780.f, 127.f } );
	CreateNIP( BackgroundScope::midground2, "mg2_crater_loop", Point2f{ 1283.f, 90.f } );
	CreateNIP( BackgroundScope::midground2, "mg2_trunk", Point2f{ 977.f, 247.f } );
	CreateNIP( BackgroundScope::midground2, "mg2_star1", Point2f{ 780.f, 385.f } );
	CreateNIP( BackgroundScope::midground2, "mg2_star2", Point2f{ 1430.f, 335.f } );
	CreateNIP( BackgroundScope::midground2, "mg2_star1", Point2f{ 3130.f, 335.f } );
	CreateNIP( BackgroundScope::midground2, "mg2_star2", Point2f{ 4505.f, 355.f } );
	CreateNIP( BackgroundScope::midground2, "mg2_blueplant", Point2f{ 2180.f, 110.f } );
	CreateNIP( BackgroundScope::midground2, "mg2_frogbot", Point2f{ 5010.f, 220.f } );

	CreateNIP( BackgroundScope::midground1, "mg1_rock1", Point2f{ 1105.f, 120.f } );
	CreateNIP( BackgroundScope::midground1, "mg1_rock1", Point2f{ 3500.f, 135.f } );
	CreateNIP( BackgroundScope::midground1, "mg1_rock2", Point2f{ 5176.f, 120.f } );
	CreateNIP( BackgroundScope::midground1, "mg1_greyplant", Point2f{ 5420.f, 90.f } );
	CreateNIP( BackgroundScope::midground1, "mg1_startfloor", Point2f{ 611.f, -37.5f } );
	CreateNIP( BackgroundScope::midground1, "mg1_floor_loop", Point2f{ 1082.f, -33.f } );
	CreateNIP( BackgroundScope::midground1, "mg1_topfloor_loop", Point2f{ 0.f, 600.f } );
		
	CreateNIP( BackgroundScope::frontground3, "fg3_startcurtain", Point2f{ -54.f, 477.f } );
	CreateNIP( BackgroundScope::frontground3, "fg3_curtain", Point2f{ 150.f, 460.f } );
	CreateNIP( BackgroundScope::frontground3, "fg3_startprops", Point2f{ 41.f, -67.f } );
	CreateNIP( BackgroundScope::frontground3, "fg3_rock2", Point2f{ 945, -190.f } );
	CreateNIP( BackgroundScope::frontground3, "fg3_greyplant", Point2f{ 1180, -110.f } );
	CreateNIP( BackgroundScope::frontground3, "fg3_blueplant", Point2f{ 1691.f, -95.f } );
	CreateNIP( BackgroundScope::frontground3, "fg3_rock1", Point2f{ 1455.f, 585.f } );
	CreateNIP( BackgroundScope::frontground3, "fg3_rock3", Point2f{ 2045.f, 630.f } );
	CreateNIP( BackgroundScope::frontground3, "fg3_trunk", Point2f{ 2490.f, -190.f } );
	CreateNIP( BackgroundScope::frontground3, "fg3_rock4", Point2f{ 3400.f, 500.f } );
	CreateNIP( BackgroundScope::frontground3, "fg3_rock2", Point2f{ 4950.f, -150.f } );
	CreateNIP( BackgroundScope::frontground3, "fg3_curtain", Point2f{ 4900.f, 530.f } );
	CreateNIP( BackgroundScope::frontground3, "fg3_blueplant2", Point2f{ 4850.f, 590.f } );
	CreateNIP( BackgroundScope::frontground3, "fg3_greyplant", Point2f{ 5705, -100.f } );
	CreateNIP( BackgroundScope::frontground3, "fg3_topgreyplant", Point2f{ 6250, 600.f } );
	CreateNIP( BackgroundScope::frontground3, "fg3_blueplant", Point2f{ 6580.f, -145.f } );
	CreateNIP( BackgroundScope::frontground3, "fg3_blueplant2", Point2f{ 6710.f, 565.f } );

	CreateNIP( BackgroundScope::frontground2, "fg2_star1", Point2f{ 1330.f, 485.f } );
	CreateNIP( BackgroundScope::frontground2, "fg2_star1", Point2f{ 3030.f, 485.f } );
	CreateNIP( BackgroundScope::frontground2, "fg2_star1", Point2f{ 4580.f, 525.f } );
	CreateNIP( BackgroundScope::frontground2, "fg2_star1", Point2f{ 5835.f, 515.f } );
	CreateNIP( BackgroundScope::frontground2, "fg2_frogbot", Point2f{ 4030.f, -190.f } );
	CreateNIP( BackgroundScope::frontground2, "fg2_frogbot", Point2f{ 6900.f, -230.f } );
	CreateNIP( BackgroundScope::frontground2, "fg2_planet", Point2f{ 5745.f, -195.f } );

	CreateNIP( BackgroundScope::frontground1, "fg1_star", Point2f{ 882.f, 470.f } );
	CreateNIP( BackgroundScope::frontground1, "fg1_star", Point2f{ 2600.f, 472.f }, .8f );
}

void StageManager::InitializeEntities( )
{
	m_pPlayer = new Cuphead( Constants::sk_CupheadStartingPosition );
	m_pResourcesLinker->LinkTexture( m_pPlayer );
}

void StageManager::CreateNIP( BackgroundScope scope, const std::string& uid, const Point2f& position, float scale )
{
	NonInterractableProp temp{  int( scope ), (Vector2f( position ) / scale).ToPoint2f(), scale };
	m_pResourcesLinker->LinkTexture( temp, uid );

	if ( scope >= BackgroundScope::midground1 )
	{
		m_BackgroundProps.push_back( temp );
	}
	else
	{
		m_FrontgroundProps.push_back( temp );
	}
}
