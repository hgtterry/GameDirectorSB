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
	BlueRotAxis_Ent = App->SBC_Ogre->mSceneMgr->createEntity("Blue_Rot_Axis", "Ring.mesh", App->SBC_Ogre->App_Resource_Group);
	BlueRotAxis_Node = App->SBC_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
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
	RedAxis_Ent = App->SBC_Ogre->mSceneMgr->createEntity("Red_Axis", "RedAxes.mesh", App->SBC_Ogre->App_Resource_Group);
	RedAxis_Node = App->SBC_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
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
	GreenAxis_Ent = App->SBC_Ogre->mSceneMgr->createEntity("Green_Axis", "GreenAxes.mesh", App->SBC_Ogre->App_Resource_Group);
	GreenAxis_Node = App->SBC_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
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
	BlueAxis_Ent = App->SBC_Ogre->mSceneMgr->createEntity("Blue_Axis", "BlueAxes.mesh", App->SBC_Ogre->App_Resource_Group);
	BlueAxis_Node = App->SBC_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
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
