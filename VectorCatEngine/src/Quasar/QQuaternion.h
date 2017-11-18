// Quasar Engine Demo
// Copyright (c) 2014 Duncan Little/Vector Kitten

// QQuaternion.h

// Quaternion struct for handling 3D rotations

// DualQuaternion struct for handling skinning transforms

#ifndef QQUATERNION_H
#define QQUATERNION_H

#include <math.h>
#include "QMaths.h"
//#include "QVector3.h"
//#include "QMatrix4.h"

namespace QE
{
	template<typename T>
	struct QuaternionT
	{
		typedef T type;

		T w, x, y, z;

		//--------------------------------------------------
		// Constructors
		inline QuaternionT()
		{
			w = 1;
			x = 0;
			y = 0;
			z = 0;
		}

		inline QuaternionT(const T &scalar, const Vector3T<T> &vec)
		{
			w = scalar;
			x = vec.x;
			y = vec.y;
			z = vec.z;
		}

		inline QuaternionT(const T &scalar, const T &i, const T &j, const T &k)
		{
			w = scalar;
			x = i;
			y = j;
			z = k;
		}

		inline QuaternionT(const QuaternionT &q)
		{
			w = q.w;
			x = q.x;
			y = q.y;
			z = q.z;
		}
		//---------------------------------------------------

		// Conjugate of Quaternion
		inline static QuaternionT Conjugate(const QuaternionT &q)
		{
			QuaternionT temp;
			temp.w = q.w;
			temp.x = -q.x;
			temp.y = -q.y;
			temp.z = -q.z;
			return temp;
		}

		// Magnitude of Quaternion
		inline T Magnitude(const QuaternionT &q)
		{
			QE::Vector3T<T> vec(q.x, q.y, q.z);
			T vecMag = vec.Magnitude(vec);
			T temp = sqrt((q.w * q.w) + (vecMag * vecMag));
			return temp;
		}

		// Normalize Quaternion
		inline QuaternionT Normalize()
		{
			T mag = Magnitude(*this);
			QuaternionT<T> qOut;
			qOut.w = w / mag;
			qOut.x = x / mag;
			qOut.y = y / mag;
			qOut.z = z / mag;
			return qOut;
		}

		// Inverse of Quaternion
		inline QuaternionT Inverse(const QuaternionT &q)
		{
			T mag = Magnitude(q);
			QuaternionT conj = Conjugate(q);

			QuaternionT temp;
			temp.w = conj.w / mag;
			temp.x = conj.x / mag;
			temp.y = conj.y / mag;
			temp.z = conj.z / mag;

			return temp;
		}

		// Quaternion multiplication using definition in 3D Math Primer for Graphics and Games Developement
		inline static QuaternionT Multiply(const QuaternionT &q1, const QuaternionT &q2)
		{
			QuaternionT temp;
			temp.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
			temp.x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
			temp.y = q1.w * q2.y + q1.y * q2.w + q1.z * q2.x - q1.x * q1.z;
			temp.z = q1.w * q2.z + q1.z * q2.w + q1.x * q2.y - q1.y * q2.x;
			return temp;
		}

		// Calculate difference between two quaternions
		inline QuaternionT Difference(const QuaternionT &q1, const QuaternionT &q2)
		{
			QuaternionT temp;
			temp = Multiply(Inverse(q1), q2);
			return temp;
		}

		// Quaternion dot product
		inline static T Dot(const QuaternionT &q1, const QuaternionT &q2)
		{
			T temp;
			temp = q1.w * q2.w + q1.x * q2.x + q1.y * q2.y + q1.z * q2.z;
			return temp;
		}

		// Create a rotation quaternion using an angle theta and a vector
		inline static QuaternionT CreateRotationFromAxisAngle(const T &theta, const Vector3T<T> &v)
		{
			Vector3T<T> axis = v.normalise();
			T alpha = theta * (T)0.5f;
			T sinAlpha = sin(alpha);
			QuaternionT q(cos(alpha), axis.x * sinAlpha, axis.y * sinAlpha, axis.z * sinAlpha);
			return q;
		}

