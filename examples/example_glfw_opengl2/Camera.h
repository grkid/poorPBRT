#pragma once
#include "vec3.h"
#include "Ray.h"
//constexpr float M_PI = 3.1415926;

class Camera
{
public:
    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 u, v, w;
    float lens_radius;

    //lookfromΪ���λ�ã�lookatΪ�۲�λ�ã�vup��(0,1,0)��vfovΪ��Ұ�Ƕȣ�aspectΪ��Ļ��߱�
    //apertureΪ��Ȧ��С��focus_distΪ������۲��ľ���
    Camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect, float aperture, float focus_dist);

    Ray getRay(float s, float t);
};
