#ifndef INCLUDED_VECTOR
#define INCLUDED_VECTOR

#include "Triplet.h"

class Vector
{
public:
	Vector( float X, float Y, float Z);
	~Vector();

	float				Length() const;
	float				LengthSquared() const;

private:
	Vector( const Triplet& T );

	friend class		VectorMath;

	Triplet				m_Triplet;
};

#endif
