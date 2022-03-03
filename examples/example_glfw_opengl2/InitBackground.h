#pragma once
#include "Background.h"
class InitBackground :
    public Background
{
public:
    virtual vec3 sample(const Ray& ray) const;
};

