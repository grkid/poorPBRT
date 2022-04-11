#include <optional>
#include "Cuboid.h"

Cuboid::Cuboid(std::vector<point3> vec, std::shared_ptr<Material> mp)
	:pLDF(vec[0]), pRDF(vec[1]), pRUF(vec[2]), pLUF(vec[3]),
	pLUB(vec[4]), pLDB(vec[5]), pRDB(vec[6]), pRUB(vec[7]),
	L(pLDF, pLUF, pLUB, pLDB, std::nullopt, mp),
	R(pRDF, pRDB, pRUB, pRUF, std::nullopt, mp),
	U(pLUF, pRUF, pRUB, pLUB, std::nullopt, mp),
	D(pLDF, pLDB, pRDB, pRDF, std::nullopt, mp),
	F(pLDF, pRDF, pRUF, pLUF, std::nullopt, mp),
	B(pLDB, pLUB, pRUB, pRDB, std::nullopt, mp)
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


}

Cuboid::Cuboid(const point3* vec, std::shared_ptr<Material> mp)
	:pLDF(vec[0]), pRDF(vec[1]), pRUF(vec[2]), pLUF(vec[3]),
	pLUB(vec[4]), pLDB(vec[5]), pRDB(vec[6]), pRUB(vec[7]),
	L(pLDF, pLUF, pLUB, pLDB, std::nullopt, mp),
	R(pRDF, pRDB, pRUB, pRUF, std::nullopt, mp),
	U(pLUF, pRUF, pRUB, pLUB, std::nullopt, mp),
	D(pLDF, pLDB, pRDB, pRDF, std::nullopt, mp),
	F(pLDF, pRDF, pRUF, pLUF, std::nullopt, mp),
	B(pLDB, pLUB, pRUB, pRDB, std::nullopt, mp)
{
	/*pLDF = vec[0];
	pRDF = vec[1];
	pRUF = vec[2];
	pLUF = vec[3];
	pLUB = vec[4];
	pLDB = vec[5];
	pRDB = vec[6];
	pRUB = vec[7];*/
}

// 正方体没有半径一说，只是借用
// radius为正方体边长的一半
Cuboid::Cuboid(const point3& centre, double radius, std::shared_ptr<Material> mp)
	:pLDF(centre + point3(-radius, -radius, -radius)), pRDF(centre + point3(+radius, -radius, -radius)), 
	pRUF(centre + point3(+radius, -radius, +radius)), pLUF(centre + point3(-radius, -radius, +radius)),
	pLUB(centre + point3(-radius, +radius, +radius)), pLDB(centre + point3(-radius, +radius, -radius)),
	pRDB(centre + point3(+radius, +radius, -radius)), pRUB(centre + point3(+radius, +radius, +radius)),
	L(pLDF, pLUF, pLUB, pLDB, std::nullopt, mp),
	R(pRDF, pRDB, pRUB, pRUF, std::nullopt, mp),
	U(pLUF, pRUF, pRUB, pLUB, std::nullopt, mp),
	D(pLDF, pLDB, pRDB, pRDF, std::nullopt, mp),
	F(pLDF, pRDF, pRUF, pLUF, std::nullopt, mp),
	B(pLDB, pLUB, pRUB, pRDB, std::nullopt, mp)
{
	// empty
}

bool Cuboid::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const
{
	// 会出现多个同时被打到的情况
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
