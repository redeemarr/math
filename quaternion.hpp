#ifndef QUATERNION_H
#define QUATERNION_H

#include "mat3.h"

namespace xxx
{

struct quaternion;

quaternion operator * (quaternion const& a, quaternion const& b);
quaternion normalize(quaternion const& q);

struct quaternion
{
	scalar_t x, y, z, w;

	quaternion() {}
	explicit quaternion(scalar_t x, scalar_t y, scalar_t z, scalar_t w) : x(x), y(y), z(z), w(w) {}
	explicit quaternion(vec3 const& v, scalar_t s) : x(v.x), y(v.y), z(v.z), w(s) {}

	quaternion& operator *= (quaternion const& q)
	{
		return *this = *this * q;
	}

	vec3 vector() const
	{
		return vec3(x, y, z);
	}

	scalar_t norm() const
	{
		return sqrt(x * x + y * y + z * z + w * w);
	}

	static quaternion identity()
	{
		return quaternion(0, 0, 0, 1);
	}

	static quaternion from_euler_angles(scalar_t x, scalar_t y, scalar_t z)
	{
		scalar_t cx, cy, cz, sx, sy, sz;
		sincos(x * static_cast<scalar_t>(0.5), sx, cx);
		sincos(y * static_cast<scalar_t>(0.5), sy, cy);
		sincos(z * static_cast<scalar_t>(0.5), sz, cz);
		return quaternion(
			cz * sy * cx + sz * cy * sx,
			cz * cy * sx - sz * sy * cx,
			sz * cy * cx - cz * sy * sx,
			cz * cy * cx + sz * sy * sx);
	}

	static quaternion from_axis_angle(vec3 const& axis, scalar_t angle)
	{
		scalar_t len = length(axis);
		if (len == 0)
		{
			return quaternion::identity();
		}
		else
		{
			scalar_t s, c;
			sincos(angle * static_cast<scalar_t>(0.5), s, c);
			return quaternion(axis.x * s, axis.y * s, axis.z * s, c);
		}
	}

	static quaternion from_shortest_arc(vec3 const& a, vec3 const& b)
	{
		vec3 c = cross(a, b);
		quaternion q(c.x, c.y, c.z, dot(a, b));
		q = normalize(q);
		q.w += 1;
		q = normalize(q);
		return q;
	}

	mat3 to_matrix() const
	{
		mat3 m;

		scalar_t wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;
		scalar_t s = 2 / norm();

		x2 = x * s;    y2 = y * s;    z2 = z * s;
		xx = x * x2;   xy = x * y2;   xz = x * z2;
		yy = y * y2;   yz = y * z2;   zz = z * z2;
		wx = w * x2;   wy = w * y2;   wz = w * z2;

		m.x.x = 1 - (yy + zz);
		m.y.x = xy - wz;
		m.z.x = xz + wy;

		m.x.y = xy + wz;
		m.y.y = 1 - (xx + zz);
		m.z.y = yz - wx;

		m.x.z = xz - wy;
		m.y.z = yz + wx;
		m.z.z = 1 - (xx + yy);

		return m;
	}
};

inline quaternion operator * (quaternion const& a, quaternion const& b)
{
	return quaternion(
		a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
		a.w * b.y + a.y * b.w + a.z * b.x - a.x * b.z,
		a.w * b.z + a.z * b.w + a.x * b.y - a.y * b.x,
		a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z);
}

inline quaternion normalize(quaternion const& q)
{
	scalar_t n = q.norm();
	scalar_t in = n == 0 ? 1 : 1 / n;
	return quaternion(q.x * in, q.y * in, q.z * in, q.w * in);
}

inline quaternion conjugate(quaternion const& q)
{
	return quaternion(-q.x, -q.y, -q.z, q.w);
}

inline quaternion inverse(quaternion const& q)
{
	quaternion r = conjugate(q);
	scalar_t in = 1 / q.norm();
	return quaternion(r.x * in, r.y * in, r.z * in, r.w * in);
}

inline vec3 rotate(vec3 const& v, quaternion const& q)
{
	return ((q * quaternion(v, 0.0)) * conjugate(q)).vector();
}

inline quaternion slerp(quaternion const& a, quaternion const& b, scalar_t t)
{
	scalar_t const epsilon = static_cast<scalar_t>(1.0e-8);

	scalar_t cosine = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	scalar_t sine = 1 - cosine * cosine;

	scalar_t sign;
	if (cosine < 0)
	{
		cosine = -cosine;
		sign = -1;
	}
	else
	{
		sign = 1;
	}

	if (sine >= epsilon * epsilon)
	{
		sine = sqrt(sine);

		scalar_t const angle = atan(sine, cosine);
		scalar_t const i_sin_angle = 1 / sine;

		scalar_t lower_weight = sin(angle * (1 - t)) * i_sin_angle;
		scalar_t upper_weight = sin(angle * t) * i_sin_angle * sign;

		return quaternion(
			a.x * lower_weight + b.x * upper_weight,
			a.y * lower_weight + b.y * upper_weight,
			a.z * lower_weight + b.z * upper_weight,
			a.w * lower_weight + b.w * upper_weight);
	}
	else
	{
		return a;
	}
}

}

#endif
