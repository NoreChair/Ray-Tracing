#pragma once
#include "Ray.h"
class Material
{
public:
	Material() {}
	virtual ~Material() {}

	virtual bool Scatter(Ray& ray_in, Hitrecord& hitrec, glm::vec3& color, Ray& ray_scatter) = 0;

	glm::vec3 GetAlbedo() { return _albedo; }
	glm::vec3 SetAlbedo(glm::vec3 albedo) { _albedo = albedo; }
protected:
	glm::vec3 _albedo =glm::vec3(1.0);
};

class Metal:public Material
{
public:
	Metal() {}
	Metal(glm::vec3 albedo) { SetAlbedo(albedo); }
	~Metal() {}

	virtual bool Scatter(Ray& ray_in, Hitrecord& hitrec, glm::vec3& color, Ray& ray_scatter) {
	
	}

};

class Diffuse:public Material
{
public:
	Diffuse() {}
	Diffuse(glm::vec3 albedo) { SetAlbedo(albedo); }
	~Diffuse() {}

	virtual bool Scatter(Ray& ray_in, Hitrecord& hitrec, glm::vec3& color, Ray& ray_scatter) {

	}
};

