#pragma once
#include "Texture.h"
class ConstTexture :
    public Texture
{
    vec3 color;
public:
    ConstTexture();
    ConstTexture(vec3 c);
    virtual vec3 sample(double u, double v, const vec3& position) const;
};

