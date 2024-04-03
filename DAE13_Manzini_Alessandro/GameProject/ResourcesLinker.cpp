#include "pch.h"
#include "ResourcesLinker.h"
#include "TextureManager.h"
#include "SpriteManager.h"
#include "PatternManager.h"
#include "Cuphead.h"
#include "NonInterractableProp.h"

ResourcesLinker::ResourcesLinker( )
	: m_pBackgroundTextures{}
{
	InitializeTextures( );
}

ResourcesLinker::~ResourcesLinker( )
{
	ReleaseTextures( );
}

void ResourcesLinker::LinkTexture( Cuphead* pPlayer ) const
{
	pPlayer->m_pTextureManager = m_pCupheadIdle; // starting sprite

	pPlayer->m_pIdleSprite = m_pCupheadIdle;
	pPlayer->m_pRunSprite = m_pCupheadRun;
}

void ResourcesLinker::LinkTexture( NonInterractableProp& nip, const std::string& uid ) const
{
	nip.m_pTextureManager = m_pBackgroundTextures.at( uid );
}

void ResourcesLinker::InitializeTextures( )
{
	InitializeEntities( );
	InitializeBackgroundProps( );
}

void ResourcesLinker::InitializeEntities( )
{
	{
		const float idleFrameDelay{ .1f };
		const float runFrameDelay{ .06f };

		m_pCupheadIdle = new SpriteManager( "player/character/AS_cuphead_idle_1x5.png", 1, 5, idleFrameDelay, true );
		m_pCupheadRun = new SpriteManager( "player/character/AS_cuphead_run_2x8.png", 2, 8, runFrameDelay, false, Vector2f{ -20.f, 0.f } );
	}
}

