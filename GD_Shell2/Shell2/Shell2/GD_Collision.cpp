#include "StdAfx.h"
#include "BT_App.h"
#include "GD_Collision.h"


GD_Collision::GD_Collision(void)
{
	ObjectIndex = 0;
	DoMove = 0;

	FinalPosition = 0;

	x = 0;
	y = 0;
	z = 0;

	px = 0;
	py = 0;
	pz = 0;
}


GD_Collision::~GD_Collision(void)
{
}

// *************************************************************************
// *						Sound_Entity Terry Bernie					   *
// *************************************************************************
bool GD_Collision::Sound_Entity(int Index)
{
	if (App->GDCL_Scene_Data->S_Object[Index]->Re_Trigger == false && App->GDCL_Scene_Data->S_Object[Index]->Triggered == 1) // Retrigger Yes No
	{
		return 1;
	}

	if (App->GDCL_Scene_Data->S_Object[Index]->Triggered == 1) // Retrigger Yes No
	{
		return 1;
	}

	Play_Sound(Index);
	
	return 1;
}

// *************************************************************************
// *						Do_Collectable Terry Bernie					   *
// *************************************************************************
bool GD_Collision::Do_Collectable(int Index)
{
	App->GDCL_Scene_Data->S_Object[Index]->OgreEntity->setVisible(0);
	App->GDCL_Scene_Data->S_Object[Index]->OgreNode->setPosition(100, 100, 100);
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->getWorldTransform().setOrigin(btVector3(100, 100, 100));

	Play_Sound(Index);

	return 1;
}

// *************************************************************************
// *						Do_Teleport Terry Bernie					   *
// *************************************************************************
bool GD_Collision::Do_Teleport(int Index)
{
	/*App->GDCL_Player->Player_Node->setPosition(App->GDCL_Scene_Data->S_Object[Index]->S_Teleport[0]->Player_Position);
	App->GDCL_Player->mObject->getWorldTransform().setOrigin(App->GDCL_Scene_Data->S_Object[Index]->S_Teleport[0]->Physics_Position);
	App->GDCL_Player->mObject->getWorldTransform().setRotation(App->GDCL_Scene_Data->S_Object[Index]->S_Teleport[0]->Physics_Rotation);

	Play_Sound(Index);*/
	

	return 1;
}


// *************************************************************************
// *						Message_Entity Terry Bernie					   *
// *************************************************************************
bool GD_Collision::Message_Entity(int Index)
{
	if (App->GDCL_Scene_Data->S_Object[Index]->Re_Trigger == false && App->GDCL_Scene_Data->S_Object[Index]->Triggered == 1) // Retrigger Yes No
	{
		return 1;
	}

	if (App->GDCL_Scene_Data->S_Object[Index]->Triggered == 1) // Retrigger Yes No
	{
		return 1;
	}
	

	
	int result = 0;
	result = strcmp(App->GDCL_Scene_Data->S_Object[Index]->Entity[0].mTextItem, "None");
	if (result != 0)
	{
		
		int Stock_Index = App->GDCL_Scene_Data->S_Object[Index]->Entity[0].Stock_mIndex;
		App->GDCL_Scene_Data->S_Messages[Stock_Index]->textArea1->setCaption(App->GDCL_Scene_Data->S_Object[Index]->Entity[0].mTextItem);
		App->GDCL_Scene_Data->S_Messages[Stock_Index]->overlay->show();
		
		App->GDCL_Scene_Data->S_Object[Index]->Triggered = 1;
	}
	
	return 1;
}

