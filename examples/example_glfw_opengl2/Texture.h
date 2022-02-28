#pragma once
#include "vec3.h"
class Texture
{
public:
	virtual vec3 sample(double u, double v, const vec3& position) const=0;
};

