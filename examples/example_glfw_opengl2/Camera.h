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

    //lookfrom为相机位置，lookat为观察位置，vup传(0,1,0)，vfov为视野角度，aspect为屏幕宽高比
    //aperture为光圈大小，focus_dist为相机到观察点的距离
    Camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect, float aperture, float focus_dist);

    Ray getRay(float s, float t);
};
