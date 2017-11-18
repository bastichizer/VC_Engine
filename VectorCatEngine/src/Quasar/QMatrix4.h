// Quasar Engine Demo
// Copyright (c) 2014 Duncan Little/Vector Kitten

// QMatrix4.h

// 4x4 matrix struct and functions

#ifndef QMATRIX4_H
#define QMATRIX4_H

#include <math.h>
//#include <d3dx9.h>
#pragma warning( default : 4996 )
#include "QMaths.h"
//#include "QVector3.h"
//#include "QQuaternion.h"

namespace QE
{
	// Forward declarations
	template<typename T>
	struct QuaternionT;

	template<typename T>

	// Matrix4T struct
	struct Matrix4T
	{
		typedef T type;
		
		T m11, m12, m13, m14;
		T m21, m22, m23, m24;
		T m31, m32, m33, m34;
		T m41, m42, m43, m44;

		// Constructor initializes matrix to identity
		inline Matrix4T(): m11(1), m12(0), m13(0), m14(0),
							m21(0), m22(1), m23(0), m24(0),
							m31(0), m32(0), m33(1), m34(0),
							m41(0), m42(0), m43(0), m44(1)
		{
		}

		inline Matrix4T(const Matrix4T &m): m11(m.m11), m12(m.m12), m13(m.m13), m14(m.m14),
											  m21(m.m21), m22(m.m22), m23(m.m23), m24(m.m24),
											  m31(m.m31), m32(m.m32), m33(m.m33), m34(m.m34),
											  m41(m.m41), m42(m.m42), m43(m.m43), m44(m.m44)
		{
		}

		// Multiply two matrices
		inline static Matrix4T Multiply(const Matrix4T &m1, const Matrix4T &m2)
		{
			Matrix4T temp;
			temp.m11 = m1.m11 * m2.m11 + m1.m12 * m2.m21 + m1.m13 * m2.m31 + m1.m14 * m2.m41;
			temp.m12 = m1.m11 * m2.m12 + m1.m12 * m2.m22 + m1.m13 * m2.m32 + m1.m14 * m2.m42;
			temp.m13 = m1.m11 * m2.m13 + m1.m12 * m2.m23 + m1.m13 * m2.m33 + m1.m14 * m2.m43;
			temp.m14 = m1.m11 * m2.m14 + m1.m12 * m2.m24 + m1.m13 * m2.m34 + m1.m14 * m2.m44;
			temp.m21 = m1.m21 * m2.m11 + m1.m22 * m2.m21 + m1.m23 * m2.m31 + m1.m24 * m2.m41;
			temp.m22 = m1.m21 * m2.m12 + m1.m22 * m2.m22 + m1.m23 * m2.m32 + m1.m24 * m2.m42;
			temp.m23 = m1.m21 * m2.m13 + m1.m22 * m2.m23 + m1.m23 * m2.m33 + m1.m24 * m2.m43;
			temp.m24 = m1.m21 * m2.m14 + m1.m22 * m2.m24 + m1.m23 * m2.m34 + m1.m24 * m2.m44;
			temp.m31 = m1.m31 * m2.m11 + m1.m32 * m2.m21 + m1.m33 * m2.m31 + m1.m34 * m2.m41;
			temp.m32 = m1.m31 * m2.m12 + m1.m32 * m2.m22 + m1.m33 * m2.m32 + m1.m34 * m2.m42;
			temp.m33 = m1.m31 * m2.m13 + m1.m32 * m2.m23 + m1.m33 * m2.m33 + m1.m34 * m2.m43;
			temp.m34 = m1.m31 * m2.m14 + m1.m32 * m2.m24 + m1.m33 * m2.m34 + m1.m34 * m2.m44;
			temp.m41 = m1.m41 * m2.m11 + m1.m42 * m2.m21 + m1.m43 * m2.m31 + m1.m44 * m2.m41;
			temp.m42 = m1.m41 * m2.m12 + m1.m42 * m2.m22 + m1.m43 * m2.m32 + m1.m44 * m2.m42;
			temp.m43 = m1.m41 * m2.m13 + m1.m42 * m2.m23 + m1.m43 * m2.m33 + m1.m44 * m2.m43;
			temp.m44 = m1.m41 * m2.m14 + m1.m42 * m2.m24 + m1.m43 * m2.m34 + m1.m44 * m2.m44;
			return temp;
		}

