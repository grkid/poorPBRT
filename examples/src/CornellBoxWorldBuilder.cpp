#include "CornellBoxWorldBuilder.h"
#include "Surface.h"
#include "Point3.h"
#include "Lambertian.h"
#include "Emit.h"
#include "Cuboid.h"
#include "Sphere.h"
#include "Dielectric.h"

void CornellBoxWorldBuilder::build(Scene& world) const
{
	auto whiteColor = std::make_shared<Lambertian>(rgb3(0.8, 0.8, 0.8));
	auto redColor = std::make_shared<Lambertian>(rgb3(0.8, 0.2, 0.2));
	auto	greenColor = std::make_shared<Lambertian>(rgb3(0.2, 0.8, 0.2));
	auto blueColor = std::make_shared<Lambertian>(rgb3(0.2, 0.2, 0.8));

	auto lightColor = std::make_shared<Emit>(rgb3(4.0, 4.0, 4.0));

	auto transparent = std::make_shared<Dielectric>(1.5);

	// down
	world.add(std::make_shared<Surface>(point3(-1, -1, -1), point3(-1, 1, -1), point3(1, 1, -1), point3(1, -1, -1), vec3(0, 0, 1), greenColor));
	// left
	world.add(std::make_shared<Surface>(point3(-1, -1, -1), point3(1, -1, -1), point3(1, -1, 1), point3(-1, -1, 1), vec3(0, 1, 0), redColor));
	// right
	world.add(std::make_shared<Surface>(point3(-1, 1, -1), point3(-1, 1, 1), point3(1, 1, 1), point3(1, 1, -1), vec3(0, -1, 0), blueColor));
	// back
	world.add(std::make_shared<Surface>(point3(-1, 1, -1), point3(-1, 1, 1), point3(-1, -1, 1), point3(-1, -1, -1), vec3(1, 0, 0), whiteColor));
	//top
	world.add(std::make_shared<Surface>(point3(-1, -1, 1), point3(1, -1, 1), point3(1, 1, 1), point3(-1, 1, 1), vec3(0, 0, -1), whiteColor));
	//light
	world.add(std::make_shared<Surface>(point3(-0.3, -0.3, 0.95), point3(0.3, -0.3, 0.95), point3(0.3, 0.3, 0.95), point3(-0.3, 0.3, 0.95), vec3(0, 0, -1), lightColor));

	// box1
	auto box1 = std::make_shared<Cuboid>(point3(-0.0, -0.0,0.0), 0.4, whiteColor);
	box1->setRotate(Angle(0.0),Angle(0.0),Angle(45.0));
	/*box1->setScale(1.0,0.1,1.0);*/
	 box1->setTranslate(-0.3, -0.3, -0.6);
	world.add(box1);
	// box2
	world.add(std::make_shared<Cuboid>(point3(0.5, 0.5, -1.0 + 0.2), 0.2, whiteColor));

}
