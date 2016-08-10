#include "Sphere.h"
#include "Ray.h"
#include "VectorMath.h"

#include <cmath>
#include <limits>

Sphere::Sphere( const Point& Location, float Radius )
	: m_Location( Location )
	, m_Radius( Radius )
{
}

Sphere::~Sphere()
{
}

bool Sphere::Intersection( const Ray& IncomingRay, Point& ThePoint ) const 
{
	// The dot product of a vector with itself is equal to the length
	// squared. And as these are unit vectors, the length squared is 1.
	// This function is called OFTEN
//	float A = VectorMath::Dot<UnitVector, UnitVector>(IncomingRay.Vector(), IncomingRay.Vector());
	float A = 1;
	Vector OminusC = VectorMath::Point2Vector( IncomingRay.Origin() - m_Location );
	float B = 2 * VectorMath::Dot<Vector,UnitVector>( OminusC, IncomingRay.Vector() );
//	float C = VectorMath::Dot<UnitVector,UnitVector>( OminusC, OminusC ) - (m_Radius*m_Radius);
	float C = OminusC.LengthSquared() - (m_Radius*m_Radius);

	float Discriminant = B * B - 4 * A * C;
    if (Discriminant < 0)
        return false;

	float Plus = (-B + sqrt(Discriminant))/2.0f;
	float Minus = (-B - sqrt(Discriminant))/2.0f;

	// need to find the smallest non-negative term
	if (Plus <= std::numeric_limits<float>::epsilon() && Minus <= std::numeric_limits<float>::epsilon()) {
		return false;
	}
	if (Plus <= std::numeric_limits<float>::epsilon()) {
		Plus = Minus;
	}
	if (Minus <= std::numeric_limits<float>::epsilon()) {
		Minus = Plus;
	}

	if (Plus <= Minus) {
		ThePoint = IncomingRay.Origin() + VectorMath::Vector2Point( IncomingRay.Vector()*Plus );
	} 
	else {
		ThePoint = IncomingRay.Origin() + VectorMath::Vector2Point( IncomingRay.Vector()*Minus );
	}

	return true;
}

