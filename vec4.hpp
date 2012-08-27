#ifndef VEC4_H
#define VEC4_H

#include "vec3.h"

namespace xxx
{

struct vec4
{
	scalar_t x, y, z, w;

	vec4() {}
	explicit vec4(scalar_t s) : x(s), y(s), z(s), w(s) {}
	explicit vec4(scalar_t x, scalar_t y, scalar_t z, scalar_t w) : x(x), y(y), z(z), w(w) {}
	explicit vec4(vec2 const& v, scalar_t z, scalar_t w) : x(v.x), y(v.y), z(z), w(w) {}
	explicit vec4(vec3 const& v, scalar_t w) : x(v.x), y(v.y), z(v.z), w(w) {}
	vec4(vec4 const& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}

	vec2 to_vec2() const
	{
		return vec2(x, y);
	}

	vec3 to_vec3() const
	{
		return vec3(x, y, z);
	}

	vec4& operator += (scalar_t s)
	{
		x += s;
		y += s;
		z += s;
		w += s;
		return *this;
	}

	vec4& operator -= (scalar_t s)
	{
		x -= s;
		y -= s;
		z -= s;
		w -= s;
		return *this;
	}

	vec4& operator *= (scalar_t s)
	{
		x *= s;
		y *= s;
		z *= s;
		w *= s;
		return *this;
	}

	vec4& operator /= (scalar_t s)
	{
		scalar_t const i = 1 / s;
		x *= i;
		y *= i;
		z *= i;
		w *= i;
		return *this;
	}

	vec4& operator += (vec4 const& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
		return *this;
	}

	vec4& operator -= (vec4 const& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
		return *this;
	}

	vec4& operator *= (vec4 const& v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
		w *= v.w;
		return *this;
	}

	vec4& operator /= (vec4 const& v)
	{
		x /= v.x;
		y /= v.y;
		z /= v.z;
		w /= v.w;
		return *this;
	}
};

inline vec4 operator + (vec4 const& v, scalar_t s)
{
	return vec4(v.x + s, v.y + s, v.z + s, v.w + s);
}

inline vec4 operator - (vec4 const& v, scalar_t s)
{
	return vec4(v.x - s, v.y - s, v.z - s, v.w - s);
}

inline vec4 operator * (vec4 const& v, scalar_t s)
{
	return vec4(v.x * s, v.y * s, v.z * s, v.w * s);
}

inline vec4 operator / (vec4 const& v, scalar_t s)
{
	scalar_t const i = 1 / s;
	return vec4(v.x * i, v.y * i, v.z * i, v.w * i);
}

inline vec4 operator + (vec4 const& a, vec4 const& b)
{
	return vec4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

inline vec4 operator - (vec4 const& a, vec4 const& b)
{
	return vec4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

inline vec4 operator * (vec4 const& a, vec4 const& b)
{
	return vec4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}

inline vec4 operator / (vec4 const& a, vec4 const& b)
{
	return vec4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
}

inline vec4 inverse(vec4 const& v)
{
	return vec4(-v.x, -v.y, -v.z, -v.w);
}

inline vec4 min(vec4 const& a, vec4 const& b)
{
	return vec4(min(a.x, b.x), min(a.y, b.y), min(a.z, b.z), min(a.w, b.w));
}

inline vec4 max(vec4 const& a, vec4 const& b)
{
	return vec4(max(a.x, b.x), max(a.y, b.y), max(a.z, b.z), max(a.w, b.w));
}

inline vec4 abs(vec4 const& v)
{
	return vec4(abs(v.x), abs(v.y), abs(v.z), abs(v.w));
}

inline scalar_t dot(vec4 const& a, vec4 const& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

inline scalar_t length(vec4 const& v)
{
	return sqrt(dot(v, v));
}

inline scalar_t distance(vec4 const& a, vec4 const& b)
{
	return length(a - b);
}

inline vec4 normalize(vec4 const& v)
{
	return v / length(v);
}

inline vec4 mix(vec4 const& a, vec4 const& b, scalar_t t)
{
	return vec4(mix(a.x, b.x, t), mix(a.y, b.y, t), mix(a.z, b.z, t), mix(a.w, b.w, t));
}

inline vec4 reflect(vec4 const& i, vec4 const& n)
{
	return i - n * dot(n, i) * 2;
}

inline vec4 refract(vec4 const& i, vec4 const& n, scalar_t eta)
{
	scalar_t const dni = dot(n, i);
	scalar_t const k = 1 - eta * eta * (1 - dni * dni);
	return k < 0 ? vec4(0) : (i * eta - n * (eta * dni + sqrt(k)));
}

}

#endif
