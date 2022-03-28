#pragma once
#include "Material.h"
#include "HitRecord.h"
#include "Texture.h"
#include "ConstTexture.h"
#include <memory>
class Lambertian : public Material
{
    //vec3 albedo;
    std::shared_ptr<Texture> baseColor;
public:
    Lambertian(std::shared_ptr<Texture> b);
    Lambertian(const rgb3& v);
    virtual bool scatter(const Ray& r_in, const HitRecord& rec, const point3& viewPoint, SampledSpectrum& attenuation, Ray& scattered) const;
};
