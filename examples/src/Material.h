#pragma once
#include "Ray.h"
#include "SampledSpectrum.h"
class HitRecord;
class Material
{
public:
    //r_in为入射光线, scattered为散射光线, attenuation 意思为衰减量，实际为各通道的反射率
    virtual bool scatter(const Ray& r_in, const HitRecord& rec,const point3& viewPoint, SampledSpectrum& attenuation, Ray& scattered) const=0;
    virtual SampledSpectrum emitted(double u, double v, const point3& p) const;
};