void ResourcesLinker::InitializeBackgroundProps( )
{
	const std::string bg_path{ "background/" };

	const float slowAnimationDelay{ 1.f };

	// part 1
	{
		const int backgroundRepetition{ 20 };
		const int curtainRepetition{ 2 };
		const int topFloorRepetition{ 2 };
		const int backRocksRepetition{ 3 };
		const int bottomFloorRepetition{ 4 };
		const int frontRocksRepetition{ 2 };
		const int craterRepetition{ 3 };

		m_pBackgroundTextures["bg5_bg_loop"] = new PatternManager( bg_path + "STL_bg5_bg.png", backgroundRepetition );

		m_pBackgroundTextures["bg4_curtain_loop"] = new PatternManager( bg_path + "part1/bg4/STL_bg4_curtain_16.png", curtainRepetition );
	
		m_pBackgroundTextures["bg3_moon"] = new PatternManager( bg_path + "part1/bg3/ST_bg3_moon_11.png" );
		m_pBackgroundTextures["bg3_rocks_loop"] = new PatternManager( bg_path + "part1/bg3/STL_bg3_rocks_12.png", backRocksRepetition );
		m_pBackgroundTextures["bg3_cloud1"] = new PatternManager( bg_path + "part1/bg3/ST_bg3_cloud1_13.png" );
		m_pBackgroundTextures["bg3_cloud2"] = new PatternManager( bg_path + "part1/bg3/ST_bg3_cloud2_14.png" );
		m_pBackgroundTextures["bg3_startcurtains"] = new PatternManager( bg_path + "part1/bg3/ST_bg3_start_curtains_15.png" );

		m_pBackgroundTextures["bg2_entrance"] = new PatternManager( bg_path + "part1/bg2/ST_bg2_entrance_04.png" );
		m_pBackgroundTextures["bg2_blueplant"] = new PatternManager( bg_path + "part1/bg2/ST_bg2_blue_plant_05.png" );
		m_pBackgroundTextures["bg2_startrock"] = new PatternManager( bg_path + "part1/bg2/ST_bg2_start_rock_06.png" );
		m_pBackgroundTextures["bg2_rocks_loop"] = new PatternManager( bg_path + "part1/bg2/STL_bg2_rocks_07.png", frontRocksRepetition );
		m_pBackgroundTextures["bg2_star1"] = new PatternManager( bg_path + "part1/bg2/ST_bg2_star1_08.png" );
		m_pBackgroundTextures["bg2_star2"] = new PatternManager( bg_path + "part1/bg2/ST_bg2_star2_09.png" );
		m_pBackgroundTextures["bg2_star3"] = new PatternManager( bg_path + "part1/bg2/ST_bg2_star3_10.png" );

		m_pBackgroundTextures["bg1_cloud1"] = new PatternManager( bg_path + "part1/bg1/ST_bg1_cloud1_01.png" );
		m_pBackgroundTextures["bg1_blueplant"] = new PatternManager( bg_path + "part1/bg1/ST_bg1_blue_plant_02.png" );
		m_pBackgroundTextures["bg1_greyplant"] = new PatternManager( bg_path + "part1/bg1/ST_bg1_grey_plant_03.png" );

		m_pBackgroundTextures["mg2_blueplant"] = new PatternManager( bg_path + "part1/mg2/ST_mg2_blue_plant_23.png" );
		m_pBackgroundTextures["mg2_craterstart"] = new PatternManager( bg_path + "part1/mg2/ST_mg2_crater_start_24.png" );
		m_pBackgroundTextures["mg2_frogbot"] = new PatternManager( bg_path + "part1/mg2/ST_mg2_frogbot_25.png" );
		m_pBackgroundTextures["mg2_mantis"] = new PatternManager( bg_path + "part1/mg2/ST_mg2_mantis_26.png" );
		m_pBackgroundTextures["mg2_trunk"] = new PatternManager( bg_path + "part1/mg2/ST_mg2_trunk_27.png" );
		m_pBackgroundTextures["mg2_crater_loop"] = new PatternManager( bg_path + "part1/mg2/ST_mg2_crater_28.png", craterRepetition );
		m_pBackgroundTextures["mg2_star1"] = new SpriteManager( bg_path + "part1/mg2/AS_mg2_star1_29.png", 1, 2, slowAnimationDelay );
		m_pBackgroundTextures["mg2_star2"] = new SpriteManager( bg_path + "part1/mg2/AS_mg2_star2_30.png", 1, 2, slowAnimationDelay );

		m_pBackgroundTextures["mg1_greyplant"] = new PatternManager( bg_path + "part1/mg1/ST_mg1_grey_plant_17.png" );
		m_pBackgroundTextures["mg1_rock1"] = new PatternManager( bg_path + "part1/mg1/ST_mg1_rock1_18.png" );
		m_pBackgroundTextures["mg1_rock2"] = new PatternManager( bg_path + "part1/mg1/ST_mg1_rock2_19.png" );
		m_pBackgroundTextures["mg1_startfloor"] = new PatternManager( bg_path + "part1/mg1/ST_mg1_start_floor_20.png" );
		m_pBackgroundTextures["mg1_floor_loop"] = new PatternManager( bg_path + "part1/mg1/STL_mg1_floor_21.png", bottomFloorRepetition );
		m_pBackgroundTextures["mg1_topfloor_loop"] = new PatternManager( bg_path + "part1/mg1/STL_mg1_top_floor_22.png", topFloorRepetition );

		m_pBackgroundTextures["fg3_blueplant"] = new PatternManager( bg_path + "part1/fg3/ST_fg3_blue_plant_35.png" );
		m_pBackgroundTextures["fg3_topgreyplant"] = new PatternManager( bg_path + "part1/fg3/ST_fg3_grey_plant_roof_36.png" );
		m_pBackgroundTextures["fg3_greyplant"] = new PatternManager( bg_path + "part1/fg3/ST_fg3_grey_plant_37.png" );
		m_pBackgroundTextures["fg3_rock1"] = new PatternManager( bg_path + "part1/fg3/ST_fg3_rock1_38.png" );
		m_pBackgroundTextures["fg3_startcurtain"] = new PatternManager( bg_path + "part1/fg3/ST_fg3_start_curtain_39.png" );
		m_pBackgroundTextures["fg3_curtain"] = new PatternManager( bg_path + "part1/fg3/ST_fg3_curtain_40.png" );
		m_pBackgroundTextures["fg3_startprops"] = new PatternManager( bg_path + "part1/fg3/ST_fg3_start_props_41.png" );
		m_pBackgroundTextures["fg3_trunk"] = new PatternManager( bg_path + "part1/fg3/ST_fg3_trunk_42.png" );
		m_pBackgroundTextures["fg3_rock2"] = new PatternManager( bg_path + "part1/fg3/ST_fg3_rock2_43.png" );
		m_pBackgroundTextures["fg3_rock3"] = new PatternManager( bg_path + "part1/fg3/ST_fg3_rock3_44.png" );
		m_pBackgroundTextures["fg3_rock4"] = new PatternManager( bg_path + "part1/fg3/ST_fg3_rock4_45.png" );
		m_pBackgroundTextures["fg3_blueplant2"] = new PatternManager( bg_path + "part1/fg3/ST_fg3_blue_plant2_46.png" );
	
		m_pBackgroundTextures["fg2_star1"] = new PatternManager( bg_path + "part1/fg2/ST_fg2_star1_32.png" );
		m_pBackgroundTextures["fg2_frogbot"] = new PatternManager( bg_path + "part1/fg2/ST_fg2_frogbot_33.png" );
		m_pBackgroundTextures["fg2_planet"] = new PatternManager( bg_path + "part1/fg2/ST_fg2_planet_34.png" );

		m_pBackgroundTextures["fg1_star"] = new PatternManager( bg_path + "part1/fg1/ST_fg1_star1_31.png" );
	}

	// part 2
	{

	}
}

void ResourcesLinker::ReleaseTextures( )
{
	ReleaseEntities( );
	ReleaseBackgroundProps( );
}

void ResourcesLinker::ReleaseEntities( )
{
	delete m_pCupheadIdle;
	delete m_pCupheadRun;
}

void ResourcesLinker::ReleaseBackgroundProps( )
{
	for ( std::pair<const std::string, TextureManager*>& pTexture : m_pBackgroundTextures )
	{
		delete pTexture.second;
	}
	m_pBackgroundTextures.clear( );
}
