#include "Ray.h"

Ray::Ray( const Point& P, const UnitVector& V )
	: m_Origin( P )	
	, m_Vector( V )
{
}

Ray::~Ray()
{
}

