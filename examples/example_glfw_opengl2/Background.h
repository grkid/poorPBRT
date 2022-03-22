#pragma once
#include "vec3.h"
#include "Ray.h"
#include "HitRecord.h"
class Background
{
public:
	virtual rgb3 sample(const Ray& ray) const = 0;
};

