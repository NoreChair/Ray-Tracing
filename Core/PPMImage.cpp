#include "PPMImage.h"
#include <fstream>

PPMImage::PPMImage()
{
}

PPMImage::~PPMImage()
{
}

bool PPMImage::OutputPPMImageWithP3(const char* fileName,unsigned char* data, int width, int height, int maxColor)
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

bool PPMImage::OutputPPMImageWithP6(const char * fileName, unsigned char * data, int width, int height, int maxColor)
{
	FILE* file=nullptr;
	fopen_s(&file,fileName, "w");
	if (file!=nullptr)
	{
		fprintf(file, "P6 \n");
		fprintf(file, "%d %d \n", width, height);
		fprintf(file, "%d \n", maxColor);
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				int index = i * width * 3 + j * 3;
				fprintf(file, "%c%c%c", data[index], data[index + 1], data[index + 2]);
			}
			fprintf(file, "\n");
		}
		fclose(file);
		return true;	
	}
	return false;
}
