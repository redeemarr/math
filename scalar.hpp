#ifndef SCALAR_H
#define SCALAR_H

#if defined(min)
#undef min
#endif

#if defined(max)
#undef max
#endif

#include <math.h>

namespace xxx
{

typedef float scalar_t;

static const scalar_t pi = static_cast<scalar_t>(3.1415926535897932384626433832795);

inline scalar_t degrees(scalar_t rad)
{
	return rad * 180 / pi;
}

inline scalar_t radians(scalar_t deg)
{
	return deg * pi / 180;
}

inline scalar_t min(scalar_t a, scalar_t b)
{
	return a < b ? a : b;
}

inline scalar_t max(scalar_t a, scalar_t b)
{
	return a > b ? a : b;
}

inline float abs(float s)
{
	return fabsf(s);
}

inline double abs(double s)
{
	return fabs(s);
}

inline scalar_t clamp(scalar_t v, scalar_t minimum, scalar_t maximum)
{
	return min(max(v, minimum), maximum);
}

inline float sqrt(float s)
{
	return ::sqrtf(s);
}

inline double sqrt(double s)
{
	return ::sqrt(s);
}

inline float sin(float s)
{
	return ::sinf(s);
}

inline double sin(double s)
{
	return ::sin(s);
}

inline float asin(float s)
{
	return ::asinf(s);
}

inline double asin(double s)
{
	return ::asin(s);
}

inline float acos(float s)
{
	return ::acosf(s);
}

inline double acos(double s)
{
	return ::acos(s);
}

inline float cos(float s)
{
	return ::cosf(s);
}

inline double cos(double s)
{
	return ::cos(s);
}

inline void sincos(scalar_t v, scalar_t& s, scalar_t& c)
{
	s = sin(v);
	c = cos(v);
}

inline float atan(float v)
{
	return atanf(v);
}

inline double atan(double v)
{
	return atan(v);
}

inline float atan(float x, float y)
{
	return atan2f(x, y);
}

inline double atan(double x, double y)
{
	return atan2(x, y);
}

inline scalar_t mix(scalar_t a, scalar_t b, scalar_t t)
{
	return a + (b - a) * t;
}

inline scalar_t sign(scalar_t s)
{
	return s < 0 ? static_cast<scalar_t>(-1) : s > 0 ? static_cast<scalar_t>(1) : 0;
}

}

#endif
