#ifndef INCLUDED_CAMERA
#define INCLUDED_CAMERA

#include <string>
#include <vector>

class Bitmap;
class Scene;
class Color;

class Camera
{
public:
	Camera();
	~Camera();

	void		CapturePhoto( const Scene& TheScene, Bitmap& Bmp );

private:
	std::vector<Color>	CaptureRow( const Scene& TheScene, int HalfWidth, int y );

	float		m_FocalLength;
	int			m_Width;
	int			m_Height;
};

#endif
