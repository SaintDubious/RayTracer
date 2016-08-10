#include "Bitmap.h"

#include <cassert>
#include <fstream>
#include <iostream>

namespace {

#pragma pack(2)
struct BitmapFileHeader
{
  unsigned char	bfType[2];    		// file type - must be "BM" for bitmap
  uint32_t		bfSize;       		// size in bytes of the bitmap file
  uint32_t		bfReserved;   		// must be zero
  uint32_t		bfOffBits;    		// offset in bytes from the BitmapFileHeader
									// structure to the bitmap bits
};

struct BitmapInfoHeader
{
  uint32_t  	biSize;				// number of bytes required by the structure
  uint32_t  	biWidth;			// width of the image in pixels
  uint32_t  	biHeight;			// height of the image in pixels
  uint16_t		biPlanes;			// number of planes for target device - must be 1
  uint16_t   	biBitCount;			// bits per pixel - 1, 4, 8, 16, 24, or 32
  uint32_t  	biCompression;		// type of compression - BI_RGB for uncompressed
  uint32_t  	biSizeImage;		// size in bytes of the image
  uint32_t  	biXPelsPerMeter;	// horizontal resolution in pixels per meter
  uint32_t  	biYPelsPerMeter;	// vertical resolution in pixels per meter
  uint32_t  	biClrUsed;			// number of colors used
  uint32_t  	biClrImportant;		// number of colors that are important
};

int PaddedWidth( int Width )
{
	return Width + (Width % 4);
}

}

Bitmap::Bitmap( int Width, int Height )
	: m_Width( Width )
	, m_Height( Height )
{
	assert(sizeof(BitmapFileHeader) == 14);
	assert(sizeof(BitmapInfoHeader) == 40);

	if (m_Width > UINT16_MAX || m_Height > UINT16_MAX) {
		throw std::runtime_error( "Sorry, can't go over UINT16_MAX in width or height" );
	}
	m_Pixels.resize( PaddedWidth( m_Width ) * m_Height );
}

Bitmap::~Bitmap()
{
}

Color& Bitmap::Pixel( uint16_t x, uint16_t y )
{
	if (x>=m_Width || y>= m_Height) {
		throw std::runtime_error( "Trying to get pixel outside of range" );
	}
	return m_Pixels[y*PaddedWidth( m_Width ) + x];
}

void Bitmap::DumpToFile( const std::string& FileName )
{
	std::ofstream str( FileName.c_str(), std::ios_base::out | std::ios::binary );
	
	BitmapFileHeader FileHeader;
	FileHeader.bfType[0]		= 'B';
	FileHeader.bfType[1]		= 'M';
	FileHeader.bfSize			= sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader) +
								  (PaddedWidth(m_Width) * m_Height * (Color::BITS_PER_PIXEL/8));
	FileHeader.bfReserved		= 0;
	FileHeader.bfOffBits		= sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);
	str.write( reinterpret_cast<char*>(&FileHeader), sizeof(FileHeader) );

	BitmapInfoHeader InfoHeader;
	InfoHeader.biSize			= sizeof(BitmapInfoHeader);
	InfoHeader.biWidth			= m_Width;
	InfoHeader.biHeight			= m_Height;
	InfoHeader.biPlanes			= 1;
	InfoHeader.biBitCount		= Color::BITS_PER_PIXEL;
 	InfoHeader.biCompression	= 0;
 	InfoHeader.biSizeImage		= 0;
	InfoHeader.biXPelsPerMeter	= 0;
 	InfoHeader.biYPelsPerMeter	= 0;
	InfoHeader.biClrUsed		= 0;
	InfoHeader.biClrImportant	= 0;
	str.write( reinterpret_cast<char*>(&InfoHeader), sizeof(InfoHeader) );

	for (int y=0; y<m_Height; ++y) {
		for (int x=0; x<PaddedWidth( m_Width ); ++x) {
			uint8_t Red		= m_Pixels[y*PaddedWidth( m_Width ) + x].Red();
			uint8_t Green	= m_Pixels[y*PaddedWidth( m_Width ) + x].Green();
			uint8_t Blue	= m_Pixels[y*PaddedWidth( m_Width ) + x].Blue();
			str.write( reinterpret_cast<char*>(&Blue), sizeof(uint8_t) );
			str.write( reinterpret_cast<char*>(&Green), sizeof(uint8_t) );
			str.write( reinterpret_cast<char*>(&Red), sizeof(uint8_t) );
		}
	}
}

