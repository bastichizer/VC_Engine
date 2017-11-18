// Quasar Engine Demo
// Copyright (c) 2014 Duncan Little/Vector Kitten

// QVector3.h

// A collection of custom 2D Vector functions

#ifndef QVECTOR2_H
#define QVECTOR2_H

#include <math.h>
#include "QMaths.h"

namespace QE
{
	// Vector2 struct, a two dimensional vector
	template<typename T>
	struct Vector2T
	{
		typedef T type;
		T x;
		T y;

		inline Vector2T(): x(0), y(0)
		{
		}

		inline Vector2T(const Vector2T &c): x(c.x), y(c.y)
		{
		}

		explicit inline Vector2T(T xy): x(xy), y(xy)
		{
		}

		template<typename T2>
		explicit inline Vector2T(const T2 *p): x(T(p[0])), y(T(p[1]))
		{
		}

		inline Vector2T(T xx, T yy): x(xx), y(yy)
		{
		}

		inline T& operator [] (unsigned int n) const
		{
			return *(&x + n);
		}

		inline Vector2T operator *= (T n)
		{
			x *= n;
			y *= n;
			return *this;
		}

		inline Vector2T operator /= (T n)
		{
			x /= n;
			y /= n;
			return *this;
		}

		inline Vector2T operator += (const Vector2T &n)
		{
			x += n.x;
			y += n.y;
			return *this;
		}

		inline Vector2T operator -= (const Vector2T &n)
		{
			x -= n.x;
			y -= n.y;
			return *this;
		}

		inline Vector2T operator *= (const Vector2T &n)
		{
			x *= n.x;
			y *= n.y;
			return *this;
		}

		inline Vector2T operator /= (const Vector2T &n)
		{
			x /= n.x;
			y /= n.y;
			return * this;
		}

		inline Vector2T operator = (const T *n)
		{
			x = n[0];
			y = n[1];
			return *this;
		}

		inline Vector2T operator = (const Vector2T<T> &n)
		{
			x = n.x;
			y = n.y;
			return *this;
		}

		inline T Magnitude() const
		{
			T temp = sqrt(x * x + y * y);
			return temp;
		}

		inline static T Magnitude(const Vector2T &v) //const
		{
			T temp = sqrt(v.x * v.x + v.y * v.y);
			return temp;
		}

		inline Vector2T Normalise() const
		{
			T magnitude;
			Vector2T temp;
			magnitude = sqrt(x * x + y * y);
			temp.x = x / magnitude;
			temp.y = y / magnitude;
			return temp;
		}

		inline static T dot(const Vector2T &v1, const Vector2T &v2) //const
		{
			T dotprod = v1.x * v2.x + v1.y * v2.y;
			return dotprod;
		}

		inline static T VecAngle(const Vector2T & v1, const Vector2T &v2) //const
		{
			T angle = acos(dot(v1, v2) / (v1.Magnitude() * v2.Magnitude()));
			return angle;
		}
	};

	typedef Vector2T<float> Vector2f;
	typedef Vector2T<double> Vector2d;
}

#endif