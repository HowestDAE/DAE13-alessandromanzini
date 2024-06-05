#pragma once
#include "vector"
#include "unordered_map"
class SoundStream;
class SoundEffect;
class ResourcesLinker;
class SoundManager final
{
public:
	static void Loop( const std::string& uid, bool pause = false );
	static void Play( const std::string& uid, int count = 0 );
	static void Stop( const std::string& uid );

	static void Reset( );

	static void LinkResources( ResourcesLinker const* pResourcesLinker );

private:
	static ResourcesLinker const* smk_pResourcesLinker;

};