		// Translation matrix
		inline static Matrix4T Translate(const Vector3T<T> &v, const Matrix4T &m)
		{
			Matrix4T matTrans;
			matTrans.m41 = (T)v.x;
			matTrans.m42 = (T)v.y;
			matTrans.m43 = (T)v.z;
			
			Matrix4T temp = Multiply(m, matTrans);
			return temp;
		}

		// Euler rotation around X axis
		inline Matrix4T RotateX(const T &theta, const Matrix4T &m)
		{
			Matrix4T Xrot;
			Xrot.m11 = 1.0f; Xrot.m12 = 0.0f;		 Xrot.m13 = 0.0f;	    Xrot.m14 = 0.0f;
			Xrot.m21 = 0.0f; Xrot.m22 = cos(theta);  Xrot.m23 = sin(theta); Xrot.m24 = 0.0f;
			Xrot.m31 = 0.0f; Xrot.m32 = -sin(theta); Xrot.m33 = cos(theta); Xrot.m34 = 0.0f;
			Xrot.m41 = 0.0f; Xrot.m42 = 0.0f;		 Xrot.m43 = 0.0f;		Xrot.m44 = 1.0f;

			Matrix4T temp = Multiply(m, Xrot);
			return temp;
		}

		// Euler rotation around Y axis
		inline Matrix4T RotateY(const T &theta, const Matrix4T &m)
		{
			Matrix4T Yrot;
			Yrot.m11 = cos(theta); Yrot.m12 = 0.0f; Yrot.m13 = -sin(theta); Yrot.m14 = 0.0f;
			Yrot.m21 = 0.0f;	   Yrot.m22 = 1.0f; Yrot.m23 = 0.0f;		Yrot.m24 = 0.0f;
			Yrot.m31 = sin(theta); Yrot.m32 = 0.0f; Yrot.m33 = cos(theta);	Yrot.m34 = 0.0f;
			Yrot.m41 = 0.0f;	   Yrot.m42 = 0.0f; Yrot.m43 = 0.0f;		Yrot.m44 = 1.0f;

			Matrix4T temp = Multiply(m, Yrot);
			return temp;
		}

		// Euler rotation around Z axis
		inline Matrix4T RotateZ(const T &theta, const Matrix4T &m)
		{
			Matrix4T Zrot;
			Zrot.m11 = cos(theta); Zrot.m12 = -sin(theta); Zrot.m13 = 0.0f; Zrot.m14 = 0.0f;
			Zrot.m21 = sin(theta); Zrot.m22 = cos(theta);  Zrot.m23 = 0.0f;	Zrot.m24 = 0.0f;
			Zrot.m31 = 0.0f;	   Zrot.m32 = 0.0f;		   Zrot.m33 = 1.0f;	Zrot.m34 = 0.0f;
			Zrot.m41 = 0.0f;	   Zrot.m42 = 0.0f;		   Zrot.m43 = 0.0f;	Zrot.m44 = 1.0f;

			Matrix4T temp = Multiply(m, Zrot);
			return temp;
		}

		// Uniform scale matrix (used for scale transform of vertices not scaling entire matrix)
		inline Matrix4T Scale(const T &Scalar, const Matrix4T &m)
		{
			Matrix4T matScale;
			matScale.m11 = Scalar; matScale.m12 = 0.0f;	  matScale.m13 = 0.0f;   matScale.m14 = 0.0f;
			matScale.m21 = 0.0f;   matScale.m22 = Scalar; matScale.m23 = 0.0f;   matScale.m24 = 0.0f;
			matScale.m31 = 0.0f;   matScale.m32 = 0.0f;   matScale.m33 = Scalar; matScale.m34 = 0.0f;
			matScale.m41 = 0.0f;   matScale.m42 = 0.0f;   matScale.m43 = 0.0f;   matScale.m44 = 1.0f;

			Matrix4T temp = Multiply(m, matScale);
			return temp;
		}

		// Scale matrix with individually defined xyz scales (used for scale transform of vertices not scaling entire matrix)
		inline Matrix4T Scale(const T &ScalarX, const T &ScalarY, const T &ScalarZ, const Matrix4T &m)
		{
			Matrix4T matScale;
			matScale.m11 = ScalarX; matScale.m12 = 0.0f;	matScale.m13 = 0.0f;    matScale.m14 = 0.0f;
			matScale.m21 = 0.0f;    matScale.m22 = ScalarY; matScale.m23 = 0.0f;    matScale.m24 = 0.0f;
			matScale.m31 = 0.0f;    matScale.m32 = 0.0f;    matScale.m33 = ScalarZ; matScale.m34 = 0.0f;
			matScale.m41 = 0.0f;    matScale.m42 = 0.0f;    matScale.m43 = 0.0f;    matScale.m44 = 1.0f;

			Matrix4T temp = Multiply(m, matScale);
			return temp;
		}

