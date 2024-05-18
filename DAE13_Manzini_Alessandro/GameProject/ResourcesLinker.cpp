#include "pch.h"
#include "ResourcesLinker.h"
#include "Texture.h"
#include "Texture2D.h"
#include "Pattern.h"
#include "Sprite.h"
#include <cassert>

ResourcesLinker::ResourcesLinker( )
	: m_pTextures{}
	, m_pInstantiatedTextures{}
	, m_TextureTypeMap{}
	, m_SpriteSettingsMap{}
	, m_PatternSettingsMap{}
{
	InitializeTextures( );
}

ResourcesLinker::~ResourcesLinker( )
{
	ReleaseTextures( );
}

Texture2D* ResourcesLinker::GetTexture( const std::string& uid )
{
	Texture2D* pTexture{};

	switch ( m_TextureTypeMap[uid] )
	{
	case TextureType::pattern:
		pTexture = new Pattern( m_pTextures[uid], m_PatternSettingsMap[uid] );
		break;
	case TextureType::sprite:
		pTexture = new Sprite( m_pTextures[uid], m_pTextures[uid + "_flash"], m_SpriteSettingsMap[uid] );
		break;
	default:
		break;
	}
	m_pInstantiatedTextures.push_back( pTexture );
	return pTexture;
}

Sprite* ResourcesLinker::GetSprite( const std::string& uid )
{
	return static_cast<Sprite*>(GetTexture( uid ));
}

Pattern* ResourcesLinker::GetPattern( const std::string& uid )
{
	return static_cast<Pattern*>(GetTexture(uid));
}

void ResourcesLinker::InitializeTextures( )
{
	InitializeEntities( );
	InitializeBackgroundProps( );
}

