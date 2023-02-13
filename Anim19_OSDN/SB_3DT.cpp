/*
Copyright (c) GameDirector 2019 Inflanite Software W.T.Flanigan H.C.Flanigan B.Parkin

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
#include "GD19_App.h"
#include "SB_3DT.h"


SB_3DT::SB_3DT()
{
	Pl_mDummyCamera = NULL;// App->SBC_Ogre->mSceneMgr->createCamera("ShootCamera");
	Pl_mDummyTranslateVector = Ogre::Vector3::ZERO;
	Selected_Entity_Index = 0;
	Selected_Object_Name[0] = 0;

	SndFile = NULL;
	timeUntilNextToggle = 1;
	DistanceToCollision = 0;
}


SB_3DT::~SB_3DT()
{
}

// *************************************************************************
// *				Fire:- Terry and Hazel Flanigan 2023			   	   *
// *************************************************************************
void SB_3DT::Fire(float deltaTime)
{
	
		char buff[1024];
		strcpy(buff, App->SBC_SoundMgr->Default_Folder);
		strcat(buff, "\\Media\\Sounds\\");

		strcat(buff, "richochet.ogg");

		SndFile = App->SBC_SoundMgr->SoundEngine->play2D(buff, false, true, true);
		SndFile->setVolume(1.0);
		SndFile->setIsPaused(false);

		DistanceToCollision = 0;

		Ogre::SceneNode* mNode;
		Vector3 oldPos = App->SBC_Ogre->mCamera->getPosition();
		Pl_mDummyCamera->setPosition(oldPos);

		Ogre::Quaternion Q;
		Q = App->SBC_Ogre->mCamera->getOrientation();

		Pl_mDummyCamera->setOrientation(Q);
		Pl_mDummyTranslateVector = Ogre::Vector3::ZERO;

		Pl_mDummyTranslateVector.z = -10000.0;
		Pl_mDummyCamera->moveRelative(Pl_mDummyTranslateVector);

		if (App->SBC_Ogre->OgreListener->mCollisionTools->collidesWithEntity(oldPos, Pl_mDummyCamera->getPosition(), 1.0f, 0, -1))
		{
			mNode = App->SBC_Ogre->OgreListener->mCollisionTools->pentity->getParentSceneNode();

			Pl_Entity_Name = App->SBC_Ogre->OgreListener->mCollisionTools->pentity->getName();

			DistanceToCollision = App->SBC_Ogre->OgreListener->mCollisionTools->distToColl;

			char buff[255];
			strcpy(buff, Pl_Entity_Name.c_str());

			App->CL_Vm_ImGui->Show_Object_Selection = 1;

			bool test = Ogre::StringUtil::match("Plane0", Pl_Entity_Name, true);
			if (test == 1)
			{
				Pl_Entity_Name = "---------";
			}
			else
			{
				bool test = Ogre::StringUtil::match("Player_1", Pl_Entity_Name, true);
				if (test == 1)
				{
					Pl_Entity_Name = "Player_1";

					return;
				}
				else
				{
					char* pdest;
					int IntNum = 0;
					char buffer[255];

					strcpy(buffer, Pl_Entity_Name.c_str());
					pdest = strstr(buffer, "GDEnt_");
					if (pdest != NULL)
					{
						sscanf((buffer + 6), "%i", &IntNum);

						App->SBC_Visuals->MarkerBB_Addjust(IntNum);
						Selected_Entity_Index = IntNum;
						strcpy(Selected_Object_Name, App->SBC_Scene->B_Object[IntNum]->Mesh_Name);
						return;

					}
				}

			}

		}
}
