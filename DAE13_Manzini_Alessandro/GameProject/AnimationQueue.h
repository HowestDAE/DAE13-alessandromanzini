#pragma once
#include <deque>
#include "TextureInfo.h"

class Texture2D;
class AnimationQueue
{
public:
	AnimationQueue( );

	bool GetReady( ) const;

	void NextAnimation( TextureInfo& textureInfo );
	void NextAnimation( TextureInfo& textureInfo, bool );

	void Enqueue( const TextureInfo& textureInfo, bool priority = false );
	void Clear( );

private:
	std::deque<TextureInfo> m_TexturesDeque;

};
