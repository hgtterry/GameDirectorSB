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
#include "Base_Locations.h"
#include "Base_Counter.h"
#include "Base_Environment.h"

class SB_Scene
{
public:
	SB_Scene();
	~SB_Scene();

	void Zero_Pointers();
	bool Clear_Level();
	bool Create_Resources_Group();
	bool Delete_Resources_Group();
	bool Add_Resource_Location_Project(char* Resource_Location);
	void Reset_Counters();

	bool Game_Mode(void);
	bool Editor_Mode(void);
	void Go_FullScreen_Mode(void);
	bool Show_Entities(bool YesNo);

	Base_Object*			B_Object[100];
	Base_Player*			B_Player[20];
	Base_Area*				B_Area[20];
	Base_Camera*			B_Camera[20];
	Base_Locations*			B_Locations[20];
	Base_Counter*			B_Counter[20];
	
	bool Scene_Loaded;	// Is the Scene Loaded

	int Player_Count;		

	int Area_Count;			
	int UniqueID_Area_Count;

	int Camera_Count;		
		
	int Counters_Count;
	int UniqueID_Counters_Count;

	int MessageNew_Count;
	int UniqueID_MessageNew_Count;

	int Object_Count;		
	int UniqueID_Object_Counter;

	int Player_Location_Count;
	int Locations_ID_Counter;

	int CurrentCamMode;

	bool Player_Added;	// Is there a vaild player in the level [081221]
	bool Area_Added;	// Is there a vaild Area or Room [131221]
	bool Camera_Added;	// Is there a vaild Area or Room [131221]
	bool Objects_Added;
	bool Project_Resources_Created;
	bool Scene_Modified;

	bool GameMode_Flag;

	bool GameMode_Running_Flag;
	bool FullScreenMode_Flag;


	Ogre::String Project_Resource_Group;
	
protected:

	void Reset_Class();

};

