#pragma once
#include "Material.h"
#include "Texture.h"
class Light: public Material
{
	std::shared_ptr<Texture> baseColor;
public:
	Light(std::shared_ptr<Texture> bc);
	virtual bool scatter(const Ray& r_in, const HitRecord& rec, vec3& attenuation, Ray& scattered) const;
	virtual SampledSpectrum emitted(double u, double v, const point3& p) const;
};

