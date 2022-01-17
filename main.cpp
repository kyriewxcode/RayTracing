#include <iostream>
#include <fstream>
#include "Vec3.h"

int main()
{
	std::ofstream out;
	out.open("../../image.ppm", std::ios::binary);

	int nx = 200;
	int ny = 100;
	out << "P3\n"
		<< nx << " " << ny
		<< "\n255\n";
	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			Vec3 color(float(i) / float(nx), float(j) / float(ny), 0.2);
			int ir = int(255.99 * color[0]);
			int ig = int(255.99 * color[1]);
			int ib = int(255.99 * color[2]);
			out << ir << " " << ig << " " << ib << "\n";
		}
	}
	out.close();
	system("..\\..\\image.ppm");
}