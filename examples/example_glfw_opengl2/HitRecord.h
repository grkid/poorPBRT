#pragma once
#include "vec3.h"
class Material;
class HitRecord
{
public:
    float t;     //�������ߵĳ���
    vec3 p;      //�����յ�����
    vec3 normal; //���е�ķ�����
    Material* mat_ptr; //new
};

