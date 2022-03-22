#pragma once
#include "Texture.h"
class ConstTexture :
    public Texture
{
    rgb3 color;
public:
    ConstTexture();
    ConstTexture(const rgb3& c);
    virtual rgb3 sample(double u, double v, const point3& position) const;
};

