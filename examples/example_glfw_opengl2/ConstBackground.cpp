#include "ConstBackground.h"

ConstBackground::ConstBackground(const vec3& color)
{
	baseColor = color;
}

vec3 ConstBackground::sample(const Ray& ray) const
{
	return baseColor;
}
