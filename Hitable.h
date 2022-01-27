#pragma once
#ifndef __HITABLE_H__
#define __HITABLE_H__
#include "ray.h"

class Material;

struct HIT_RECORD
{
	float time{};
	Vec3 point;
	Vec3 normal;
	Material* mat_ptr;
};

class Hitable
{
public:
	virtual bool hit(const Ray& r, float t_min, float t_max, HIT_RECORD& rec) const = 0;

};

#endif // !__HITABLE_H__

