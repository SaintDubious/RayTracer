#include "Scene.h"
#include "Color.h"
#include "VectorMath.h"
#include "UnitVector.h"
#include "Sphere.h"
#include "Ray.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::AddSphere( const Sphere& Sphere )
{
	m_Spheres.push_back( Sphere );
}

void Scene::AddLight( const Light& Light )
{
	m_Lights.push_back( Light );
}

bool Scene::Intersects( const Ray& R, Color& C ) const
{
	Sphere Skip( Point(), 1 );
	return Intersects( R, C, Skip, 3 );
}

bool Scene::Intersects( const Ray& R, Color& C, const Sphere& Skip, int Depth ) const
{
	if (Depth == 0) {
		return false;
	}
	Point IntersectPoint;
	Sphere IntersectSphere( Point(), 1 );
	if (!Intersects( R, Skip, IntersectSphere, IntersectPoint )) {
		return false;
	}
	C = RayColor( R, IntersectSphere, IntersectPoint, Depth );

	return true;
}

bool Scene::Intersects( const Ray& R, const Sphere& Skip, Sphere& IntersectSphere, Point& IntersectPoint ) const
{
	float MinDistance = std::numeric_limits<float>::max();
	IntersectPoint = Point( std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max() );

	for (const Sphere &S : m_Spheres) {
		if (S == Skip) {
			continue;
		}
		Point I;
		if (S.Intersection( R, I )) {
			float Distance = VectorMath::Point2Vector( I - R.Origin() ).LengthSquared();
			if (Distance < MinDistance) {
				MinDistance = Distance;
				IntersectPoint = I;
				IntersectSphere = S;
			}
		}
	}
	if (MinDistance == std::numeric_limits<float>::max()) {
		return false;
	}
	return true;
}

Color Scene::RayColor( const Ray& R, const Sphere& S, const Point& I, int Depth ) const
{
	Color	RetVal( 0 );	// Ambient

	UnitVector Normal = VectorMath::Point2UnitVector( I - S.Location() );
	
	for (const Light& L : m_Lights) {
		// Shadows
		// There's a bug, in that the sphere can be on the other side of
		// the light and still cast a shadow.  I'm not worrying about that
		// for this test program.
		UnitVector LightVector = VectorMath::Point2UnitVector( L.Position() - I );
		Ray LightRay( I, LightVector );
		Sphere LightIntersectSphere( Point(), 1 );
		Point LightIntersectPoint;
		if (!Intersects( LightRay, S, LightIntersectSphere, LightIntersectPoint )) {

			// Diffuse
			float Diffuse = VectorMath::Dot( LightVector, Normal );
			if (Diffuse > 0) {
				RetVal = RetVal + Color( Diffuse * 210 );
			}
			// Specular
			Ray		ReflectRay( I, VectorMath::Reflection( LightVector, Normal ) );
			float	Specular = VectorMath::Dot( R.Vector(), ReflectRay.Vector() );
			if (Specular > 0) {
				Specular = pow( Specular, 100.0f );
				RetVal = RetVal + Color( Specular * 200 );
			}
		}

		// Reflection
		Color	ReflectColor;
		Ray		IncomingRayReflection( I, VectorMath::Reflection( R.Vector(), Normal ) );
		if (Intersects( IncomingRayReflection, ReflectColor, S, Depth-1 )) {
			RetVal = (RetVal*1) + (ReflectColor * 0.1);
//			RetVal = RetVal + ReflectColor;
		}
	}
	return RetVal;

	// just for testing
//	float blah = fabs(VectorMath::Dot( R.Vector(), ReflectRay.Vector() ));
	//return Color( blah * 255 );
}
