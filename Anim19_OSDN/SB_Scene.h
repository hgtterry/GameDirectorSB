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

#pragma once

#include "Base_Player.h"
#include "Base_Area.h"
#include "Base_Object.h"
#include "Base_Camera.h"

class SB_Scene
{
public:
	SB_Scene();
	~SB_Scene();

	bool Clear_Level();
	bool Create_Resources_Group();
	bool Delete_Resources_Group();
	bool Add_Resource_Location_Project(char* Resource_Location);
	
	bool Game_Mode(void);
	bool Editor_Mode(void);
	bool Show_Entities(bool YesNo);

	Base_Player*			SBC_Base_Player[100];
	Base_Area*				SBC_Base_Area[100];
	Base_Object*			B_Object[100];
	Base_Camera*			B_Camera[20];

	bool Scene_Loaded;	// Is the Scene Loaded [131221]

	int Player_Count;		// Actual Player Count Zero Based
	int Area_Count;			// Actual Area Count Zero Based [161221]
	int Object_Count;		// Actual Object Count Zero Based [171221]
	int Camera_Count;		// Actual Object Count Zero Based [171221]
	int Entity_Count;		// Actual Object Count Zero Based [171221]

	bool Player_Added;	// Is there a vaild player in the level [081221]
	bool Area_Added;	// Is there a vaild Area or Room [131221]
	bool Camera_Added;	// Is there a vaild Area or Room [131221]
	bool Objects_Added;

	bool Scene_Modified;

	Ogre::String Project_Resource_Group;
	
protected:

	void Reset_Class();

	int CurrentCamMode;
};

