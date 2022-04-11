#pragma once
#include "Material.h"
#include "Texture.h"
#include "ConstTexture.h"
class Emit: public Material
{
	std::shared_ptr<Texture> baseColor;
public:
	Emit(std::shared_ptr<Texture> bc);
	Emit(const rgb3& v);
	virtual bool scatter(const Ray& r_in, const HitRecord& rec, const point3& viewPoint, SampledSpectrum& attenuation, Ray& scattered) const;
	virtual SampledSpectrum emitted(double u, double v, const point3& p) const;
};

