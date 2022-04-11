#pragma once
#include "Hittable.h"
#include "Mesh.h"
class Surface :
    public Hittable
{
    point3 p0, p1, p2, p3;    // �ĵ�λ�á�������������mesh�ĵ��ӣ�������ͬһƽ����
    vec3 n; //����
    Mesh m0;
    Mesh m1;
    std::shared_ptr<Material> matPtr;
public:
    Surface();
    Surface(const point3& _p0, const point3& _p1, const point3& _p2, const point3& _p3, const std::optional<vec3> _n, std::shared_ptr<Material> mp);
    virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const;
};

