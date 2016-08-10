#ifndef INCLUDED_BITMAP
#define INCLUDED_BITMAP

#include "Color.h"

#include <cstdint>
#include <vector>

class Bitmap
{
public:
	Bitmap( int Width, int Height );
	~Bitmap();

	Color&				Pixel( uint16_t x, uint16_t y );
	void				DumpToFile( const std::string& FileName );

	int					Width() const { return m_Width; }
	int					Height() const { return m_Height; }

private:
	Bitmap( const Bitmap& );
	Bitmap( const Bitmap&& );
	Bitmap& operator=( const Bitmap& );

	int					m_Width;
	int					m_Height;
	std::vector<Color>	m_Pixels;
};

#endif
