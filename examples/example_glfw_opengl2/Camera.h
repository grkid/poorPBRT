#pragma once
#include "vec3.h"
#include "Ray.h"
//constexpr double M_PI = 3.1415926;

class Camera
{
public:
    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 u, v, w;
    double lens_radius;
    double time0, time1;

    //lookfromΪ���λ�ã�lookatΪ�۲�λ�ã�vup��(0,1,0)��vfovΪ��Ұ�Ƕȣ�aspectΪ��Ļ��߱�
    //apertureΪ��Ȧ��С��focus_distΪ������۲��ľ���
    Camera(vec3 lookfrom, vec3 lookat, vec3 vup, double vfov, double aspect, double aperture, double focus_dist,double t0=0.0,double t1=0.0);

    Ray getRay(double s, double t);
};