		// Scale matrix with scale defined by QE::Vector3T<T> object (used for scale transform of vertices not scaling entire matrix)
		inline Matrix4T Scale(const Vector3T<T> Scalar, const Matrix4T &m)
		{
			Matrix4T matScale;
			matScale.m11 = Scalar.x; matScale.m12 = 0.0f;	  matScale.m13 = 0.0f;     matScale.m14 = 0.0f;
			matScale.m21 = 0.0f;     matScale.m22 = Scalar.y; matScale.m23 = 0.0f;     matScale.m24 = 0.0f;
			matScale.m31 = 0.0f;     matScale.m32 = 0.0f;     matScale.m33 = Scalar.z; matScale.m34 = 0.0f;
			matScale.m41 = 0.0f;     matScale.m42 = 0.0f;     matScale.m43 = 0.0f;     matScale.m44 = 1.0f;

			Matrix4T temp = Multiply(m, matScale);
			return temp;
		}

		// Find and return the transpose of the matrix
		inline Matrix4T Transpose(const Matrix4T &m)
		{
			Matrix4T matTrans;
			matTrans.m11 = m.m11; matTrans.m12 = m.m21; matTrans.m13 = m.m31; matTrans.m14 = m.m41;
			matTrans.m21 = m.m12; matTrans.m22 = m.m22; matTrans.m23 = m.m32; matTrans.m24 = m.m42;
			matTrans.m31 = m.m13; matTrans.m32 = m.m23; matTrans.m33 = m.m33; matTrans.m34 = m.m43;
			matTrans.m41 = m.m14; matTrans.m42 = m.m24; matTrans.m43 = m.m34; matTrans.m44 = m.m44;
			return matTrans;
		}

		// Scale entire matrix
		inline Matrix4T MatScale(const T &s, const Matrix4T &m)
		{
			Matrix4T matScaled;
			matScaled.m11 = m.m11 * s; matScaled.m12 = m.m12 * s; matScaled.m13 = m.m13 * s; matScaled.m14 = m.m14 * s;
			matScaled.m21 = m.m21 * s; matScaled.m22 = m.m22 * s; matScaled.m23 = m.m23 * s; matScaled.m24 = m.m24 * s;
			matScaled.m31 = m.m31 * s; matScaled.m32 = m.m32 * s; matScaled.m33 = m.m33 * s; matScaled.m34 = m.m34 * s;
			matScaled.m41 = m.m41 * s; matScaled.m42 = m.m42 * s; matScaled.m43 = m.m43 * s; matScaled.m44 = m.m44 * s;
			return matScaled;
		}

		// Find determinant of the matrix
		inline T Determinant()
		{
			T Det;
			Det = m11*(m22*(m33*m44 - m34*m43) - m32*(m23*m44 + m24*m43) + m42*(m23*m34 - m24*m33))
				- m21*(m12*(m33*m44 - m34*m43) - m32*(m13*m44 + m14*m43) + m42*(m13*m34 - m14*m33))
				+ m31*(m12*(m23*m44 - m24*m43) - m22*(m13*m44 + m14*m43) + m42*(m13*m24 - m14*m23))
				- m41*(m12*(m23*m34 - m24*m33) - m22*(m13*m34 + m14*m33) + m32*(m13*m24 - m14*m23));
			return Det;
		}

		// Cofactor (determinant of 3x3 submatrix)
		inline T Cofactor(T _11, T _12, T _13,
						  T _21, T _22, T _23,
						  T _31, T _32, T _33)
		{
			T cf;
			cf = _11*(_22*_33 - _23*_32) + _12*(_23*_31 - _21*_33) + _13*(_21*_32 - _22*_31);
			return cf;
		}

