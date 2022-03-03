#pragma once
#include "Background.h"
#include "vec3.h"
class ConstBackground :
    public Background
{
    vec3 baseColor;
public:
    ConstBackground(const vec3& color);
    virtual vec3 sample(const Ray& ray) const;
};

