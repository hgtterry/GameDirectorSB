/*
Copyright (c) 2022 Equity_ME Model Editor -- Inflanite Software W.T.Flanigan H.C.Flanigan

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

#include "stdafx.h"
#include "ME_App.h"
#include "ME_Ogre.h"


ME_Ogre::ME_Ogre()
{
	Ogre_Started = 0;
}


ME_Ogre::~ME_Ogre()
{
}

// *************************************************************************
// *						InitOgre Terry Bernie						   *
// *************************************************************************
bool ME_Ogre::Init_Ogre(void)
{
	//OgreCreateRoot();
	//SetUpResources();
	//Configure();
	//chooseSceneManager();
	//createCamera();
	//createViewports();
	//loadResources();

	//manObj = mSceneMgr->createManualObject("sampleArea");
	//ModelNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	//ModelNode->attachObject(manObj);

	//// Set Up Grid Functions
	//App->Cl_Grid->Grid_Update(1);
	//App->Cl_Grid->Hair_Update(1);

	//App->Cl_Grid->DummyNode = App->Cl19_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	//App->Cl_Visuals->Load_PickSight();
	//App->Cl_Grid->Load_Arrow();

	//m_imgui.Init(mSceneMgr, RenderHwnd);


	//createFrameListener();

	return 1;
}
