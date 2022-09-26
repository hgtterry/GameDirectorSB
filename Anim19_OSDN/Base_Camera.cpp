#include "stdafx.h"
#include "Base_Camera.h"

Base_Camera::Base_Camera()
{
}

Base_Camera::~Base_Camera()
{

	Init_Camera();

}

// *************************************************************************
// *	  		Init_Camera:- Terry and Hazel Flanigan 2022				   *
// *************************************************************************
void Base_Camera::Init_Camera(void)
{
	CamPos.x = 0;
	CamPos.y = 0;
	CamPos.z = 0;

	LookAt.x = 0;
	LookAt.y = 0;
	LookAt.z = 0;

}
