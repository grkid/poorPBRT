#include "Camera.h"

Camera::Camera(point3 lookfrom, vec3 lookat, vec3 vup, double vfov, double aspect, double aperture, double focus_dist,double t0,double t1)
{
    lens_radius = aperture / 2;
    double theta = vfov * M_PI / 180;
    double half_height = tan(theta / 2);
    double half_width = aspect * half_height;
    origin = lookfrom;
    w = unit_vector(lookat-lookfrom);
    u = unit_vector(cross(w, vup));
    v = cross(u, w);
    lower_left_corner = origin - half_width * focus_dist * u - half_height * focus_dist * v + focus_dist * w;
    horizontal = 2 * half_width * focus_dist * u;
    vertical = 2 * half_height * focus_dist * v;
    time0 = t0;
    time1 = t1;
}

Ray Camera::getRay(double s, double t)
{
    vec3 rd = lens_radius * random_in_unit_disk();
    vec3 offset = u * rd.x() + v * rd.y();
    return Ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset,random_float(time0,time1));
}
