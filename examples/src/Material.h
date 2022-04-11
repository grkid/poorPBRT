#pragma once
#include "Ray.h"
#include "SampledSpectrum.h"
class HitRecord;
class Material
{
public:
    //r_inΪ�������, scatteredΪɢ�����, attenuation ��˼Ϊ˥������ʵ��Ϊ��ͨ���ķ�����
    virtual bool scatter(const Ray& r_in, const HitRecord& rec,const point3& viewPoint, SampledSpectrum& attenuation, Ray& scattered) const=0;
    virtual SampledSpectrum emitted(double u, double v, const point3& p) const;
};

