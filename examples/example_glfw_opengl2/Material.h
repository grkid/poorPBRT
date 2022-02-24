#pragma once
#include "Ray.h"
class HitRecord;
class Material
{
public:
    //r_inΪ�������, scatteredΪɢ�����, attenuation ��˼Ϊ˥������ʵ��Ϊ��ͨ���ķ�����
    virtual bool scatter(const Ray& r_in, const HitRecord& rec, vec3& attenuation, Ray& scattered) const=0;
};

