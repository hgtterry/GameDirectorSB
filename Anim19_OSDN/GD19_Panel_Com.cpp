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

#include "StdAfx.h"
#include "GD19_App.h"
#include "GD19_Panel_Com.h"

#pragma warning( disable : 4700)

GD19_Panel_Com::GD19_Panel_Com(void)
{
	Zero_Pointers();

	Panel_Count = 0;
	Font_Name[0] = 0;
}

GD19_Panel_Com::~GD19_Panel_Com(void)
{
}

// *************************************************************************
// *						Zero Pointers  Terry						   *
// *************************************************************************
void GD19_Panel_Com::Zero_Pointers()
{
	for (int x = 0; x < MAXPANELS; x++)
	{
		CL_Panel[x] = nullptr;
	}
}

// *************************************************************************
// *						Delete_All_Panels  Terry					   *
// *************************************************************************
bool GD19_Panel_Com::Delete_All_Panels()
{
	// delete all of the Panels in the list
	for (int x = 0; x < MAXPANELS; x++)
	{
		if (CL_Panel[x] != nullptr)
		{
			delete CL_Panel[x];
			CL_Panel[x] = nullptr;
		}
	}

	return false;
}

// *************************************************************************
// *							Create_Panel  Terry						   *
// *************************************************************************
int GD19_Panel_Com::Create_Panel()
{
	char OverlayName[256];
	char TextAreaName[256];
	char Name[256];
	char Num[256];

	_itoa(Panel_Count, Num, 10);

	strcpy(Name, "mPanel_");
	strcat(Name, Num);

	strcpy(TextAreaName, "mTextArea_");
	strcat(TextAreaName, Num);

	strcpy(OverlayName, "mOverlayName_");
	strcat(OverlayName, Num);

	if (CL_Panel[Panel_Count] != nullptr)
	{
		delete CL_Panel[Panel_Count];

		CL_Panel[Panel_Count] = nullptr;
		CL_Panel[Panel_Count] = new GD19_Panel(Name, OverlayName, TextAreaName);
	}
	else
	{
		CL_Panel[Panel_Count] = nullptr;
		CL_Panel[Panel_Count] = new GD19_Panel(Name, OverlayName, TextAreaName);
	}

	Panel_Count++;

	// Panel_Count is incremented and does not Exsist so -1 for return last created Panel
	return Panel_Count - 1;
}

// *************************************************************************
// *						Get_Panel_Name  Terry						   *
// *************************************************************************
char* GD19_Panel_Com::Get_Panel_Name(int Slot)
{
	return CL_Panel[Slot]->mPanel_Name;
}

// *************************************************************************
// *						Set_Panel_Name  Terry						   *
// *************************************************************************
void GD19_Panel_Com::Set_Panel_Name(char* New_Name,int Slot)
{
	strcpy(CL_Panel[Slot]->mPanel_Name, New_Name);
}


// *************************************************************************
// *						Get_User_Text  Terry						   *
// *************************************************************************
char* GD19_Panel_Com::Get_User_Text(int Slot)
{
	return CL_Panel[Slot]->mText;
}

// *************************************************************************
// *						Set_User_Text  Terry						   *
// *************************************************************************
void GD19_Panel_Com::Set_User_Text(char* User_Text,int Slot)
{
	strcpy(CL_Panel[Slot]->mText, User_Text);
	CL_Panel[Slot]->textArea->setCaption(User_Text);
}

// *************************************************************************
// *						Get_Font_Size  Terry						   *
// *************************************************************************
int GD19_Panel_Com::Get_Font_Size(int Slot)
{
	return CL_Panel[Slot]->Font_Size;
}

// *************************************************************************
// *						Set_Font_Size  Terry						   *
// *************************************************************************
void GD19_Panel_Com::Set_Font_Size(int Size, int Slot)
{
	CL_Panel[Slot]->Font_Size = Size;
	CL_Panel[Slot]->textArea->setCharHeight(Ogre::Real(Size));
}

