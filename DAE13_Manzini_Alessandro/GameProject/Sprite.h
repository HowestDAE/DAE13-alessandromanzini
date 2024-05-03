#pragma once
#include "Texture2D.h"
#include "SpriteSettings.h"

class Sprite final :
    public Texture2D
{
public:
    explicit Sprite( Texture* pTexture, const SpriteSettings& spriteSettings );
    explicit Sprite( Texture* pTexture, int rows, int cols, float frameDelay, bool boomerang = false, const Vector2f& offset = {}, bool mustComplete = false );
    Sprite( const Sprite& other ) = delete;
    virtual ~Sprite( ) override = default;

    virtual void Draw( const Point2f& pos, bool flipX = false, bool flipY = false ) const override;

    virtual void Update( float elapsedSec ) override;

    virtual float GetWidth( ) const override;
    virtual float GetHeight( ) const override;

    bool GetIsLastFrameReached( ) const;
    virtual void ForceReady( ) override;
    virtual bool GetIsReady( ) const override;
    virtual float GetAnimationTimer( ) const override;

    int GetCurrentFrame( ) const;
    void SetCurrentFrame( int currentFrame );
    
    // Resets animation data
    virtual void Reset( ) override;

    Sprite& operator=( const Sprite& rhs ) = delete;

private:
    const int mk_Rows;
    const int mk_Cols;

    const float mk_FrameDelay;
    const bool mk_Boomerang;

    const float mk_TotalAnimationTime;

    const bool mk_MustComplete;

    Rectf m_SourceRect;

    int m_CurrentFrame;
    int m_Increment;
    float m_AccumulatedTime;

    bool m_LastFrameReached;
};

