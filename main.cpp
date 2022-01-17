#include <iostream>
#include <fstream>
#include "Vec3.h"
#include "Ray.h"

float hit_sphere(const Vec3& center, float radius, const Ray& r)
{
	Vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction()); // A项
	float b = 2.0 * dot(oc, r.direction());	// B项
	float c = dot(oc, oc) - radius * radius; // 常数项
	float discriminat = b * b - 4 * a * c; // b^2-4ac
	if (discriminat < 0)
	{
		return -1.0;
	}
	else
	{
		return (-b - sqrt(discriminat)) / (2.0 * a);
	}
}

Vec3 color(const Ray& r)
{
	float t = hit_sphere(Vec3(0, 0, -1), 0.5, r);
	if (t > 0.0)
	{
		Vec3 N = normalize(r.point_at_parameter(t) - Vec3(0.0, 0.0, -1.0));
		return 0.5 * Vec3(N.x() + 1, N.y() + 1, N.z() + 1);
	}
	Vec3 dir = normalize(r.direction());
	t = 0.5 * (dir.y() + 1.0);
	return (1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
}

int main()
{
	std::ofstream out;
	out.open("../../image.ppm", std::ios::binary);

	int nx = 200;
	int ny = 100;
	out << "P3\n" << nx << " " << ny << "\n255\n";
	Vec3 lower_letf_corner(-2.0, -1.0, -1.0);
	Vec3 horizontal(4.0, 0.0, 0.0);
	Vec3 vertical(0.0, 2.0, 0.0);
	Vec3 origin(0.0, 0.0, 0.0);
	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);
			Ray r(origin, lower_letf_corner + u * horizontal + v * vertical);
			Vec3 col = color(r);

			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);
			out << ir << " " << ig << " " << ib << "\n";
		}
	}
	out.close();
	system("..\\..\\image.ppm");
}