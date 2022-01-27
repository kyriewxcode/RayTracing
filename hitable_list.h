#pragma once
#ifndef __HITABLE_LIST_H__
#define __HITABLE_LIST_H__

#include "hitable.h"

class Hitable_list : public Hitable
{
public:
	Hitable_list() : list(), list_size() {};
	Hitable_list(Hitable** l, int n)
	{
		list = l;
		list_size = n;
	}
	virtual bool hit(const Ray& r, float tmin, float tmax, HIT_RECORD& rec) const;

	Hitable** list;
	size_t list_size;
};

bool Hitable_list::hit(const Ray& r, float t_min, float t_max, HIT_RECORD& rec) const
{
	HIT_RECORD temp_rec;
	bool hit_anything = false;
	double closest_so_far = t_max;
	for (size_t i = 0; i < list_size; i++)
	{
		if (list[i]->hit(r, t_min, closest_so_far, temp_rec))
		{
			hit_anything = true;
			closest_so_far = temp_rec.time;
			rec = temp_rec;
		}
	}
	return hit_anything;
}

#endif // !__HITABLE_LIST_H__

