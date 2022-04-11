#pragma once
#include <cmath>
#include <cfloat>

double utilLerp(double t, double s0, double s1);

double utilClamp(double source, double low = 0.0, double high = DBL_MAX);
