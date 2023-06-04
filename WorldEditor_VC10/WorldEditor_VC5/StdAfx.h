/****************************************************************************************/
/*  StdAfx.h                                                                            */
/*                                                                                      */
/*  Author:       Jim Mischel, Ken Baird, Jeff Lomax                                    */
/*  Description:  Genesis world editor header file                                      */
/*                                                                                      */
/*  The contents of this file are subject to the Genesis3D Public License               */
/*  Version 1.01 (the "License"); you may not use this file except in                   */
/*  compliance with the License. You may obtain a copy of the License at                */
/*  http://www.genesis3d.com                                                            */
/*                                                                                      */
/*  Software distributed under the License is distributed on an "AS IS"                 */
/*  basis, WITHOUT WARRANTY OF ANY KIND, either express or implied.  See                */
/*  the License for the specific language governing rights and limitations              */
/*  under the License.                                                                  */
/*                                                                                      */
/*  The Original Code is Genesis3D, released March 25, 1999.                            */
/*  Copyright (C) 1996-1999 Eclipse Entertainment, L.L.C. All Rights Reserved           */
/*                                                                                      */
/****************************************************************************************/
// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//
#ifndef STDAFX_H
#define STDAFX_H

#define WINVER 0x0500

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

/*
  Disable warnings for Windows headers
	4201 - nonstandard extension used : nameless struct/union
	4214 - nonstandard extension used : bit field types other than int
	4115 - 'type' : named type definition in parentheses
	4514 - unreferenced inline/local function has been removed
*/
#pragma warning(disable : 4201 4214 4115 4514 4711 4505)

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxtempl.h>		// Support for templates.

#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows 95 Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

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

namespace Enums
{
	enum Camera
	{
		CamNone = 0,
		CamFirst = 1,
		CamDetached = 2,
		CamThird = 3,
		CamModel = 4
	};
}
// re-enable warnings except 4514
#pragma warning(default : 4201 4214 4115)

#define Debug MessageBox(NULL,"Here","Message",MB_OK);

#endif
