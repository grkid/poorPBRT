#include "Light.h"

Light::Light(std::shared_ptr<Texture> bc)
{
	baseColor = bc;
}

bool Light::scatter(const Ray& r_in, const HitRecord& rec, vec3& attenuation, Ray& scattered) const
{
	return false;
}

vec3 Light::emitted(double u, double v, const vec3& p) const
{
	// û�п��ǹ��ߵ�˥��
	return baseColor->sample(u, v, p);
}
