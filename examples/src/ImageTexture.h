#pragma once
#include "Texture.h"
#include <string>
#include <map>
class ImageTexture :
    public Texture
{
    // 通过某种标识符索引图片。必须是weak指针，否则资源永远不会释放。
    // TODO:MD5/随机采样/目录/前数个字节 选择一种哈希方法
    static std::map <std::string, std::weak_ptr<ImageTexture>> imageMap;
    std::shared_ptr<unsigned char> imageData;
    int imageWidth, imageHeight, imageChannels;
    rgb3 imageSample(double u, double v) const;
    rgb3 imagePixelAt(int x, int y) const;
public:
    ImageTexture(std::string path);
    virtual SampledSpectrum sample(double u, double v, const point3& position) const;
};

