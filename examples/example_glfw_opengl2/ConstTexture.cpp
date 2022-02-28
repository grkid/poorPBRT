#include "ConstTexture.h"

ConstTexture::ConstTexture() {}

ConstTexture::ConstTexture(vec3 c)
{
	color = c;
}

vec3 ConstTexture::sample(double u, double v, const vec3& position) const
{
	return color;
}
