#include "UnitVector.h"

#include <cmath>
#include <limits>
#include <stdexcept>

UnitVector::UnitVector( float X, float Y, float Z )	
	: m_Triplet( X, Y, Z )
{
	Normalize();
}

UnitVector::UnitVector( const Triplet& T )
	: m_Triplet( T )
{
	Normalize();
}

UnitVector::~UnitVector()
{
}

void UnitVector::Normalize()
{
	float Length = sqrt( m_Triplet.X() * m_Triplet.X() + m_Triplet.Y() * m_Triplet.Y() + m_Triplet.Z() * m_Triplet.Z() );
	if (Length <= std::numeric_limits<float>::epsilon()) {
		throw std::runtime_error( "Couldn't normalize UnitVector with length 0" );
	}
	m_Triplet = m_Triplet / Length;
}
