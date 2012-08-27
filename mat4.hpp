#ifndef MAT4_H
#define MAT4_H

#include "vec4.h"
#include "mat3.h"

namespace xxx
{

struct mat4;

mat4 operator * (mat4 const& a, mat4 const& b);

struct mat4
{
	vec4 x, y, z, w;

	mat4() {}
	explicit mat4(vec4 const& x, vec4 const& y, vec4 const& z, vec4 const& w) : x(x), y(y), z(z), w(w) {}
	explicit mat4(mat3 const& m, vec4 const& w) : x(m.x, 0), y(m.y, 0), z(m.z, 0), w(w) {}

	mat3 to_mat3() const
	{
		return mat3(x.to_vec3(), y.to_vec3(), z.to_vec3());
	}

	static mat4 identity()
	{
		return mat4(vec4(1, 0, 0, 0), vec4(0, 1, 0, 0), vec4(0, 0, 1, 0), vec4(0, 0, 0, 1));
	}

	static mat4 frustum(float left, float right, float bottom, float top, float znear, float zfar)
	{
		scalar_t const a = 2 * znear;
		scalar_t const b = right - left;
		scalar_t const c = top - bottom;
		scalar_t const d = zfar - znear;
		return mat4(
			vec4(a / b, 0, 0, 0),
			vec4(0, a / c, 0, 0),
			vec4((right + left) / b, (top + bottom) / c, (-zfar - znear) / d, -1),
			vec4(0, 0, (-a * zfar) / d, 0));
	}

	static mat4 ortho(scalar_t width, scalar_t height, scalar_t znear, scalar_t zfar)
	{
		return mat4(
			vec4(2 / width, 0, 0, -1),
			vec4(0, 2 / height, 0, -1),
			vec4(0, 0, -2 / (zfar - znear), -(zfar + znear) / (zfar - znear)),
			vec4(0, 0, 0, -1));
	}

	static mat4 perspective(scalar_t width, scalar_t height, scalar_t fov_radians, scalar_t znear, scalar_t zfar)
	{
		scalar_t const ymax = znear * tan(fov_radians / 2);
		scalar_t const xmax = ymax * (width / height);
		return frustum(-xmax, xmax, -ymax, ymax, znear, zfar);
	}

