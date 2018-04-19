#include "PPMImage.h"
#include <fstream>

PPMImage::PPMImage()
{
}

PPMImage::~PPMImage()
{
}

bool PPMImage::OutputPPMImage(const char* fileName,unsigned char* data, int width, int height, int maxColor)
{

	std::fstream fst;
	fst.open(fileName, std::ios::out);
	if (fst.is_open()&&fst.good())
	{
		fst << "P3" << std::endl;
		fst << width << " " << height << std::endl;
		fst << maxColor << std::endl;
		for (size_t i = 0; i < height ; i++)
		{
			for (size_t j = 0; j < width; j++)
			{
				int index = i * width*3+j*3;
				fst << (int)data[index] << " " << (int)data[index + 1] << " " << (int)data[index + 2] <<" ";
			}
			fst << std::endl;
		}
		fst.close();
		return true;
	}

	return false;
}
