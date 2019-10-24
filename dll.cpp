#include <string>
#include "dll.hpp"

using std::string;
using std::vector<voxel>ListName;




int answer(const char * question)
{
	// Note the usage of C++ while using a plain C interface!

	string str = std::string(question);

	if (str == "What is the answer to life, the universe and everything?")
	{
		return 42;
	}
	else
	{
		return -1;
	}
}


int fenster(int startValue, int windowWidth, int fileValue)
{
	int y;
	if (fileValue <= startValue)
	{
		y = 0;
	}
	else if (fileValue >= (startValue + windowWidth))
	{
		y = 255;
	}
	else
	{
		y = (fileValue - startValue)* 255.0 / (windowWidth);
	}
	return y;
}

return_t windowing(const image3D &image, const int &layer, const short &windowingStart, const short &windowingWidth, image2D &returnImage)
{
	for (int y = 0; y < 512; y++)
	{
		for (int x = 0; x < 512; x++)
		{
			returnImage[x + y*IMAGE_WIDTH] = fenster(windowingStart, windowingWidth, image.data[x + y*IMAGE_WIDTH + layer*IMAGE_SIZE);
		}
	}
}


return_t performRegionGrowing(const image3D &image, const voxel &seed, const short &segmentationThresh, image3D &returnImage)
{
	int a;
	for (a!=0)
	{
		int i = fenster(0, 1500, //Bildvalue);
		if ()
		{
		}
		//Ursprungapixel in ListeFertig --> 0 oder 1 in Short
		//Pixel in sechs Richtungen angucken
		//Neue Pixel mit ListeFertig und ListeÜberprüfen abgleichen, wenn keine Übereinstimmung  in ListeÜberprüfen schreiben

	}
}


return_t intensityMap(const image3D &image, const short &segmentationThresh, image2D &returnImage)
{
}

