#pragma once
#include "Hittable.h"
#include <memory>
class Sphere : public Hittable
{
    point3 center;
    double radius;
    std::shared_ptr<Material> mat_ptr; /* NEW */
public:
    Sphere();
    Sphere(point3 cen, double r, std::shared_ptr<Material> m); //new

    virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const;

    virtual point3 getCenter() const;
    virtual double getRadius() const;
};
