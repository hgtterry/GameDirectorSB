#include "stdafx.h"
#include "GD19_App.h"
#include "EQ15_WE_Listener.h"


EQ15_WE_Listener::EQ15_WE_Listener()
{
}


EQ15_WE_Listener::~EQ15_WE_Listener()
{
}


// *************************************************************************
// *			WE_RenderingQueued   Terry Flanigan						   *
// *************************************************************************
bool EQ15_WE_Listener::WE_RenderingQueued(const FrameEvent& evt)
{
	Ogre::Radian Rotation_Speed;
	Rotation_Speed = 1 / (float)57.3;
	App->Cl_Vm_MeshDesign->MvNode->yaw(Rotation_Speed);
	
	return 1;
}