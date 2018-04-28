// RayTracing.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include <PPMImage.h>
#include <RTDefined.hpp>
#include <HitableList.h>
#include <Sphere.h>
#include <Camera.hpp>
PPMImage* _ppmImage = nullptr;
unsigned char* g_imageData = nullptr;
HitableList* g_hitlist=nullptr;
std::vector<Material*> g_materialList;
Camera _camera;

int g_width = 600;
int g_height = 300;
int g_aanos = 200;

void Init() {
	_ppmImage = new PPMImage();
	g_imageData = new unsigned char[g_width*g_height * 3];
	g_hitlist = new HitableList();
	Material* metal = new Metal({0.8,0.6,0.2});
	Material* diffuse = new Diffuse({0.8,0.8,0.0});
	g_materialList.reserve(4);
	g_materialList.push_back(metal);
	g_materialList.push_back(diffuse);

	Shape* shape = new Sphere({ 0.0,0.0,-1.0 }, 0.5);
	shape->material = metal;
	g_hitlist->_list.push_back(shape);

	shape = new Sphere({ -0.3,0.5,-0.4 }, 0.3);
	shape->material = diffuse;
	g_hitlist->_list.push_back(shape);

	shape = new Sphere({ 0.7,0.2,-0.2 }, 0.3);
	shape->material = diffuse;
	g_hitlist->_list.push_back(shape);

	shape = new Sphere({ 0.0, -100.5, -1.0 }, 100.0);
	shape->material = diffuse;
	g_hitlist->_list.push_back(shape);

	printf("init over \n");
}

void Destory() {
	Delete_Pointer(_ppmImage);
	Delete_Array_Pointer(g_imageData);
	Delete_Pointer(g_hitlist);
	for (size_t i = 0; i < g_materialList.size(); i++)
	{
		Delete_Pointer(g_materialList[i]);
	}
	
	printf("destory over \n");
}



glm::vec3 toColor(Ray& ray,int maxcount) {
	Hitrecord rec;
	if (g_hitlist->IsHitRay(ray,rec,0.0001,10.0))
	{
		if (maxcount>0)
		{
			maxcount--;
			Material* material = rec._shape->material;
			glm::vec3 color;
			Ray r_out;
			material->Scatter(ray, rec, color, r_out);
			return color * toColor(r_out, maxcount);
		}
		else {
			return glm::vec3(0.0f);
		}

	}
	else {
		glm::vec3 nor = glm::normalize(ray._direction);
		float t = 0.5f*nor.y + 1.0f;
		return glm::mix(glm::vec3(1.0), glm::vec3(0.5, 0.7, 1.0), t);
	}
}


int main()
{
	Init();
	for (int i = 0; i < g_height; i++)
	{
		for (int j = 0; j < g_width; j++)
		{
			glm::vec3 c;
			for (int k = 0; k < g_aanos; k++)
			{
				float u = float(j+drand48()) / g_width;
				float v = 1.0 - float(i+ drand48()) / g_height; // opengl.v=1.0 - dx.v;
				Ray r = _camera.Get_ray(u, v);
				c += toColor(r,50);
			}
			c/=float(g_aanos);
			c=glm::pow(c,glm::vec3(ONE_GAMAMA));
			c*=255.0f;
			g_imageData[i * g_width * 3 + j * 3] = Cast_UnChar(c.r);
			g_imageData[i * g_width * 3 + j * 3+1] = Cast_UnChar(c.g);
			g_imageData[i * g_width * 3 + j * 3+2] = Cast_UnChar(c.b);
		}
		printf("wait a moment ：%% %.1f \n", float(i) / float(g_height)*100.0f);
	}
	_ppmImage->OutputPPMImageWithP3("res/rayimage.ppm", g_imageData, g_width,g_height);
	Destory();
	printf("finsh \n");
	system("PAUSE");
	return 0;
}

