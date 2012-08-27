#ifndef VEC2_H
#define VEC2_H

#include "scalar.h"

namespace xxx
{

struct vec2
{
	scalar_t x, y;

	vec2() {}
	explicit vec2(scalar_t s) : x(s), y(s) {}
	explicit vec2(scalar_t x, scalar_t y) : x(x), y(y) {}
	vec2(vec2 const& v) : x(v.x), y(v.y) {}

	vec2& operator += (scalar_t s)
	{
		x += s;
		y += s;
		return *this;
	}

	vec2& operator -= (scalar_t s)
	{
		x -= s;
		y -= s;
		return *this;
	}

	vec2& operator *= (scalar_t s)
	{
		x *= s;
		y *= s;
		return *this;
	}

	vec2& operator /= (scalar_t s)
	{
		scalar_t const i = 1 / s;
		x *= i;
		y *= i;
		return *this;
	}

	vec2& operator += (vec2 const& v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}

	vec2& operator -= (vec2 const& v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}

	vec2& operator *= (vec2 const& v)
	{
		x *= v.x;
		y *= v.y;
		return *this;
	}

	vec2& operator /= (vec2 const& v)
	{
		x /= v.x;
		y /= v.y;
		return *this;
	}
};

inline vec2 operator + (vec2 const& v, scalar_t s)
{
	return vec2(v.x + s, v.y + s);
}

inline vec2 operator - (vec2 const& v, scalar_t s)
{
	return vec2(v.x - s, v.y - s);
}

inline vec2 operator * (vec2 const& v, scalar_t s)
{
	return vec2(v.x * s, v.y * s);
}

inline vec2 operator / (vec2 const& v, scalar_t s)
{
	scalar_t const i = 1 / s;
	return vec2(v.x * i, v.y * i);
}

inline vec2 operator + (vec2 const& a, vec2 const& b)
{
	return vec2(a.x + b.x, a.y + b.y);
}

inline vec2 operator - (vec2 const& a, vec2 const& b)
{
	return vec2(a.x - b.x, a.y - b.y);
}

inline vec2 operator * (vec2 const& a, vec2 const& b)
{
	return vec2(a.x * b.x, a.y * b.y);
}

inline vec2 operator / (vec2 const& a, vec2 const& b)
{
	return vec2(a.x / b.x, a.y / b.y);
}

inline vec2 inverse(vec2 const& v)
{
	return vec2(-v.x, -v.y);
}

inline vec2 min(vec2 const& a, vec2 const& b)
{
	return vec2(min(a.x, b.x), min(a.y, b.y));
}

inline vec2 max(vec2 const& a, vec2 const& b)
{
	return vec2(max(a.x, b.x), max(a.y, b.y));
}

inline vec2 abs(vec2 const& v)
{
	return vec2(abs(v.x), abs(v.y));
}

inline scalar_t dot(vec2 const& a, vec2 const& b)
{
	return a.x * b.x + a.y * b.y;
}

inline scalar_t length(vec2 const& v)
{
	return sqrt(dot(v, v));
}

inline scalar_t distance(vec2 const& a, vec2 const& b)
{
	return length(a - b);
}

inline vec2 normalize(vec2 const& v)
{
	return v / length(v);
}

inline vec2 mix(vec2 const& a, vec2 const& b, scalar_t t)
{
	return vec2(mix(a.x, b.x, t), mix(a.y, b.y, t));
}

inline vec2 reflect(vec2 const& i, vec2 const& n)
{
	return i - n * dot(n, i) * 2;
}

inline vec2 refract(vec2 const& i, vec2 const& n, scalar_t eta)
{
	scalar_t const dni = dot(n, i);
	scalar_t const k = 1 - eta * eta * (1 - dni * dni);
	return k < 0 ? vec2(0) : (i * eta - n * (eta * dni + sqrt(k)));
}

}

#endif
