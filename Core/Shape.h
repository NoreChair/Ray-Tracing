#pragma once
#include "Ray.h"
#include "Material.hpp"
#define SHAPE_UNDIFEND 0
#define SHAPE_SPHERE 0x0001

class Shape
{
public:
	Shape() {}
	~Shape() {}
	virtual void IsHitRay(Ray& ray, Hitrecord& hit, float tmin, float tmax) = 0;


	Material* material = nullptr;
	int _shapeType= SHAPE_UNDIFEND;
};