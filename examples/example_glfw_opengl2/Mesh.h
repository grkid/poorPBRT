#pragma once
#include "Hittable.h"
class Mesh :
    public Hittable
{
    vec3 p0, p1, p2;    // ����λ��
    vec3 n; //����
    std::shared_ptr<Material> matPtr;
    //double time0, time1;

public:
    Mesh();
    Mesh(const vec3& _p0, const vec3& _p1, const vec3& _p2, const vec3& normal,std::shared_ptr<Material> mp);
    virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const;
};

