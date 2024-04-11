#include "pch.h"
#include "Entity.h"

Entity::Entity( const Point2f& position )
    : TexturedModel( position )
    , m_Velocity{}
{
}

//void Entity::Update( float elapsedSec )
//{
//    
//}

void Entity::ProcessPlatformCollision( const Vector2f& displacement )
{
	m_Location += displacement;
}

Vector2f Entity::GetVelocity( ) const
{
    return m_Velocity;
}

bool Entity::TryQueueTexture( TextureManager* pTexture, bool flipX, bool flipY )
{
	const bool horizontalFlip{ m_FlipX != flipX };
	// Queue texture only if different.
	if ( m_pTextureManager != pTexture || horizontalFlip )
	{
		const bool textureOnQueue{ m_AnimationQueue.Queue( pTexture ) };
		if ( textureOnQueue )
		{
			m_FlipX = flipX;
			m_FlipY = flipY;
			m_pTextureManager = m_AnimationQueue.GetCurrentTexture( );
		}
		return textureOnQueue;
	}
	return false;
}
