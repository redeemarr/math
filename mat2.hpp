#ifndef MAT2_H
#define MAT2_H

#include "vec2.h"

namespace xxx
{

struct mat2
{
	vec2 x, y;

	mat2() {}
	explicit mat2(vec2 const& x, vec2 const& y) : x(x), y(y) {}

	scalar_t determinant() const
	{
		return x.x * y.y - x.y * y.x;
	}

	static mat2 identity()
	{
		return mat2(vec2(1, 0), vec2(0, 1));
	}

	static mat2 from_angle(scalar_t angle)
	{
		float sa, ca;
		sincos(angle, sa, ca);
		return mat2(vec2(ca, sa), vec2(-sa, ca));
	}
};

inline mat2 transpose(mat2 const& m)
{
	return mat2(
		vec2(m.x.x, m.y.x),
		vec2(m.x.y, m.y.y));
}

inline mat2 inverse(mat2 const& m)
{
	scalar_t const d = 1 / m.determinant();
	if (d != 0)
	{
		scalar_t const id = 1 / d;
		return mat2(
			vec2( m.y.y, -m.x.y) * id,
			vec2(-m.y.x,  m.x.x) * id);
	}
	else
	{
		return mat2::identity();
	}
}

inline vec2 operator * (mat2 const& m, vec2 const& v)
{
	return vec2(
		v.x * m.x.x + v.y * m.y.x,
		v.x * m.x.y + v.y * m.y.y);
}

inline mat2 operator * (mat2 const& a, mat2 const& b)
{
	return mat2(
		vec2(
			a.x.x * b.x.x + a.x.y * b.y.x,
			a.x.x * b.x.y + a.x.y * b.y.y),
		vec2(
			a.y.x * b.x.x + a.y.y * b.y.x,
			a.y.x * b.x.y + a.y.y * b.y.y));
}

}

#endif
