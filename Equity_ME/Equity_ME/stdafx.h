// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")

#if defined(_MSC_VER) && !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS
#endif

#pragma warning( disable : 4251 4193 4275 4005)
#pragma warning( disable : 4996)
#pragma warning( disable : 4305)
#pragma warning( disable : 4316) // Heap Alication
#pragma warning( disable : 4477) // format string

#pragma comment(lib, "legacy_stdio_definitions.lib")

//typedef unsigned long  uint32;

#include "targetver.h"

#define NOMINMAX
#include <windows.h>
//#include <Genesis.h>
//#include "btBulletDynamicsCommon.h"
// C RunTime Header Files
//#include <stdint.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <direct.h>
#include <Commctrl.h>   // includes the Common control header

#include "Ogre.h"
#include "OgreConfigFile.h"
#include "OgreStringConverter.h"
#include "OgreException.h"
#include "OgreTerrain.h"
#include "OgreTerrainGroup.h"
#include "OgreTerrainMaterialGeneratorA.h"
#include "OgreTextAreaOverlayElement.h"
#include "OgreBillboardParticleRenderer.h"
#include "OgreStringConverter.h"
#include "OgreDefaultHardwareBufferManager.h"
#include "OgreHardwareVertexBuffer.h"
#include "OgreVertexIndexData.h"
#include "OgreResourceGroupManager.h"
//#include "irrKlang.h"

#include <gl/gl.h>
#include <gl/glu.h>

//#include "Gen_Structures.h"

namespace Enums
{
	enum LoadedFile
	{
		LoadedFile_None = 0,
		LoadedFile_Actor = 1,
		LoadedFile_Assimp = 2,
		LoadedFile_Ogre = 3,
		LoadedFile_STL = 4
	};
}


#define Debug App->Say_Win("Debug");
//
//#define Func_DLog(...) App->Cl_ImGui->ImGui_Test_Log(__VA_ARGS__)
//
//
//#define  DLog(x) { if (App->FollowFunctions == 1) {App->Cl_ImGui->ImGui_Test_Log(x); }}
//
//// TODO: reference additional headers your program requires here