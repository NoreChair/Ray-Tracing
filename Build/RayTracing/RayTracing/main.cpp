// RayTracing.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include <mutex>
#include <thread>
#include <time.h>

#include <PPMImage.h>
#include <RTDefined.hpp>
#include <HitableList.h>
#include <Sphere.h>
#include <Camera.hpp>

PPMImage* _ppmImage = nullptr;
unsigned char* g_imageData = nullptr;
HitableList* g_hitlist=nullptr;
std::vector<Material*> g_materialList;
Camera g_camera;

std::mutex g_mutex;

int g_width = 500;
int g_height = 300;
int g_aanos = 150;
int g_curWidth = 0;
int g_curHeight = 0;
void Init() {
	g_camera = Camera(glm::vec3(-1.0, 2.0, 1.0), glm::vec3(1.0, 0, -1.0), { 0,1.0,0 }, 90, float(g_width) / g_height);

	_ppmImage = new PPMImage();
	g_imageData = new unsigned char[g_width*g_height * 3];
	g_hitlist = new HitableList();
	Material* metal = new Metal({0.8,0.6,0.2},0.8f);
	Material* dielectric = new Dielectric({ 1.0,1.0,1.0 },1.5f);
	Material* diffuse = new Diffuse({0.8,0.8,0.0});

	g_materialList.reserve(4);
	g_materialList.push_back(metal);
	g_materialList.push_back(dielectric);
	g_materialList.push_back(diffuse);

	Shape* shape = new Sphere({ 0.0,0.0,-1.0 }, 0.5);
	shape->material = diffuse;
	g_hitlist->_list.push_back(shape);

	shape = new Sphere({ -1.0,0.0,-1.0}, 0.5);
	shape->material = metal;
	g_hitlist->_list.push_back(shape);

	shape = new Sphere({ 1.0,0.0,-1.0 }, 0.5);
	shape->material = dielectric;
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
	if (g_hitlist->IsHitRay(ray,rec,0.0001f,10.0f))
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
			Material* material = rec._shape->material;
			return material->GetAlbedo();
		}

	}
	else {
		glm::vec3 nor = glm::normalize(ray._direction);
		float t = 0.5f*nor.y + 1.0f;
		return glm::mix(glm::vec3(1.0), glm::vec3(0.5, 0.7, 1.0), t);
	}
}

void CalcData(int i,int j) {
	glm::vec3 c;
	for (int k = 0; k < g_aanos; k++)
	{
		float u = float(j + drand48()) / g_width;
		float v = 1.0f - float(i + drand48()) / g_height; // opengl.v=1.0 - dx.v;
		Ray r = g_camera.Get_ray(u, v);
		c += toColor(r, 50);
	}
	c /= float(g_aanos);
	c = glm::pow(c, glm::vec3(ONE_GAMAMA));
	c *= 255.0f;
	g_imageData[i * g_width * 3 + j * 3] = Cast_UnChar(c.r);
	g_imageData[i * g_width * 3 + j * 3 + 1] = Cast_UnChar(c.g);
	g_imageData[i * g_width * 3 + j * 3 + 2] = Cast_UnChar(c.b);
}

void RayTracingNoThread() {

	for (int i = 0; i < g_height; i++)
	{
		for (int j = 0; j < g_width; j++)
		{
			CalcData(i, j);
		}
		printf("wait a moment %.3f \n", float(i) / g_height);
	}
}

void RayTracingWithThread(int index) {
	

	while (1)
	{
		while (1)
		{
			int i=0, j=0;
			{
				std::lock_guard<std::mutex> grad(g_mutex);
				i = g_curHeight; j = g_curWidth;
				g_curWidth++;		
				if (i >= g_height|| j >= g_width) break;
				//printf(" cur height %d ,cur width %d \n", i, j);
			}
			CalcData(i, j);
		}
		{
			std::lock_guard<std::mutex> grad(g_mutex);
			g_curHeight++;
			g_curWidth = 0;
			if (g_curHeight >= g_height) break;
			printf("wait a moment %.3f flash this thread %d \n", float(g_curHeight) / g_height,index);

		}	
	}

}

int main()
{
	Init();

	time_t beginTime = time(NULL);
#if 0
	// 12m 
	RayTracingNoThread();
#else 
	/// 这里并不去百分百的使用cpu 因为这样反而会使速度变慢
	/// 7线程跑的时间15min 4线程反而才5min 
	/// 猜测可能是因为cpu指令并行的原因导致
	/// 单线程吃多少cpu 看硬件 所以可以适当增加
	constexpr int size = 3;
	std::thread th[size];
	for (int i = 0; i < size; i++)
	{
		th[i] = std::thread(RayTracingWithThread,i);
	}
	for (int i = 0; i < size; i++) {
		th[i].join();
	}
#endif
	time_t endTime = time(NULL);
	int s = endTime-beginTime;
	printf("ray tracing use time %d m,%d s", s / 60, s % 60);

	_ppmImage->OutputPPMImageWithP3("res/rayimage.ppm", g_imageData, g_width,g_height);
	Destory();
	printf("finsh \n");
	system("PAUSE");
	return 0;
}

