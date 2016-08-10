#include "Camera.h"
#include "Bitmap.h"
#include "Ray.h"
#include "Scene.h"

#include <chrono>
#include <iostream>
#include <future>

Camera::Camera()
	: m_FocalLength( 500 )
	, m_Width( 600 )
	, m_Height( 600 )
{
}

Camera::~Camera()
{
}

//#define ASYNC 1
#ifdef ASYNC

void Camera::CapturePhoto( const Scene& TheScene, Bitmap& Bmp )
{
	int HalfHeight = Bmp.Height()/2;
	int HalfWidth  = Bmp.Width()/2;
	std::vector<std::future<std::vector<Color>>> RawData;
	RawData.resize( Bmp.Height() );

	auto StartTime = std::chrono::high_resolution_clock::now();
	for (int y=HalfHeight-1; y>=-HalfHeight; --y) {
		int yOffset = (y+HalfHeight);
		RawData[yOffset] = std::async( std::launch::async, &Camera::CaptureRow, this, TheScene, HalfWidth, y );
	}
	
	for (int y=HalfHeight-1; y>=-HalfHeight; --y) {
		int yOffset = (y+HalfHeight);
		RawData[yOffset].wait();
	}
	
	auto StopTime = std::chrono::high_resolution_clock::now();
	std::cout << "Duration: " << std::chrono::duration_cast<std::chrono::milliseconds>( StopTime-StartTime ).count() << "\n";

	for (int y=HalfHeight-1; y>=-HalfHeight; --y) {
		int yOffset = (y+HalfHeight);
		std::vector<Color> Row = RawData[yOffset].get();
		for (int x=-HalfWidth; x<HalfWidth; ++x) {
			Bmp.Pixel( x+HalfWidth, y+HalfHeight ) = Row[x + HalfWidth];
		}
	}
}
#else
void Camera::CapturePhoto( const Scene& TheScene, Bitmap& Bmp )
{
	int HalfHeight = Bmp.Height()/2;
	int HalfWidth  = Bmp.Width()/2;
	std::vector<std::vector<Color>> RawData;
	RawData.resize( Bmp.Height() );

	auto StartTime = std::chrono::high_resolution_clock::now();
	for (int y=HalfHeight-1; y>=-HalfHeight; --y) {
		int yOffset = (y+HalfHeight);
		RawData[yOffset] = Camera::CaptureRow( TheScene, HalfWidth, y );
	}
	auto StopTime = std::chrono::high_resolution_clock::now();
	std::cout << "Duration: " << std::chrono::duration_cast<std::chrono::milliseconds>( StopTime-StartTime ).count() << "\n";

	for (int y=HalfHeight-1; y>=-HalfHeight; --y) {
		int yOffset = (y+HalfHeight);
		std::vector<Color> Row = RawData[yOffset];
		for (int x=-HalfWidth; x<HalfWidth; ++x) {
			Bmp.Pixel( x+HalfWidth, y+HalfHeight ) = Row[x + HalfWidth];
		}
	}
}

#endif

std::vector<Color> Camera::CaptureRow( const Scene& TheScene, int HalfWidth, int y )
{
	std::vector<Color> Row;
	Row.resize( HalfWidth*2 );
	for (int x=-HalfWidth; x<HalfWidth; ++x) {
		Ray ThisRay( Point( 0, 0, -m_FocalLength ), UnitVector( static_cast<float>(x), static_cast<float>(y), m_FocalLength ) );
		Color Pixel( 0 );
		TheScene.Intersects( ThisRay, Pixel );
		Row[x + HalfWidth] = Pixel;
	}
	return Row;
}

