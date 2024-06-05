#include "pch.h"
#include "Entity.h"
#include "Constants.h"
#include "PlatformManager.h"
#include "Texture2D.h"
#include <stdexcept>

Entity::Entity( const Point2f& position, int hp, int contactDamage, bool isPink )
    : TexturedModel( position )
    , CollidableEntity( contactDamage, isPink )
    , m_IsAlive{ true }
    , m_HP{ hp }
    , m_Velocity{}
    , m_FlashElapsedTime{}
    , m_AnimationQueues{}
    , m_TextureInfos{}
    , m_BacksideLimitIndex{}
{
}

Entity::Entity( Entity&& other ) noexcept
    : TexturedModel( other.m_Location.ToPoint2f( ) )
    , CollidableEntity( other.GetContactDamage( ), other.GetIsPink( ) )
    , m_IsAlive{ other.GetIsAlive( ) }
    , m_HP{ other.GetHP( ) }
    , m_Velocity{ other.GetVelocity( ) }
    , m_FlashElapsedTime{ other.m_FlashElapsedTime }
    , m_AnimationQueues{ std::move( other.m_AnimationQueues ) }
    , m_TextureInfos{ std::move( other.m_TextureInfos ) }
    , m_BacksideLimitIndex{ other.m_BacksideLimitIndex }
{
}

void Entity::Draw( ) const
{
    for ( int i{ m_BacksideLimitIndex }; i < m_TextureInfos.size(); ++i )
    {
        Draw( i );
    }
    DrawCollision( );
}

void Entity::DrawBackside( ) const
{
    for ( int i{}; i < m_BacksideLimitIndex; ++i )
    {
        Draw( i );
    }
}

void Entity::Update( float elapsedSec )
{
    for ( int i{}; i < m_AnimationQueues.size( ); ++i )
    {
        if ( m_TextureInfos[i].pTexture )
        {
            m_TextureInfos[i].pTexture->Update( elapsedSec );
        }

        m_AnimationQueues[i].NextAnimation( m_TextureInfos[i] );
    }

    UpdateHitFlashing( elapsedSec, Constants::sk_DefaultFlashDuration );
}

bool Entity::CheckCollision( PlatformManager const* pPlatformManager )
{
    Vector2f displacement{};
    const bool collision{ pPlatformManager->CheckCollision( this, displacement ) };

    m_Location += displacement;
    return collision;
}

Vector2f Entity::GetVelocity( ) const
{
    return m_Velocity;
}

bool Entity::GetIsAlive( ) const
{
    return m_IsAlive;
}

int Entity::GetHP( ) const
{
    return m_HP;
}

float Entity::GetTextureWidth( ) const
{
    if ( m_TextureInfos[0].pTexture )
    {
        return m_TextureInfos[0].pTexture->GetWidth( );
    }
    return 0.f;
}

float Entity::GetTextureHeight( ) const
{
    if ( m_TextureInfos[0].pTexture )
    {
        return m_TextureInfos[0].pTexture->GetHeight( );
    }
    return 0.f;
}

Vector2f Entity::GetTextureOffset( ) const
{
    if ( m_TextureInfos[0].pTexture )
    {
        return m_TextureInfos[0].pTexture->GetOffset( );
    }
    return Vector2f{};
}

void Entity::Draw( int index ) const
{
    TexturedModel::Draw( m_TextureInfos[index] );
}

void Entity::UpdateLocation( float elapsedSec )
{
    m_Location += m_Velocity * elapsedSec;
}

void Entity::UpdateHitFlashing( float elapsedSec, float epsilonTime, bool toggle )
{
    if ( m_TextureFlashing || toggle )
    {
        m_FlashElapsedTime += elapsedSec;

        if ( m_FlashElapsedTime >= epsilonTime )
        {
            // toggle if toggle, otherwise se to false
            m_TextureFlashing = toggle && !m_TextureFlashing;
            m_FlashElapsedTime = 0.f;
        }
    }
}

void Entity::Hit( int damage )
{
    if ( GetIsAlive( ) && damage > 0 )
    {
        m_HP -= damage;

        m_TextureFlashing = true;
        m_FlashElapsedTime = 0.f;

        m_IsAlive = (m_HP > 0);
        if ( !GetIsAlive( ) )
        {
            Kill( );
        }
    }
}

bool Entity::GetIFrameState( ) const
{
    return m_TextureFlashing;
}

void Entity::InitializeQueues( unsigned int count, unsigned int backsideIndex )
{
    if ( backsideIndex > count )
    {
        throw std::invalid_argument( "Tried to set the backside index to " + std::to_string( backsideIndex ) + " while count is " + std::to_string( count ) + ". Backside index must be lower/equal than count." );
    }
    m_AnimationQueues = std::vector<AnimationQueue>( count );
    m_TextureInfos = std::vector<TextureInfo>( count );
    m_BacksideLimitIndex = backsideIndex;
}

void Entity::QueueTexture( unsigned int index, const TextureInfo& textureInfo, bool priority )
{
    if ( index > m_AnimationQueues.size( ) )
    {
        throw std::invalid_argument( "Trying to queue texture at index " + std::to_string( index ) + " but max index is " + std::to_string( m_AnimationQueues.size( ) - 1 ) + "." );
    }

    m_AnimationQueues[index].Enqueue( textureInfo, priority );
}

void Entity::QueueTexture( unsigned int index, Texture2D* pTexture, bool flipX, bool flipY, bool priority )
{
    QueueTexture( index, TextureInfo{ pTexture, flipX, flipY }, priority );
}

bool Entity::IsQueueReady( unsigned int index ) const
{
    return m_TextureInfos[index].pTexture && m_TextureInfos[index].pTexture->GetIsReady( );
}

void Entity::Kill( )
{
    m_IsAlive = false;
    m_HP = 0;
}

void Entity::Revive( int hp )
{
    m_IsAlive = true;
    m_HP = hp;
}
