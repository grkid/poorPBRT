#include "Emit.h"

Emit::Emit(std::shared_ptr<Texture> bc)
{
	baseColor = bc;
}

Emit::Emit(const rgb3& v)
{
	baseColor = std::make_shared<ConstTexture>(v);
}

bool Emit::scatter(const Ray& r_in, const HitRecord& rec, const point3& viewPoint, SampledSpectrum& attenuation, Ray& scattered) const
{
	return false;
}

SampledSpectrum Emit::emitted(double u, double v, const point3& p) const
{
	// 没有考虑光线的衰减
	return baseColor->sample(u, v, p);
}
