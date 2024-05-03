#pragma once
#include <deque>
#include "TextureInfo.h"

class Texture2D;
class AnimationQueue
{
public:
	AnimationQueue( );

	void NextAnimation( TextureInfo& textureInfo );

	void Enqueue( const TextureInfo& textureInfo, bool priority = false );
	void Clear( );

private:
	std::deque<TextureInfo> m_TexturesDeque;
};
