#include "pch.h"
#include "StringTexture.h"
#include "Texture.h"

StringTexture::StringTexture( const Point2f& position, const std::string& text, const std::string& fontPath, int size, const Color4f& color )
	: mk_FontPath{ fontPath }
	, mk_Size{ size }
	, m_Text{ text }
	, m_Color{ color }
	, m_Position{ position }
{
	Initialize( );
}

StringTexture::~StringTexture( )
{
	Release( );
}

StringTexture::StringTexture( const StringTexture& other )
	: mk_FontPath{ other.mk_FontPath }
	, m_Text{ other.m_Text }
	, mk_Size{ other.mk_Size }
	, m_Position{ other.m_Position }
	, m_pTexture{}
{
	Initialize( );
}

StringTexture::StringTexture( StringTexture&& other ) noexcept
	: mk_FontPath{ other.mk_FontPath }
	, m_Text{ other.m_Text }
	, mk_Size{ other.mk_Size }
	, m_Position{ std::move( other.m_Position ) }
	, m_pTexture{ std::move( other.m_pTexture ) }
{
	other.m_pTexture = nullptr;
}

void StringTexture::Initialize( )
{
	m_pTexture = new Texture( m_Text, mk_FontPath, mk_Size, m_Color );
}

void StringTexture::Release( )
{
	if ( m_pTexture != nullptr )
	{
		delete m_pTexture;
		m_pTexture = nullptr;
	}
}

void StringTexture::Draw( bool center ) const
{
	Point2f pos{ m_Position.x, m_Position.y };
	if ( center )
	{
		pos.x -= m_pTexture->GetWidth( ) / 2.f;
		pos.y -= m_pTexture->GetHeight( ) / 2.f;
	}

	m_pTexture->Draw( std::move( pos ) );
}

void StringTexture::SetColor( const Color4f& color )
{
	m_Color = color;

	Release( );
	Initialize( );
}

void StringTexture::SetText( const std::string& text )
{
	m_Text = text;

	Release( );
	Initialize( );
}

void StringTexture::SetPosition( const Point2f& position )
{
	m_Position = position;
}
