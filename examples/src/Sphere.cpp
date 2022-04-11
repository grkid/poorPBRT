#include "Sphere.h"

Sphere::Sphere() {};
Sphere::Sphere(point3 cen, double r, std::shared_ptr<Material> m) :
    center(cen),
    radius(r),
    mat_ptr(m)
{}

bool Sphere::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const
{
    vec3 oc = r.origin() - getCenter();
    double a = dot(r.direction(), r.direction());
    double b = dot(oc, r.direction());
    double c = dot(oc, oc) - getRadius() * getRadius();
    double discriminant = b * b - a * c;
    if (discriminant > 0)
    {
        double temp = (-b - sqrt(discriminant)) / a; //小实数根
        if (temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - getCenter()) / getRadius();
            rec.mat_ptr = mat_ptr; /* NEW */
            return true;
        }
        temp = (-b + sqrt(discriminant)) / a; //大实数根
        if (temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - getCenter()) / getRadius();
            rec.mat_ptr = mat_ptr; /* NEW */
            return true;
        }
    }
    return false;
}

point3 Sphere::getCenter() const
{
    return center;
}
double Sphere::getRadius() const
{
    return radius;
}