#ifndef INCLUDED_UNIT_VECTOR
#define INCLUDED_UNIT_VECTOR

#include "Triplet.h"

class UnitVector
{
public:
	UnitVector( float X, float Y, float Z);
	~UnitVector();

private:
	UnitVector( const Triplet& T );

	void				Normalize();

	friend class		VectorMath;

	Triplet				m_Triplet;
};

#endif