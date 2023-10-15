#pragma once
#include <iostream>

template <typename T>
class Vec3
{
public:
	T x = 0.0;
	T y = 0.0;
	T z = 0.0;

public:

	Vec3() = default;
	Vec3(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {};
	Vec3(const Vec3<T> &other) : x(other.x), y(other.y), z(other.z) {};

	~Vec3() {};

	const Vec3<T> operator+(const Vec3<T>&other) const
	{
		return Vec3<T>(x + other.x, y + other.y, z + other.z);
	}
	const Vec3<T> operator-(const Vec3<T>&other) const
	{
		return Vec3<T>(x - other.x, y - other.y, z - other.z);
	}
	const Vec3<T> operator*(T scalar) const
	{
		return Vec3<T>(x * scalar, y * scalar, z * scalar);
	}
	const Vec3<T> operator/(T scalar) const
	{
		return Vec3<T>(x / scalar, y / scalar, z / scalar);
	}

	//TODO: operator<< for printing in console 

	void Print() { std::cout << '(' << x << ',' << y << ',' << z << ")\n"; }

	inline void SetX(const T x) { this->x = x; }
	inline void SetY(const T y) { this->y = y; }
	inline void SetZ(const T z) { this->z = z; }

	inline T GetX() const { return x; };
	inline T GetY() const { return y; };
	inline T GetZ() const { return z; };

	const T Magnitude()
	{
		return std::sqrt((x * x) + (y * y) + (z * z));
	}

	const Vec3<T> Normalize()
	{
		T magnitude = Magnitude();

		x = x / magnitude;
		y = y / magnitude;
		z = z / magnitude;

		return *this;
	}

	const T DistanceTo(const Vec3<T> &vec) const  //Final - Ini
	{
		return std::sqrt(((vec.x - x) * (vec.x - x)) + ((vec.y - y) * (vec.y - y)) + ((vec.z - z) * (vec.z - z)));
	}

	const T DotProduct(const Vec3<T> &vec) const
	{
		return ((x * vec.x) + (y * vec.y) + (z * vec.z));
	}

	const Vec3<T> CrossProduct(const Vec3<T>& vec) const
	{
		return Vec3<T>((y*vec.z - z*vec.y), (z*vec.x - x*vec.z), (x*vec.y - y*vec.x));
	}

	const T AngleBetween(Vec3<T> &vec) //Rad to degrees 
	{
		return std::acos((*this).DotProduct(vec) / ((*this).Magnitude() * vec.Magnitude())) * (180/3.14159);
	}
};