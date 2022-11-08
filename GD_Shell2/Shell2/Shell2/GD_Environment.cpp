#include "StdAfx.h"
#include "BT_App.h"
#include "GD_Environment.h"


GD_Environment::GD_Environment(void)
{
}


GD_Environment::~GD_Environment(void)
{
}

// *************************************************************************
// *				Load_Environment  Terry Bernie						   *
// *************************************************************************
void GD_Environment::Load_Environment(void)
{
	float x = App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->AmbientColour.x;
	float y = App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->AmbientColour.y;
	float z = App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->AmbientColour.z;

	App->Ogre17->mSceneMgr->setAmbientLight(ColourValue(x, y, z));

	if (App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->Fog_On == 1)
	{
		EnableFog(true);
	}
	else
	{
		App->Ogre17->mSceneMgr->setFog(FOG_NONE, ColourValue(0.7, 0.7, 0.8), 0, 100, 1000);
	}
}

// *************************************************************************
// *	  					SetSky Terry Bernie							   *
// *************************************************************************
void GD_Environment::SetSky(bool Enable)
{
	App->Ogre17->mSceneMgr->setSkyDome(Enable,
	App->GDCL_Scene_Data->S_Scene[0]->Sky[0].Material,
	App->GDCL_Scene_Data->S_Scene[0]->Sky[0].Curvature,
	App->GDCL_Scene_Data->S_Scene[0]->Sky[0].Tiling,
	App->GDCL_Scene_Data->S_Scene[0]->Sky[0].Distance);
}

// *************************************************************************
// *	  				  EnableFog	Terry Bernie						   *
// *************************************************************************
bool GD_Environment::EnableFog(bool SetFog)
{
	if (SetFog == true)
	{
		float Start = App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->Fog_Start;
		float End = App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->Fog_End;
		float Density = App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->Fog_Density;

		float x = App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->Fog_Colour.x;
		float y = App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->Fog_Colour.y;
		float z = App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->Fog_Colour.z;

		App->Ogre17->mSceneMgr->setFog(FOG_LINEAR, ColourValue(x, y, z), Density, (Ogre::Real)Start, (Ogre::Real)End);
	}
	else
	{
		App->Ogre17->mSceneMgr->setFog(FOG_NONE, ColourValue(0.7, 0.7, 0.8), 0, 100, 1000);
	}

	return 1;
}
