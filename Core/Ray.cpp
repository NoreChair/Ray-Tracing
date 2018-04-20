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

 void Ray::SetOrigin(glm::vec3 orgin)
{
	_origin = orgin;
}

 void Ray::SetOrigin(float x, float y, float z)
{
	_origin = glm::vec3(x, y, z);
}

 void Ray::SetDirection(glm::vec3 direction)
{
	_direction = direction;
}

 void Ray::SetDirection(float x, float y, float z)
{
	_direction = glm::vec3(x, y, z);
}

 glm::vec3 Ray::GetDirection()
{
	return _direction;
}

 glm::vec3 Ray::GetOrigin()
{
	return _origin;
}

 glm::vec3 Ray::GetPointAtParameter(float t)
{
	return _origin+t*_direction;
}
