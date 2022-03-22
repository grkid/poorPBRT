#pragma once
#include "Background.h"
#include "vec3.h"
class ConstBackground :
    public Background
{
    rgb3 baseColor;
public:
    ConstBackground(const rgb3& color);
    virtual rgb3 sample(const Ray& ray) const;
};

