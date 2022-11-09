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
#pragma once

#include "ExampleLoadingBar.h"
#include "OgreOverlaySystem.h"
#include "BT_PhysicsListener.h"

#include "ImguiManager.h"

//using namespace Noesis;

#define TERRAIN_FILE_PREFIX String("GDTest")
#define TERRAIN_FILE_SUFFIX String(".dat")
#define TERRAIN_SIZE 513

class GameDirectorOgre

{
public:
	GameDirectorOgre(void);
	~GameDirectorOgre(void);

	void InitOgre(void);
	bool createFrameListener(void);
	
	Ogre::Root *mRoot;
	Ogre::String mResourcePath;
	Ogre::SceneManager* mSceneMgr;
	Ogre::Camera*		mCamera;
	Ogre::Camera* mDummyCamera2;
	Ogre::Camera* PlacementCam;
	Ogre::RenderWindow* mWindow;

	Ogre::Terrain* mTerrain;
	Ogre::TerrainGlobalOptions* mTerrainGlobals;
	Ogre::Light* l;
	
	BT_PhysicsListener* PhysicsFrameListener;
	ExampleLoadingBar mLoadingBar;

	bool Full_Screen;
	Ogre::String PermResourceGroup;   // permanent Resource Group

	HWND WinHwnd;

protected:

	bool Configure(void);
	bool OgreCreateRoot(void);
	bool SetUpResources(void);
	bool chooseSceneManager(void);
	bool createCamera(void);
	bool loadResources(void);
	bool createViewports(void);
};
