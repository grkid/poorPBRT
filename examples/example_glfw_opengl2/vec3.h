// #ifndef VEC3H
// #define VEC3H
//==================================================================================================
// Written in 2016 by Peter Shirley <ptrshrl@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related and
// neighboring rights to this software to the public domain worldwide. This software is distributed
// without any warranty.
//
// You should have received a copy (see file COPYING.txt) of the CC0 Public Domain Dedication along
// with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
//==================================================================================================
#pragma once
#include <math.h>
#include <stdlib.h>
#include <iostream>


static constexpr double M_PI = 3.1415926f;

double random_float();
double random_float(double, double);

class vec3  {
    public:
        vec3() {}
        vec3(double e0, double e1, double e2) { e[0] = e0; e[1] = e1; e[2] = e2; }
        inline double x() const { return e[0]; }
        inline double y() const { return e[1]; }
        inline double z() const { return e[2]; }
        inline double r() const { return e[0]; }
        inline double g() const { return e[1]; }
        inline double b() const { return e[2]; }

        inline const vec3& operator+() const { return *this; }
        inline vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
        inline double operator[](int i) const { return e[i]; }
        inline double& operator[](int i) { return e[i]; }

        inline vec3& operator+=(const vec3 &v2);
        inline vec3& operator-=(const vec3 &v2);
        inline vec3& operator*=(const vec3 &v2);
        inline vec3& operator/=(const vec3 &v2);
        inline vec3& operator*=(const double t);
        inline vec3& operator/=(const double t);

        static inline vec3 random();
        static inline vec3 random(double a, double b);

        inline double length() const { return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]); }
        inline double squared_length() const { return e[0]*e[0] + e[1]*e[1] + e[2]*e[2]; }
        inline void make_unit_vector();

        double e[3];
};
