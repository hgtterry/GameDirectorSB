/*
Copyright (c) World_Viewer 2023 Inflanite Software W.T.Flanigan H.C.Flanigan

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

#include "WV_OgreListener.h"
#include "OgreOverlaySystem.h"
#include <OgreParticleSystem.h>
#include "ImguiManager.h"

//#include "GD_Bt_Render.h"

#include <chrono>

class WV_Ogre
{
public:
	WV_Ogre(void);
	~WV_Ogre(void);

	bool Ogre_Render_Loop(void);

	bool InitOgre(void);
	bool OgreCreateRoot(void);
	bool SetUpResources(void);
	bool Configure(void);
	bool chooseSceneManager(void);
	bool createCamera(void);
	bool Initialise_Resources(void);
	bool createViewports(void);
	bool createFrameListener(void);

	bool Get_Main_Folders();
	bool Get_Sub_Folders(char* Sub_folder);

	bool RenderFrame(void);

	bool Get_View_Height_Width(void);

	void GetVersion_OpenGL(char* buff);

	bool Block_RenderingQueued;


	HWND RenderHwnd;
	Ogre::Root* mRoot;
	Ogre::RenderWindow* mWindow;
	Ogre::SceneManager* mSceneMgr;
	Ogre::Camera* mCamera;
	Ogre::Camera* PlacementCam;
	Ogre::ManualObject *manObj;
	Ogre::SceneNode*	ModelNode;

	Ogre::Entity*		OgreModel_Ent;
	Ogre::SceneNode*	OgreModel_Node;

	Ogre::String mResourcePath;

	Ogre::String App_Resource_Group;		// App Resource Group
	
	Ogre::OverlaySystem *mOverlaySystem;

	//Ogre::Billboard* sunBillboard;

	WV_OgreListener*	OgreListener;

	//GD_Bt_Render*	BulletListener;

	OgreImGui  m_imgui;

	Ogre::Timer FPStimer;

	int Fps_Tick;

	int FPSLock;

	double PCFreq;
	_int64 CounterStart;
};

