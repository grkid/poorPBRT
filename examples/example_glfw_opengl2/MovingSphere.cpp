#include "MovingSphere.h"

MovingSphere::MovingSphere()
{
}

MovingSphere::MovingSphere(vec3 cen0, vec3 cen1, double r, std::shared_ptr<Material> m,double t0, double t1)
	:center0(cen0),
	center1(cen1),
	radius(r),
	matPtr(m)
{
	// done
    setTimeInterval(t0, t1);
}

MovingSphere::MovingSphere(const Sphere& base, vec3 cen1, double t0, double t1)
    :Sphere(base),
    center1(cen1)
{
    // TODO：接口未经测试
    setTimeInterval(t0, t1);
}


bool MovingSphere::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const
{
    auto _center = getCenter(r.time());
    vec3 oc = r.origin() - _center;
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
            rec.normal = (rec.p - _center) / radius;
            rec.mat_ptr = matPtr; /* NEW */
            return true;
        }
        temp = (-b + sqrt(discriminant)) / a; //大实数根
        if (temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - _center) / radius;
            rec.mat_ptr = matPtr; /* NEW */
            return true;
        }
    }
    return false;
}

vec3 MovingSphere::getCenter(double time) const {
    return center0 + ((time - time0) / (time1 - time0)) * (center1 - center0);
}

void MovingSphere::setTimeInterval(double t0, double t1)
{
    time0 = t0;
    time1 = t1;
}
