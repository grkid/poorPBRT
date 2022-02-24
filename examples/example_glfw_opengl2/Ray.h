#pragma once
#include "vec3.h"
class Ray
{
    vec3 A; //���
    vec3 B; //����
    float tm; //ʱ��

public:

    Ray() {}
    Ray(const vec3& a, const vec3& b,float t=0.0);
    vec3 origin() const;
    vec3 direction() const;
    vec3 point_at_parameter(float t) const; //�յ������
    float time() const;
};
