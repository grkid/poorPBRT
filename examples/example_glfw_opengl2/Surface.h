#pragma once
#include "Hittable.h"
class Surface :
    public Hittable
{
    vec3 p0, p1, p2, p3;    // 四点位置。本质上是两个mesh的叠加，无需在同一平面上
    vec3 n; //法线
    std::shared_ptr<Material> matPtr;
public:
    Surface();
    Surface(const vec3& _p0, const vec3& _p1, const vec3& _p2, const vec3& _p3, const vec3& _n, std::shared_ptr<Material> mp);
    virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const;
};

