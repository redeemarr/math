#ifndef VEC3_H
#define VEC3_H

#include "vec2.h"

namespace xxx
{

struct vec3
{
	scalar_t x, y, z;

	vec3() {}
	explicit vec3(scalar_t s) : x(s), y(s), z(s) {}
	explicit vec3(scalar_t x, scalar_t y, scalar_t z) : x(x), y(y), z(z) {}
	explicit vec3(vec2 const& v, scalar_t z) : x(v.x), y(v.y), z(z) {}
	vec3(vec3 const& v) : x(v.x), y(v.y), z(v.z) {}

	vec2 to_vec2() const
	{
		return vec2(x, y);
	}

	vec3& operator += (scalar_t s)
	{
		x += s;
		y += s;
		z += s;
		return *this;
	}

	vec3& operator -= (scalar_t s)
	{
		x -= s;
		y -= s;
		z -= s;
		return *this;
	}

	vec3& operator *= (scalar_t s)
	{
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}

	vec3& operator /= (scalar_t s)
	{
		scalar_t const i = 1 / s;
		x *= i;
		y *= i;
		z *= i;
		return *this;
	}

	vec3& operator += (vec3 const& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	vec3& operator -= (vec3 const& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	vec3& operator *= (vec3 const& v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}

	vec3& operator /= (vec3 const& v)
	{
		x /= v.x;
		y /= v.y;
		z /= v.z;
		return *this;
	}
};

inline vec3 operator + (vec3 const& v, scalar_t s)
{
	return vec3(v.x + s, v.y + s, v.z + s);
}

inline vec3 operator - (vec3 const& v, scalar_t s)
{
	return vec3(v.x - s, v.y - s, v.z - s);
}

inline vec3 operator * (vec3 const& v, scalar_t s)
{
	return vec3(v.x * s, v.y * s, v.z * s);
}

inline vec3 operator / (vec3 const& v, scalar_t s)
{
	scalar_t const i = 1 / s;
	return vec3(v.x * i, v.y * i, v.z * i);
}

inline vec3 operator + (vec3 const& a, vec3 const& b)
{
	return vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

inline vec3 operator - (vec3 const& a, vec3 const& b)
{
	return vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

inline vec3 operator * (vec3 const& a, vec3 const& b)
{
	return vec3(a.x * b.x, a.y * b.y, a.z * b.z);
}

inline vec3 operator / (vec3 const& a, vec3 const& b)
{
	return vec3(a.x / b.x, a.y / b.y, a.z / b.z);
}

inline vec3 inverse(vec3 const& v)
{
	return vec3(-v.x, -v.y, -v.z);
}

inline vec3 min(vec3 const& a, vec3 const& b)
{
	return vec3(min(a.x, b.x), min(a.y, b.y), min(a.z, b.z));
}

inline vec3 max(vec3 const& a, vec3 const& b)
{
	return vec3(max(a.x, b.x), max(a.y, b.y), max(a.z, b.z));
}

inline vec3 abs(vec3 const& v)
{
	return vec3(abs(v.x), abs(v.y), abs(v.z));
}

inline scalar_t dot(vec3 const& a, vec3 const& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline scalar_t length(vec3 const& v)
{
	return sqrt(dot(v, v));
}

inline scalar_t distance(vec3 const& a, vec3 const& b)
{
	return length(a - b);
}

inline vec3 normalize(vec3 const& v)
{
	return v / length(v);
}

inline vec3 cross(vec3 const& a, vec3 const& b)
{
	return vec3(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x);
}

inline vec3 mix(vec3 const& a, vec3 const& b, scalar_t t)
{
	return vec3(mix(a.x, b.x, t), mix(a.y, b.y, t), mix(a.z, b.z, t));
}

inline vec3 reflect(vec3 const& i, vec3 const& n)
{
	return i - n * dot(n, i) * 2;
}

inline vec3 refract(vec3 const& i, vec3 const& n, scalar_t eta)
{
	scalar_t const dni = dot(n, i);
	scalar_t const k = 1 - eta * eta * (1 - dni * dni);
	return k < 0 ? vec3(0) : (i * eta - n * (eta * dni + sqrt(k)));
}

}

#endif
