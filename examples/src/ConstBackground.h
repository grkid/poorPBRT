#pragma once
#include "Background.h"
#include "vec3.h"
class ConstBackground :
    public Background
{
    SampledSpectrum baseColor;
public:
    ConstBackground(const rgb3& color);
    virtual SampledSpectrum sample(const Ray& ray) const;
};