void ResourcesLinker::InitializeEntities( )
{
	// Cuphead
	{
		const float idleFrameDelay{ .1f };

		const float runFrameDelay{ .05f };
		const float runLoopFrameDelay{ .06f };
		const Vector2f runOffset{ -20.f, -3.f };
		const Vector2f runLoopOffset{ -20.f, 0.f };

		const float duckBeginFrameDelay{ .05f };
		const float duckEndFrameDelay{ .03f };
		const float duckLoopFrameDelay{ .09f };
		const Vector2f duckOffset{ -24.f, -3.f };
		const Vector2f duckLoopOffset{ -24.f, -3.f };
		const Vector2f duckShootOffset{ -37.f, -3.f };

		const float jumpFrameDelay{ .04f };
		const Vector2f jumpOffset{ 0.f, 0.f };
		const Vector2f parryOffset{ -20.f, -20.f };

		const float dashFrameDelay{ .05f };
		const Vector2f dashOffset{ -145.f, 0.f };

		const float shootFrameDelay{ .06f };
		const Vector2f shootOffset{ -20.f, -5.f };

		const float hitFrameDelay{ .05f };
		const Vector2f hitOffset{ -13.f, 0.f };

		const float ghostFrameDelay{ .08f };
		const Vector2f ghostOffset{ -10.f, -5.f };

		const float exAirFrameDelay{ .08f };
		const Vector2f exAirOffset{ 0.f, 0.f };

		PushSprite( "cuphead_idle", "player/character/AS_cuphead_idle_1x5.png", SpriteSettings( 1, 5, idleFrameDelay, true ) );

		PushSprite( "cuphead_run", "player/character/AS_cuphead_run_2x8.png", SpriteSettings( 2, 8, runLoopFrameDelay, false, runLoopOffset ) );
		PushSprite( "cuphead_run_begin", "player/character/AS_cuphead_run_begin_1x2.png", SpriteSettings( 1, 2, runFrameDelay, false, runOffset ) );
		PushSprite( "cuphead_run_end", "player/character/AS_cuphead_run_end_1x2.png", SpriteSettings( 1, 2, runFrameDelay, false, runOffset ) );

		PushSprite( "cuphead_duck", "player/character/AS_cuphead_duck_1x5.png", SpriteSettings( 1, 5, duckLoopFrameDelay, true, duckLoopOffset ) );
		PushSprite( "cuphead_duck_begin", "player/character/AS_cuphead_duck_begin_1x5.png", SpriteSettings( 1, 5, duckBeginFrameDelay, false, duckOffset, true ) );
		PushSprite( "cuphead_duck_end", "player/character/AS_cuphead_duck_end_1x5.png", SpriteSettings( 1, 5, duckEndFrameDelay, false, duckOffset, true ) );
		PushSprite( "cuphead_duckshoot", "player/character/AS_cuphead_duckshoot_1x3.png", SpriteSettings( 1, 3, shootFrameDelay, false, duckShootOffset ) );

		PushSprite( "cuphead_jump", "player/character/AS_cuphead_jump_2x4.png", SpriteSettings( 2, 4, jumpFrameDelay, false, jumpOffset ) );
		PushSprite( "cuphead_parry", "player/character/AS_cuphead_parry_2x4.png", SpriteSettings( 2, 4, jumpFrameDelay, false, parryOffset ) );

		PushSprite( "cuphead_dash_ground", "player/character/AS_cuphead_dash_ground_2x3.png", SpriteSettings( 2, 3, dashFrameDelay, false, dashOffset ) );
		PushSprite( "cuphead_dash_ground_begin", "player/character/AS_cuphead_dash_ground_begin_1x2.png", SpriteSettings( 1, 2, dashFrameDelay, false, dashOffset ) );
		PushSprite( "cuphead_dash_ground_end", "player/character/AS_cuphead_dash_ground_end_1x2.png", SpriteSettings( 1, 2, dashFrameDelay, false, dashOffset ) );

		PushSprite( "cuphead_dash_air", "player/character/AS_cuphead_dash_air_2x3.png", SpriteSettings( 2, 3, dashFrameDelay, false, dashOffset ) );
		PushSprite( "cuphead_dash_air_begin", "player/character/AS_cuphead_dash_air_begin_1x2.png", SpriteSettings( 1, 2, dashFrameDelay, false, dashOffset ) );
		PushSprite( "cuphead_dash_air_end", "player/character/AS_cuphead_dash_air_end_1x2.png", SpriteSettings( 1, 2, dashFrameDelay, false, dashOffset ) );

		PushSprite( "cuphead_shoot_straight", "player/character/AS_cuphead_shoot_straight_1x3.png", SpriteSettings( 1, 3, shootFrameDelay, false, shootOffset ) );
		PushSprite( "cuphead_shoot_diagonalup", "player/character/AS_cuphead_shoot_diagonalup_1x3.png", SpriteSettings( 1, 3, shootFrameDelay, false, shootOffset ) );
		PushSprite( "cuphead_shoot_diagonaldown", "player/character/AS_cuphead_shoot_diagonaldown_1x3.png", SpriteSettings( 1, 3, shootFrameDelay, false, shootOffset ) );
		PushSprite( "cuphead_shoot_down", "player/character/AS_cuphead_shoot_down_1x3.png", SpriteSettings( 1, 3, shootFrameDelay, false, shootOffset ) );
		PushSprite( "cuphead_shoot_up", "player/character/AS_cuphead_shoot_up_1x3.png", SpriteSettings( 1, 3, shootFrameDelay, false, shootOffset ) );
		
		PushSprite( "cuphead_aim_up", "player/character/AS_cuphead_aim_up_1x5.png", SpriteSettings( 1, 5, idleFrameDelay, true, shootOffset ) );
		PushSprite( "cuphead_aim_straight", "player/character/AS_cuphead_aim_straight_1x5.png", SpriteSettings( 1, 5, idleFrameDelay, true, shootOffset ) );
		PushSprite( "cuphead_aim_diagonaldown", "player/character/AS_cuphead_aim_diagonaldown_1x5.png", SpriteSettings( 1, 5, idleFrameDelay, true, shootOffset ) );
		PushSprite( "cuphead_aim_diagonalup", "player/character/AS_cuphead_aim_diagonalup_1x5.png", SpriteSettings( 1, 5, idleFrameDelay, true, shootOffset ) );
		PushSprite( "cuphead_aim_down", "player/character/AS_cuphead_aim_down_1x5.png", SpriteSettings( 1, 5, idleFrameDelay, true, shootOffset ) );
		
		PushSprite( "cuphead_ex_air_up", "player/character/AS_cuphead_ex_air_up_1x6.png", SpriteSettings( 1, 6, exAirFrameDelay, true, exAirOffset, true ) );
		PushSprite( "cuphead_ex_air_straight", "player/character/AS_cuphead_ex_air_straight_1x6.png", SpriteSettings( 1, 6, exAirFrameDelay, true, exAirOffset, true ) );
		PushSprite( "cuphead_ex_air_diagonaldown", "player/character/AS_cuphead_ex_air_diagonaldown_1x6.png", SpriteSettings( 1, 6, exAirFrameDelay, true, exAirOffset, true ) );
		PushSprite( "cuphead_ex_air_diagonalup", "player/character/AS_cuphead_ex_air_diagonalup_1x6.png", SpriteSettings( 1, 6, exAirFrameDelay, true, exAirOffset, true ) );
		PushSprite( "cuphead_ex_air_down", "player/character/AS_cuphead_ex_air_down_1x6.png", SpriteSettings( 1, 6, exAirFrameDelay, true, exAirOffset, true ) );

		PushSprite( "cuphead_runshoot_straight", "player/character/AS_cuphead_runshoot_straight_2x8.png", SpriteSettings( 2, 8, shootFrameDelay, false, shootOffset ) );

		PushSprite( "cuphead_runshoot_diagonalup", "player/character/AS_cuphead_runshoot_diagonalup_2x8.png", SpriteSettings( 2, 8, shootFrameDelay, false, shootOffset ) );
		
		PushSprite( "cuphead_hit", "player/character/AS_cuphead_hit_1x6.png", SpriteSettings( 1, 6, hitFrameDelay, false, hitOffset, true ) );
		
		PushSprite( "cuphead_ghost", "player/character/AS_cuphead_ghost_4x6.png", SpriteSettings( 4, 6, ghostFrameDelay, false, ghostOffset, true ) );
	}

	// HUD
	{
		const float oneHpFlashDelay{ 0.2f };
		PushPattern( "hud_hp_dead", "ui/hud/ST_hud_hp_dead.png" );
		PushSprite( "hud_hp_1", "ui/hud/AS_hud_hp_1_1x2.png", SpriteSettings{ 1, 2, oneHpFlashDelay } );
		PushPattern( "hud_hp_2", "ui/hud/ST_hud_hp_2.png" );
		PushPattern( "hud_hp_3", "ui/hud/ST_hud_hp_3.png" );
		PushPattern( "excard_faceup", "ui/hud/ST_hud_excard_faceup.png" );
		PushPattern( "excard_facedown", "ui/hud/ST_hud_excard_facedown.png" );
	}

	// Weapons
	{
		const float peashooterFrameDelay{ .1f };
		const Vector2f peashooterExOffset{ -90.f, 0.f };

		PushSprite( "peashooter", "player/weapons/AS_peashooter_loop_1x6.png", SpriteSettings( 1, 6, peashooterFrameDelay ) );
		PushSprite( "peashooter_ex", "player/weapons/AS_peashooter_ex_loop_2x4.png", SpriteSettings( 2, 4, peashooterFrameDelay, false, peashooterExOffset ) );
	}

	// Card
	{
		const float idleFrameDelay{ .1f };
		const float starsFrameDelay{ .08f };

		PushSprite( "card_idle", "enemy/card/AS_card_idle_1x13.png", SpriteSettings( 1, 13, idleFrameDelay, true ) );
		PushSprite( "card_spin", "enemy/card/AS_card_spin_2x9.png", SpriteSettings( 2, 9, idleFrameDelay, false, Vector2f{}, true ) );
		PushSprite( "card_stars", "enemy/card/AS_card_stars_2x8.png", SpriteSettings( 2, 8, starsFrameDelay ) );
	}

	// Toyduck
	{
		const float idleFrameDelay{ .07f };

		PushSprite( "toyduck_idle", "enemy/toyduck/AS_toyduck_idle_2x8.png", SpriteSettings( 2, 8, idleFrameDelay, false ) );
		PushSprite( "toyduck_backtire", "enemy/toyduck/AS_toyduck_backtire_2x8.png", SpriteSettings( 2, 8, idleFrameDelay, false ) );
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
		const int craterRepetition{ 4 };

		PushPattern( "bg5_bg_loop", bg_path + "STL_bg5_bg.png", PatternSettings( backgroundRepetition ) );

		PushPattern( "bg4_curtain_loop", bg_path + "part1/bg4/STL_bg4_curtain_16.png", PatternSettings( curtainRepetition ) );

		PushPattern( "bg3_moon", bg_path + "part1/bg3/ST_bg3_moon_11.png" );
		PushPattern( "bg3_rocks_loop", bg_path + "part1/bg3/STL_bg3_rocks_12.png", PatternSettings( backRocksRepetition ) );
		PushPattern( "bg3_cloud1", bg_path + "part1/bg3/ST_bg3_cloud1_13.png" );
		PushPattern( "bg3_cloud2", bg_path + "part1/bg3/ST_bg3_cloud2_14.png" );
		PushPattern( "bg3_startcurtains", bg_path + "part1/bg3/ST_bg3_start_curtains_15.png" );

		PushPattern( "bg2_entrance", bg_path + "part1/bg2/ST_bg2_entrance_04.png" );
		PushPattern( "bg2_blueplant", bg_path + "part1/bg2/ST_bg2_blue_plant_05.png" );
		PushPattern( "bg2_startrock", bg_path + "part1/bg2/ST_bg2_start_rock_06.png" );
		PushPattern( "bg2_rocks_loop", bg_path + "part1/bg2/STL_bg2_rocks_07.png", PatternSettings( frontRocksRepetition ) );
		PushPattern( "bg2_star1", bg_path + "part1/bg2/ST_bg2_star1_08.png" );
		PushPattern( "bg2_star2", bg_path + "part1/bg2/ST_bg2_star2_09.png" );
		PushPattern( "bg2_star3", bg_path + "part1/bg2/ST_bg2_star3_10.png" );

		PushPattern( "bg1_cloud1", bg_path + "part1/bg1/ST_bg1_cloud1_01.png" );
		PushPattern( "bg1_blueplant", bg_path + "part1/bg1/ST_bg1_blue_plant_02.png" );
		PushPattern( "bg1_greyplant", bg_path + "part1/bg1/ST_bg1_grey_plant_03.png" );

		PushPattern( "mg2_blueplant", bg_path + "part1/mg2/ST_mg2_blue_plant_23.png" );
		PushPattern( "mg2_craterstart", bg_path + "part1/mg2/ST_mg2_crater_start_24.png" );
		PushPattern( "mg2_frogbot", bg_path + "part1/mg2/ST_mg2_frogbot_25.png" );
		PushPattern( "mg2_mantis", bg_path + "part1/mg2/ST_mg2_mantis_26.png" );
		PushPattern( "mg2_trunk", bg_path + "part1/mg2/ST_mg2_trunk_27.png" );
		PushPattern( "mg2_crater_loop", bg_path + "part1/mg2/STL_mg2_crater_28.png", PatternSettings( craterRepetition ) );
		PushSprite( "mg2_star1", bg_path + "part1/mg2/AS_mg2_star1_29.png", SpriteSettings( 1, 2, slowAnimationDelay ) );
		PushSprite( "mg2_star2", bg_path + "part1/mg2/AS_mg2_star2_30.png", SpriteSettings( 1, 2, slowAnimationDelay ) );

		PushPattern( "mg1_greyplant", bg_path + "part1/mg1/ST_mg1_grey_plant_17.png" );
		PushPattern( "mg1_rock1", bg_path + "part1/mg1/ST_mg1_rock1_18.png" );
		PushPattern( "mg1_rock2", bg_path + "part1/mg1/ST_mg1_rock2_19.png" );
		PushPattern( "mg1_startfloor", bg_path + "part1/mg1/ST_mg1_start_floor_20.png" );
		PushPattern( "mg1_floor_loop", bg_path + "part1/mg1/STL_mg1_floor_21.png", PatternSettings( bottomFloorRepetition ) );
		PushPattern( "mg1_topfloor_loop", bg_path + "part1/mg1/STL_mg1_top_floor_22.png", PatternSettings( topFloorRepetition ) );

		PushPattern( "fg3_blueplant", bg_path + "part1/fg3/ST_fg3_blue_plant_35.png" );
		PushPattern( "fg3_topgreyplant", bg_path + "part1/fg3/ST_fg3_grey_plant_roof_36.png" );
		PushPattern( "fg3_greyplant", bg_path + "part1/fg3/ST_fg3_grey_plant_37.png" );
		PushPattern( "fg3_rock1", bg_path + "part1/fg3/ST_fg3_rock1_38.png" );
		PushPattern( "fg3_startcurtain", bg_path + "part1/fg3/ST_fg3_start_curtain_39.png" );
		PushPattern( "fg3_curtain", bg_path + "part1/fg3/ST_fg3_curtain_40.png" );
		PushPattern( "fg3_startprops", bg_path + "part1/fg3/ST_fg3_start_props_41.png" );
		PushPattern( "fg3_trunk", bg_path + "part1/fg3/ST_fg3_trunk_42.png" );
		PushPattern( "fg3_rock2", bg_path + "part1/fg3/ST_fg3_rock2_43.png" );
		PushPattern( "fg3_rock3", bg_path + "part1/fg3/ST_fg3_rock3_44.png" );
		PushPattern( "fg3_rock4", bg_path + "part1/fg3/ST_fg3_rock4_45.png" );
		PushPattern( "fg3_blueplant2", bg_path + "part1/fg3/ST_fg3_blue_plant2_46.png" );

		PushPattern( "fg2_star1", bg_path + "part1/fg2/ST_fg2_star1_32.png" );
		PushPattern( "fg2_frogbot", bg_path + "part1/fg2/ST_fg2_frogbot_33.png" );
		PushPattern( "fg2_planet", bg_path + "part1/fg2/ST_fg2_planet_34.png" );

		PushPattern( "fg1_star", bg_path + "part1/fg1/ST_fg1_star1_31.png" );
	}

	// part 2
	{

	}
}

void ResourcesLinker::ReleaseTextures( )
{
	for ( Texture2D* pTexture : m_pInstantiatedTextures )
	{
		delete pTexture;
	}
	m_pInstantiatedTextures.clear( );

	for ( std::pair<const std::string, Texture*>& pair : m_pTextures )
	{
		delete pair.second;
	}
	m_pTextures.clear( );
}

void ResourcesLinker::PushPattern( const std::string& uid, const std::string& path, const PatternSettings& settings )
{
	m_pTextures[uid] = new Texture( path );
	m_PatternSettingsMap[uid] = settings;
	m_TextureTypeMap[uid] = TextureType::pattern;
}

void ResourcesLinker::PushSprite( const std::string& uid, const std::string& path, const SpriteSettings& settings )
{
	m_pTextures[uid] = new Texture( path );
	m_pTextures[uid + "_flash"] = new Texture( path, true );
	m_SpriteSettingsMap[uid] = settings;
	m_TextureTypeMap[uid] = TextureType::sprite;
}
