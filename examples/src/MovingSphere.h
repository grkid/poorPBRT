#pragma once
#include "Hittable.h"
#include "Moving.h"
#include "Sphere.h"
#include <memory>
class MovingSphere:public Sphere,Moving
{
	point3 center0, center1;
	double time0, time1;
	double radius;
	std::shared_ptr<Material> matPtr;

	// 继承覆写纯虚函数需要声明
	virtual void setTimeInterval(double, double);
public:
	MovingSphere();
	MovingSphere(point3 cen0, point3 cen1,double r, std::shared_ptr<Material> m, double t0, double t1);
	MovingSphere(const Sphere& base,point3 cen1, double t0, double t1);

	bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const;
	
	virtual point3 getCenter(double) const;
	// getRadius()无需覆盖
};