		inline Matrix4T CofactorMatrix()
		{
			Matrix4T matOut;

			matOut.m11 = Cofactor(m22, m23, m24,
								  m32, m33, m34,
								  m42, m43, m44);
			matOut.m12 = -Cofactor(m21, m23, m24,
								   m31, m33, m34,
								   m41, m43, m44);
			matOut.m13 = Cofactor(m21, m22, m24,
								  m31, m32, m34,
								  m41, m42, m44);
			matOut.m14 = -Cofactor(m21, m22, m23,
								   m31, m32, m33,
								   m41, m42, m43);

			matOut.m21 = -Cofactor(m12, m13, m14,
								   m32, m33, m34,
								   m42, m43, m44);
			matOut.m22 = Cofactor(m11, m13, m14,
								  m31, m33, m34,
								  m41, m43, m44);
			matOut.m23 = -Cofactor(m11, m12, m14,
								   m31, m32, m34,
								   m41, m42, m44);
			matOut.m24 = Cofactor(m11, m12, m13,
								  m31, m32, m33,
								  m41, m42, m43);

			matOut.m31 = Cofactor(m12, m13, m14,
								  m22, m23, m24,
								  m42, m43, m44);
			matOut.m32 = -Cofactor(m11, m13, m14,
								   m21, m23, m24,
								   m41, m43, m44);
			matOut.m33 = Cofactor(m11, m12, m14,
								  m21, m22, m24,
								  m41, m42, m44);
			matOut.m34 = -Cofactor(m11, m12, m13,
								   m21, m22, m23,
								   m41, m42, m43);

			matOut.m41 = -Cofactor(m12, m13, m14,
								   m22, m23, m24,
								   m32, m33, m34);
			matOut.m42 = Cofactor(m11, m13, m14,
								  m21, m23, m24,
								  m31, m33, m34);
			matOut.m43 = -Cofactor(m11, m12, m14,
								   m21, m22, m24,
								   m31, m32, m34);
			matOut.m44 = Cofactor(m11, m12, m13,
								  m21, m22, m23,
								  m31, m32, m33);

			return matOut;
		}

		inline Matrix4T Inverse()
		{
			Matrix4T adjoint = Transpose(CofactorMatrix());
			T determinant = Determinant();
			Matrix4T inverse;
			inverse.m11 = adjoint.m11 / determinant;
			inverse.m12 = adjoint.m12 / determinant;
			inverse.m13 = adjoint.m13 / determinant;
			inverse.m14 = adjoint.m14 / determinant;
			
			inverse.m21 = adjoint.m21 / determinant;
			inverse.m22 = adjoint.m22 / determinant;
			inverse.m23 = adjoint.m23 / determinant;
			inverse.m24 = adjoint.m24 / determinant;
			
			inverse.m31 = adjoint.m31 / determinant;
			inverse.m32 = adjoint.m32 / determinant;
			inverse.m33 = adjoint.m33 / determinant;
			inverse.m34 = adjoint.m34 / determinant;
			
			inverse.m41 = adjoint.m41 / determinant;
			inverse.m42 = adjoint.m42 / determinant;
			inverse.m43 = adjoint.m43 / determinant;
			inverse.m44 = adjoint.m44 / determinant;

			return inverse;
		}

		inline Matrix4T LookLH(const Vector3T<T> &EyePt, const Vector3T<T> &Target, const Vector3T<T> &Up)
		{
			Vector3T<T> z = Target;
			z -= EyePt;
			z = z.normalise();
			Vector3T<T> x = Up.cross(Up, z);
			x = x.normalise();
			Vector3T<T> y = z.cross(x);

			Matrix4T Look;
			Look.m11 = x.x;				 Look.m12 = y.x;			  Look.m13 = z.x;			   Look.m14 = 0.0f;
			Look.m21 = x.y;				 Look.m22 = y.y;			  Look.m23 = z.y;			   Look.m24 = 0.0f;
			Look.m31 = x.z;				 Look.m32 = y.z;			  Look.m33 = z.z;			   Look.m34 = 0.0f;
			Look.m41 = -x.dot(x, EyePt); Look.m42 = -y.dot(y, EyePt); Look.m43 = -z.dot(z, EyePt); Look.m44 = 1.0f;

			return Look;
		}

		inline Matrix4T PerspectiveFovLH(const T fovy, const T Aspect, const T zn, const T zf)
		{
			T ScaleY = 1.0f / tan(fovy / 2.0f);
			T ScaleX = ScaleY / Aspect;

			Matrix4T Proj;
			Proj.m11 = ScaleX; Proj.m12 = 0.0f;	  Proj.m13 = 0.0f;				   Proj.m14 = 0.0f;
			Proj.m21 = 0.0f;   Proj.m22 = ScaleY; Proj.m23 = 0.0f;				   Proj.m24 = 0.0f;
			Proj.m31 = 0.0f;   Proj.m32 = 0.0f;   Proj.m33 = zf / (zf - zn);	   Proj.m34 = 1.0f;
			Proj.m41 = 0.0f;   Proj.m42 = 0.0f;   Proj.m43 = -zn * zf / (zf - zn); Proj.m44 = 0.0f;

			return Proj;
		}

