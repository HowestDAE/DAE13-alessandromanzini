#pragma once
class Texture;

class StringTexture final
{
public:
	explicit StringTexture( const Point2f& position, const std::string& text, const std::string& fontPath, int size, const Color4f& color = {} );
	~StringTexture( ) noexcept;

	StringTexture( const StringTexture& other );
	StringTexture( StringTexture&& other ) noexcept;
	StringTexture& operator=( const StringTexture& other ) = delete;
	StringTexture& operator=( StringTexture&& other ) = delete;

	void Draw( bool center = true ) const;

	void SetColor( const Color4f& color );
	void SetText( const std::string& text );
	void SetPosition( const Point2f& position );

private:
	const std::string mk_FontPath;
	const int mk_Size;

	std::string m_Text;
	Color4f m_Color;

	Texture* m_pTexture;
	Point2f m_Position;

	void Initialize( );
	void Release( );

};

