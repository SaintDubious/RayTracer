#ifndef INCLUDED_VECTOR_MATH
#define INCLUDED_VECTOR_MATH

#include "Vector.h"
#include "UnitVector.h"
#include "Sphere.h"

class VectorMath
{
public:
	static Vector Point2Vector( const Point& P )
	{
		return Vector( P.m_Triplet );
	}

	static UnitVector Point2UnitVector( const Point& P )
	{
		return UnitVector( P.m_Triplet );
	}

	static Point Vector2Point( const Vector& V )
	{
		return Point( V.m_Triplet );
	}

	static UnitVector Vector2UnitVector( const Vector& V )
	{
		return UnitVector( V.m_Triplet );
	}

	template<class T, class U>
	static float Dot( const T& A, const U& B) 
	{
		return A.m_Triplet.X() * B.m_Triplet.X() + A.m_Triplet.Y() * B.m_Triplet.Y() + A.m_Triplet.Z() * B.m_Triplet.Z();
	}

	static UnitVector Reflection( const UnitVector& Incident, const UnitVector& Normal) 
	{
		float 	DotProduct = Dot( Normal, Incident*-1 );
		return	Vector2UnitVector( Normal*(2*DotProduct) + Incident);
	}

private:
	friend Vector operator* (const UnitVector& V, float S );
	template<class T, class U>
	friend Vector operator+ ( const T& A, const U& B );

	template<class T>
	static Vector Multiply( const T& V, float S )
	{
		return Vector( V.m_Triplet * S );
	}

	template<class T, class U>
	static Vector Add( const T& A, const U& B )
	{
		return Vector( A.m_Triplet + B.m_Triplet );
	}
};

inline Vector operator* (const UnitVector& V, float S )
{
	return Vector( VectorMath::Multiply(V, S) );
}

template<class T, class U>
inline Vector operator+ ( const T& A, const U& B )
{
	return Vector( VectorMath::Add( A, B ) );
}

#endif
