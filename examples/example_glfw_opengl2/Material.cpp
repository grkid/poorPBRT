#include "Material.h"

// virtual
vec3 Material::emitted(double u, double v, const vec3& p) const {
	return vec3(0.0f, 0.0f, 0.0f);
}
