#include "HittableList.h"

HittableList::HittableList(Hittable** l, int n)
{
    list = l;
    list_size = n;
}
//��������ˣ����м�¼���浽rec
bool HittableList::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const
{
    HitRecord temp_rec;
    bool hit_anything = false;
    double closest_so_far = t_max; //��¼Ŀǰ�����tֵ
    for (int i = 0; i < list_size; i++)
    {
        if (list[i]->hit(r, t_min, closest_so_far, temp_rec))
        {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec; //ֻ��¼�򵽵��������
        }
    }
    return hit_anything;
}