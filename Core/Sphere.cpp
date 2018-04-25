#include "Sphere.h"

Sphere::Sphere()
{
	_shapeType = SHAPE_SPHERE;
}

Sphere::Sphere(glm::vec3 center, float radius)
{
	_center = center;
	_radius = radius;
	_shapeType = SHAPE_SPHERE;
}

Sphere::~Sphere()
{

}

void Sphere::IsHitRay(Ray& ray, Hitrecord& hit, float tmin, float tmax)
{
	glm::vec3 oc = ray._origin - _center;
	float a = glm::dot(ray._direction, ray._direction);
	float b = glm::dot(ray._direction, oc);
	float c = glm::dot(oc, oc) - _radius * _radius;
	float r = b * b - a*c;
	if (r>=0.0)
	{
		float sqr = glm::sqrt(r);
		float temp = (-b - sqr) / a;
		if (temp>tmin&&temp<tmax)
		{
			hit._t = temp;
			hit._ishit = true;
			hit._p = ray.GetPointAtParameter(temp);
			hit._n = (hit._p - _center) / _radius;
			hit._shape = this;
			return;
		}
		temp = (-b + sqr) / a;
		if (temp>tmin&&temp<tmax)
		{
			hit._t = temp;
			hit._ishit = true;
			hit._p = ray.GetPointAtParameter(temp);
			hit._n = (hit._p - _center) / _radius;
			hit._shape = this;
			return;
		}
	}
	hit._ishit = false;
	hit._shape = nullptr;
}
