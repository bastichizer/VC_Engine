//===================================================================
// Camera.h
//
// Basic camera class, used to hold the view and projection matrices,
// in this case orthogonal projection is used since we are rendering
// only 2d sprites
//===================================================================

#ifndef CAMERA_H
#define CAMERA_H

#include "RenderManager.h"

#include "Quasar\QMaths.h"

class Camera
{
public:
	Camera();
	~Camera();

	void InitProjMatrix();
	//XMMATRIX GetViewProjMatrix();
	QE::Matrix4f GetViewProjMatrix();
	void UpdateViewMatrix();

protected:
	virtual void InitOrthoProjMatrix();
	virtual void InitPerspectiveProjMatrix();
	//XMMATRIX m_matView;
	QE::Matrix4f m_matView;
	//XMMATRIX m_matProj;
	QE::Matrix4f m_matProj;

	//XMFLOAT3 m_currentPos;
	QE::Vector3f m_currentPos;
	//XMFLOAT3 m_currentForward;
	QE::Vector3f m_currentForward;
	//XMFLOAT3 m_currentUp;
	QE::Vector3f m_currentUp;
	//XMFLOAT3 m_currentRight;
	QE::Vector3f m_currentRight;

	bool m_isPerspective;
	float m_fov;
	float m_orthoWidth;
	float m_orthoHeight;
	float m_aspectRatio;
	float m_nearClip;
	float m_farClip;
};

#endif // CAMERA_H

