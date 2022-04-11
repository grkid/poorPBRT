#include "HittableList.h"

HittableList::HittableList() {/*nothing to do*/ }

HittableList::HittableList(std::vector<std::shared_ptr<Hittable>> vec)
{
    list = vec;
}
void HittableList::add(std::shared_ptr<Hittable> obj)
{
    list.push_back(obj);
}

//如果命中了，命中记录保存到rec
bool HittableList::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const
{
    HitRecord temp_rec;
    bool hit_anything = false;
    double closest_so_far = t_max; //记录目前最近的t值
    auto list_size = list.size();
    for (int i = 0; i < list_size; i++)
    {
        if (list[i]->hit(r, t_min, closest_so_far, temp_rec))
        {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec; //只记录打到的最近的物体
        }
    }
    return hit_anything;
}

void HittableList::clear()
{
    list.clear();
}
