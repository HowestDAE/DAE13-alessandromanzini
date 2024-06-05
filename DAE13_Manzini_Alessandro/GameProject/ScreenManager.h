#pragma once
class ResourcesLinker;
class ScreenManager
{
public:
	ScreenManager( const Rectf& viewport );

	virtual void Draw( ) const = 0;
	virtual void Update( float elapsedSec ) = 0;

	virtual void KeyDownEvent( const SDL_KeyboardEvent& e ) = 0;

	virtual void LinkTexture( ResourcesLinker* pResourcesLinker ) = 0;

protected:
	static const int smk_HeadingTextSize;
	static const int smk_SmallTextSize;
	static const int smk_MediumTextSize;
	static const int smk_LargeTextSize;

	static const Color4f smk_DefaultColor;
	static const Color4f smk_ActiveColor;

	const Rectf mk_ViewPort;

};

