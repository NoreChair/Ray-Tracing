// RayTracing.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <PPMImage.h>
#include <RTDefined.h>
PPMImage* _ppmImage = nullptr;


void Init() {
	_ppmImage = new PPMImage();

}

void Destory() {
	Delete_Pointer(_ppmImage);

}

void TestOutputImage() {
	unsigned char* data = new unsigned char[4 * 4 * 3];
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			float r = (float)i / 4.0*255;
			float g = (float)j / 4.0*255;
			float b = 200;
			data[i * 4 * 3 + j * 3] = r;
			data[i * 4 * 3 + j * 3 + 1] = g;
			data[i * 4 * 3 + j * 3 + 2] = b;
		}
	}
	_ppmImage->OutputPPMImage("res/test.ppm",data,4,4);
	Delete_Array_Pointer(data);
}

int main()
{
	Init();
	TestOutputImage();

	Destory();
}