		// Convert QE::Matrix4T to a d3d matrix
		//inline D3DXMATRIX D3DXConvert()
		//{
		//	D3DXMATRIX newMat;
		//	newMat._11 = (FLOAT)m11; newMat._12 = (FLOAT)m12; newMat._13 = (FLOAT)m13; newMat._14 = (FLOAT)m14;
		//	newMat._21 = (FLOAT)m21; newMat._22 = (FLOAT)m22; newMat._23 = (FLOAT)m23; newMat._24 = (FLOAT)m24;
		//	newMat._31 = (FLOAT)m31; newMat._32 = (FLOAT)m32; newMat._33 = (FLOAT)m33; newMat._34 = (FLOAT)m34;
		//	newMat._41 = (FLOAT)m41; newMat._42 = (FLOAT)m42; newMat._43 = (FLOAT)m43; newMat._44 = (FLOAT)m44;
		//	return newMat;
		//}

		// Convert rotation matrix to Euler angles
		inline QE::Vector3T<T> MatrixToEuler()
		{
			QE::Vector3T<T> EulerAngles;
			EulerAngles.x = (T)asin(m23);
			if((T)cos(EulerAngles.x) != (T)0.0f)
			{
				EulerAngles.y = (T)atan2(m13, m33);
				EulerAngles.z = (T)atan2(m21, m22);
			}
			else
			{
				EulerAngles.y = (T)atan2(m31, m11);
				EulerAngles.z = (T)0.0f;
			}
			return EulerAngles;
		}

		// Convert rotation matrix to Quaternion
		inline QE::QuaternionT<T> MatrixToQuaternion()
		{
			QE::QuaternionT<T> q;

			T FourWSquaredMinus1 = m11 + m22 + m33;
			T FourXSquaredMinus1 = m11 - m22 - m33;
			T FourYSquaredMinus1 = m22 - m11 - m33;
			T FourZSquaredMinus1 = m33 - m11 - m22;

			int Biggest = 0;
			T FourBiggestSquaredMinus1 = FourWSquaredMinus1;
			if(FourXSquaredMinus1 > FourBiggestSquaredMinus1)
			{
				FourBiggestSquaredMinus1 = FourXSquaredMinus1;
				Biggest = 1;
			}
			if(FourYSquaredMinus1 > FourBiggestSquaredMinus1)
			{
				FourBiggestSquaredMinus1 = FourYSquaredMinus1;
				Biggest = 2;
			}
			if(FourZSquaredMinus1 > FourBiggestSquaredMinus1)
			{
				FourBiggestSquaredMinus1 = FourZSquaredMinus1;
				Biggest = 3;
			}

			T BiggestVal = sqrt(FourBiggestSquaredMinus1 + 1.0f) * 0.5f;
			T mult = (T)(0.25f / BiggestVal);

			switch(Biggest)
			{
			case 0:
				q.w = BiggestVal;
				q.x = (m23 - m32) * mult;
				q.y = (m31 - m13) * mult;
				q.z = (m12 - m21) * mult;
				break;

			case 1:
				q.w = (m23 - m32) * mult;
				q.x = BiggestVal;
				q.y = (m12 + m21) * mult;
				q.z = (m23 + m32) * mult;
				break;

			case 2:
				q.w = (m31 - m13) * mult;
				q.x = (m12 + m21) * mult;
				q.y = BiggestVal;
				q.z = (m23 + m32) * mult;
				break;

			case 3:
				q.w = (m12 - m21) * mult;
				q.x = (m31 + m13) * mult;
				q.y = (m23 + m32) * mult;
				q.z = BiggestVal;
				break;
			}

			return q;
		}

		inline static QE::Vector3T<T> VectorMultiply(QE::Vector3T<T> v, Matrix4T m)
		{
			QE::Vector3T<T> vOut;
			vOut.x = v.x * m.m11 + v.y * m.m21 + v.z * m.m31;
			vOut.y = v.x * m.m12 + v.y * m.m22 + v.z * m.m32;
			vOut.z = v.x * m.m13 + v.y * m.m23 + v.z * m.m33;
			return vOut;
		}

		inline void SetTranslation(QE::Vector3f translation)
		{
			m41 = translation.x;
			m42 = translation.y;
			m43 = translation.z;
		}

		inline Matrix4T GetCofactorMatrix()
		{
			Matrix4T CofactorMatrix;

			return CofactorMatrix;
		}
	};

	typedef Matrix4T<float> Matrix4f;
	typedef Matrix4T<double> Matrix4d;
}

#endif