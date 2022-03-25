#pragma once
#include <optional>
#include "Hittable.h"
class Mesh :
    public Hittable
{
    point3 p0, p1, p2;    // 三点位置
    vec3 n; //法线
    std::shared_ptr<Material> matPtr;
    //double time0, time1;

public:
    friend class Surface;
    Mesh();
    Mesh(const point3& _p0, const point3& _p1, const point3& _p2, const std::optional<vec3> normal,std::shared_ptr<Material> mp);
    virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const;
};

