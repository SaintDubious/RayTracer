#ifndef INCLUDED_RAY
#define INCLUDED_RAY

#include "Point.h"
#include "UnitVector.h"

class Ray
{
public:
	Ray( const Point& P, const UnitVector& V );
	~Ray();

	const Point&		Origin() const { return m_Origin; }
	const UnitVector&	Vector() const { return m_Vector; }
private:
	Point				m_Origin;
	UnitVector 			m_Vector;
};

#endif
