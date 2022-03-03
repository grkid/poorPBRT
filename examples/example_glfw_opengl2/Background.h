#pragma once
#include "vec3.h"
#include "Ray.h"
#include "HitRecord.h"
class Background
{
public:
	virtual vec3 sample(const Ray& ray) const = 0;
};

