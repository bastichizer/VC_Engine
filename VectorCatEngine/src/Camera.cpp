//================================================================
// Camera.cpp
//================================================================

#include "Camera.h"
#include "global.h"

#include <DirectXMath.h>
using namespace DirectX;

Camera::Camera() :
m_isPerspective(true)
{
	m_currentPos = QE::Vector3f(0.0f, 0.0f, 0.0f);
	m_currentForward = QE::Vector3f(0.0f, 0.0f, 1.0f);
	m_currentUp = QE::Vector3f(0.0f, 1.0f, 0.0f);
	m_currentRight = QE::Vector3f(1.0f, 0.0f, 0.0f);
	m_aspectRatio = (float)g_windowWidth / (float)g_windowHeight;
	InitProjMatrix();
}

Camera::~Camera()
{

}

void Camera::InitProjMatrix()
{
	if (m_isPerspective)
	{
		InitPerspectiveProjMatrix();
	}
	else
	{
		InitOrthoProjMatrix();
	}
}

void Camera::InitPerspectiveProjMatrix()
{

}

void Camera::InitOrthoProjMatrix()
{
	float l = 0.0f;
	float r = m_orthoWidth;
	float b = 0.0f;
	float t = m_orthoHeight;
	float n = m_nearClip;
	float f = m_farClip;

	m_matProj.m11 = 2.0f / (r - l);
	m_matProj.m12 = 0.0f;
	m_matProj.m13 = 0.0f;
	m_matProj.m14 = 0.0f;

	m_matProj.m21 = 0.0f;
	m_matProj.m22 = 2.0f / (t - b);
	m_matProj.m23 = 0.0f;
	m_matProj.m24 = 0.0f;

	m_matProj.m31 = 0.0f;
	m_matProj.m32 = 0.0f;
	m_matProj.m33 = 1.0f / (f - n);
	m_matProj.m34 = 0.0f;

	m_matProj.m41 = 0.0f;
	m_matProj.m42 = 0.0f;
	m_matProj.m43 = -(f - n) * n;
	m_matProj.m44 = 1.0f;
}

void Camera::UpdateViewMatrix()
{
	m_matView.m11 = m_currentRight.x;
	m_matView.m12 = m_currentUp.x;
	m_matView.m13 = m_currentForward.x;
	m_matView.m14 = 0.0f;

	m_matView.m21 = m_currentRight.y;
	m_matView.m22 = m_currentUp.y;
	m_matView.m23 = m_currentForward.y;
	m_matView.m24 = 0.0f;

	m_matView.m31 = m_currentRight.z;
	m_matView.m32 = m_currentUp.z;
	m_matView.m33 = m_currentForward.z;
	m_matView.m34 = 0.0f;

	XMVECTOR r;
	r.m128_f32[0] = m_currentRight.x;
	r.m128_f32[1] = m_currentRight.y;
	r.m128_f32[2] = m_currentRight.z;
	r.m128_f32[3] = 0.0f;
	XMVECTOR u;
	u.m128_f32[0] = m_currentUp.x;
	u.m128_f32[1] = m_currentUp.y;
	u.m128_f32[2] = m_currentUp.z;
	u.m128_f32[3] = 0.0f;
	XMVECTOR f;
	f.m128_f32[0] = m_currentForward.x;
	f.m128_f32[1] = m_currentForward.y;
	f.m128_f32[2] = m_currentForward.z;
	f.m128_f32[3] = 0.0f;
	XMVECTOR p;
	p.m128_f32[0] = -m_currentPos.x;
	p.m128_f32[1] = -m_currentPos.y;
	p.m128_f32[2] = -m_currentPos.z;
	p.m128_f32[3] = 1.0f;

	m_matView.m41 = DirectX::XMVector4Dot(r, p).m128_f32[3];
	m_matView.m42 = DirectX::XMVector4Dot(u, p).m128_f32[3];
	m_matView.m43 = DirectX::XMVector4Dot(f, p).m128_f32[3];
	m_matView.m44 = 1.0f;
}

QE::Matrix4f Camera::GetViewProjMatrix()
{
	//return XMMatrixMultiply(m_matView, m_matProj);
	return QE::Matrix4f::Multiply(m_matView, m_matProj);
}