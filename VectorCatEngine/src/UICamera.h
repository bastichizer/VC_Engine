//===============================================================
// UICamera.h
//
// UI Camera class, creates ortho camera whose projection matrix 
// is sized to the window
//===============================================================

#ifndef UICAMERA_H
#define UICAMERA_H

#include "Camera.h"

class UICamera : public Camera
{
public:
	UICamera();
	~UICamera();

private:
	virtual void InitOrthoProjMatrix();
};

#endif // UICAMERA_H

