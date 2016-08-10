#ifndef INCLUDED_SPHERE
#define INCLUDED_SPHERE

#include "Point.h"

class Ray;

class Sphere
{
public:
	Sphere( const Point& Location, float Radius );
	~Sphere();

	bool				Intersection( const Ray& IncomingRay, Point& ThePoint ) const;

	const Point&		Location() const { return m_Location; }

private:
	friend bool			operator== (const Sphere& A, const Sphere& B);

	Point				m_Location;
	float				m_Radius;
};

inline bool operator== (const Sphere& A, const Sphere& B)
{
	return (A.m_Location == B.m_Location) && (A.m_Radius == B.m_Radius);
}

#endif
