#include "pch.h"
#include "AnimationQueue.h"
#include "Texture2D.h"
#include "Sprite.h"
#include "iostream"

AnimationQueue::AnimationQueue( )
    : m_TexturesDeque{}
{
}

bool AnimationQueue::GetReady( ) const
{
    return m_TexturesDeque.empty( );
}

void AnimationQueue::NextAnimation( TextureInfo& textureInfo )
{
    const bool canGetNext{ textureInfo.pTexture == nullptr || textureInfo.pTexture->GetIsReady( ) };
    // If the queue is not empty...
    if ( !m_TexturesDeque.empty( ) && canGetNext )
    {
        // give the next step
        textureInfo = m_TexturesDeque.front( );

        // Reset texture if it is not a loop
        if ( static_cast<Sprite*>( textureInfo.pTexture )->GetMustComplete( ) 
            && textureInfo.pTexture->GetIsReady( ) )
        {
            textureInfo.pTexture->Reset( );
        }

        m_TexturesDeque.pop_front( );
    }
}

void AnimationQueue::NextAnimation( TextureInfo& textureInfo, bool )
{
    if ( GetReady( ) && textureInfo.pTexture && textureInfo.pTexture->GetIsReady( ) && textureInfo.pTexture->GetAnimationTimer() != 0.f )
    {
        textureInfo.pTexture = nullptr;
    }
    else
    {
        NextAnimation( textureInfo );
    }
}

void AnimationQueue::Enqueue( const TextureInfo& textureInfo, bool priority )
{
    if ( textureInfo.pTexture == nullptr )
    {
        throw std::invalid_argument( "Cannot enqueue a NULL texture pointer." );
    }

    if ( priority )
    {
        Clear( );
    }
    else
    {
        // If the last animation on queue is optional, pop
        if ( !m_TexturesDeque.empty() && 
            !static_cast<Sprite*>(m_TexturesDeque.back( ).pTexture)->GetMustComplete( ) )
        {
            m_TexturesDeque.pop_back( );
        }
    }
    m_TexturesDeque.push_back( textureInfo );
}

void AnimationQueue::Clear( )
{
    m_TexturesDeque.clear( );
}
