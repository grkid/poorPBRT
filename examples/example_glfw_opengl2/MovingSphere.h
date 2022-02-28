#pragma once
#include "Hittable.h"
#include <memory>
class MovingSphere:public Hittable
{
	vec3 center0, center1;
	double time0, time1;
	double radius;
	std::shared_ptr<Material> matPtr;

	vec3 center(double time) const;
public:
	MovingSphere();
	MovingSphere(vec3 cen0, vec3 cen1, double t0, double t1, double r, std::shared_ptr<Material> m);
	virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const;
};

