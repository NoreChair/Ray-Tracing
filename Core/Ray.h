#pragma once
#include <glm\glm.hpp>
#include <glm\ext.hpp>
class Ray
{
public:
	Ray();
	Ray(glm::vec3 orgin, glm::vec3 direction);
	~Ray();
	
	 void SetOrigin(glm::vec3 orgin);
	 void SetOrigin(float x, float y, float z);
	 void SetDirection(glm::vec3 direction);
	 void SetDirection(float, float y, float z);

	 glm::vec3 GetDirection();
	 glm::vec3 GetOrigin();

	 glm::vec3 GetPointAtParameter(float t);

private:
	glm::vec3 _origin;
	glm::vec3 _direction;
};

