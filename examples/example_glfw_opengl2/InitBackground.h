#pragma once
#include "Background.h"
class InitBackground :
    public Background
{
public:
    virtual rgb3 sample(const Ray& ray) const;
};

