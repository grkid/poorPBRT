#include "Light.h"

Light::Light(std::shared_ptr<Texture> bc)
{
	baseColor = bc;
}

bool Light::scatter(const Ray& r_in, const HitRecord& rec, vec3& attenuation, Ray& scattered) const
{
	return false;
}

rgb3 Light::emitted(double u, double v, const point3& p) const
{
	// 没有考虑光线的衰减
	return baseColor->sample(u, v, p);
}
