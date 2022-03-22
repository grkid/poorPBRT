#include "Material.h"

// virtual
rgb3 Material::emitted(double u, double v, const point3& p) const {
	return rgb3(0.0f, 0.0f, 0.0f);
}
