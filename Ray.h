#pragma once
#ifndef __RAY_H__
#define __RAY_H__
#include "Vec3.h"

class Ray
{
public:
	Ray() {};
	Ray(const Vec3& a, const Vec3& b) { A = a; B = b; }
	Vec3 origin() const { return A; }
	Vec3 direction() const { return B; }
	Vec3 point_at_parameter(float time) const { return A + time * B; }

	Vec3 A;
	Vec3 B;
};

#endif // !__RAY_H__


