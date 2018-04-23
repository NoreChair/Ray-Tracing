#pragma once

#include"Shape.h"
#include "RTDefined.hpp"
class Sphere:public Shape
{
public:
	Sphere();
	Sphere(glm::vec3 center, float radius);
	~Sphere();

	/// @ return  -1, 0 ,1
	void IsHitRay( Ray& ray, Hitrecord& hit, float tmin, float tmax);

public:
	glm::vec3 _center;
	float _radius=1.0;
};