		// Quaternion slerp (based on example in 3D Math Primer for Graphics and Game Development)
		inline QuaternionT Slerp(const QuaternionT &q1, QuaternionT &q2, const T &t)
		{
			T cosOmega = Dot(q1, q2);
			if(cosOmega < (T)0.0f)
			{
				q2.w = -q2.w;
				q2.x = -q2.x;
				q2.y = -q2.y;
				q2.z = -q2.z;
				cosOmega = -cosOmega;
			}

			T k1, k2;
			if(cosOmega < (T)0.9999f)
			{
				k1 = (T)1.0f - t;
				k2 = t;
			}
			else
			{
				T sinOmega = sqrt((T)1.0f - cosOmega * cosOmega);
				T Omega = atan2(sinOmega, cosOmega);
				T OneOverSinOmega = (T)1.0f / sinOmega;
				k1 = sin(((T)1.0f - t) * Omega) * OneOverSinOmega;
				k2 = sin(t * Omega) * OneOverSinOmega;
			}

			QuaternionT q;
			q.w = q1.w * k1 + q2.w * k2;
			q.x = q1.x * k1 + q2.x * k2;
			q.y = q1.y * k1 + q2.y * k2;
			q.z = q1.z * k1 + q2.z * k2;
			return q;
		}

		// Convert quaternion to rotation matrix
		inline QE::Matrix4T<T> QuaternionToMatrix()
		{
			QE::Matrix4T<T> RotationMatrix;
			RotationMatrix.m11 = (T)(1.0f - (2.0f * (y * y)) - (2.0f * (z * z)));
			RotationMatrix.m12 = (T)((2.0f * x * y) + (2.0f * w * z));
			RotationMatrix.m13 = (T)((2.0f * x * z) - (2.0f * w * y));
			RotationMatrix.m21 = (T)((2.0f * x * y) - (2.0f * w * z));
			RotationMatrix.m22 = (T)(1.0f - (2.0f * (x * x)) - (2.0f * (z * z)));
			RotationMatrix.m23 = (T)((2.0f * y * z) + (2.0f * w * x));
			RotationMatrix.m31 = (T)((2.0f * x * z) + (2.0f * w * y));
			RotationMatrix.m32 = (T)((2.0f * y * z) - (2.0f * w * x));
			RotationMatrix.m33 = (T)(1.0f - (2.0f * (x * x)) - (2.0f * (y * y)));

			return RotationMatrix;
		}

		// Convert quaternion to Euler angles
		inline QE::Vector3T<T> QuternionToEuler()
		{
			QE::Vector3T EulerAngles;

			T sp = (T)(-2.0f * (y * z + w * x));

			if(abs(sp) > (T)0.9999f)
			{
				EulerAngles.x = (T)((D3DXPI * 0.5f) * sp);
				EulerAngles.y = (T)(atan2(x * z - w * y, 0.5f - y * y - z * z));
				EulerAngles.z = (T)0.0f;
			}
			else
			{
				EulerAngles.x = (T)(asin(sp));
				EulerAngles.y = (T)(atan2(x * z - w * y, 0.5f - x * x - y * y));
				EulerAngles.z = (T)(atan2(x * y - w * z, 0.5f - x * x - z * z));
			}

			return EulerAngles;
		}

		// Create a quaternion from Euler angles
		inline static QuaternionT EulerToQuaternion(T thetaX, T thetaY, T thetaZ)
		{
			QuaternionT qY = CreateRotationFromAxisAngle(thetaY, QE::Vector3T<T>((T)0.0f, (T)1.0f, (T)0.0f));
			QuaternionT qX = CreateRotationFromAxisAngle(thetaX, QE::Vector3T<T>((T)1.0f, (T)0.0f, (T)0.0f));
			QuaternionT qZ = CreateRotationFromAxisAngle(thetaZ, QE::Vector3T<T>((T)0.0f, (T)0.0f, (T)1.0f));

			QuaternionT qOut = Multiply(qY, qX);
			qOut = Multiply(qOut, qZ);
			return qOut;
		}

		inline static QuaternionT EulerToQuaternion(T thetaX, T thetaY, T thetaZ, QE::Vector3T<T> axisX, QE::Vector3T<T> axisY, QE::Vector3T<T> axisZ)
		{
			QuaternionT qY = CreateRotationFromAxisAngle(thetaY, axisY);
			QuaternionT qX = CreateRotationFromAxisAngle(thetaX, axisX);
			QuaternionT qZ = CreateRotationFromAxisAngle(thetaZ, axisZ);

			QuaternionT qOut = Multiply(qY, qX);
			qOut = Multiply(qOut, qZ);
			return qOut;
		}

