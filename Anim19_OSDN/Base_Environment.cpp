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

#include "stdafx.h"
#include "GD19_App.h"
#include "Base_Environment.h"

Base_Environment::Base_Environment()
{
	Set_Environment_Defaults();
}

Base_Environment::~Base_Environment()
{
}

// *************************************************************************
// *	  	Set_Environment_Defaults:- Terry and Hazel Flanigan 2022	   *
// *************************************************************************
void Base_Environment::Set_Environment_Defaults()
{
	Deleted = 0;
	Altered = 0;

	FileViewItem = nullptr;
	This_Object_UniqueID = 0;
	strcpy(Name, "Not_Set");

	//----------------------- Sound
	strcpy(Sound_File, "The_Sun.ogg");
	SndFile = NULL;
	Play = 0;
	Loop = 1;
	SndVolume = 0.5;

	//----------------------- Light
	AmbientColour.x = 1;
	AmbientColour.y = 1;
	AmbientColour.z = 1;

	DiffuseColour.x = 0;
	DiffuseColour.y = 0;
	DiffuseColour.z = 0;

	SpecularColour.x = 0;
	SpecularColour.y = 0;
	SpecularColour.z = 0;

	Light_Position.x = 0;
	Light_Position.y = 0;
	Light_Position.z = 0;

	// Sky
	Curvature = 15;
	Distance = 4000;
	Enabled = 0;
	strcpy(Material, "Examples/CloudySky");
	Tiling = 15;
	type = 1;

	// Fog
	Fog_On = 0;
	Fog_Mode = FOG_LINEAR;
	Fog_Density = 0.001000;
	Fog_Start = 50;
	Fog_End = 300;
	Fog_Colour = Ogre::Vector3(1, 1, 1);
}
