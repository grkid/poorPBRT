#pragma once
#include "Background.h"
#include "Texture.h"
// ����������һ��ͼƬ���ߴ�ɫ
// TODO:��ʱ���ã�û���뵽�õ�ʵ�ַ�����
class FloatingBackground :
    public Background
{
    std::shared_ptr<Texture> baseColor;
//public:
    FloatingBackground(const rgb3& color);
    FloatingBackground(std::shared_ptr<Texture> color);
    virtual SampledSpectrum sample(const Ray& ray) const;
};

