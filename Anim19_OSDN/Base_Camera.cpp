#include "stdafx.h"
#include "Base_Camera.h"

Base_Camera::Base_Camera()
{
	Init_Camera();
}

Base_Camera::~Base_Camera()
{

}

// *************************************************************************
// *	  		Init_Camera:- Terry and Hazel Flanigan 2022				   *
// *************************************************************************
void Base_Camera::Init_Camera(void)
{
	CamPos.x = 0;
	CamPos.y = 90;
	CamPos.z = 100;

	LookAt.x = 0;
	LookAt.y = 30;
	LookAt.z = 0;

	Altered = 1;

	Cam_Quat.IDENTITY;

	Camera_Name[0] = 0;

	FileViewItem = nullptr;

}
