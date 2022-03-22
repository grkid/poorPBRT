#include "Mesh.h"

Mesh::Mesh()
{
}

Mesh::Mesh(const point3& _p0, const point3& _p1, const point3& _p2, const vec3& normal,std::shared_ptr<Material> mp)
{
	p0 = _p0;
	p1 = _p1;
	p2 = _p2;
	n = normal;
	matPtr = mp;
}

bool Mesh::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const
{
	// 命中返回True填写rec的各种，没命中不修改rec返回false
	// https://zhuanlan.zhihu.com/p/137756970
	vec3 e1, e2;
	e1 = p1 - p0;
	e2 = p2 - p0;
	vec3 p = cross(r.direction(), e2);
	float det = dot(e1, p);
	vec3 T;
	if (det > 0)
		T = r.origin() - p0;
	else
	{
		T = p0 - r.origin();
		det = -det;
	}

	if (det < 0.0)
		return false;

	double u, v;
	u = dot(T, p);
	if (u<0.0 || u >det)
	{
		return false;
	}
	vec3 Q = cross(T, e1);
	v = dot(r.direction(), Q);
	if (v<0.0 || u + v>det)
	{
		return false;
	}

	double t= dot(e2, Q) * (1.0 / det);
	if (t < t_min || t>t_max)
		return false;

	rec.t = t;
	rec.mat_ptr = matPtr;
	rec.p = r.point_at_parameter(rec.t);
	/*TODO:UV*/
	rec.normal = n;
	return true;
}

