#pragma once
#include "Background.h"
class InitBackground :
    public Background
{
public:
    virtual SampledSpectrum sample(const Ray& ray) const;
};

