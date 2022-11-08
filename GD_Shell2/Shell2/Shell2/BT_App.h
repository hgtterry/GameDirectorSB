/*	
	Copyright (c) 2009 - 2013 W.T.Flanigan H.C.Flanigan and Bernard Parkin

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

#include "GameDirectorOgre.h"

#include "GD_Utilities.h"
#include "GD_BULLET.h"
#include "GD_Scene_Data.h"
#include "GD_SoundMgr.h"
#include "GD_Collision.h"

#include "GD_Add_Objects.h"
#include "GD_Environment.h"

#include "GD10_Load_Scene.h"
#include "GD10_Ini.h"

#include "SB_Player.h"
#include "SB_Aera.h"
#include "SB_Physics.h"
#include "SB_Object.h"

class BT_App
{
public:

	GameDirectorOgre *			Ogre17;

	GD_Utilities*				GDCL_Utilities;
	GD_BULLET*					GDCL_Bullet;
	GD_Scene_Data*				GDCL_Scene_Data;
	GD_SoundMgr*				GDCL_SoundMgr;
	GD_Collision*				GDCL_Collision;
	GD_Add_Objects*				GDCL_Add_Objects;
	GD_Environment*				GDCL_Environment;

	GD10_Load_Scene*			CL10_Load_Scene;
	GD10_Ini*					CL10_Ini;
	
	SB_Player*					SBC_Player;
	SB_Aera*					SBC_Aera;
	SB_Physics*					SBC_Physics;
	SB_Object*					SBC_Object;

	BT_App(void);
	~BT_App(void);

	bool DebugMessage(void);
	void Say(const char* Message);
	void Say_Int(int Value);

	bool InitApp(void);

	bool SetStructures(void);
	bool SetCamera(void);
	bool SetFlags(void);
	bool SetPlayerStructure(void);
	bool SetLoadOptions(void);
	bool SetScene(void);

	void Set_ObjectCount(int NewObjectCount);
	int GetObjectCount(void);

	int ObjectCount;
	int NewObjectID;

	bool DebugModeOn;

	char FileName[255];
	char Path_FileName[255];
	char LevelDirectory[1024];
	char GameDirecory_FullPath[1024];

	bool TestText;
	bool FullScreen;

	int ScreenHeight;
	int ScreenWidth;

	HWND MainHwnd;
	HWND WinHwnd;
	HCURSOR CUR;
};
extern BT_App *App;