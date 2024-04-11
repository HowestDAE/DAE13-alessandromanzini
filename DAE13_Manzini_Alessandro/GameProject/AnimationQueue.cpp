#include "pch.h"
#include "AnimationQueue.h"
#include "TextureManager.h"

AnimationQueue::AnimationQueue( )
    : m_pCurrentTexture{ nullptr }
{
}

TextureManager* AnimationQueue::GetCurrentTexture( ) const
{
    return m_pCurrentTexture;
}

bool AnimationQueue::Queue( TextureManager* pTexture )
{
    if ( m_pCurrentTexture == nullptr || m_pCurrentTexture->GetIsReady( ) )
    {
        pTexture->Reset( );
        m_pCurrentTexture = pTexture;
        return true;
    }

    m_pCurrentTexture->ForceReady( );

    return false;
}
