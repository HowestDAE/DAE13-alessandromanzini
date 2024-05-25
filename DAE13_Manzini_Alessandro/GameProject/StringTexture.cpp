#include "pch.h"
#include "StringTexture.h"
#include "Texture.h"

StringTexture::StringTexture( const Point2f& position, const std::string& text, const std::string& fontPath, int size, const Color4f& color )
	: mk_FontPath{ fontPath }
	, mk_Text{ text }
	, mk_Size{ size }
	, m_Position{ position }
{
	Initialize( color );
}

StringTexture::~StringTexture( )
{
	Release( );
}

StringTexture::StringTexture( const StringTexture& other )
	: mk_FontPath{ other.mk_FontPath }
	, mk_Text{ other.mk_Text }
	, mk_Size{ other.mk_Size }
	, m_Position{ other.m_Position }
	, m_pTexture{}
{
	Initialize( );
}

StringTexture::StringTexture( StringTexture&& other ) noexcept
	: mk_FontPath{ other.mk_FontPath }
	, mk_Text{ other.mk_Text }
	, mk_Size{ other.mk_Size }
	, m_Position{ std::move( other.m_Position ) }
	, m_pTexture{ std::move( other.m_pTexture ) }
{
	other.m_pTexture = nullptr;
}

void StringTexture::Initialize( const Color4f& color )
{
	m_pTexture = new Texture( mk_Text, mk_FontPath, mk_Size, color );
}

void StringTexture::Release( )
{
	if ( m_pTexture != nullptr )
	{
		delete m_pTexture;
		m_pTexture = nullptr;
	}
}

void StringTexture::Draw( ) const
{
	const Point2f pos{ m_Position.x - m_pTexture->GetWidth( ) / 2.f, m_Position.y - m_pTexture->GetHeight( ) / 2.f };
	m_pTexture->Draw( pos );
}

void StringTexture::SetColor( const Color4f& color )
{
	Release( );
	Initialize( color );
}

void StringTexture::SetPosition( const Point2f& position )
{
	m_Position = position;
}
