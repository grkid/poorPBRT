#pragma once
#include "Material.h"
#include "HitRecord.h"
class Metal : public Material
{
public:
    vec3 albedo;
    double fuzz;

    Metal(const vec3& a, double f);

    virtual bool scatter(const Ray& r_in, const HitRecord& rec, vec3& attenuation, Ray& scattered) const;
};

