/*
Copyright (c) 2022 GameDirectorSB and EquityME -- HGTInflanite Software W.T.Flanigan H.C.Flanigan

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

#include "StdAfx.h"
#include "GD19_App.h"
#include "GD19_Visuals.h"


SB_Visuals::SB_Visuals(void)
{
	mPickSight = NULL;
	BoxManual = NULL;
	BoxNode = NULL;
}


SB_Visuals::~SB_Visuals(void)
{
}

// *************************************************************************
// *			Load_PickSight:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void SB_Visuals::Load_PickSight(void)
{
	mPickSight = OverlayManager::getSingleton().getByName("MyOverlays/PicksightOverlay");
	mPickSight->hide();
}

// *************************************************************************
// *	  		MarkerBB_Setup:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_Visuals::MarkerBB_Setup(void)
{
	float BoxDepth=2.5;
	float BoxHeight=2.5;
	float BoxWidth=2.5;

	BoxManual = App->SBC_Ogre->mSceneMgr->createManualObject("BB_Box");
	BoxManual->begin("BaseWhiteNoLighting", RenderOperation::OT_LINE_STRIP);
	
	BoxManual->colour(0,1,0);
	
    BoxManual->position(-BoxWidth, -BoxHeight, BoxDepth);
    BoxManual->position( BoxWidth, -BoxHeight, BoxDepth);
    BoxManual->position( BoxWidth,  BoxHeight, BoxDepth);
    BoxManual->position(-BoxWidth,  BoxHeight, BoxDepth);

	BoxManual->position(-BoxWidth, -BoxHeight, -BoxDepth);
    BoxManual->position( BoxWidth, -BoxHeight, -BoxDepth);
    BoxManual->position( BoxWidth,  BoxHeight, -BoxDepth);
    BoxManual->position(-BoxWidth,  BoxHeight, -BoxDepth);

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
    BoxNode = App->SBC_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	BoxNode->attachObject(BoxManual);

	BoxNode->setPosition(0,0,0);
	BoxNode->setVisible(false);
	return 1;
}
// *************************************************************************
// *	  	MarkerBB_Update:- Terry and Hazel Flanigan 2022				   *
// *************************************************************************
bool SB_Visuals::MarkerBB_Update(float Depth,float Height,float Width)
{
	BoxManual->beginUpdate(0);
	BoxManual->colour(0,1,0,0.5);

    BoxManual->position(-Depth, -Height, Width);
    BoxManual->position( Depth, -Height, Width);
    BoxManual->position( Depth,  Height, Width);
    BoxManual->position(-Depth,  Height, Width);
	BoxManual->position(-Depth, -Height, -Width);
    BoxManual->position( Depth, -Height, -Width);
    BoxManual->position( Depth,  Height, -Width);
    BoxManual->position(-Depth,  Height, -Width);

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
void SB_Visuals::MarkerBB_Addjust(int Index)
{

	Base_Object* Object = App->SBC_Scene->B_Object[Index];

	Ogre::Vector3 Position = Object->Object_Node->getPosition();
	Ogre::Quaternion Rot = Object->Object_Node->getOrientation();

	Ogre::Vector3 Size = App->SBC_Object->GetMesh_BB_Size(Object->Object_Node);
	MarkerBB_Update(Size.x/2,Size.y/2,Size.z/2);

	Ogre::Vector3 Centre = Object->Object_Node->getAttachedObject(0)->getBoundingBox().getCenter();
	Ogre::Vector3 WS = Object->Object_Node->convertLocalToWorldPosition(Centre);

	BoxNode->setPosition(WS);
	BoxNode->setOrientation(Rot);
	BoxNode->setVisible(true);

	App->SBC_Grid->Move_Arrow(WS);
}

