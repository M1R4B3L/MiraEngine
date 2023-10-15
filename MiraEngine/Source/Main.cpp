#include "Vector3.h"

int main()
{

	Vec3<float> a;
	Vec3<float> b(1,0,1);
	Vec3<float> c(b);

	Vec3<float> d = b + c;
	Vec3<float> e = b - d;

	e = e * 5.0f;

	e.Normalize();

	a.Print();
	b.Print();
	c.Print();
	d.Print();
	e.Print();

	std::cout << a.DistanceTo(b) << "\n" << e.DotProduct(d) << "\n";

	Vec3<float> f = b.CrossProduct(d);
	f.Print();

	Vec3<float> g(1, 2, 3);
	Vec3<float> h(3,-2, 1);

	std::cout << g.AngleBetween(h);

	return 0;
}