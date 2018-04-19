#pragma once
#include <stdio.h>

class PPMImage
{
public:
	PPMImage();
	~PPMImage();
	/*
		@fileName 输出图像名称
		@data 数据流 左到右  上到下
		@width height  图像宽高
		@maxColor 0~255 颜色最大值
		只输出RGB颜色值的图片
	*/
	bool OutputPPMImage(const char* fileName,unsigned char* data, int width, int height, int maxColor=255);
	
};

