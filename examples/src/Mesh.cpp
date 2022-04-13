#include "Mesh.h"
#include "Lambertian.h"
Mesh::Mesh()
{
}

Mesh::Mesh(const point3& _p0, const point3& _p1, const point3& _p2, const std::optional<vec3> normal,std::shared_ptr<Material> mp, std::shared_ptr<Matrix4x4> _mat)
{
	// Mesh默认从上方获取变换矩阵
	/*transformGen();*/
	// 默认逆时针
	p0 = _p0;
	p1 = _p1;
	p2 = _p2;
	/*n = normal;*/
	if (normal.has_value())
		n = normal.value();
	else {
		// std::optional做不到最优传参开销
		vec3 v0 = p1 - p0;
		vec3 v1 = p2 - p1;
		vec3 _v = cross(v0, v1);
		n = _v / _v.length();
	}
	matPtr = mp;
	transformMat = _mat;
}

bool Mesh::hit(const Ray& r, double t_min, double t_max, HitRecord& rec)
{
	// 命中返回True填写rec的各种，没命中不修改rec返回false
	// https://zhuanlan.zhihu.com/p/137756970
	transformUpdate();
	vec3 e1, e2;
	e1 = cacheP1 - cacheP0;
	e2 = cacheP2 - cacheP0;
	vec3 p = cross(r.direction(), e2);
	float det = dot(e1, p);
	vec3 T;
	if (det > 0)
		T = r.origin() - cacheP0;
	else
	{
		T = cacheP0 - r.origin();
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

	if (isnan(t))
		return false;

	rec.t = t;
	rec.mat_ptr = matPtr;
	rec.p = r.point_at_parameter(rec.t);
	/*TODO:UV*/
	rec.normal = cacheN;
	return true;
}

void Mesh::update()
{
	cacheP0 = transformMat * p0;
	cacheP1 = transformMat * p1;
	cacheP2 = transformMat * p2;
	cacheN = transformMat * n;
}

