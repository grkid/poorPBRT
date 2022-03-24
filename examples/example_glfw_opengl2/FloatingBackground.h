#pragma once
#include "Background.h"
#include "Texture.h"
// 悬浮背景，一张图片或者纯色
// TODO:暂时禁用，没有想到好的实现方法。
class FloatingBackground :
    public Background
{
    std::shared_ptr<Texture> baseColor;
//public:
    FloatingBackground(const rgb3& color);
    FloatingBackground(std::shared_ptr<Texture> color);
    virtual SampledSpectrum sample(const Ray& ray) const;
};