// *************************************************************************
// *						Get_Text_Colour  Terry						   *
// *************************************************************************
Panel_Colour_Strt GD19_Panel_Com::Get_Text_Colour(int Slot)
{
	Panel_Colour_Strt Col;

	Col.Red = CL_Panel[Slot]->Red;
	Col.Green = CL_Panel[Slot]->Green;
	Col.Blue = CL_Panel[Slot]->Blue;

	return Col;
}

// *************************************************************************
// *						Get_Text_Colour  Terry						   *
// *************************************************************************
void GD19_Panel_Com::Set_Text_Colour(float Red, float Green, float Blue,int Slot)
{
	CL_Panel[Slot]->Red = Red;
	CL_Panel[Slot]->Green = Green;
	CL_Panel[Slot]->Blue = Blue;

	CL_Panel[Slot]->textArea->setColour(ColourValue(Red, Green, Blue));
}

// *************************************************************************
// *						Get_Font_Name  Terry						   *
// *************************************************************************
void GD19_Panel_Com::Get_Font_Name(int Slot)
{
	Font_Name[0] = 0;
	strcpy(Font_Name, CL_Panel[Slot]->mFont_Name);
	return ;
}

// *************************************************************************
// *					Get_Text_Position  Terry Bernie					   *
// *************************************************************************
Ogre::Vector3 GD19_Panel_Com::Get_Text_Position(int Slot)
{
	Ogre::Vector3 pos;

	pos.x = CL_Panel[Slot]->textArea->getLeft();
	pos.y = CL_Panel[Slot]->textArea->getTop();
	pos.z = 0;

	return pos;
}

// *************************************************************************
// *					Set_Text_Position  Terry Bernie					   *
// *************************************************************************
void GD19_Panel_Com::Set_Text_Position(float x,float y,int Slot)
{
	Ogre::Vector3 pos;

	CL_Panel[Slot]->textArea->setPosition(Ogre::Real(x), Ogre::Real(y));
	CL_Panel[Slot]->mText_Pos_X = x;
	CL_Panel[Slot]->mText_Pos_Y = y;
}

// *************************************************************************
// *					Get_Panel_Position  Terry Bernie				   *
// *************************************************************************
Ogre::Vector3 GD19_Panel_Com::Get_Panel_Position(int Slot)
{
	Ogre::Vector3 pos;

	pos.x = CL_Panel[Slot]->panel->getLeft();
	pos.y = CL_Panel[Slot]->panel->getTop();
	pos.z = 0;

	return pos;
}

// *************************************************************************
// *					Set_Panel_Position  Terry Bernie				   *
// *************************************************************************
void GD19_Panel_Com::Set_Panel_Position(float x, float y, int Slot)
{
	Ogre::Vector3 pos;

	CL_Panel[Slot]->panel->setPosition(Ogre::Real(x), Ogre::Real(y));
	CL_Panel[Slot]->mPanel_Pos_X = x;
	CL_Panel[Slot]->mPanel_Pos_Y = y;
}

// *************************************************************************
// *					Get_Panel_Dimensions  Terry Bernie				   *
// *************************************************************************
Ogre::Vector3 GD19_Panel_Com::Get_Panel_Dimensions(int Slot)
{
	Ogre::Vector3 pos;

	pos.x = CL_Panel[Slot]->panel->getWidth();
	pos.y = CL_Panel[Slot]->panel->getHeight();
	pos.z = 0;

	return pos;
}

// *************************************************************************
// *					Set_Panel_Dimensions  Terry Bernie				   *
// *************************************************************************
void GD19_Panel_Com::Set_Panel_Dimensions(float Width, float Height, int Slot)
{
	Ogre::Vector3 pos;

	CL_Panel[Slot]->panel->setDimensions(Ogre::Real(Width), Ogre::Real(Height));
	CL_Panel[Slot]->mPanel_Width = Width;
	CL_Panel[Slot]->mPanel_Height = Height;
}

// *************************************************************************
// *					Set_Panel_Dimensions  Terry Bernie				   *
// *************************************************************************
void GD19_Panel_Com::Show_Overlay(bool mShow, int Slot)
{
	if (mShow == 1)
	{
		CL_Panel[Slot]->overlay->show();
	}
	else
	{
		CL_Panel[Slot]->overlay->hide();
	}
}


