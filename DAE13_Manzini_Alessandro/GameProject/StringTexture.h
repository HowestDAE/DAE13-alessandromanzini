#pragma once
class Texture;

class StringTexture final
{
public:
	explicit StringTexture( const Point2f& position, const std::string& text, const std::string& fontPath, int size, const Color4f& color = {} );
	~StringTexture( );

	StringTexture( const StringTexture& other );
	StringTexture( StringTexture&& other ) noexcept;
	StringTexture& operator=( const StringTexture& other ) = delete;
	StringTexture& operator=( StringTexture&& other ) = delete;

	void Draw( ) const;

	void SetColor( const Color4f& color );
	void SetPosition( const Point2f& position );

private:
	const std::string mk_FontPath;
	const std::string mk_Text;
	const int mk_Size;

	Texture* m_pTexture;
	Point2f m_Position;

	void Initialize( const Color4f& color = {} );
	void Release( );

};

