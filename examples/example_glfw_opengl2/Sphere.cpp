#include "Sphere.h"

Sphere::Sphere() {};
Sphere::Sphere(vec3 cen, double r, std::shared_ptr<Material> m) :
    center(cen),
    radius(r),
    mat_ptr(m)
{}

bool Sphere::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const
{
    vec3 oc = r.origin() - center;
    double a = dot(r.direction(), r.direction());
    double b = dot(oc, r.direction());
    double c = dot(oc, oc) - radius * radius;
    double discriminant = b * b - a * c;
    if (discriminant > 0)
    {
        double temp = (-b - sqrt(discriminant)) / a; //小实数根
        if (temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat_ptr; /* NEW */
            return true;
        }
        temp = (-b + sqrt(discriminant)) / a; //大实数根
        if (temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat_ptr; /* NEW */
            return true;
        }
    }
    return false;
}