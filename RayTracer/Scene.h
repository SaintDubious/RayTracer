#ifndef INCLUDED_SCENE
#define INCLUDED_SCENE

#include "Sphere.h"
#include "Light.h"

#include <vector>

class Color;

class Scene
{
public:
	Scene();
	~Scene();

	typedef std::vector<Sphere> SphereVector;
	typedef std::vector<Light> LightVector;

	void				AddSphere( const Sphere& Sphere );
	void				AddLight( const Light& Light );
	bool				Intersects( const Ray& R, Color& C ) const;

private:
	bool				Intersects( const Ray& R, Color& C, const Sphere& Skip, int Depth ) const;
	bool				Intersects( const Ray& R, const Sphere& Skip, Sphere& IntersectSphere, Point& IntersectPoint ) const;
	Color				RayColor( const Ray& R, const Sphere& S, const Point& I, int Depth ) const;

	SphereVector		m_Spheres;
	LightVector			m_Lights;
};

#endif
