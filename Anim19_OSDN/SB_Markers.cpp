/*
Copyright (c) 2021 Scene Builder and Equity -- Inflanite Software W.T.Flanigan H.C.Flanigan

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software. If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.

3. This notice may not be removed or altered from any source
distribution.
*/

#include "stdafx.h"
#include "GD19_App.h"
#include "SB_Markers.h"


SB_Markers::SB_Markers(void)
{
	BoxManual = NULL;
	BoxNode = NULL;

	Arrow_Ent = NULL;
	Arrow_Node = NULL;

	mPickSight = NULL;

	Target_Hit_Ent = NULL;
	Target_Hit_Node = NULL;

	RedAxis_Ent = nullptr;
	RedAxis_Node = nullptr;

	BlueAxis_Ent = nullptr;
	BlueAxis_Node = nullptr;

	GreenAxis_Ent = nullptr;
	GreenAxis_Node = nullptr;

	BlueRotAxis_Ent = nullptr;
	BlueRotAxis_Node = nullptr;
}

SB_Markers::~SB_Markers(void)
{
}

// *************************************************************************
// *	  		MarkerBB_Setup:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_Markers::MarkerBB_Setup(void)
{
	float BoxDepth = 2.5;
	float BoxHeight = 2.5;
	float BoxWidth = 2.5;

	BoxManual = App->CL_Ogre->mSceneMgr->createManualObject("BB_Box");
	BoxManual->begin("BaseWhiteNoLighting", RenderOperation::OT_LINE_STRIP);

	BoxManual->colour(0, 1, 0);

	BoxManual->position(-BoxWidth, -BoxHeight, BoxDepth);
	BoxManual->position(BoxWidth, -BoxHeight, BoxDepth);
	BoxManual->position(BoxWidth, BoxHeight, BoxDepth);
	BoxManual->position(-BoxWidth, BoxHeight, BoxDepth);

	BoxManual->position(-BoxWidth, -BoxHeight, -BoxDepth);
	BoxManual->position(BoxWidth, -BoxHeight, -BoxDepth);
	BoxManual->position(BoxWidth, BoxHeight, -BoxDepth);
	BoxManual->position(-BoxWidth, BoxHeight, -BoxDepth);

	BoxManual->index(0);
	BoxManual->index(1);
	BoxManual->index(2);
	BoxManual->index(3);
	BoxManual->index(0);

	BoxManual->index(4);
	BoxManual->index(5);
	BoxManual->index(6);
	BoxManual->index(7);
	BoxManual->index(4);

	BoxManual->index(5);
	BoxManual->index(1);

	BoxManual->index(2);
	BoxManual->index(6);

	BoxManual->index(7);
	BoxManual->index(3);

	BoxManual->end();
	BoxNode = App->CL_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	BoxNode->attachObject(BoxManual);

	BoxNode->setPosition(0, 0, 0);
	BoxNode->setVisible(false);
	return 1;
}
// *************************************************************************
// *	  	MarkerBB_Update:- Terry and Hazel Flanigan 2022				   *
// *************************************************************************
bool SB_Markers::MarkerBB_Update(float Depth, float Height, float Width)
{
	BoxManual->beginUpdate(0);
	BoxManual->colour(0, 1, 0, 0.5);

	BoxManual->position(-Depth, -Height, Width);
	BoxManual->position(Depth, -Height, Width);
	BoxManual->position(Depth, Height, Width);
	BoxManual->position(-Depth, Height, Width);
	BoxManual->position(-Depth, -Height, -Width);
	BoxManual->position(Depth, -Height, -Width);
	BoxManual->position(Depth, Height, -Width);
	BoxManual->position(-Depth, Height, -Width);

	BoxManual->index(0);
	BoxManual->index(1);
	BoxManual->index(2);
	BoxManual->index(3);
	BoxManual->index(0);
	BoxManual->index(4);
	BoxManual->index(5);
	BoxManual->index(6);
	BoxManual->index(7);
	BoxManual->index(4);
	BoxManual->index(5);
	BoxManual->index(1);
	BoxManual->index(2);
	BoxManual->index(6);
	BoxManual->index(7);
	BoxManual->index(3);

	BoxManual->end();

	return 1;
}

