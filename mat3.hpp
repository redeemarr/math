#ifndef MAT3_H
#define MAT3_H

#include "vec3.h"
#include "mat2.h"

namespace xxx
{

struct mat3
{
	vec3 x, y, z;

	mat3() {}
	explicit mat3(vec3 const& x, vec3 const& y, vec3 const& z) : x(x), y(y), z(z) {}
	explicit mat3(mat2 const& m, vec3 const& z) : x(m.x, 0), y(m.y, 0), z(z) {}

	scalar_t determinant() const
	{
		return
			x.x * (y.y * z.z - y.z * z.y) -
			x.y * (y.x * z.z - y.z * z.x) +
			x.z * (y.x * z.y - y.y * z.x);
	}

	static mat3 identity()
	{
		return mat3(vec3(1, 0, 0), vec3(0, 1, 0), vec3(0, 0, 1));
	}

	static mat3 from_axis_angle(vec3 const& axis, scalar_t angle)
	{
		scalar_t const xy = axis.x * axis.y;
		scalar_t const xz = axis.x * axis.z;
		scalar_t const yz = axis.y * axis.z;

		scalar_t s, c;
		sincos(angle, s, c);
		c = 1 - c;

		return mat3(
			vec3(
				1 + c * (axis.x * axis.x - 1),
				-axis.z * s + c * xy,
				axis.y * s + c * xz),
			vec3(
				axis.z * s + c * xy,
				1 + c * (axis.y * axis.y - 1),
				-axis.x * s + c * yz),
			vec3(
				-axis.y * s + c * xz,
				axis.x * s + c * yz,
				1 + c * (axis.z * axis.z - 1)));
	}

	static mat3 from_euler_angles(scalar_t x, scalar_t y, scalar_t z)
	{
		scalar_t cx, sx, cy, sy, cz, sz;
		sincos(x, sx, cx);
		sincos(y, sy, cy);
		sincos(z, sz, cz);
		return mat3(
			vec3(cy * cz, sy * sx - cy * sz * cx, cy * sz * sx + sy * cx),
			vec3(sz, cz * cx, -cz * sx),
			vec3(-sy * cz, sy * sz * cx + cy * sx, cy * cx - sy * sz * sx));
	}
};

inline mat3 transpose(mat3 const& m)
{
	return mat3(
		vec3(m.x.x, m.y.x, m.z.x),
		vec3(m.x.y, m.y.y, m.z.y),
		vec3(m.x.z, m.y.z, m.z.z));
}

inline mat3 inverse(mat3 const& m)
{
	scalar_t const d = 1 / m.determinant();
	if (d != 0)
	{
		scalar_t const id = 1 / d;
		return mat3(
			vec3(
				 id * (m.y.y * m.z.z - m.y.z * m.z.y),
				-id * (m.x.y * m.z.z - m.x.z * m.z.y),
				 id * (m.x.y * m.y.z - m.x.z * m.y.y)),

			 vec3(
				-id * (m.y.x * m.z.z - m.y.z * m.z.x),
				 id * (m.x.x * m.z.z - m.x.z * m.z.x),
				-id * (m.x.x * m.y.z - m.x.z * m.y.x)),

			vec3(
				 id * (m.y.x * m.z.y - m.y.y * m.z.x),
				-id * (m.x.x * m.z.y - m.x.y * m.z.x),
				 id * (m.x.x * m.y.y - m.x.y * m.y.x)));
	}
	else
	{
		return mat3::identity();
	}
}

inline vec3 operator * (mat3 const& m, vec3 const& v)
{
	return vec3(
		v.x * m.x.x + v.y * m.y.x + v.z * m.z.x,
		v.x * m.x.y + v.y * m.y.y + v.z * m.z.y,
		v.x * m.x.z + v.y * m.y.z + v.z * m.z.z);
}

inline mat3 operator * (mat3 const& a, mat3 const& b)
{
	return mat3(
		vec3(
		a.x.x * b.x.x + a.x.y * b.y.x + a.x.z * b.z.x,
		a.x.x * b.x.y + a.x.y * b.y.y + a.x.z * b.z.y,
		a.x.x * b.x.z + a.x.y * b.y.z + a.x.z * b.z.z),
		vec3(
		a.y.x * b.x.x + a.y.y * b.y.x + a.y.z * b.z.x,
		a.y.x * b.x.y + a.y.y * b.y.y + a.y.z * b.z.y,
		a.y.x * b.x.z + a.y.y * b.y.z + a.y.z * b.z.z),
		vec3(
		a.z.x * b.x.x + a.z.y * b.y.x + a.z.z * b.z.x,
		a.z.x * b.x.y + a.z.y * b.y.y + a.z.z * b.z.y,
		a.z.x * b.x.z + a.z.y * b.y.z + a.z.z * b.z.z));
}

}

#endif
