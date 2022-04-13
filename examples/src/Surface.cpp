#include "Surface.h"

Surface::Surface()
{
	// empty
}

Surface::Surface(const point3& _p0, const point3& _p1, const point3& _p2, const point3& _p3, const std::optional<vec3> _n, std::shared_ptr<Material> mp, std::shared_ptr<Matrix4x4> _mat)
	:m0(_p0,_p1,_p2,_n,mp,_mat),
	m1(_p2,_p3,_p0,_n,mp,_mat)
{
	/*n = m0.n;*/
	/*checkInit();
	m0.set(mat);
	m1.set(mat);*/

	// 除非多加一个flag，否则没法做到零成本抽象 TODO
	transformMat = _mat;
}

bool Surface::hit(const Ray& r, double t_min, double t_max, HitRecord& rec)
{	
	// 不考虑两个同时被打到的情况
	transformUpdate();
	if (m0.hit(r, t_min, t_max, rec))
		return true;
	else if (m1.hit(r, t_min, t_max, rec))
		return true;

	return false;
}

void Surface::update()
{
	m0.update();
	m1.update();
}

//void Surface::transformSet(std::shared_ptr<Matrix4x4> ref)
//{
//	Transform::transformSet(ref);
//	m0.transformSet(ref);
//	m1.transformSet(ref);
//}
