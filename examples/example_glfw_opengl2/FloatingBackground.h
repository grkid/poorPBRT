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
    FloatingBackground(const vec3& color);
    FloatingBackground(std::shared_ptr<Texture> color);
    virtual vec3 sample(const Ray& ray) const;
};

