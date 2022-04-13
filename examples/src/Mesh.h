#pragma once
#include <optional>
#include "Hittable.h"
#include "Transform.h"
class Mesh :
    public Hittable, public Transform
{
    point3 p0, p1, p2;    // 三点位置
    vec3 n; //法线
    std::shared_ptr<Material> matPtr;
    //double time0, time1;

    // Transform cache
    point3 cacheP0, cacheP1, cacheP2;
    vec3 cacheN;

public:
    friend class Surface;
    Mesh();
    Mesh(const point3& _p0, const point3& _p1, const point3& _p2, const std::optional<vec3> normal,std::shared_ptr<Material> mp, std::shared_ptr<Matrix4x4> _mat=std::make_shared<Matrix4x4>());
    virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec);

    // Transform
    virtual void update();
};