		inline QuaternionT operator*(T s)
		{
			QuaternionT<T> q;
			q.w = w * s;
			q.x = x * s;
			q.y = y * s;
			q.z = z * s;
			return q;
		}

		inline QuaternionT operator *(QuaternionT<T> q) const
		{
			QuaternionT qOut;
			qOut.w = w * q.w - x * q.x - y * q.y - z * q.z;
			qOut.x = w * q.x + x * q.w + y * q.z - z * q.y;
			qOut.y = w * q.y + y * q.w + z * q.x - x * q.z;
			qOut.z = w * q.z + z * q.w + x * q.y - y * q.x;
			return qOut;
		}

		inline void operator *=(T s)
		{
			w *= s;
			x *= s;
			y *= s;
			z *= s;
		}

		inline QuaternionT operator +(QuaternionT<T> q) const
		{
			QuaternionT<T> qOut;
			qOut.w = w + q.w;
			qOut.x = x + q.x;
			qOut.y = y + q.y;
			qOut.z = z + q.z;
			return qOut;
		}
	};

	typedef QuaternionT<float> Quaternionf;
	typedef QuaternionT<double> Quaterniond;

	template<typename T>
	struct DualQuaternionT
	{
		typedef T type;

		QuaternionT<T> qR; // the "real" component (rotation)
		QuaternionT<T> qD; // the "dual component (translation)

		DualQuaternionT()
		{
			qR.w = 1.0f;
			qR.x, qR.y, qR.z = 0.0f;
			qD.w, qD.x, qD.y, qD.z = 0.0f;
		}

		DualQuaternionT(const QuaternionT<T>& q, const QE::Vector3T<T>& v)
		{
			qR = QuaternionT<T>(q).Normalize();
			qD = (QuaternionT<T>(0.0f, v) * qR) * 0.5f;
		}

		DualQuaternionT(const DualQuaternionT<T>& dq)
		{
			qR.w = dq.qR.w;
			qR.x = dq.qR.x;
			qR.y = dq.qR.y;
			qR.z = dq.qR.z;

			qD.w = dq.qD.w;
			qD.x = dq.qD.x;
			qD.y = dq.qD.y;
			qD.z = dq.qD.z;
		}

		DualQuaternionT(const QuaternionT<T>& r, const QuaternionT<T>& d)
		{
			qR = r;
			qD = d;
		}

		inline DualQuaternionT operator *(T s) const
		{
			DualQuaternionT dq;
			dq.qR = qR * s;
			dq.qD = qD * s;
		}

		inline static float Dot(DualQuaternionT<T> dq1, DualQuaternionT<T> dq2)
		{
			return QuaternionT<T>::Dot(dq1.qR, dq2.qR);
		}

		inline DualQuaternionT Normalize()
		{
			DualQuaternionT<T> dqOut;

			T mag = QuaternionT<T>::Dot(qR, qR);
			if(mag > 0.0000001f)
			{
				dqOut.qR = qR * (1.0f / mag);
				dqOut.qD = qD * (1.0f / mag);
			}
			return dqOut;
		}

		inline DualQuaternionT operator +(DualQuaternionT<T> dq) const
		{
			DualQuaternionT<T> dqOut;
			dqOut.qR = qR + dq.qR;
			dqOut.qD = qD + dq.qD;
		}

		inline DualQuaternionT operator *(DualQuaternionT<T> dq) const
		{
			DualQuaternionT<T> dqOut = DualQuaternionT<T>(qR * dq.qR, (qD * dq.qR) + (qR * dq.qD));
			return dqOut;
		}

		inline DualQuaternionT Conjugate()
		{
			DualQuaternionT<T> dqOut = DualQuaternionT<T>(QuaternionT<T>::Conjugate(qR), QuaternionT<T>::Conjugate(qD));
			return dqOut;
		}

		inline QuaternionT<T> GetRotation()
		{
			return qR;
		}

		inline QE::Vector3T<T> GetTranslation()
		{
			QuaternionT<T> t = (qD * 2.0f) * QuaternionT<T>::Conjugate(qR);
			return QE::Vector3T<T>(t.x, t.y, t.z);
		}
	};

	typedef DualQuaternionT<float> DualQuaternionf;
	typedef DualQuaternionT<double> DualQuaterniond;
}

#endif