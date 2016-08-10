#include "Vector.h"

#include <cmath>

Vector::Vector( float X, float Y, float Z )
	: m_Triplet( X, Y, Z )
{
}

Vector::Vector( const Triplet& T )
	: m_Triplet( T )
{
}

Vector::~Vector()
{
}

float Vector::Length() const
{
	return sqrt( LengthSquared() );
}

float Vector::LengthSquared() const
{
	return m_Triplet.X() * m_Triplet.X() + m_Triplet.Y() * m_Triplet.Y() + m_Triplet.Z() * m_Triplet.Z();
}

