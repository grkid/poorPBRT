#pragma once
#include "Ray.h"
class HitRecord;
class Material
{
public:
    //r_in为入射光线, scattered为散射光线, attenuation 意思为衰减量，实际为各通道的反射率
    virtual bool scatter(const Ray& r_in, const HitRecord& rec, vec3& attenuation, Ray& scattered) const=0;
};

