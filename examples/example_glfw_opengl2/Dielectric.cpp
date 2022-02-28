#include "Dielectric.h"

Dielectric::Dielectric(double ri) : ref_idx(ri) {} //n2/n1
bool Dielectric::scatter(const Ray& r_in, const HitRecord& rec, vec3& attenuation, Ray& scattered) const
{
    vec3 outward_normal;
    vec3 reflected = reflect(r_in.direction(), rec.normal);
    double ni_over_nt;
    attenuation = vec3(1.0, 1.0, 1.0);
    vec3 refracted;

    double reflect_prob; //�������
    double cosine;

    if (dot(r_in.direction(), rec.normal) > 0) //���ﵽ�⣬�����������ڷ���������һ������
    {
        outward_normal = -rec.normal;   //�Է�����ȡ��
        ni_over_nt = ref_idx;
        cosine = ref_idx * dot(r_in.direction(), rec.normal) / r_in.direction().length();
        //��֪��Ϊʲô����Ҫ��һ��ref_idx
    }
    else    //���⵽������������ڷ�����ͬһ��
    {
        outward_normal = rec.normal;    //����������
        ni_over_nt = 1.0 / ref_idx;
        cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().length();
    }

    if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted))
    {
        reflect_prob = schlick(cosine, ref_idx);
    }
    else    //�������䣬��ȫ����
    {
        reflect_prob = 1.0;
    }

    if (random_float() < reflect_prob)
    {
        scattered = Ray(rec.p, reflected,r_in.time());
    }
    else
    {
        scattered = Ray(rec.p, refracted,r_in.time());
    }

    return true;
}
