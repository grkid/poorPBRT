#include "ConstBackground.h"

ConstBackground::ConstBackground(const rgb3& color)
{
	baseColor = color;
}

rgb3 ConstBackground::sample(const Ray& ray) const
{
	return baseColor;
}