// *************************************************************************
// *						Move_Entity Terry Bernie					   *
// *************************************************************************
bool GD_Collision::Move_Entity(int Index)
{
	//if (App->GDCL_Scene_Data->S_Object[Index]->Triggered == 1) // Retrigger Yes No
	//{
	//	return 1;
	//}

	//App->GDCL_Scene_Data->S_Object[Index]->Triggered = 1;

	//Ogre::Vector3 M_Pos;
	//Ogre::Vector3 P_Pos;
	//ObjectIndex = Index;

	//int ObjectToMove = App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->Object_Index;

	//M_Pos = App->GDCL_Scene_Data->S_Object[ObjectToMove]->Mesh_Pos;
	//P_Pos = App->GDCL_Scene_Data->S_Object[ObjectToMove]->Physics_Pos;

	//App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->MeshPos  = Ogre::Vector3(M_Pos);
	//App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->PhysicsPos = Ogre::Vector3(P_Pos);

	//x = App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->MeshPos.x;
	//y = App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->MeshPos.y;
	//z = App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->MeshPos.z;

	//px = App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->PhysicsPos.x;
	//py = App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->PhysicsPos.y;
	//pz = App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->PhysicsPos.z;

	//if (App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->WhatDirection == Enums::Axis_x)
	//{
	//	FinalPosition = x + App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->Distance;
	//}

	//if (App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->WhatDirection == Enums::Axis_y)
	//{
	//	FinalPosition = y + App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->Distance;
	//}

	//if (App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->WhatDirection == Enums::Axis_z)
	//{
	//	FinalPosition = z + App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->Distance;
	//}

	//Play_Sound(Index);

	//DoMove  = 1; // Trigger Ogre Listener to update
	
	return 1;
}

