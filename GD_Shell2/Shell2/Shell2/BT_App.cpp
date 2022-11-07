/*	
	Copyright (c) 2009 - 2013 W.T.Flanigan Bernard Parkin and H.C.Flanigan

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
#include "BT_App.h"

BT_App::BT_App(void)
{
	Ogre17 = NULL;

	strcpy(FileName," ");
	Path_FileName[0]=0;
	LevelDirectory[0]=0;
	DebugModeOn = 1;
	WinHwnd = NULL;
	MainHwnd = NULL;
	CUR = NULL;
	TestText = 0;
	FullScreen = 0;
	ObjectCount = 0;
	NewObjectID = NULL;

	GDCL_Player = NULL;
	GDCL_Utilities = NULL;
	GDCL_Bullet = NULL;
	GDCL_Scene_Data = NULL;
	GDCL_SoundMgr = NULL;
	GDCL_Collision = NULL;
	GDCL_Add_Objects = NULL;
	GDCL_Environment = NULL;

	CL10_Load_Scene = NULL;
	CL10_Ini = NULL;

	SBC_Aera = nullptr;
}

BT_App::~BT_App(void)
{
}
// *************************************************************************
// *					 	DebugMessage(Terry Bernie)			 	 	   *
// *************************************************************************
bool BT_App::DebugMessage(void)
{
	MessageBox(NULL,"Debug Test","Debug Test",MB_OK);
	return 1;
}

// *************************************************************************
// *									Say								   *
// *************************************************************************
void BT_App::Say(const char* Message)
{
	MessageBox(NULL,Message,"Equity Notice",MB_OK);
}

// *************************************************************************
// *								Say_Int								   *
// *************************************************************************
void BT_App::Say_Int(int Value)
{
	char buf[255];
	itoa(Value,buf,10);
	MessageBox(MainHwnd,buf,"Equity Notice",MB_OK);
}

// *************************************************************************
// *						InitApp Terry Bernie						   *
// *************************************************************************
bool BT_App::InitApp(void)
{
	Ogre17 =					new GameDirectorOgre();			
					
	GDCL_Utilities =			new GD_Utilities();
	GDCL_Player =				new GD_Player();
	GDCL_Bullet =				new GD_BULLET();
	GDCL_Scene_Data =			new GD_Scene_Data();
	GDCL_SoundMgr =				new GD_SoundMgr();
	GDCL_Add_Objects =			new GD_Add_Objects();
	GDCL_Environment =			new GD_Environment();	
	GDCL_Collision =			new GD_Collision();		

	CL10_Load_Scene =			new GD10_Load_Scene();		
	CL10_Ini =					new GD10_Ini();

	SBC_Aera =					new SB_Aera();
	return 1;
}
// *************************************************************************
// *					SetStructures Terry Bernie						   *
// *************************************************************************
bool BT_App::SetStructures(void)
{
	SetFlags();
	SetScene();
	SetLoadOptions();
	SetPlayerStructure();
	SetCamera();
	return 1;
}
// *************************************************************************
// *					SetCamera Terry Bernie							   *
// *************************************************************************
bool BT_App::SetCamera(void)
{
	/*S_Camera[0]->WalkSpeed=15;

	S_Camera[0]->PosX = 0;
	S_Camera[0]->PosY = 500;
	S_Camera[0]->PosZ = 0;

	S_Camera[0]->RotW=1;
	S_Camera[0]->RotX=0;
	S_Camera[0]->RotY=0;
	S_Camera[0]->RotZ=0;

	S_Camera[0]->RunSpeed = 16;
	S_Camera[0]->RunSpeed = 8;*/
	return 1;
}
// *************************************************************************
// *						SetFlags Terry Bernie						   *
// *************************************************************************
bool BT_App::SetFlags(void)
{
	//Flags[0]->RenderBackGround=0;		// Render Scene if a Dialog is open 
	//Flags[0]->SceneLoadedOnce=0;		// 
	//Flags[0]->OgreIsRunning=0;			// Ogre is running
	//Flags[0]->GameSpeedOn=0;
	//Flags[0]->FlyOn=0;
	//Flags[0]->RenderNxOgre=0;
	//Flags[0]->Save = 0;					// Flag if any thing has chaned in the Scene 
	//Flags[0]->CamDetached = 0;
	//Flags[0]->CamFirst = 1;
	//Flags[0]->CamThird = 0;
	//Flags[0]->CamLookAt = 0;
	//Flags[0]->MovePalyer = 0;
	//Flags[0]->MoveCamera = 1;
	//Flags[0]->StartScreen = 1;			// Start Screen is Active
	//Flags[0]->GameMode = 0;				// Are we in Game Mode
	//Flags[0]->PosEitorActive = 0;		// Position Editor is Active
	//Flags[0]->SaveScene = 0;			// Flag to save the scene if altered
	//Flags[0]->ShowOgreDebug = 0;		// Show Ogre debug stuff fps etc
	//Flags[0]->PosEditorScale = 0;		// The Object Scale function is active
	//Flags[0]->StopKeys = 0;				// Stop wasd keys moving CC if dialog is open
	//Flags[0]->StopCapture = 0;			// Stop Ogre window gaining controll

	//Flags[0]->FileView_SceneLoaded = 0;
	//Flags[0]->ShowContactReport = 0;

	//Flags[0]->Show_VRD_Editor = 0;
	//Flags[0]->Show_VRD_Shape = 0;
	//Flags[0]->VRD_HideMesh = 0;
	//Flags[0]->SceneAltered = 0;
	//Flags[0]->ShowMarker = 1;

	return 1;
}
// *************************************************************************
// *					SetPlayerStructure Terry Bernie					   *
// *************************************************************************
bool BT_App::SetPlayerStructure(void)
{
	/*strcpy(S_Player[0]->Name,"Charlie");
	S_Player[0]->PlayerMode = Enums::CamFirst;
	S_Player[0]->MaxGroundSpeed = 35;
	S_Player[0]->StepOffset = 0.25;
	S_Player[0]->mSlopeLimit = 0.707;
	S_Player[0]->Sharpness = 0.0;
	S_Player[0]->JumpHeight = 0.5;
	S_Player[0]->TurnRate = 0.03;
	S_Player[0]->PlayerPoseY = -3.4;*/
	return 1;
}
// *************************************************************************
// *						SetLoadOptions Terry Bernie					   *
// *************************************************************************
bool BT_App::SetLoadOptions(void)
{
	/*S_LoadOptions[0]->Has_Objects=0;
	S_LoadOptions[0]->Has_Particles=0;
	S_LoadOptions[0]->Has_Planes=0;
	S_LoadOptions[0]->Has_Weapons=0;
	S_LoadOptions[0]->Has_CC=0;
	S_LoadOptions[0]->Has_Debug=0;*/
	return 1;
}
// *************************************************************************
// *						SetScene Terry Bernie						   *
// *************************************************************************
bool BT_App::SetScene(void)
{
	/*S_Scene[0]->SceneType = 0;
	S_Scene[0]->LastSceneType = 0;
	S_Scene[0]->CompositeMapDistance=8000;
	S_Scene[0]->PlaneCount=0;
	S_Scene[0]->Fog[0].FogOn=0;

	S_Scene[0]->AmbientColour.x=1;
	S_Scene[0]->AmbientColour.y=1;
	S_Scene[0]->AmbientColour.z=1;

	S_Scene[0]->DiffuseColour.x=0;
	S_Scene[0]->DiffuseColour.y=0;
	S_Scene[0]->DiffuseColour.z=0;

	S_Scene[0]->SpecularColour.x=0;
	S_Scene[0]->SpecularColour.y=0;
	S_Scene[0]->SpecularColour.z=0;

	strcpy(S_Scene[0]->Sound[0].SoundFile,"None");
	S_Scene[0]->Sound[0].Volume = 1;
	S_Scene[0]->Sound[0].Loop = 1;
	S_Scene[0]->Sound[0].Is3D = 0;
	S_Scene[0]->Sound[0].Pan = 0;
	S_Scene[0]->Sound[0].Data0 = 0;
	S_Scene[0]->Sound[0].Data1 = 0;
	S_Scene[0]->Sound[0].SndFile = NULL;*/

	return 1;
}


// *************************************************************************
// *	  				Set_ObjectCount Terry Bernie				   *
// *************************************************************************
void BT_App::Set_ObjectCount(int NewObjectCount)
{
	ObjectCount = NewObjectCount;
}
// *************************************************************************
// *	  				GetObjectCount Terry Bernie						   *
// *************************************************************************
int BT_App::GetObjectCount(void)
{
	return ObjectCount;
}