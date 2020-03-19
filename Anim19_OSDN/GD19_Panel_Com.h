/*
	Copyright (c) GD10 (GameDirector) 2019 Inflanite Software W.T.Flanigan H.C.Flanigan B.Parkin

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

#include "GD19_Panel.h"

// ------------------------ Player_Location_type
typedef struct Panel_Colour_Strt
{
	float Red;
	float Green;
	float Blue;

}Panel_Colour_Strt;

#define MAXPANELS 100

#pragma once
class GD19_Panel_Com
{
public:
	GD19_Panel_Com(void);
	~GD19_Panel_Com(void);

	void Zero_Pointers();
	bool Delete_All_Panels();
	int Create_Panel();

	char* Get_Panel_Name(int Slot);
	void Set_Panel_Name(char* New_Name, int Slot);

	char* Get_User_Text(int Slot);
	void Set_User_Text(char* User_Text, int Slot);

	int Get_Font_Size(int Slot);
	void Set_Font_Size(int Size,int Slot);

	void Get_Font_Name(int Slot);
	char Font_Name[256];

	Panel_Colour_Strt Get_Text_Colour(int Slot);
	void Set_Text_Colour(float Red, float Green, float Blue, int Slot);

	Ogre::Vector3 Get_Text_Position(int Slot);
	void Set_Text_Position(float x, float y, int Slot);

	Ogre::Vector3 Get_Panel_Position(int Slot);
	void Set_Panel_Position(float x, float y, int Slot);

	Ogre::Vector3 Get_Panel_Dimensions(int Slot);
	void Set_Panel_Dimensions(float Width, float Height, int Slot);

	void Show_Overlay(bool mShow, int Slot);

	GD19_Panel* CL_Panel[100];

	int Panel_Count;
};

