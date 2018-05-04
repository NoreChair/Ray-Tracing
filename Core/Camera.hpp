#pragma once
#include "Ray.h"
class Camera
{
public:
	Camera() {}
	Camera(glm::vec3 eye,glm::vec3 lookat,glm::vec3 up,float fov,float aspect) {
		glm::vec3 u, v, w;
		float theta = glm::radians(fov);
		float half_h = glm::tan(theta / 2.0f);
		float half_w = aspect * half_h;
		_origin = eye;
		w = glm::normalize(eye - lookat);
		u = glm::normalize(glm::cross(up, w));
		v = glm::cross(w, u);
		_bottom_left_corner = _origin - half_w * u - half_h * v - w;
		_horizontal = 2.0f*half_h*u;
		_vertical = 2.0f*half_w*v;

	}
	~Camera() {}


	Ray Get_ray(float u, float v) { return Ray(_origin, _bottom_left_corner + u * _horizontal + v * _vertical-_origin); }


	/// 屏幕左下坐标点
	glm::vec3 _bottom_left_corner = glm::vec3(-2.0, -1.0, -1.0);
	/// 屏幕横轴长度
	glm::vec3 _horizontal = glm::vec3(4.0, 0.0, 0.0);
	/// 屏幕纵轴长度
	glm::vec3 _vertical = glm::vec3(0.0, 2.0, 0.0);
	/// 摄像机
	glm::vec3 _origin = glm::vec3(0.0, 0.0, 0.0);

};

