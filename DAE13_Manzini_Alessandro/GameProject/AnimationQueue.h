#pragma once

class TextureManager;
class AnimationQueue
{
public:
	AnimationQueue( );

	TextureManager* GetCurrentTexture( ) const;

	// Queue the texture. Returns true if successful, false if not.
	bool Queue( TextureManager* pTexture );

private:
	TextureManager* m_pCurrentTexture;
};
