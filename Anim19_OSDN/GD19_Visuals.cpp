#include "StdAfx.h"
#include "GD19_App.h"
#include "GD19_Visuals.h"


GD19_Visuals::GD19_Visuals(void)
{
	mPickSight = NULL;
	BoxManual = NULL;
	BoxNode = NULL;
}


GD19_Visuals::~GD19_Visuals(void)
{
}

// *************************************************************************
// *					Load_PickSight (Terry Bernie)					   *
// *************************************************************************
void GD19_Visuals::Load_PickSight(void) // BERNIE_GUN_SIGHT
{
	mPickSight = OverlayManager::getSingleton().getByName("MyOverlays/PicksightOverlay");
	mPickSight->hide();
}

// *************************************************************************
// *	  				MarkerBB_Setup Terry Bernie						   *
// *************************************************************************
bool GD19_Visuals::MarkerBB_Setup(void)
{
	float BoxDepth=2.5;
	float BoxHeight=2.5;
	float BoxWidth=2.5;

	BoxManual = App->Cl19_Ogre->mSceneMgr->createManualObject("BB_Box");
	BoxManual->begin("BaseWhiteNoLighting", RenderOperation::OT_LINE_STRIP);
	//BoxManual->begin("BaseWhiteNoLighting", RenderOperation::OT_TRIANGLE_FAN);

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
    BoxNode = App->Cl19_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	BoxNode->attachObject(BoxManual);

	BoxNode->setPosition(0,0,0);
	BoxNode->setVisible(false);
	return 1;
}
// *************************************************************************
// *	  			MarkerBB_Update Terry Bernie						   *
// *************************************************************************
bool GD19_Visuals::MarkerBB_Update(float Depth,float Height,float Width)
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
// *	  				MarkerBB_Addjust Terry Bernie					   *
// *************************************************************************
void GD19_Visuals::MarkerBB_Addjust(int Index)
{

	Base_Object* Object = App->SBC_Scene->B_Object[Index];

	Ogre::Vector3 Position = Object->Object_Node->getPosition();
	Ogre::Quaternion Rot = Object->Object_Node->getOrientation();

	Ogre::Vector3 Size = App->Cl_Objects_Com->GetMesh_BB_Size(Object->Object_Node);
	MarkerBB_Update(Size.x/2,Size.y/2,Size.z/2);

	Ogre::Vector3 Centre = Object->Object_Node->getAttachedObject(0)->getBoundingBox().getCenter();
	Ogre::Vector3 WS = Object->Object_Node->convertLocalToWorldPosition(Centre);

	BoxNode->setPosition(WS);
	BoxNode->setOrientation(Rot);
	BoxNode->setVisible(true);

	//App->Cl_Grid->Move_Arrow(WS);
}