// *************************************************************************
// *	  		MarkerBB_Addjust:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
void SB_Markers::MarkerBB_Addjust(int Index)
{

	Base_Object* Object = App->SBC_Scene->B_Object[Index];

	Ogre::Vector3 Position = Object->Object_Node->getPosition();
	Ogre::Quaternion Rot = Object->Object_Node->getOrientation();

	Ogre::Vector3 Size = App->SBC_Object->GetMesh_BB_Size(Object->Object_Node);
	MarkerBB_Update(Size.x / 2, Size.y / 2, Size.z / 2);

	Ogre::Vector3 Centre = Object->Object_Node->getAttachedObject(0)->getBoundingBox().getCenter();
	Ogre::Vector3 WS = Object->Object_Node->convertLocalToWorldPosition(Centre);

	BoxNode->setPosition(WS);
	BoxNode->setOrientation(Rot);
	BoxNode->setVisible(true);

	App->SBC_Markers->Move_Arrow(WS);
}

// **************************************************************************
// *	  			Set_Markers:- Terry and Hazel Flanigan 2022				*
// **************************************************************************
void SB_Markers::Set_Markers()
{
	Load_PickSight();
	Load_Arrow();
	Load_Target_Hit();
	Load_All_Axis();
	MarkerBB_Setup();
}

// *************************************************************************
// *	  		Target_Hit:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
void SB_Markers::Load_Target_Hit()
{
	Target_Hit_Ent = App->CL_Ogre->mSceneMgr->createEntity("Target_Hit", "Gizmo.mesh", App->CL_Ogre->App_Resource_Group);
	Target_Hit_Node = App->CL_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Target_Hit_Node->attachObject(Target_Hit_Ent);

	Target_Hit_Node->setVisible(false);
	Target_Hit_Node->setPosition(0, 0, 0);
	Target_Hit_Node->setScale(10, 10, 10);
}

// *************************************************************************
// *	  		Load_Arrow:- Terry and Hazel Flanigan 2022				   *
// *************************************************************************
void SB_Markers::Load_Arrow()
{
	Arrow_Ent = App->CL_Ogre->mSceneMgr->createEntity("Arrow", "Gizmo.mesh", App->CL_Ogre->App_Resource_Group);
	Arrow_Node = App->CL_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Arrow_Node->attachObject(Arrow_Ent);

	Arrow_Node->setVisible(false);
	Arrow_Node->setPosition(0, 0, 0);
	Arrow_Node->setScale(7, 7, 7);
}

// *************************************************************************
// *			Load_PickSight:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void SB_Markers::Load_PickSight(void)
{
	mPickSight = OverlayManager::getSingleton().getByName("MyOverlays/PicksightOverlay");
	mPickSight->hide();
}

// **************************************************************************
// *	  			Load_All_Axis:- Terry and Hazel Flanigan 2022			*
// **************************************************************************
void SB_Markers::Load_All_Axis()
{
	Load_Blue_Rot_Axis();
	Load_Red_Axis();
	Load_Green_Axis();
	Load_Blue_Axis();
}

// **************************************************************************
// *	  		Load_Blue_Rot_Axis:- Terry and Hazel Flanigan 2022			*
// **************************************************************************
void SB_Markers::Load_Blue_Rot_Axis()
{
	BlueRotAxis_Ent = App->CL_Ogre->mSceneMgr->createEntity("Blue_Rot_Axis", "Ring.mesh", App->CL_Ogre->App_Resource_Group);
	BlueRotAxis_Node = App->CL_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	BlueRotAxis_Node->attachObject(BlueRotAxis_Ent);

	BlueRotAxis_Node->setVisible(false);
	BlueRotAxis_Node->setPosition(0, 0, 0);
	BlueRotAxis_Node->setScale(1, 1, 1);
}

// **************************************************************************
// *	  			Load_Red_Axis:- Terry and Hazel Flanigan 2022			*
// **************************************************************************
void SB_Markers::Load_Red_Axis()
{
	RedAxis_Ent = App->CL_Ogre->mSceneMgr->createEntity("Red_Axis", "RedAxes.mesh", App->CL_Ogre->App_Resource_Group);
	RedAxis_Node = App->CL_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	RedAxis_Node->attachObject(RedAxis_Ent);

	RedAxis_Node->setVisible(false);
	RedAxis_Node->setPosition(0, 0, 0);
	RedAxis_Node->setScale(1, 1, 2);
}

