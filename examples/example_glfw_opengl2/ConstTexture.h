#pragma once
#include "Texture.h"
class ConstTexture :
    public Texture
{
    SampledSpectrum color;
public:
    ConstTexture();
    ConstTexture(const rgb3& c);
    virtual SampledSpectrum sample(double u, double v, const point3& position) const;
};

