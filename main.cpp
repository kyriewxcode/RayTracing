#include <iostream>
#include <fstream>
#include "drand48.h"
#include "hitable_list.h"
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

Vec3 color(const Ray& r, Hitable* world, int depth)
{
	HIT_RECORD rec;
	if (world->hit(r, 0.001, FLT_MAX, rec))
	{
		Ray scattered;
		Vec3 attenuation;
		if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
		{
			return attenuation * color(scattered, world, depth + 1);
		}
		else
		{
			return Vec3(0, 0, 0);
		}
	}
	else
	{
		Vec3 dir = normalize(r.direction());
		float t = 0.5 * (dir.y() + 1.0);
		return (1.0 - t) * Vec3::one() + t * Vec3(0.5, 0.7, 1.0);
	}
}

Hitable* random_scene()
{
	int n = 500;
	Hitable** list = new Hitable * [n + 1];
	list[0] = new Sphere(Vec3(0, -1000, 0), 1000, new Lambertian(Vec3(0.5, 0.5, 0.5)));
	int i = 1;
	for (int a = -11; a < 11; a++)
	{
		for (int b = -11; b < 11; b++)
		{
			float choose_mat = random_double();
			Vec3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());
			if ((center - Vec3(4, 0.2, 0)).length() > 0.9)
			{
				if (choose_mat < 0.8)
				{  // diffuse
					list[i++] = new Sphere(
						center, 0.2,
						new Lambertian(Vec3(random_double() * random_double(),
							random_double() * random_double(),
							random_double() * random_double()))
					);
				}
				else if (choose_mat < 0.95)
				{ // metal
					list[i++] = new Sphere(
						center, 0.2,
						new Metal(Vec3(0.5 * (1 + random_double()),
							0.5 * (1 + random_double()),
							0.5 * (1 + random_double())),
							0.5 * random_double())
					);
				}
				else
				{  // glass
					list[i++] = new Sphere(center, 0.2, new Dielectric(1.5));
				}
			}
		}
	}

	list[i++] = new Sphere(Vec3(0, 1, 0), 1.0, new Dielectric(1.5));
	list[i++] = new Sphere(Vec3(-4, 1, 0), 1.0, new Lambertian(Vec3(0.4, 0.2, 0.1)));
	list[i++] = new Sphere(Vec3(4, 1, 0), 1.0, new Metal(Vec3(0.7, 0.6, 0.5), 0.0));

	return new Hitable_list(list, i);
}

int main()
{
	std::remove("../../image.ppm");
	std::ofstream out;
	out.open("../../image.ppm", std::ios::binary);

	int nx = 1200;
	int ny = 800;
	int ns = 100;
	out << "P3\n" << nx << " " << ny << "\n255\n";
	Hitable* world = random_scene();

	Vec3 lookfrom(13, 2, 3);
	Vec3 lookat(0, 0, 0);
	float aperture = 0.1;
	float dist_to_focus = 10.0;
	Camera cam(lookfrom, lookat, Vec3(0, 1, 0), 40, float(nx) / float(ny), aperture, dist_to_focus);

	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			Vec3 col(0, 0, 0);
			for (int s = 0; s < ns; s++)
			{
				float u = float(i + drand48()) / float(nx);
				float v = float(j + drand48()) / float(ny);
				Ray r = cam.get_ray(u, v);
				col += color(r, world, 0);
			}
			col /= float(ns);
			col = Vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);

			out << ir << " " << ig << " " << ib << "\n";
		}
	}
	out.close();
	system("..\\..\\image.ppm");
}