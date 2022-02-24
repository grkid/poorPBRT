#pragma once
#include "vec3.h"
class Ray
{
    vec3 A; //���
    vec3 B; //����
    double tm; //ʱ��

public:

    Ray() {}
    Ray(const vec3& a, const vec3& b,double t=0.0);
    vec3 origin() const;
    vec3 direction() const;
    vec3 point_at_parameter(double t) const; //�յ������
    double time() const;
};
