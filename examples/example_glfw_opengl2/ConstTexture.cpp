#include "ConstTexture.h"

ConstTexture::ConstTexture() {}

ConstTexture::ConstTexture(const rgb3& c)
{
	color = c;
}

rgb3 ConstTexture::sample(double u, double v, const point3& position) const
{
	return color;
}
