#pragma once
#include "Hittable.h"
#include "Mesh.h"
class Surface :
    public Hittable
{
    point3 p0, p1, p2, p3;    // 四点位置。本质上是两个mesh的叠加，无需在同一平面上
    vec3 n; //法线
    Mesh m0;
    Mesh m1;
    std::shared_ptr<Material> matPtr;
public:
    Surface();
    Surface(const point3& _p0, const point3& _p1, const point3& _p2, const point3& _p3, const std::optional<vec3> _n, std::shared_ptr<Material> mp);
    virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const;
};

