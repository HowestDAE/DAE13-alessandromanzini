#include "pch.h"
#include "SoundManager.h"
#include "ResourcesLinker.h"
#include "SoundStream.h"
#include "SoundEffect.h"

ResourcesLinker const* SoundManager::smk_pResourcesLinker{};

void SoundManager::Loop( const std::string& uid, bool pause )
{
	SoundStream const* const pSoundStream{ smk_pResourcesLinker->GetSoundStream( uid ) };

	if ( !pause )
	{
		if ( pSoundStream->IsPlaying( ) )
		{
			pSoundStream->Resume( );
		}
		else
		{
			pSoundStream->Play( true );
		}
	}
	else
	{
		pSoundStream->Pause( );
	}
}

void SoundManager::Play( const std::string& uid, int count )
{
	SoundEffect const* const pSoundEffect{ smk_pResourcesLinker->GetSoundEffect( uid ) };
	
	pSoundEffect->Play( count );
}

void SoundManager::Stop( const std::string& uid )
{
	SoundEffect const* const pSoundEffect{ smk_pResourcesLinker->GetSoundEffect( uid ) };

	pSoundEffect->StopAll( );
}

void SoundManager::Reset( )
{
	smk_pResourcesLinker->ResetSound( );
}

void SoundManager::LinkResources( ResourcesLinker const* pResourcesLinker )
{
	smk_pResourcesLinker = pResourcesLinker;
}
