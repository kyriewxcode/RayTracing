#pragma once
#ifndef __METERIAL_H__
#define __METERIAL_H__
#include "ray.h"
#include "hitable.h"
#include "drand48.h"

struct HIT_RECORD;

Vec3 random_in_uint_sphere()
{
	Vec3 p;
	do
	{
		p = 2.0 * Vec3(drand48(), drand48(), drand48()) - Vec3::one();
	} while (p.squared_length() >= 1.0);
	return p;
}

Vec3 reflect(const Vec3& v, const Vec3& n)
{
	return v - 2 * dot(v, n) * n;
}

bool refract(const Vec3& v, const Vec3& n, float ni_over_nt, Vec3& refracted)
{
	Vec3 uv = normalize(v);
	float dt = dot(uv, n);
	float discriminant = 1.0 - ni_over_nt * ni_over_nt * (1 - dt * dt);
	if (discriminant > 0)
	{
		refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
		return true;
	}
	else
	{
		return false;
	}
}

float schlick(float cosine, float ref_idx)
{
	float r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 *= r0;
	return r0 - +(1 - r0) * pow((1 - cosine), 5);
}

class Material
{
public:
	virtual bool scatter(const Ray& r_in, const HIT_RECORD& rec, Vec3& attenuation, Ray& scattered) const = 0;
};

/// <summary>
/// Lambertian material
/// </summary>
class Lambertian :public Material
{
public:
	Lambertian(const Vec3& a) : albedo(a) {}
	virtual bool scatter(const Ray& r_in, const HIT_RECORD& rec, Vec3& attenuation, Ray& scattered) const
	{
		Vec3 target = rec.point + rec.normal + random_in_uint_sphere();
		scattered = Ray(rec.point, target - rec.point);
		attenuation = albedo;
		return true;
	}

	Vec3 albedo;
};

/// <summary>
/// Metal material
/// </summary>
class Metal : public Material
{
public:
	Metal(const Vec3& a, float f) :albedo(a) { if (f < 1) fuzz = f; else fuzz = 1; }
	virtual bool scatter(const Ray& r_in, const HIT_RECORD& rec, Vec3& attenuation, Ray& scattered) const
	{
		Vec3 reflected = reflect(r_in.direction(), rec.normal);
		scattered = Ray(rec.point, reflected + fuzz * random_in_uint_sphere());
		attenuation = albedo;
		return dot(scattered.direction(), rec.normal) > 0;
	}

	Vec3 albedo;
	float fuzz;
};

/// <summary>
/// Dielectric material
/// </summary>
class Dielectric : public Material
{
public:
	Dielectric(float ri) : ref_idx(ri) {}
	virtual bool scatter(const Ray& r_in, const HIT_RECORD& rec, Vec3& attenuation, Ray& scattered) const
	{
		Vec3 outward_normal;
		Vec3 reflected = reflect(r_in.direction(), rec.normal);
		Vec3 refracted;
		float ni_over_nt = 0.0;
		attenuation = Vec3::one();

		float reflect_prob;
		float cosine;

		if (dot(r_in.direction(), rec.normal) > 0)
		{
			outward_normal = -rec.normal;
			ni_over_nt = ref_idx;
			cosine = ref_idx * dot(r_in.direction(), rec.normal) / r_in.direction().length();
		}
		else
		{
			outward_normal = rec.normal;
			ni_over_nt = 1.0 / ref_idx;
			cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().length();
		}

		if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted))
		{
			reflect_prob = schlick(cosine, ref_idx);
		}
		else
		{
			reflect_prob = 1.0;
		}

		if (drand48() < reflect_prob)
		{
			scattered = Ray(rec.point, reflected);
		}
		else
		{
			scattered = Ray(rec.point, refracted);
		}
		return true;
	}

	float ref_idx;
};

#endif // !__METERIAL_H__