	static mat4 look_at(vec3 const& eye, vec3 const& target, vec3 const& up)
	{
		// TODO: clean up
		vec3 const z = normalize(eye - target);
		vec3 const x = normalize(cross(up, z));
		vec3 const y = normalize(cross(z, x));

		mat4 r = mat4(vec4(x.x, y.x, z.x, 0), vec4(x.y, y.y, z.y, 0), vec4(x.z, y.z, z.z, 0), vec4(0,0,0,1));
		mat4 t = mat4(vec4(1,0,0,0), vec4(0,1,0,0), vec4(0,0,1,0), vec4(eye * -1,1));

		return t * r;
	}
};

inline mat4 transpose(mat4 const& m)
{
	return mat4(
		vec4(m.x.x, m.y.x, m.z.x, m.w.x),
		vec4(m.x.y, m.y.y, m.z.y, m.w.y),
		vec4(m.x.z, m.y.z, m.z.z, m.w.z),
		vec4(m.x.w, m.y.w, m.z.w, m.w.w));
}

inline mat4 inverse(mat4 const& m)
{
	mat4 r;
	mat4 t = transpose(m);

	{
		scalar_t k[12] =
		{
			t.z.z * t.w.w,
			t.z.w * t.w.z,
			t.z.y * t.w.w,
			t.z.w * t.w.y,
			t.z.y * t.w.z,
			t.z.z * t.w.y,
			t.z.x * t.w.w,
			t.z.w * t.w.x,
			t.z.x * t.w.z,
			t.z.z * t.w.x,
			t.z.x * t.w.y,
			t.z.y * t.w.x
		};

		r.x.x = (k[0] * t.y.y + k[3] * t.y.z + k[4]  * t.y.w) - (k[1] * t.y.y + k[2] * t.y.z + k[5]  * t.y.w);
		r.x.y = (k[1] * t.y.x + k[6] * t.y.z + k[9]  * t.y.w) - (k[0] * t.y.x + k[7] * t.y.z + k[8]  * t.y.w);
		r.x.z = (k[2] * t.y.x + k[7] * t.y.y + k[10] * t.y.w) - (k[3] * t.y.x + k[6] * t.y.y + k[11] * t.y.w);
		r.x.w = (k[5] * t.y.x + k[8] * t.y.y + k[11] * t.y.z) - (k[4] * t.y.x + k[9] * t.y.y + k[10] * t.y.z);

		r.y.x = (k[1] * t.x.y + k[2] * t.x.z + k[5]  * t.x.w) - (k[0] * t.x.y + k[3] * t.x.z + k[4]  * t.x.w);
		r.y.y = (k[0] * t.x.x + k[7] * t.x.z + k[8]  * t.x.w) - (k[1] * t.x.x + k[6] * t.x.z + k[9]  * t.x.w);
		r.y.z = (k[3] * t.x.x + k[6] * t.x.y + k[11] * t.x.w) - (k[2] * t.x.x + k[7] * t.x.y + k[10] * t.x.w);
		r.y.w = (k[4] * t.x.x + k[9] * t.x.y + k[10] * t.x.z) - (k[5] * t.x.x + k[8] * t.x.y + k[11] * t.x.z);
	}
	{
		scalar_t k[12] =
		{
			t.x.z * t.y.w,
			t.x.w * t.y.z,
			t.x.y * t.y.w,
			t.x.w * t.y.y,
			t.x.y * t.y.z,
			t.x.z * t.y.y,
			t.x.x * t.y.w,
			t.x.w * t.y.x,
			t.x.x * t.y.z,
			t.x.z * t.y.x,
			t.x.x * t.y.y,
			t.x.y * t.y.x
		};

		r.z.x = (k[0] * t.w.y  + k[3]  * t.w.z + k[4] * t.w.w)  - (k[1]  * t.w.y + k[2]  * t.w.z + k[5]  * t.w.w);
		r.z.y = (k[1] * t.w.x  + k[6]  * t.w.z + k[9] * t.w.w)  - (k[0]  * t.w.x + k[7]  * t.w.z + k[8]  * t.w.w);
		r.z.z = (k[2] * t.w.x  + k[7]  * t.w.y + k[10] * t.w.w) - (k[3]  * t.w.x + k[6]  * t.w.y + k[11] * t.w.w);
		r.z.w = (k[5] * t.w.x  + k[8]  * t.w.y + k[11] * t.w.z) - (k[4]  * t.w.x + k[9]  * t.w.y + k[10] * t.w.z);

		r.w.x = (k[2] * t.z.z  + k[5]  * t.z.w + k[1] * t.z.y)  - (k[4]  * t.z.w + k[0]  * t.z.y + k[3]  * t.z.z);
		r.w.y = (k[8] * t.z.w  + k[0]  * t.z.x + k[7] * t.z.z)  - (k[6]  * t.z.z + k[9]  * t.z.w + k[1]  * t.z.x);
		r.w.z = (k[6] * t.z.y  + k[11] * t.z.w + k[3] * t.z.x)  - (k[10] * t.z.w + k[2]  * t.z.x + k[7]  * t.z.y);
		r.w.w = (k[10] * t.z.z + k[4]  * t.z.x + k[9] * t.z.y)  - (k[8]  * t.z.y + k[11] * t.z.z + k[5]  * t.z.x);
	}

	scalar_t const d = t.x.x * r.x.x + t.x.y * r.x.y + t.x.z * r.x.z + t.x.w * r.x.w;
	if (d != 0)
	{
		scalar_t const id = 1 / d;
		t.x *= id;
		t.y *= id;
		t.z *= id;
		t.w *= id;
		return r;
	}
	else
	{
		return mat4::identity();
	}
}

inline vec4 operator * (mat4 const& m, vec4 const& v)
{
	return vec4(
		v.x * m.x.x + v.y * m.y.x + v.z * m.z.x + v.w * m.w.x,
		v.x * m.x.y + v.y * m.y.y + v.z * m.z.y + v.w * m.w.y,
		v.x * m.x.z + v.y * m.y.z + v.z * m.z.z + v.w * m.w.z,
		v.x * m.x.w + v.y * m.y.w + v.z * m.z.w + v.w * m.w.w);
}

inline mat4 operator * (mat4 const& a, mat4 const& b)
{
	return mat4(
		vec4(
			a.x.x * b.x.x + a.x.y * b.y.x + a.x.z * b.z.x + a.x.w * b.w.x,
			a.x.x * b.x.y + a.x.y * b.y.y + a.x.z * b.z.y + a.x.w * b.w.y,
			a.x.x * b.x.z + a.x.y * b.y.z + a.x.z * b.z.z + a.x.w * b.w.z,
			a.x.x * b.x.w + a.x.y * b.y.w + a.x.z * b.z.w + a.x.w * b.w.w),
		vec4(
			a.y.x * b.x.x + a.y.y * b.y.x + a.y.z * b.z.x + a.y.w * b.w.x,
			a.y.x * b.x.y + a.y.y * b.y.y + a.y.z * b.z.y + a.y.w * b.w.y,
			a.y.x * b.x.z + a.y.y * b.y.z + a.y.z * b.z.z + a.y.w * b.w.z,
			a.y.x * b.x.w + a.y.y * b.y.w + a.y.z * b.z.w + a.y.w * b.w.w),
		vec4(
			a.z.x * b.x.x + a.z.y * b.y.x + a.z.z * b.z.x + a.z.w * b.w.x,
			a.z.x * b.x.y + a.z.y * b.y.y + a.z.z * b.z.y + a.z.w * b.w.y,
			a.z.x * b.x.z + a.z.y * b.y.z + a.z.z * b.z.z + a.z.w * b.w.z,
			a.z.x * b.x.w + a.z.y * b.y.w + a.z.z * b.z.w + a.z.w * b.w.w),
		vec4(
			a.w.x * b.x.x + a.w.y * b.y.x + a.w.z * b.z.x + a.w.w * b.w.x,
			a.w.x * b.x.y + a.w.y * b.y.y + a.w.z * b.z.y + a.w.w * b.w.y,
			a.w.x * b.x.z + a.w.y * b.y.z + a.w.z * b.z.z + a.w.w * b.w.z,
			a.w.x * b.x.w + a.w.y * b.y.w + a.w.z * b.z.w + a.w.w * b.w.w));
}

}

#endif
