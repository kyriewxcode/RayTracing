#pragma once

#include "hitable.h"

class Sphere : public Hitable
{
public:
    Sphere() :
        center(), radius(), mat_ptr() {}
    Sphere(Vec3 cen, float r, Material* m) :
        center(cen), radius(r), mat_ptr(m) {};
    virtual bool hit(const Ray& r, float tmin, float tmax, HIT_RECORD& rec) const;
    Vec3 center;
    float radius;
    Material* mat_ptr;
};

bool Sphere::hit(const Ray& r, float t_min, float t_max, HIT_RECORD& rec) const
{
    Vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = dot(oc, r.direction());
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - a * c;

    if (discriminant > 0)
    {
        float temp = (-b - sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min)
        {
            rec.time = temp;
            rec.point = r.point_at_parameter(rec.time);
            rec.normal = (rec.point - center) / radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }
        temp = (-b + sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min)
        {
            rec.time = temp;
            rec.point = r.point_at_parameter(rec.time);
            rec.normal = (rec.point - center) / radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }
    }
    return false;
}
