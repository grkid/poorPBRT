// #include <cmath>
#include "Angle.h"
constexpr auto M_PI = 3.14159265358979323846 ;
Angle::Angle(double v, AngleType type)
{
	if (type== AngleType::ANGLE_DEG) {
		deg = v;
		rad = deg * M_PI / 180.0;
	}
	else { // rad
		rad = v;
		deg = rad / M_PI * 180.0;
	}
}

double Angle::getDeg() const
{
	return deg;
}

double Angle::getRad() const
{
	return rad;
}
