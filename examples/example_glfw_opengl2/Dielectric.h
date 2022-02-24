#pragma once
#include "Material.h"
#include "HitRecord.h"
class Dielectric : public Material
{
public:
    Dielectric(double ri); //n2/n1
    virtual bool scatter(const Ray& r_in, const HitRecord& rec, vec3& attenuation, Ray& scattered) const;

    double ref_idx;
};

