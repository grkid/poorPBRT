#include <optional>
#include "Cuboid.h"

Cuboid::Cuboid(std::vector<point3> vec, std::shared_ptr<Material> mp, std::shared_ptr<Matrix4x4> _mat)
	:pLDF(vec[0]), pRDF(vec[1]), pRUF(vec[2]), pLUF(vec[3]),
	pLUB(vec[4]), pLDB(vec[5]), pRDB(vec[6]), pRUB(vec[7]),
	L(pLDF, pLUF, pLUB, pLDB, std::nullopt, mp, _mat),
	R(pRDF, pRDB, pRUB, pRUF, std::nullopt, mp, _mat),
	U(pLUF, pRUF, pRUB, pLUB, std::nullopt, mp, _mat),
	D(pLDF, pLDB, pRDB, pRDF, std::nullopt, mp, _mat),
	F(pLDF, pRDF, pRUF, pLUF, std::nullopt, mp, _mat),
	B(pLDB, pLUB, pRUB, pRDB, std::nullopt, mp, _mat)
{
	// LDF RDF RUF LUF
	// LUB LDB RDB RUB
	/*pLDF = vec[0];
	pRDF = vec[1];
	pRUF = vec[2];
	pLUF = vec[3];
	pLUB = vec[4];
	pLDB = vec[5];
	pRDB = vec[6];
	pRUB = vec[7];*/
	/*transformSet(_mat)*/
	transformMat = _mat;


}

Cuboid::Cuboid(const point3* vec, std::shared_ptr<Material> mp, std::shared_ptr<Matrix4x4> _mat)
	:pLDF(vec[0]), pRDF(vec[1]), pRUF(vec[2]), pLUF(vec[3]),
	pLUB(vec[4]), pLDB(vec[5]), pRDB(vec[6]), pRUB(vec[7]),
	L(pLDF, pLUF, pLUB, pLDB, std::nullopt, mp, _mat),
	R(pRDF, pRDB, pRUB, pRUF, std::nullopt, mp, _mat),
	U(pLUF, pRUF, pRUB, pLUB, std::nullopt, mp, _mat),
	D(pLDF, pLDB, pRDB, pRDF, std::nullopt, mp, _mat),
	F(pLDF, pRDF, pRUF, pLUF, std::nullopt, mp, _mat),
	B(pLDB, pLUB, pRUB, pRDB, std::nullopt, mp, _mat)
{
	/*pLDF = vec[0];
	pRDF = vec[1];
	pRUF = vec[2];
	pLUF = vec[3];
	pLUB = vec[4];
	pLDB = vec[5];
	pRDB = vec[6];
	pRUB = vec[7];*/
	/*transformGen();*/
	transformMat = _mat;
}

// 正方体没有半径一说，只是借用
// radius为正方体边长的一半
Cuboid::Cuboid(const point3& centre, double radius, std::shared_ptr<Material> mp, std::shared_ptr<Matrix4x4> _mat)
	:pLDF(centre + point3(-radius, -radius, -radius)), pRDF(centre + point3(+radius, -radius, -radius)), 
	pRUF(centre + point3(+radius, -radius, +radius)), pLUF(centre + point3(-radius, -radius, +radius)),
	pLUB(centre + point3(-radius, +radius, +radius)), pLDB(centre + point3(-radius, +radius, -radius)),
	pRDB(centre + point3(+radius, +radius, -radius)), pRUB(centre + point3(+radius, +radius, +radius)),
	L(pLDF, pLUF, pLUB, pLDB, std::nullopt, mp, _mat),
	R(pRDF, pRDB, pRUB, pRUF, std::nullopt, mp, _mat),
	U(pLUF, pRUF, pRUB, pLUB, std::nullopt, mp, _mat),
	D(pLDF, pLDB, pRDB, pRDF, std::nullopt, mp, _mat),
	F(pLDF, pRDF, pRUF, pLUF, std::nullopt, mp, _mat),
	B(pLDB, pLUB, pRUB, pRDB, std::nullopt, mp, _mat)
{
	/*transformGen();*/
	transformMat = _mat;
}

bool Cuboid::hit(const Ray& r, double t_min, double t_max, HitRecord& rec)
{
	// 会出现多个同时被打到的情况
	transformUpdate();
	HitRecord stand;	// “替身”
	std::vector<HitRecord> vec;	// 复制

	// 一条射线最多与两个面相交

	int hitCount = 0;

	if (hitCount<2 && L.hit(r, t_min, t_max, stand)) {
		vec.push_back(stand);
		hitCount++;
	}
	if (hitCount < 2 && R.hit(r, t_min, t_max, stand)) {
		vec.push_back(stand);
		hitCount++;
	}
	if (hitCount < 2 && U.hit(r, t_min, t_max, stand)) {
		vec.push_back(stand);
		hitCount++;
	}
	if (hitCount < 2 && D.hit(r, t_min, t_max, stand)) {
		vec.push_back(stand);
		hitCount++;
	}
	if (hitCount < 2 && F.hit(r, t_min, t_max, stand)) {
		vec.push_back(stand);
		hitCount++;
	}
	if (hitCount < 2 && B.hit(r, t_min, t_max, stand)) {
		vec.push_back(stand);
		hitCount++;
	}

	if (vec.empty())
		return false;

	HitRecord* temp = &vec[0];
	double minRayT = DBL_MAX;
	for (auto& item : vec) {
		if (item.t < minRayT) {
			minRayT = item.t;
			temp = &item;
		}
	}
	rec = *temp;
	return true;
}

void Cuboid::update()
{
	L.update();
	R.update();
	U.update();
	D.update();
	F.update();
	B.update();
}

//void Cuboid::transformSet(std::shared_ptr<Matrix4x4> ref)
//{
//	Transform::transformSet(ref);
//	L.transformSet(ref);
//	R.transformSet(ref);
//	U.transformSet(ref);
//	D.transformSet(ref);
//	F.transformSet(ref);
//	B.transformSet(ref);
//}
