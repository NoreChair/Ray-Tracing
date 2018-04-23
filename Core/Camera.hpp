#pragma once
#include "Ray.h"
class Camera
{
public:
	Camera() {}
	~Camera() {}


	Ray Get_ray(float u, float v) { return Ray(_origin, _bottom_left_corner + u * _horizontal + v * _vertical); }


	/// 屏幕左下坐标点
	glm::vec3 _bottom_left_corner = glm::vec3(-2.0, -1.0, -1.0);
	/// 屏幕横轴长度
	glm::vec3 _horizontal = glm::vec3(4.0, 0.0, 0.0);
	/// 屏幕纵轴长度
	glm::vec3 _vertical = glm::vec3(0.0, 2.0, 0.0);
	/// 摄像机
	glm::vec3 _origin = glm::vec3(0.0, 0.0, 0.0);

};

