#pragma once
struct _TTF_Font;
namespace dae
{
	/**
	 * Simple RAII wrapper for an _TTF_Font
	 */
	class Font
	{
	public:
		_TTF_Font* GetFont() const;
		explicit Font(const std::string& fullPath, unsigned int size);
		~Font();

		//avoid font to be moved or copied anywhere -> RAII takes care of that
		Font(const Font &) = delete;
		Font(Font &&) = delete;
		Font & operator= (const Font &) = delete;
		Font & operator= (const Font &&) = delete;
	private:
		_TTF_Font* m_Font;
		unsigned int m_Size;
	};
}
