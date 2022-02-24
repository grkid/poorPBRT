#pragma once
#include "Hittable.h"
class Sphere : public Hittable
{
public:
    vec3 center;
    double radius;
    Material* mat_ptr; /* NEW */
    Sphere();
    Sphere(vec3 cen, double r, Material* m); //new
    //��������ˣ����м�¼���浽rec
    virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const;
};
