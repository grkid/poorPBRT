#include "ImageTexture.h"
// 只在cpp文件中引入stb image，否则会极大增加编译时间。
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <math.h>

rgb3 ImageTexture::imageSample(double u, double v) const
{
	// NEAREST采样
	int x = round(u * imageWidth);
	int y = round(v * imageHeight);
	return imagePixelAt(x, y);
}

rgb3 ImageTexture::imagePixelAt(int x, int y) const
{
	double v[3]{ 0.0f,0.0f,0.0f };
	int maxChannels = (imageChannels < 3 ? imageChannels : 3);
	// 获取裸指针
	unsigned char* _data = imageData.get();
	for (int i = 0; i < maxChannels; i++)
	{
		v[i] = _data[(x+y*imageHeight)*imageChannels+i]/255.99f;
	}

	return rgb3(v[0], v[1], v[2]);

}

// 图片的内存管理需要及其小心
ImageTexture::ImageTexture(std::string path)
{

	unsigned char* _data = stbi_load(path.c_str(),&imageWidth,&imageHeight,&imageChannels,0);
	if (!_data) {
		std::cout << "ERROR Image Texture loading" << std::endl;
		return;
	}
	std::shared_ptr<unsigned char> _pt(_data, free);
	imageData = _pt;

}
rgb3 ImageTexture::sample(double u, double v, const point3& position) const
{
	if(!imageData)
		return rgb3(0,0,0);
	return imageSample(u, v);

}
