#include "MathUtil.h"
double utilLerp(double t, double s0, double s1)
{
	return (1.0 - t) * s0 + t * s1;
}

double utilClamp(double source, double low, double high)
{
	if (source < low) {
		return low;
	}
	else if (source > high) {
		return high;
	}
	return source;
}