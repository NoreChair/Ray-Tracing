#include "HitableList.h"
#include "RTDefined.hpp"
HitableList::HitableList()
{
}

HitableList::~HitableList()
{
	for (size_t i = 0; i < _list.size(); i++)
	{
		Delete_Pointer(_list[i]);
	}
	_list.clear();
}

bool HitableList::IsHitRay(Ray & ray, Hitrecord& hit, float tmin, float tmax)
{
	Hitrecord temp_rec;
	bool hit_anything = false;
	double so_far = tmax;
	for (auto it = _list.begin(); it != _list.end(); it++)
	{
		(*it)->IsHitRay(ray, temp_rec, tmin, so_far);
		if (temp_rec._ishit)
		{
			hit_anything = true;	
			so_far = temp_rec._t;
			hit = temp_rec; 
		}
	}
	return hit_anything;
}
