#include "Surface.h"

Surface::Surface()
{
}

Surface::Surface(const vec3& _p0, const vec3& _p1, const vec3& _p2, const vec3& _p3, const vec3& _n, std::shared_ptr<Material> mp)
	:m0(_p0,_p1,_p2,_n,mp),
	m1(_p2,_p3,_p0,_n,mp)
{

}

bool Surface::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const
{	
	// 不考虑两个同时被打到的情况
	if (m0.hit(r, t_min, t_max, rec))
		return true;
	else if (m1.hit(r, t_min, t_max, rec))
		return true;

	return false;
}
