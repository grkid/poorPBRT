#pragma once
#include "Material.h"
#include "HitRecord.h"
#include "Texture.h"
#include "ConstTexture.h"
class Metal : public Material
{
    //vec3 albedo;
    std::shared_ptr<Texture> baseColor;
    double fuzz;
public:

    Metal(std::shared_ptr<Texture> b, double f);
    Metal(const rgb3& v, double f);
    virtual bool scatter(const Ray& r_in, const HitRecord& rec, const point3& viewPoint, SampledSpectrum& attenuation, Ray& scattered) const;
};

