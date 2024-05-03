#include "pch.h"
#include "AnimationQueue.h"
#include "Texture2D.h"
#include "iostream"

AnimationQueue::AnimationQueue( )
    : m_TexturesDeque{}
{
}

void AnimationQueue::NextAnimation( TextureInfo& textureInfo )
{
    // If the queue is not empty...
    if ( !m_TexturesDeque.empty( ) && textureInfo.pTexture->GetIsReady( ) )
    {
        // give the next step
        textureInfo = m_TexturesDeque.front( );
        m_TexturesDeque.pop_front( );
    }
}

void AnimationQueue::Enqueue( const TextureInfo& textureInfo, bool priority )
{
    if ( priority )
    {
        Clear( );
    }
    else
    {
        // If the last animation on queue is optional, substitute
        if ( !m_TexturesDeque.empty() && m_TexturesDeque.back( ).pTexture->GetIsReady( ) )
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
