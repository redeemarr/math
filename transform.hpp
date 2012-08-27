#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "vec3.h"
#include "quaternion.h"
#include "mat4.h"

namespace xxx
{

struct transform
{
	vec3       position;
	quaternion rotation;

	transform()
	{
		position = vec3(0, 0, 0);
		rotation = quaternion::identity();
	}

	explicit transform(vec3 const& v, quaternion const& q)
	{
		position = v;
		rotation = q;
	}

	mat4 model_matrix() const
	{
		return mat4(rotation.to_matrix(), vec4(position, 1));
	}

	mat4 view_matrix() const
	{
		mat4 p = mat4::identity();
		p.w.x = -position.x;
		p.w.y = -position.y;
		p.w.z = -position.z;
		mat4 r = mat4(rotation.to_matrix(), vec4(0, 0, 0, 1));
		return p * r;
	}
};

inline transform inverse(transform const& t)
{
	quaternion q = inverse(t.rotation);
	return transform(rotate(inverse(t.position), q), q);
}

inline vec3 operator * (transform const& t, vec3 const& v)
{
	return rotate(v, t.rotation) + t.position;
}

inline transform operator * (transform const& a, transform const& b)
{
	return transform(b * a.position, a.rotation * b.rotation);
}

}

#endif
