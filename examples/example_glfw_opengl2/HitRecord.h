#pragma once
#include "vec3.h"
class Material;
class HitRecord
{
public:
    float t;     //命中射线的长度
    vec3 p;      //命中终点坐标
    vec3 normal; //命中点的法向量
    Material* mat_ptr; //new
};

