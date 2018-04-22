// RayTracing.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include <PPMImage.h>
#include <RTDefined.h>
#include <HitableList.h>
#include <Sphere.h>
PPMImage* _ppmImage = nullptr;
unsigned char* g_imageData = nullptr;
HitableList* g_hitlist=nullptr;

int g_width = 600;
int g_height = 300;
/// 屏幕左下坐标点
glm::vec3 g_bottom_left_corner(-2.0, -1.0, -1.0);
/// 屏幕横轴长度
glm::vec3 g_horizontal(4.0, 0.0, 0.0);
/// 屏幕纵轴长度
glm::vec3 g_vertical(0.0, 2.0, 0.0);
/// 摄像机
glm::vec3 g_origin(0.0, 0.0, 0.0);


void Init() {
	_ppmImage = new PPMImage();
	g_imageData = new unsigned char[g_width*g_height * 3];
	g_hitlist = new HitableList();

	Shape* shape = new Sphere({ 0.0,0.0,-1.0 }, 0.5);
	g_hitlist->_list.push_back(shape);
	shape = new Sphere({ 0.0, -100.5, -1.0 }, 100.0);
	g_hitlist->_list.push_back(shape);

	printf("init over \n");
}

void Destory() {
	Delete_Pointer(_ppmImage);
	Delete_Array_Pointer(g_imageData);
	Delete_Pointer(g_hitlist);
	printf("destory over \n");
}



glm::vec3 toColor(Ray& ray) {
	Hitrecord rec;
	if (g_hitlist->IsHitRay(ray,rec,0.0,10.0))
	{
		return rec._n*0.5f + 0.5f;
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
			float u = float(j) / g_width;
			float v =1.0- float(i) / g_height; // opengl.v=1.0 - dx.v;
			Ray r(g_origin, g_bottom_left_corner + u * g_horizontal + v * g_vertical);
			glm::vec3 c = toColor(r)*255.0f;
			g_imageData[i * g_width * 3 + j * 3] = Cast_UnChar(c.r);
			g_imageData[i * g_width * 3 + j * 3+1] = Cast_UnChar(c.g);
			g_imageData[i * g_width * 3 + j * 3+2] = Cast_UnChar(c.b);
		}
	}
	_ppmImage->OutputPPMImageWithP3("res/rayimage.ppm", g_imageData, g_width,g_height);
	Destory();
	//system("PAUSE");
	return 0;
}

