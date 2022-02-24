#pragma once
#include "Material.h"
#include "HitRecord.h"
class Lambertian : public Material
{
public:
    vec3 albedo; //·´ÉäÂÊ
    Lambertian(const vec3& a) : albedo(a) {}
    virtual bool scatter(const Ray& r_in, const HitRecord& rec, vec3& attenuation, Ray& scattered) const;
};