// **************************************************************************
// *	  			Load_Green_Axis:- Terry and Hazel Flanigan 2022			*
// **************************************************************************
void SB_Markers::Load_Green_Axis()
{
	GreenAxis_Ent = App->CL_Ogre->mSceneMgr->createEntity("Green_Axis", "GreenAxes.mesh", App->CL_Ogre->App_Resource_Group);
	GreenAxis_Node = App->CL_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	GreenAxis_Node->attachObject(GreenAxis_Ent);

	GreenAxis_Node->setVisible(false);
	GreenAxis_Node->setPosition(0, 0, 0);
	GreenAxis_Node->setScale(1, 2, 1);
}

// **************************************************************************
// *	  			Load_Blue_Axis:- Terry and Hazel Flanigan 2022			*
// **************************************************************************
void SB_Markers::Load_Blue_Axis()
{
	BlueAxis_Ent = App->CL_Ogre->mSceneMgr->createEntity("Blue_Axis", "BlueAxes.mesh", App->CL_Ogre->App_Resource_Group);
	BlueAxis_Node = App->CL_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	BlueAxis_Node->attachObject(BlueAxis_Ent);

	BlueAxis_Node->setVisible(false);
	BlueAxis_Node->setPosition(0, 0, 0);
	BlueAxis_Node->setScale(2, 1, 1);
}

// **************************************************************************
// *	  	Update_Red_Axis_Marker:- Terry and Hazel Flanigan 2022			*
// **************************************************************************
void SB_Markers::Update_Red_Axis_Marker(int Index)
{

	Ogre::Vector3 Centre = App->SBC_Object->Get_BoundingBox_World_Centre(Index);

	App->SBC_Markers->RedAxis_Node->setPosition(Centre);
	App->SBC_Markers->RedAxis_Node->setVisible(true);
}

// **************************************************************************
// *	  	Update_Blue_Axis_Marker:- Terry and Hazel Flanigan 2022			*
// **************************************************************************
void SB_Markers::Update_Green_Axis_Marker(int Index)
{

	Ogre::Vector3 Centre = App->SBC_Object->Get_BoundingBox_World_Centre(Index);

	App->SBC_Markers->GreenAxis_Node->setPosition(Centre);
	App->SBC_Markers->GreenAxis_Node->setVisible(true);
}

// **************************************************************************
// *	  	Update_Blue_Axis_Marker:- Terry and Hazel Flanigan 2022			*
// **************************************************************************
void SB_Markers::Update_Blue_Axis_Marker(int Index)
{

	//App->SBC_Markers->BlueAxis_Node->setOrientation = App->SBC_Scene->B_Object[Index]->Object_Node->getOrientation();

	Ogre::Vector3 Centre = App->SBC_Object->Get_BoundingBox_World_Centre(Index);

	App->SBC_Markers->BlueAxis_Node->setPosition(Centre);
	App->SBC_Markers->BlueAxis_Node->setVisible(true);
}

// **************************************************************************
// *			Hide_Axis_Marker:- Terry and Hazel Flanigan 2022			*
// **************************************************************************
void SB_Markers::Hide_Axis_Marker()
{
	App->SBC_Markers->BlueAxis_Node->setVisible(false);
	App->SBC_Markers->RedAxis_Node->setVisible(false);
	App->SBC_Markers->GreenAxis_Node->setVisible(false);
}

// *************************************************************************
// *			Move_Arrow:- Terry and Hazel Flanigan 2022				   *
// *************************************************************************
void SB_Markers::Move_Arrow(Ogre::Vector3 pos)
{
	Arrow_Node->setVisible(true);
	Arrow_Node->setPosition(pos);
}

// *************************************************************************
// *	  	Move_Target_Hit:- Terry and Hazel Flanigan 2022				   *
// *************************************************************************
void SB_Markers::Move_Target_Hit(Ogre::Vector3 pos)
{
	Target_Hit_Node->setVisible(true);
	Target_Hit_Node->setPosition(pos);
}
