#pragma once
#include "Texture.h"
#include <string>
#include <map>
class ImageTexture :
    public Texture
{
    // ͨ��ĳ�ֱ�ʶ������ͼƬ��������weakָ�룬������Դ��Զ�����ͷš�
    // TODO:MD5/�������/Ŀ¼/ǰ�����ֽ� ѡ��һ�ֹ�ϣ����
    static std::map <std::string, std::weak_ptr<ImageTexture>> imageMap;
    std::shared_ptr<unsigned char> imageData;
    int imageWidth, imageHeight, imageChannels;
    rgb3 imageSample(double u, double v) const;
    rgb3 imagePixelAt(int x, int y) const;
public:
    ImageTexture(std::string path);
    virtual SampledSpectrum sample(double u, double v, const point3& position) const;
};

