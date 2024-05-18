#include "pch.h"
#include "Entity.h"
#include "Constants.h"
#include "PlatformManager.h"
#include "Texture2D.h"

Entity::Entity( const Point2f& position, int hp, int contactDamage )
    : TexturedModel( position )
    , CollidableEntity( contactDamage )
    , m_IsAlive{ true }
    , m_HP{ hp }
    , m_Velocity{}
    , m_FlashElapsedTime{}
    , m_AnimationQueues{}
    , m_TextureInfos{}
{
}

void Entity::Draw( ) const
{
    for ( const TextureInfo& textureInfo : m_TextureInfos )
    {
        TexturedModel::Draw( textureInfo );
    }
    DrawCollision( );
}

void Entity::Update( float elapsedSec )
{
    for ( int i{}; i < m_AnimationQueues.size( ); ++i )
    {
        m_AnimationQueues[i].NextAnimation( m_TextureInfos[i] );
        m_TextureInfos[i].pTexture->Update( elapsedSec );
    }

    UpdateHitFlashing( elapsedSec, Constants::sk_DefaultFlashDuration );
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

void Entity::CheckCollision( PlatformManager const* pPlatformManager )
{
    const Vector2f displacement{ pPlatformManager->GetDisplacementFromPlatform( this ) };
    m_Location += displacement;
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
    return m_TextureInfos[0].pTexture->GetWidth();
}

float Entity::GetTextureHeight( ) const
{
    return m_TextureInfos[0].pTexture->GetHeight( );
}

void Entity::Hit( int damage )
{
    m_HP -= damage;

    m_TextureFlashing = true;
    m_FlashElapsedTime = 0.f;

    m_IsAlive = (m_HP > 0);
}

void Entity::InitializeQueues( int count )
{
    m_AnimationQueues = std::vector<AnimationQueue>( count );
    m_TextureInfos = std::vector<TextureInfo>( count );
}

void Entity::QueueTexture( int index, Texture2D* pTexture, bool flipX, bool flipY, bool priority )
{
    m_AnimationQueues[index].Enqueue( TextureInfo{ pTexture, flipX, flipY }, priority );
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
