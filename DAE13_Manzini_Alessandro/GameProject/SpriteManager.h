#pragma once
#include <vector>
class Sprite;

class SpriteManager
{
public:


private:
	std::vector<std::vector<Sprite*>> m_pSprites;
	std::vector<int> m_SpriteFrames;

};


