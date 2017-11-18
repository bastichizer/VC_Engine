//================================================================
// UICamera.cpp
//================================================================

#include "UICamera.h"
#include "global.h"

UICamera::UICamera() : Camera()
{
	m_isPerspective = false;
	m_orthoWidth = (float)g_windowWidth;
	m_orthoHeight = (float)g_windowHeight;
	m_currentPos = QE::Vector3f((float)(g_windowWidth / 2), (float)(g_windowHeight / 2), -1.0f);
	m_currentForward = QE::Vector3f(0.0f, 0.0f, 1.0f);
	m_currentUp = QE::Vector3f(0.0f, 1.0f, 0.0f);
	m_currentRight = QE::Vector3f(1.0f, 0.0f, 0.0f);
	m_nearClip = 0.1f;
	m_farClip = 2.0f;
	InitProjMatrix();
}

UICamera::~UICamera()
{

}

void UICamera::InitOrthoProjMatrix()
{
	// Build an orthogonal projection matrix sized so that one unit of space in width or height is equivalent to one pixel
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