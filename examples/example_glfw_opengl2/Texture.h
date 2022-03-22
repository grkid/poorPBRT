#pragma once
#include "vec3.h"
#include "rgb3.h"
#include "point3.h"
class Texture
{
public:
	virtual rgb3 sample(double u, double v, const point3& position) const=0;
};

