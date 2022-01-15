/*
Copyright (c) 2022 Equity_ME Model Editor -- Inflanite Software W.T.Flanigan H.C.Flanigan

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
#include "ME_App.h"
#include "ME_Grid.h"


ME_Grid::ME_Grid()
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

	ColourHairZ = Ogre::ColourValue(1, 0, 0, 1);
	ColourHairX = Ogre::ColourValue(0, 0, 1, 1);
	ColourHairY = Ogre::ColourValue(0, 1, 0, 1);
	ColourMain = Ogre::ColourValue(0.7, 0.7, 0, 0.6);
	ColourDivision = Ogre::ColourValue(1, 1, 1, 0.4);

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


ME_Grid::~ME_Grid()
{
}

// *************************************************************************
// *	  					Reset_Class Terry Bernie					   *
// *************************************************************************
void ME_Grid::Reset_Class()
{
	//App->SBC_Camera->Reset_View();
}

// *************************************************************************
// *	  					Grid_Update Terry Bernie					   *
// *************************************************************************
void ME_Grid::Load_Crosshair()
{
	Crosshair_Ent = App->CL_Ogre->mSceneMgr->createEntity("Crosshair", "axes.mesh", App->CL_Ogre->App_Resource_Group);
	Crosshair_Node = App->CL_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Crosshair_Node->attachObject(Crosshair_Ent);

	Crosshair_Node->setVisible(true);
	Crosshair_Node->setPosition(0, 0, 0);
	Crosshair_Node->setScale(1, 1, 1);
}
// *************************************************************************
// *	  					Grid_Update Terry Bernie					   *
// *************************************************************************
void ME_Grid::Grid_Update(bool Create)
{
	int i = 0;
	Ogre::Real r;

	if (Create == 1)
	{
		GridManual = App->CL_Ogre->mSceneMgr->createManualObject("BoxManual");
		GridManual->setRenderQueueGroup(1);
	}

	GridManual->clear();
	GridManual->begin("BaseWhiteAlphaBlended", Ogre::RenderOperation::OT_LINE_LIST);

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
					r = x + (1.0 / Ogre::Real(Division_X))*Ogre::Real(d);
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
					r = z + (1.0 / Ogre::Real(Division_Y))*Ogre::Real(d);
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
		GridNode = App->CL_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
		GridNode->attachObject(GridManual);
	}

	GridNode->setPosition(0, 0, 0);
	GridNode->setVisible(true);
	GridNode->setScale(Scale_X, Scale_Y, Scale_Z);
}
// *************************************************************************
// *	  					Hair_Update Terry Bernie					   *
// *************************************************************************
void ME_Grid::Hair_Update(bool Create)
{
	if (Create == 1)
	{
		HairManual = App->CL_Ogre->mSceneMgr->createManualObject("HairManual");
		HairManual->setRenderQueueGroup(5);
	}

	HairManual->clear();
	HairManual->begin("BaseWhiteAlphaBlended", Ogre::RenderOperation::OT_LINE_LIST);

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
		HairNode = App->CL_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
		HairNode->attachObject(HairManual);
	}

	HairNode->setPosition(0, 0, 0);
	HairNode->setVisible(true);
	HairNode->setScale(Scale_X, Scale_Y, Scale_Z);
}
// *************************************************************************
// *	  				Grid_SetVisiable Terry Bernie					   *
// *************************************************************************
void ME_Grid::Grid_SetVisible(bool Option)
{
	GridNode->setVisible(Option);
}
// *************************************************************************
// *	  				Hair_SetVisiable Terry Bernie					   *
// *************************************************************************
void ME_Grid::Hair_SetVisible(bool Option)
{
	HairNode->setVisible(Option);
}

// *************************************************************************
// *	  			Hair_DisplayGeneralCrossHair Terry Bernie			   *
// *************************************************************************
void ME_Grid::Hair_DisplayGeneralCrossHair(float x, float y, float z, bool Option)
{
	/*App->Cl_Ogre->RenderListener->Hair_1PosX = x;
	App->Cl_Ogre->RenderListener->Hair_1PosY = y;
	App->Cl_Ogre->RenderListener->Hair_1PosZ = z;*/
}

// *************************************************************************
// *	  					Load_Arrow Terry Bernie						   *
// *************************************************************************
void ME_Grid::Load_Arrow()
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
void ME_Grid::Move_Arrow(Ogre::Vector3 pos)
{
	Arrow_Node->setVisible(true);
	Arrow_Node->setPosition(pos);
}
