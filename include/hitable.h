#pragma once
#include "ray.h"

class Material;

struct HIT_RECORD
{
    float time {};
    Vec3 point;
    Vec3 normal;
    Material* mat_ptr;
};

class Hitable
{
public:
    virtual bool hit(const Ray& r, float t_min, float t_max, HIT_RECORD& rec) const = 0;
};
