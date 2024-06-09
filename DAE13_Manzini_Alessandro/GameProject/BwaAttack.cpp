#include "pch.h"
#include "BwaAttack.h"
#include "Constants.h"
#include "ResourcesLinker.h"
#include "Sprite.h"

const float BwaAttack::smk_BwaChangeSpeedTime{ .6f };
const float BwaAttack::smk_BwaChangeSpeedDuration{ 0.25f };

BwaAttack::BwaAttack( const Point2f& position )
	: Entity{ position, 1 }
	, m_StartLocation{ position }
	, m_Letters{}
	, m_VisibleLetterIndex{ 1 }
	, m_Distance{}
	, m_TravelTime{}
	, m_IsActive{}
{
	SetCollisionManager( &m_CollisionManager );
	m_Velocity.Set( -Constants::sk_BwaSpeed.x, 0.f );
}

void BwaAttack::Draw( ) const
{
	if ( !m_IsActive ) return;

	Entity::Draw( );

	for( int i{}; i < m_VisibleLetterIndex; ++i )
	{
		m_Letters.at( i ).pSprite->Draw( m_Letters.at( i ).position + m_Location );
	}
}

void BwaAttack::Update( float elapsedSec )
{
	Entity::Update( elapsedSec );

	if( m_IsActive )
	{
		UpdateLocation( elapsedSec );
		m_Distance += abs(m_Velocity.x * elapsedSec);
		m_TravelTime += elapsedSec;

		if ( m_VisibleLetterIndex < m_Letters.size() && m_Distance >= m_Letters.at( m_VisibleLetterIndex ).pSprite->GetWidth() )
		{
			++m_VisibleLetterIndex;
			m_Distance = 0.f;	
		}
		for ( int i{}; i < m_VisibleLetterIndex; ++i )
		{
			m_Letters.at( i ).pSprite->Update( elapsedSec );
		}

		if ( m_TravelTime >= smk_BwaChangeSpeedTime + smk_BwaChangeSpeedDuration )
		{
			m_Velocity.y = 0.f;
		}
		else if( m_TravelTime >= smk_BwaChangeSpeedTime )
		{
			m_Velocity.y = Constants::sk_BwaSpeed.y;
		}
	}
}

bool BwaAttack::GetIFrameState( ) const
{
	return !m_IsActive;
}

void BwaAttack::Reset( )
{
	m_Location = m_StartLocation;
	m_VisibleLetterIndex = 1;
	m_Distance = 0.f;
	m_TravelTime = 0.f;
	m_IsActive = true;
}

void BwaAttack::Kill( )
{
	m_IsActive = false;
}

void BwaAttack::LinkTexture( ResourcesLinker* pResourcesLinker )
{
	m_Letters.push_back( Letter{ pResourcesLinker->GetSprite( "tuba_bw_letter" ), Point2f{} } );

	const int aCount{ 5 };
	Vector2f offset{};
	for ( int i{}; i < aCount; ++i )
	{
		offset.x += m_Letters.at( i ).pSprite->GetWidth( );
		m_Letters.push_back( Letter{ pResourcesLinker->GetSprite( "tuba_a_letter" ), offset.ToPoint2f( ) } );
	}
	offset.x += (m_Letters.end( )-1)->pSprite->GetWidth( );
	m_Letters.push_back( Letter{ pResourcesLinker->GetSprite( "tuba_exclamation_mark" ), offset.ToPoint2f( ) } );

	std::vector<CollisionCircle> collisionCircles{ m_Letters.size( ) };
	collisionCircles.clear( );
	for( const Letter& letter : m_Letters )
	{
		collisionCircles.push_back( CollisionCircle{ letter.position.x + 50.f, 50.f, 50.f, CollisionType::noHit } );
	}
	m_CollisionManager = CollisionManager{ collisionCircles, &m_Location };
}
