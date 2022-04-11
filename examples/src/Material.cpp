#include "Material.h"

// virtual
SampledSpectrum Material::emitted(double u, double v, const point3& p) const {
	return SampledSpectrum(0.0);
}
