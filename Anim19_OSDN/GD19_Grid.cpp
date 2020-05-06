/*
Copyright (c) GameDirector 2019 Inflanite Software W.T.Flanigan H.C.Flanigan B.Parkin

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
#include "GD19_Grid.h"
#include <process.h>

#pragma warning( disable : 4244 4305)


GD19_Grid::GD19_Grid(void)
{
	GridManual = NULL;
	GridNode = NULL;

	HairManual = NULL;
	HairNode = NULL;

	DummyNode = NULL;

	Crosshair_Ent = NULL;
	Crosshair_Node = NULL;

	Arrow_Ent = NULL;
	Arrow_Node = NULL;

	Selection_Ent = NULL;
	Selection_Node = NULL;

	ColourHairZ = ColourValue(1, 0, 0, 1);
	ColourHairX = ColourValue(0, 0, 1, 1);
	ColourHairY = ColourValue(0, 1, 0, 1);
	ColourMain = ColourValue(0.7, 0.7, 0, 0.6);
	ColourDivision = ColourValue(1, 1, 1, 0.4);

	YAxis_min = -8;
	YAxis_max = 8;

	ZAxis_min = -8;
	ZAxis_max = 8;

	XAxis_min = -8;
	XAxis_max = 8;

	HairExtend = 8;

	Division_X = 2;
	Division_Y = 2;
	Division_Z = 2;

	Scale_X = 4;
	Scale_Y = 4;
	Scale_Z = 4;

	ShowGridFlag = 1;
	ShowDivisions = 1;
	ShowHair = 1;
}


GD19_Grid::~GD19_Grid(void)
{
}

// *************************************************************************
// *	  					Reset_Class Terry Bernie					   *
// *************************************************************************
void GD19_Grid::Reset_Class()
{
	Reset_View();
}

// *************************************************************************
// *	  					Grid_Update Terry Bernie					   *
// *************************************************************************
void GD19_Grid::Load_Crosshair()
{
	Crosshair_Ent = App->Cl19_Ogre->mSceneMgr->createEntity("Crosshair", "axes.mesh", App->Cl19_Ogre->PermResourceGroup);
	Crosshair_Node = App->Cl19_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Crosshair_Node->attachObject(Crosshair_Ent);

	Crosshair_Node->setVisible(true);
	Crosshair_Node->setPosition(0, 0, 0);
	Crosshair_Node->setScale(1, 1, 1);
}
// *************************************************************************
// *	  					Grid_Update Terry Bernie					   *
// *************************************************************************
void GD19_Grid::Grid_Update(bool Create)
{
	int i = 0;
	Real r;

	if (Create == 1)
	{
		GridManual = App->Cl19_Ogre->mSceneMgr->createManualObject("BoxManual");
		GridManual->setRenderQueueGroup(1);
	}

	GridManual->clear();
	GridManual->begin("BaseWhiteAlphaBlended", RenderOperation::OT_LINE_LIST);

	if (ShowGridFlag == 1)
	{
		for (int x = XAxis_min; x <= XAxis_max; ++x)
		{
			GridManual->position(x, 0, ZAxis_min);
			GridManual->colour(ColourMain);
			GridManual->position(x, 0, ZAxis_max);
			GridManual->colour(ColourMain);
			if (x < XAxis_max && ShowDivisions == 1)
			{
				for (int d = 0; d < Division_X; ++d)
				{
					r = x + (1.0 / Real(Division_X))*Real(d);
					GridManual->position(r, 0, ZAxis_min);
					GridManual->colour(ColourDivision);
					GridManual->position(r, 0, ZAxis_max);
					GridManual->colour(ColourDivision);
				}
			}
		}

		for (int z = ZAxis_min; z <= ZAxis_max; ++z)
		{
			GridManual->position(Ogre::Vector3(XAxis_min, 0, z));
			GridManual->colour(ColourMain);
			GridManual->position(Ogre::Vector3(XAxis_max, 0, z));
			GridManual->colour(ColourMain);
			if (z < ZAxis_max && ShowDivisions == 1)
			{
				for (int d = 1; d < Division_Y; ++d)
				{
					r = z + (1.0 / Real(Division_Y))*Real(d);
					GridManual->position(XAxis_min, 0, r);
					GridManual->colour(ColourDivision);
					GridManual->position(XAxis_max, 0, r);
					GridManual->colour(ColourDivision);
				}
			}
		}
	}

	
	GridManual->end();

	if (Create == 1)
	{
		GridNode = App->Cl19_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
		GridNode->attachObject(GridManual);
	}

	GridNode->setPosition(0, 0, 0);
	GridNode->setVisible(true);
	GridNode->setScale(Scale_X, Scale_Y, Scale_Z);
}
// *************************************************************************
// *	  					Hair_Update Terry Bernie					   *
// *************************************************************************
void GD19_Grid::Hair_Update(bool Create)
{
	if (Create == 1)
	{
		HairManual = App->Cl19_Ogre->mSceneMgr->createManualObject("HairManual");
		HairManual->setRenderQueueGroup(5);
	}

	HairManual->clear();
	HairManual->begin("BaseWhiteAlphaBlended", RenderOperation::OT_LINE_LIST);

	// X Axis
	HairManual->position(Ogre::Vector3(YAxis_min - HairExtend, 0, 0));
	HairManual->colour(ColourHairX);
	HairManual->position(Ogre::Vector3(YAxis_max + HairExtend, 0, 0));
	HairManual->colour(ColourHairX);
	// Y Axis
	HairManual->position(Ogre::Vector3(0, YAxis_min - HairExtend, 0));
	HairManual->colour(ColourHairY);
	HairManual->position(Ogre::Vector3(0, YAxis_max + HairExtend, 0));
	HairManual->colour(ColourHairY);
	// Z Axis
	HairManual->position(Ogre::Vector3(0, 0, ZAxis_min - HairExtend));
	HairManual->colour(ColourHairZ);
	HairManual->position(Ogre::Vector3(0, 0, ZAxis_max + HairExtend));
	HairManual->colour(ColourHairZ);

	HairManual->end();

	if (Create == 1)
	{
		HairNode = App->Cl19_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
		HairNode->attachObject(HairManual);
	}

	HairNode->setPosition(0, 0, 0);
	HairNode->setVisible(true);
	HairNode->setScale(Scale_X, Scale_Y, Scale_Z);
}
// *************************************************************************
// *	  				Grid_SetVisiable Terry Bernie					   *
// *************************************************************************
void GD19_Grid::Grid_SetVisible(bool Option)
{
	GridNode->setVisible(Option);
}
// *************************************************************************
// *	  				Hair_SetVisiable Terry Bernie					   *
// *************************************************************************
void GD19_Grid::Hair_SetVisible(bool Option)
{
	HairNode->setVisible(Option);
}

// *************************************************************************
// *	  				Reset_View Terry Bernie							   *
// *************************************************************************
void GD19_Grid::Reset_View(void)
{
	GridNode->setPosition(0, 0, 0);
	GridNode->resetOrientation();

	HairNode->setPosition(0, 0, 0);
	HairNode->resetOrientation();

	App->Cl19_Ogre->RenderListener->RX = 0;
	App->Cl19_Ogre->RenderListener->RZ = 0;

	App->Cl19_Ogre->mCamera->setPosition(Ogre::Vector3(0, 90, 100));
	App->Cl19_Ogre->mCamera->lookAt(Ogre::Vector3(0, 30, 0));

	//Zoom();

}

// *************************************************************************
// *				Zoom   Terry Bernie								   *
// *************************************************************************
void GD19_Grid::Zoom(void)
{
	if (App->CL_Vm_Model->Model_Loaded == 1)
	{
		App->Cl_Grid->Reset_View();
		App->Cl19_Ogre->mCamera->setPosition(App->CL_Vm_Model->S_BoundingBox[0]->Centre[0].x, App->CL_Vm_Model->S_BoundingBox[0]->Centre[0].y, App->CL_Vm_Model->S_BoundingBox[0]->Centre[0].z);

		Ogre::Vector3 Move;
		Move.x = 0;
		Move.y = 0;//App->CL_Model_Data->S_BoundingBox[0]->Size[0].y;
				   //Move.z = App->CL_Model_Data->S_BoundingBox[0]->Size[0].y*2;

		if (App->CL_Vm_Model->S_BoundingBox[0]->Size[0].z > App->CL_Vm_Model->S_BoundingBox[0]->Size[0].y)
		{
			Move.z = App->CL_Vm_Model->S_BoundingBox[0]->Size[0].z * 2;
		}
		else
		{
			Move.z = App->CL_Vm_Model->S_BoundingBox[0]->Size[0].y * 2;
		}

		App->Cl19_Ogre->mCamera->moveRelative(Move);
	}

}

// *************************************************************************
// *	  			Hair_DisplayGeneralCrossHair Terry Bernie			   *
// *************************************************************************
void GD19_Grid::Hair_DisplayGeneralCrossHair(float x, float y, float z, bool Option)
{
	/*App->Cl_Ogre->RenderListener->Hair_1PosX = x;
	App->Cl_Ogre->RenderListener->Hair_1PosY = y;
	App->Cl_Ogre->RenderListener->Hair_1PosZ = z;*/
}

// *************************************************************************
// *	  					Load_Arrow Terry Bernie						   *
// *************************************************************************
void GD19_Grid::Load_Arrow()
{
	/*Arrow_Ent = App->Cl19_Ogre->mSceneMgr->createEntity("Arrow", "Gizmo.mesh", App->Cl19_Ogre->PermResourceGroup);
	Arrow_Node = App->Cl19_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Arrow_Node->attachObject(Arrow_Ent);

	Arrow_Node->setVisible(false);
	Arrow_Node->setPosition(0, 0, 0);
	Arrow_Node->setScale(7, 7, 7);*/

	/*Ogre::MaterialPtr materialPtr = Ogre::MaterialManager::getSingleton().getByName("BaseYellowLine");
	Arrow_Ent->setMaterial(materialPtr);*/
}

// *************************************************************************
// *	  					Move_ArrowTerry Bernie						   *
// *************************************************************************
void GD19_Grid::Move_Arrow(Ogre::Vector3 pos)
{
	Arrow_Node->setVisible(true);
	Arrow_Node->setPosition(pos);
}


