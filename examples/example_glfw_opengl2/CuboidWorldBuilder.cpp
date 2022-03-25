#include "CuboidWorldBuilder.h"
#include "Cuboid.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"

void CuboidWorldBuilder::build(HittableList& world) const
{
    world.add(std::make_shared<Cuboid>(
        point3(0, 0, -1000), 1000, std::make_shared<Lambertian>(rgb3(0.5, 0.5, 0.5))));

    int i = 1;
    for (int a = -10; a < 10; a++) {
        for (int b = -10; b < 10; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9 * random_double(), b + 0.9 * random_double(), 0.2);
            if ((center - vec3(4, 0, .2)).length() > 0.9) {
                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = vec3::random() * vec3::random();
                    world.add(std::make_shared<Cuboid>(
                        center, 0.2,
                        std::make_shared<Lambertian>(rgb3::fromVec3(albedo))));
                }
                else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = vec3::random(.5, 1);
                    auto fuzz = random_double(0, .5);
                    world.add(
                        std::make_shared<Cuboid>(center, 0.2, std::make_shared<Metal>(rgb3::fromVec3(albedo), fuzz)));
                }
                else {
                    // glass
                    world.add(std::make_shared<Cuboid>(center, 0.2, std::make_shared<Dielectric>(1.5)));
                }
            }
        }
    }

    world.add(std::make_shared<Cuboid>(point3(0, 0, 1), 1.0, std::make_shared<Dielectric>(1.5)));
    world.add(std::make_shared<Cuboid>(
        point3(-4, 0, 1), 1.0, std::make_shared<Lambertian>(rgb3(0.4, 0.2, 0.1))));
    world.add(std::make_shared<Cuboid>(
        point3(4, 0, 1), 1.0, std::make_shared<Metal>(rgb3(0.7, 0.6, 0.5), 0.0)));
}
