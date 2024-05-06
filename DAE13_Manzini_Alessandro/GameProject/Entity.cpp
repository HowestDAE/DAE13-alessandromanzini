#include "pch.h"
#include "Entity.h"
#include "Constants.h"
#include "PlatformManager.h"

Entity::Entity( const Point2f& position, int hp, int contactDamage )
    : TexturedModel( position )
    , CollidableEntity( contactDamage )
    , m_IsAlive{ true }
    , m_HP{ hp }
    , m_Velocity{}
    , m_FlashElapsedTime{}
{
}

void Entity::Update( float elapsedSec )
{
    m_AnimationQueue.NextAnimation( m_TextureInfo );
}

void Entity::UpdateHitFlashing( float elapsedSec, float epsilonTime, bool toggle )
{
    if ( m_TextureFlashing || toggle )
    {
        m_FlashElapsedTime += elapsedSec;

        if ( m_FlashElapsedTime >= epsilonTime )
        {
            // toggle if toggle
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

void Entity::Hit( int damage )
{
    m_HP -= damage;

    m_TextureFlashing = true;
    m_FlashElapsedTime = 0.f;

    m_IsAlive = (m_HP > 0);
}

Vector2f Entity::GetVelocity( ) const
{
    return m_Velocity;
}

bool Entity::GetIsAlive( ) const
{
    return m_IsAlive;
}