// *************************************************************************
// *					MoveObject (Terry Bernie)						   *
// *************************************************************************
void GD_Collision::MoveObject(Ogre::Real Time)
{

	//// X Axis
	//if (App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->WhatDirection == Enums::Axis_x)
	//{

	//	if (App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->IsNegative == false)
	//	{
	//		int ObjectToMove = App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->Object_Index;

	//		App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->MeshPos.x += App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->Speed * Time;
	//		App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->PhysicsPos.x += App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->Speed * Time;

	//		x = App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->MeshPos.x;
	//		px = App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->PhysicsPos.x;

	//		App->GDCL_Scene_Data->S_Object[ObjectToMove]->OgreNode->setPosition(x,y,z);
	//		App->GDCL_Scene_Data->S_Object[ObjectToMove]->bt_body->getWorldTransform().setOrigin(btVector3(px,py,pz));

	//		if(App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->MeshPos.x > FinalPosition)
	//		{

	//			/*App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_Sounds[0]->SndFile->stop();
	//			App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_Sounds[0]->SndFile->drop();
	//			App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_Sounds[0]->SndFile = NULL;*/

	//			DoMove = 0; // Stop Listener
	//		}

	//		return;
	//	}	
	//	else
	//	{
	//		int ObjectToMove = App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->Object_Index;

	//		App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->MeshPos.x -= App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->Speed * Time;
	//		App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->PhysicsPos.x -= App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->Speed * Time;

	//		x = App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->MeshPos.x;
	//		px = App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->PhysicsPos.x;

	//		App->GDCL_Scene_Data->S_Object[ObjectToMove]->OgreNode->setPosition(x,y,z);
	//		App->GDCL_Scene_Data->S_Object[ObjectToMove]->bt_body->getWorldTransform().setOrigin(btVector3(px,py,pz));

	//		if(App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->MeshPos.x < FinalPosition)
	//		{
	//			/*App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_Sounds[0]->SndFile->stop();
	//			App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_Sounds[0]->SndFile->drop();
	//			App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_Sounds[0]->SndFile = NULL;*/

	//			DoMove = 0; // Stop Listener
	//		}

	//		return;
	//	}
	//}

	//// Y Axis
	//if (App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->WhatDirection == Enums::Axis_y)
	//{
	//	if (App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->IsNegative == false)
	//	{
	//		int ObjectToMove = App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->Object_Index;

	//		App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->MeshPos.y += App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->Speed * Time;
	//		App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->PhysicsPos.y += App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->Speed * Time;

	//		y = App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->MeshPos.y;
	//		py = App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->PhysicsPos.y;

	//		App->GDCL_Scene_Data->S_Object[ObjectToMove]->OgreNode->setPosition(x,y,z);
	//		App->GDCL_Scene_Data->S_Object[ObjectToMove]->bt_body->getWorldTransform().setOrigin(btVector3(px,py,pz));

	//		if(App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->MeshPos.y > FinalPosition)
	//		{
	//			/*App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_Sounds[0]->SndFile->stop();
	//			App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_Sounds[0]->SndFile->drop();
	//			App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_Sounds[0]->SndFile = NULL;*/

	//			DoMove = 0; // Stop Listener
	//		}

	//		return;
	//	}	
	//	else
	//	{
	//		int ObjectToMove = App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->Object_Index;

	//		App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->MeshPos.y -= App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->Speed * Time;
	//		App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->PhysicsPos.y -= App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->Speed * Time;

	//		y = App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->MeshPos.y;
	//		py = App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->PhysicsPos.y;

	//		App->GDCL_Scene_Data->S_Object[ObjectToMove]->OgreNode->setPosition(x,y,z);
	//		App->GDCL_Scene_Data->S_Object[ObjectToMove]->bt_body->getWorldTransform().setOrigin(btVector3(px,py,pz));

	//		if(App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->MeshPos.y < FinalPosition)
	//		{
	//			/*App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_Sounds[0]->SndFile->stop();
	//			App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_Sounds[0]->SndFile->drop();
	//			App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_Sounds[0]->SndFile = NULL;*/

	//			DoMove = 0; // Stop Listener
	//		}

	//		return;
	//	}
	//}
	//
	//// Z Axis
	//if (App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->WhatDirection == Enums::Axis_z)
	//{
	//	if (App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->IsNegative == false)
	//	{
	//		int ObjectToMove = App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->Object_Index;

	//		App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->MeshPos.z += App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->Speed * Time;
	//		App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->PhysicsPos.z += App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->Speed * Time;

	//		z = App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->MeshPos.z;
	//		pz = App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->PhysicsPos.z;

	//		App->GDCL_Scene_Data->S_Object[ObjectToMove]->OgreNode->setPosition(x,y,z);
	//		App->GDCL_Scene_Data->S_Object[ObjectToMove]->bt_body->getWorldTransform().setOrigin(btVector3(px,py,pz));

	//		if(App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->MeshPos.z > FinalPosition)
	//		{
	//			/*App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_Sounds[0]->SndFile->stop();
	//			App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_Sounds[0]->SndFile->drop();
	//			App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_Sounds[0]->SndFile = NULL;*/

	//			DoMove = 0; // Stop Listener
	//		}

	//		return;
	//	}	
	//	else
	//	{
	//		int ObjectToMove = App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->Object_Index;

	//		App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->MeshPos.z -= App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->Speed * Time;
	//		App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->PhysicsPos.z -= App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->Speed * Time;

	//		z = App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->MeshPos.z;
	//		pz = App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->PhysicsPos.z;

	//		App->GDCL_Scene_Data->S_Object[ObjectToMove]->OgreNode->setPosition(x,y,z);
	//		App->GDCL_Scene_Data->S_Object[ObjectToMove]->bt_body->getWorldTransform().setOrigin(btVector3(px,py,pz));

	//		if(App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_MoveType->MeshPos.z < FinalPosition)
	//		{
	//			/*App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_Sounds[0]->SndFile->stop();
	//			App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_Sounds[0]->SndFile->drop();
	//			App->GDCL_Scene_Data->S_Object[ObjectIndex]->S_Sounds[0]->SndFile = NULL;*/

	//			DoMove = 0; // Stop Listener
	//		}

	//		return;
	//	}
	//}

	return;
}

// *************************************************************************
// *						Play_Sound Terry Bernie						   *
// *************************************************************************
bool GD_Collision::Play_Sound(int Index)
{

	if (App->GDCL_Scene_Data->S_Object[Index]->HasSound == 1 && App->GDCL_Scene_Data->S_Object[Index]->Play_v2 == 1)
	{
		char buff[1024];
		strcpy(buff, App->GDCL_SoundMgr->Default_Folder);
		strcat(buff, "\\Media\\Sounds\\");

		int SndIndex = App->GDCL_Scene_Data->S_Object[Index]->Sound_ID_v2;

		strcat(buff, App->GDCL_Scene_Data->St_Sounds[SndIndex]->SoundFile);

		App->GDCL_Scene_Data->St_Sounds[SndIndex]->SndFile = App->GDCL_SoundMgr->SoundEngine->play2D(buff, false, true, true);
		App->GDCL_Scene_Data->St_Sounds[SndIndex]->SndFile->setVolume(App->GDCL_Scene_Data->St_Sounds[SndIndex]->Volume);
		App->GDCL_Scene_Data->St_Sounds[SndIndex]->SndFile->setIsPaused(false);

		App->GDCL_Scene_Data->S_Object[Index]->Triggered = 1;
	}

	return 1;
}

