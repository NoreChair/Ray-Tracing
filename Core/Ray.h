#pragma once
#include <glm\glm.hpp>
#include <glm\ext.hpp>
class Ray
{
public:
	Ray();
	Ray(glm::vec3 orgin, glm::vec3 direction);
	~Ray();
	
	 glm::vec3 GetPointAtParameter(float t);

public:
	glm::vec3 _origin;
	glm::vec3 _direction;
};

// ��ײ��Ϣ
struct Hitrecord
{
	bool  _ishit=false;
	
	float _t = 0.0;
	// ��ײ��
	glm::vec3 _p;
	// ��ײ�㷨��
	glm::vec3 _n;
};
