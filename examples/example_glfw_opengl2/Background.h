#pragma once
#include "vec3.h"
#include "Ray.h"
#include "HitRecord.h"
#include "SampledSpectrum.h"
class Background
{
public:
	virtual SampledSpectrum sample(const Ray& ray) const = 0;
};

