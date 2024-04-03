#pragma once
#include "TextureManager.h"

class SpriteManager final :
    public TextureManager
{
public:
    explicit SpriteManager( const std::string& texturePath, int rows, int cols, float frameDelay, bool boomerang = false, const Vector2f& offset = {} );
    SpriteManager( const SpriteManager& other ) = delete;
    virtual ~SpriteManager( ) override;

    virtual void Draw( const Point2f& pos, bool flipX = false, bool flipY = false ) const override;

    virtual void Update( float elapsedSec ) override;

    void Reset( );

    virtual float GetWidth( ) const override;
    virtual float GetHeight( ) const override;

    SpriteManager& operator=( const SpriteManager& rhs ) = delete;

private:
    const int mk_Rows;
    const int mk_Cols;

    const float mk_FrameDelay;
    const bool mk_Boomerang;

    Texture* m_pTexture;

    int m_CurrentFrame;
    int m_Increment;
    float m_AccumulatedTime;

    Rectf m_SourceRect;
};

