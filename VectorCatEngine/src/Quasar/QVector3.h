// Quasar Engine Demo
// Copyright (c) 2014 Duncan Little/Vector Kitten

// QVector3.h

// A collection of custom 3D Vector functions

#ifndef QVECTOR3_H
#define QVECTOR3_H

#include <math.h>
#include "QMaths.h"
//#include "QMatrix4.h"
//#include "QQuaternion.h"

namespace QE
{
	// Forward declarations
	template<typename T>
	struct Matrix4T;

	template<typename T>
	struct QuaternionT;

	template<typename T>

	// Vector3 struct, a three dimensional vector
	struct Vector3T
	{
		typedef T type;
		T x;
		T y;
		T z;

		inline Vector3T(): x(0), y(0), z(0)
		{
		}

		inline Vector3T(const Vector3T &c): x(c.x), y(c.y), z(c.z)
		{
		}

		explicit inline Vector3T(T xyz): x(xyz), y(xyz), z(xyz)
		{
		}

		template<typename T2>
		explicit inline Vector3T(const T2 *p): x(T(p[0])),y(T(p[1])),z(T(p[2]))
		{
		}

		inline Vector3T(T xx, T yy, T zz): x(xx), y(yy), z(zz)
		{
		}

		inline T operator [] (unsigned int n) const
		{
			return *(&x + n);
		}

		inline T& operator [] (unsigned int n) 
		{
			return *(&x + n);
		}

		inline Vector3T operator *= (T n)
		{
			x *= n;
			y *= n;
			z *= n;
			return *this;
		}

		inline Vector3T operator /= (T n)
		{
			x /= n;
			y /= n;
			z /= n;
			return *this;
		}

		inline Vector3T operator += (const Vector3T &n)
		{
			x += n.x;
			y += n.y;
			z += n.z;
			return *this;
		}

		inline Vector3T operator -= (const Vector3T &n)
		{
			x -= n.x;
			y -= n.y;
			z -= n.z;
			return *this;
		}

		inline Vector3T operator *= (const Vector3T &n)
		{
			x *= n.x;
			y *= n.y;
			z *= n.z;
			return *this;
		}

		inline Vector3T operator /= (const Vector3T &n)
		{
			x /= n.x;
			y /= n.y;
			z /= n.z;
			return *this;
		}

		inline Vector3T operator = (const T *n)
		{
			x = n[0];
			y = n[1];
			z = n[2];
			return *this;
		}

		inline Vector3T operator = (const Vector3T<T> &n)
		{
			x = n.x;
			y = n.y;
			z = n.z;
			return *this;
		}

		inline Vector3T operator - (const Vector3T &v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
			return *this;
		}
		inline Vector3T operator + (const Vector3T &v)
		{
			x += v.x;
			y += v.y;
			z += v.z;
			return *this;
		}

		inline Vector3T operator * (const T &n)
		{
			x *= n;
			y *= n;
			z *= n;
			return *this;
		}

		inline T Magnitude() const
		{
			T temp = sqrt(x * x + y * y + z * z);
			return temp;
		}

		inline T Magnitude(const Vector3T &v) const
		{
			T temp = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
			return temp;
		}

		inline Vector3T normalise() const
		{
			T magnitude;
			Vector3T temp;
			magnitude = sqrt(x * x + y * y + z * z);
			temp.x = x / magnitude;
			temp.y = y / magnitude;
			temp.z = z / magnitude;
			return temp;
		}

		inline T dot(const Vector3T &v) const
		{
			T dotprod = x * v.x + y * v.y + z * v.z;
			return dotprod;
		}

		inline T dot(const Vector3T &v1, const Vector3T &v2) const
		{
			T dotprod = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
			return dotprod;
		}

		inline T VecAngle(const Vector3T &v) const
		{
			T angle = acos(dot(v) / (Magnitude() *v.Magnitude()));
		}

		inline T VecAngle(const Vector3T &v1, const Vector3T &v2) const
		{
			T angle = acos(dot(v1, v2) / (v1.Magnitude() * v2.Magnitude()));
			return angle;
		}

		inline Vector3T cross(const Vector3T &v) const
		{
			Vector3T crossprod;
			crossprod.x = y * v.z - v.y * z;
			crossprod.y = z * v.x - v.z * x;
			crossprod.z = x * v.y - v.x * y;
			return crossprod;
		}

		inline Vector3T cross(const Vector3T &v1, const Vector3T &v2) const
		{
			Vector3T crossprod;
			crossprod.x = v1.y * v2.z - v2.y * v1.z;
			crossprod.y = v1.z * v2.x - v2.z * v1.x;
			crossprod.z = v1.x * v2.y - v2.x * v1.y;
			return crossprod;
		}

		//inline D3DXVECTOR3 D3DXConvert()
		//{
		//	D3DXVECTOR3 temp;
		//	temp.x = x;
		//	temp.y = y;
		//	temp.z = z;
		//	return temp;
		//}

		// Convert a vector of Euler angles to a rotation matrix
		inline QE::Matrix4T<T> EulerToMatrix()
		{
			QE::Matrix4T<T> RotationMatrix;
			QE::Matrix4T<T> Heading;
			Heading = Heading.RotateY(-y, Heading);
			QE::Matrix4T<T> Pitch;
			Pitch = Pitch.RotateX(-x, Pitch);
			QE::Matrix4T<T> Bank;
			Bank = Bank.RotateZ(-z, Bank);
			RotationMatrix = RotationMatrix.Multiply(Heading, Pitch);
			RotationMatrix = RotationMatrix.Multiply(RotationMatrix, Bank);
			return RotationMatrix;
		}

		// Convert a vector of Euler angles to a quaternion
		inline QE::QuaternionT<T> EulerToQuaternion()
		{
			QE::QuaternionT<T> q;
			q.w = (T)((cos(y * 0.5f) * cos(x * 0.5f) * cos(z * 0.5f)) + (sin(y * 0.5f) * sin(x * 0.5f) * sin(z * 0.5f)));
			q.x = (T)((-cos(y * 0.5f) * sin(x * 0.5f) * cos(z * 0.5f)) - (sin(y * 0.5f) * cos(x * 0.5f) * sin(z * 0.5f)));
			q.y = (T)((cos(y * 0.5f) * sin(x * 0.5f) * sin(z * 0.5f)) - (sin(y * 0.5f) * cos(x * 0.5f) * cos(z * 0.5f)));
			q.z = (T)((sin(y * 0.5f) * sin(x * 0.5f) * cos(z * 0.5f)) - (cos(y * 0.5f) * cos(x * 0.5f) * sin(z * 0.5f)));
			return q;
		}
	};

	typedef Vector3T<float> Vector3f;
	typedef Vector3T<double> Vector3d;
}

#endif