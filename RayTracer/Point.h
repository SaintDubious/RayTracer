#ifndef INCLUDED_POINT
#define INCLUDED_POINT

#include "Triplet.h"

class Point
{
public:
	Point()
	{}

	Point( float x, float y, float z )
		: m_Triplet( x, y, z )
	{}

	~Point()
	{}

private:
	Point( const Triplet& T )
		: m_Triplet( T )
	{}

	friend Point	operator+ (const Point &A, const Point &B);
	friend Point	operator- (const Point &A, const Point &B);
	friend bool 	operator== (const Point &A, const Point &B);
	friend class	VectorMath;

	Triplet			m_Triplet;
};

inline Point operator+ (const Point &A, const Point &B)
{
	return Point( A.m_Triplet + B.m_Triplet );
}

inline Point operator- (const Point &A, const Point &B)
{
	return Point( A.m_Triplet - B.m_Triplet );
}

inline bool operator== (const Point &A, const Point &B)
{
	return A.m_Triplet == B.m_Triplet;
}

#endif
