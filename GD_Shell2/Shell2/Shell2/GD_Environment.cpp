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
	float x = App->GDCL_Scene_Data->S_Scene[0]->AmbientColour.x;
	float y = App->GDCL_Scene_Data->S_Scene[0]->AmbientColour.y;
	float z = App->GDCL_Scene_Data->S_Scene[0]->AmbientColour.z;

	App->Ogre17->mSceneMgr->setAmbientLight(ColourValue(x,y,z));

	if (App->GDCL_Scene_Data->S_Scene[0]->Fog[0].FogOn == 1)
	{
		EnableFog();
	}
	else
	{
		App->Ogre17->mSceneMgr->setFog(FOG_NONE, ColourValue(0.7, 0.7, 0.8), 0, 100, 1000);
	}

	if (App->GDCL_Scene_Data->S_Scene[0]->Sky[0].Enabled == 1)
	{
		SetSky(1);
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
bool GD_Environment::EnableFog()
{

	float Start = App->GDCL_Scene_Data->S_Scene[0]->Fog[0].Start;
	float End = App->GDCL_Scene_Data->S_Scene[0]->Fog[0].End;
	float Density = App->GDCL_Scene_Data->S_Scene[0]->Fog[0].Density;

	//if (strcmp(App->GDCL_Scene_Data->S_Scene[0]->Fog[0].Mode,"FOG_LINEAR")==0)
	{
		float x = App->GDCL_Scene_Data->S_Scene[0]->Fog[0].Colour.x;
		float y = App->GDCL_Scene_Data->S_Scene[0]->Fog[0].Colour.y;
		float z = App->GDCL_Scene_Data->S_Scene[0]->Fog[0].Colour.z;

		App->Ogre17->mSceneMgr->setFog(FOG_LINEAR, ColourValue(x,y,z),Density,(Ogre::Real)Start,(Ogre::Real)End);
	}

	return 1;
}
