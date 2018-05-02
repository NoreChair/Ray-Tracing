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
	Metal(glm::vec3 albedo, float rough) { SetAlbedo(albedo); _roughness = rough; }

	virtual ~Metal() {}

	virtual bool Scatter(Ray& ray_in, Hitrecord& hitrec, glm::vec3& color, Ray& ray_scatter) {
		glm::vec3 target = glm::reflect(ray_in._direction, hitrec._n);
		ray_scatter._origin = hitrec._p; ray_scatter._direction = target+ _roughness*Random_vec_in_sphere();
		color = _albedo;
		return (glm::dot(ray_scatter._direction, hitrec._n)>0);
	}

	float _roughness = 0.7f;
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

class Dielectric :public Material {

public:
	Dielectric() {}
	Dielectric(glm::vec3 albedo) { SetAlbedo(albedo); }
	Dielectric(glm::vec3 albedo, float eta) { SetAlbedo(albedo); _eta = eta; }
	virtual ~Dielectric() {}

	virtual bool Scatter(Ray& ray_in, Hitrecord& hitrec, glm::vec3& color, Ray& ray_scatter) {
		glm::vec3 unor =hitrec._n;
		float eta= _eta;
		float cosine = glm::dot(ray_in._direction, unor);

		if (glm::dot(ray_in._direction,hitrec._n)>0)
		{
			unor = -hitrec._n;
			eta = 1.0f/_eta;
			cosine = glm::dot(ray_in._direction, unor)*_eta;
		}

		glm::vec3 refr;
		float refprob=1.0;
		if (refract(ray_in._direction, unor, refr, eta)) {
			refprob = schilck(cosine, _eta);
		}
		if (drand48() < refprob)
		{
			ray_scatter._origin = hitrec._p;
			ray_scatter._direction = glm::reflect(ray_in._direction, hitrec._n);
		}
		else {
			ray_scatter._origin = hitrec._p;
			ray_scatter._direction = refr;
		}

		color = _albedo;
		return true;
	}

	float _eta = 1.0;

protected:
	bool refract(glm::vec3& v, glm::vec3& n, glm::vec3& refracted,float eta) {
		float dt = glm::dot(v, n);
		float discrimian = 1.0f - eta * eta*(1.0f - dt * dt);
		if (discrimian>0)
		{
			refracted = eta * (glm::normalize(v) - n * dt) - n * glm::sqrt(discrimian);
			return true;
		}
		else {
			return false;
		}
	}

	float schilck(float cosine, float eta) {
		float r0 = (1.0f - eta) / (1.0f + eta);
		r0 *= r0;
		return r0 + (1.0f - r0)*glm::pow((1.0f - cosine), 5.0f);
	}
};

