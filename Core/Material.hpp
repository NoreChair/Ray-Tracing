#pragma once
#include "Ray.h"
#include "RTDefined.hpp"
class Material
{
public:
	Material() {}
	virtual ~Material() {}

	virtual bool Scatter(Ray& ray_in, Hitrecord& hitrec, glm::vec3& color, Ray& ray_scatter) = 0;

	glm::vec3 GetAlbedo() { return _albedo; }
	void SetAlbedo(glm::vec3 albedo) { _albedo = albedo; }
protected:
	glm::vec3 _albedo =glm::vec3(1.0);
};

class Metal:public Material
{
public:
	Metal() {}
	Metal(glm::vec3 albedo) { SetAlbedo(albedo); }
	virtual ~Metal() {}

	virtual bool Scatter(Ray& ray_in, Hitrecord& hitrec, glm::vec3& color, Ray& ray_scatter) {
		glm::vec3 target = glm::reflect(ray_in._direction, hitrec._n);
		ray_scatter._origin = hitrec._p; ray_scatter._direction = target+ _roughness*Random_vec_in_sphere();
		color = _albedo;
		return (glm::dot(ray_scatter._direction, hitrec._n)>0);
	}

	float _roughness = 0.7;
};

class Diffuse:public Material
{
public:
	Diffuse() {}
	Diffuse(glm::vec3 albedo) { SetAlbedo(albedo); }
	virtual ~Diffuse() {}

	virtual bool Scatter(Ray& ray_in, Hitrecord& hitrec, glm::vec3& color, Ray& ray_scatter) {
		glm::vec3 target = hitrec._p + hitrec._n + Random_vec_in_sphere();
		ray_scatter._origin = hitrec._p; ray_scatter._direction = target;
		color = _albedo;
		return true;
	}
};

