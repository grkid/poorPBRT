#pragma once
#include "Material.h"
#include "Texture.h"
class Light: public Material
{
	std::shared_ptr<Texture> baseColor;
public:
	Light(std::shared_ptr<Texture> bc);
	virtual bool scatter(const Ray& r_in, const HitRecord& rec, vec3& attenuation, Ray& scattered) const;
	virtual vec3 emitted(double u, double v, const vec3& p) const;
};

