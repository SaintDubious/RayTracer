#ifndef INCLUDED_LIGHT
#define INCLUDED_LIGHT

#include "Point.h"

class Light
{
public:
	Light( const Point& P )
		: m_Position( P )
	{}

	~Light()
	{}

	const Point&		Position() const { return m_Position; }

private:
	Point				m_Position;
};

#endif
