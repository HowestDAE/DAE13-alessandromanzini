#pragma once
#include "TextureManager.h"
#include "SpriteManager.h"

class CompositeSpriteManager final :
    public TextureManager
{
public:
    explicit CompositeSpriteManager( SpriteManager* pBegin, SpriteManager* pLoop, SpriteManager* pEnd );
    CompositeSpriteManager(const CompositeSpriteManager& other ) = default;
    virtual ~CompositeSpriteManager( ) override = default;

    virtual void Draw( const Point2f& pos, bool flipX = false, bool flipY = false ) const override;
    virtual void Update( float elapsedSec ) override;

    virtual float GetWidth( ) const override;
    virtual float GetHeight( ) const override;

    TextureManager* GetLoopSprite( ) const;

    virtual void ForceReady( ) override;
    virtual bool GetIsReady( ) const override;
    virtual float GetAnimationTimer( ) const override;

    virtual void Reset( ) override;

    CompositeSpriteManager& operator=( const CompositeSpriteManager& rhs ) = default;

private:
    enum class AnimationPhase;
    AnimationPhase m_Phase;

    SpriteManager* m_pCurrentSprite;

    SpriteManager* m_pBeginSprite;
    SpriteManager* m_pLoopSprite;
    SpriteManager* m_pEndSprite;

    void SetPhase( AnimationPhase phase );
    void RequestEnd( );
};

enum class CompositeSpriteManager::AnimationPhase
{
    begin,
    loop,
    end,
    over
};
