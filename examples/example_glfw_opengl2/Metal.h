#pragma once
#include "Material.h"
#include "HitRecord.h"
class Metal : public Material
{
public:
    vec3 albedo;
    float fuzz;

    Metal(const vec3& a, float f);

    virtual bool scatter(const Ray& r_in, const HitRecord& rec, vec3& attenuation, Ray& scattered) const;
};

