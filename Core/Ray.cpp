#include "Ray.h"
Ray::Ray()
{
}

Ray::Ray(glm::vec3 orgin, glm::vec3 direction)
{
	_origin = orgin;
	_direction = direction;
}

Ray::~Ray()
{
}


 glm::vec3 Ray::GetPointAtParameter(float t)
{
	return _origin+t*_direction;
}
