#pragma once
#include <vector>
#include "Ray.h"
#include "Shape.h"

class HitableList
{
public:
	HitableList();
	~HitableList();

	bool IsHitRay(Ray& ray, Hitrecord& hit, float tmin, float tmax);

	std::vector<Shape*> _list;
};


