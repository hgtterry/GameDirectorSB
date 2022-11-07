#include "StdAfx.h"
#include "BT_App.h"
#include "GD_Add_Objects.h"


GD_Add_Objects::GD_Add_Objects(void)
{
}


GD_Add_Objects::~GD_Add_Objects(void)
{
}

// *************************************************************************
//							Add_Stock_Message Terry Bernie				   *
// *************************************************************************
void GD_Add_Objects::Add_Stock_Message()
{
	char ConNum[256];
	char AName[256];

	int MessageIndex = App->GDCL_Scene_Data->Stock_Messgae_Count;
	App->GDCL_Scene_Data->S_Messages[MessageIndex] = new Stock_Messages_type();
	App->GDCL_Scene_Data->Set_Mesgaes_Defaults(MessageIndex);

	strcpy(AName,"Message_");
	itoa(MessageIndex,ConNum,10);
	strcat(AName,ConNum);

	strcpy(App->GDCL_Scene_Data->S_Messages[MessageIndex]->Name,AName);

	OverlayManager& overlayManager = OverlayManager::getSingleton();
	App->GDCL_Scene_Data->S_Messages[MessageIndex]->panel = static_cast<OverlayContainer*>(overlayManager.createOverlayElement("Panel",AName));
	
	App->GDCL_Scene_Data->S_Messages[MessageIndex]->panel->setMetricsMode(Ogre::GMM_RELATIVE_ASPECT_ADJUSTED);
	App->GDCL_Scene_Data->S_Messages[MessageIndex]->panel->setHorizontalAlignment(Ogre::GuiHorizontalAlignment::GHA_CENTER);
	App->GDCL_Scene_Data->S_Messages[MessageIndex]->panel->setVerticalAlignment(Ogre::GuiVerticalAlignment::GVA_CENTER);
	App->GDCL_Scene_Data->S_Messages[MessageIndex]->panel->setPosition(-20, -30);
	App->GDCL_Scene_Data->S_Messages[MessageIndex]->panel->setDimensions(100, 100);

	strcpy(AName,"TextArea_");
	itoa(MessageIndex,ConNum,10);
	strcat(AName,ConNum);

	App->GDCL_Scene_Data->S_Messages[MessageIndex]->textArea1 = static_cast<TextAreaOverlayElement*>(overlayManager.createOverlayElement("TextArea",AName));
	
	float Vert = App->GDCL_Scene_Data->S_Messages[MessageIndex]->Pos_Vert;
	float Hoz = App->GDCL_Scene_Data->S_Messages[MessageIndex]->Pos_Hoz;

	App->GDCL_Scene_Data->S_Messages[MessageIndex]->textArea1->setMetricsMode(Ogre::GMM_PIXELS);
	App->GDCL_Scene_Data->S_Messages[MessageIndex]->textArea1->setPosition(Hoz,Vert);
	App->GDCL_Scene_Data->S_Messages[MessageIndex]->textArea1->setDimensions(100, 100);
	App->GDCL_Scene_Data->S_Messages[MessageIndex]->textArea1->setCaption(App->GDCL_Scene_Data->S_Messages[MessageIndex]->Default_Text);
	App->GDCL_Scene_Data->S_Messages[MessageIndex]->textArea1->setCharHeight((Ogre::Real)App->GDCL_Scene_Data->S_Messages[MessageIndex]->Font_Size);
	App->GDCL_Scene_Data->S_Messages[MessageIndex]->textArea1->setFontName("BlueHighway");
	App->GDCL_Scene_Data->S_Messages[MessageIndex]->textArea1->setColour(ColourValue(1,1,1));
	//App->GDCL_Scene_Data->S_Messages[MessageIndex]->textArea1->setColourTop(ColourValue(1,1,1));


	// Create an overlay, and add the panel
	strcpy(AName,"OverlayName_");
	itoa(MessageIndex,ConNum,10);
	strcat(AName,ConNum);

	App->GDCL_Scene_Data->S_Messages[MessageIndex]->overlay = overlayManager.create(AName);
	App->GDCL_Scene_Data->S_Messages[MessageIndex]->overlay->add2D(App->GDCL_Scene_Data->S_Messages[MessageIndex]->panel);
 
// Add the text area to the panel
	App->GDCL_Scene_Data->S_Messages[MessageIndex]->panel->addChild(App->GDCL_Scene_Data->S_Messages[MessageIndex]->textArea1); // C Styl
//	App->GDCL_Scene_Data->S_Messages[MessageIndex]->panel->addChild(S_Message[0]->textArea2);

	
	App->GDCL_Scene_Data->Stock_Messgae_Count++;
}


// *************************************************************************
//						Add_Object Terry Bernie							   *
// *************************************************************************
bool GD_Add_Objects::Add_Object()
{
	char ConNum[256];
	char ATest[256];
	char Name[255];
	char Mesh_File[255];

	int Object_Count = App->GDCL_Scene_Data->ObjectCount;
	int Count = 0;

	while(Count < Object_Count)
	{
		if(App->GDCL_Scene_Data->S_Object[Count]->Usage == Enums::Usage_Sound)
		{
			Add_SoundEntity(Count);
		}
		else if(App->GDCL_Scene_Data->S_Object[Count]->Usage == Enums::Usage_Message)
		{
			Add_MessageEntity(Count);
		}
		else if (App->GDCL_Scene_Data->S_Object[Count]->Usage == Enums::Usage_Colectable)
		{
			Add_CollectableEntity(Count);
		}
		else if(App->GDCL_Scene_Data->S_Object[Count]->Usage == Enums::Usage_Move)
		{
			Add_MoveEntity(Count);
		}
		else
		{
			strcpy_s(ATest,"GDEnt_");
			itoa(Count,ConNum,10);
			strcat(ATest,ConNum);

			strcpy(Name,App->GDCL_Scene_Data->S_Object[Count]->Name);
			strcpy(Mesh_File,App->GDCL_Scene_Data->S_Object[Count]->MeshName);

			App->GDCL_Scene_Data->S_Object[Count]->OgreEntity = App->Ogre17->mSceneMgr->createEntity(ATest,Mesh_File,App->Ogre17->PermResourceGroup);
			App->GDCL_Scene_Data->S_Object[Count]->OgreNode = App->Ogre17->mSceneMgr->getRootSceneNode()->createChildSceneNode();
			App->GDCL_Scene_Data->S_Object[Count]->OgreNode->attachObject(App->GDCL_Scene_Data->S_Object[Count]->OgreEntity); 

			App->GDCL_Scene_Data->S_Object[Count]->OgreNode->setVisible(true);
			App->GDCL_Scene_Data->S_Object[Count]->OgreNode->setScale(App->GDCL_Scene_Data->S_Object[Count]->Mesh_Scale);

			Ogre::Vector3 Pos = App->GDCL_Scene_Data->S_Object[Count]->Mesh_Pos;
			Ogre::Quaternion Rot = App->GDCL_Scene_Data->S_Object[Count]->Mesh_Quat;

			App->GDCL_Scene_Data->S_Object[Count]->OgreNode->setOrientation(Rot);
			App->GDCL_Scene_Data->S_Object[Count]->OgreNode->setPosition(Pos);

			//---------------------- Static
			if(App->GDCL_Scene_Data->S_Object[Count]->Type == Enums::Bullet_Type_Static || App->GDCL_Scene_Data->S_Object[Count]->Type == Enums::Bullet_Type_Dynamic)
			{
				if(App->GDCL_Scene_Data->S_Object[Count]->Shape == Enums::Shape_Box)
				{
					Add_Physics_Static_Box(false,Count);
					App->GDCL_Scene_Data->S_Object[Count]->Physics_Valid = 1;
				}

				if(App->GDCL_Scene_Data->S_Object[Count]->Shape == Enums::Sphere)
				{
					Add_Physics_Static_Sphere(false,Count);
					App->GDCL_Scene_Data->S_Object[Count]->Physics_Valid = 1;
				}

				if(App->GDCL_Scene_Data->S_Object[Count]->Shape == Enums::Capsule)
				{
					Add_Physics_Static_Capsule(false,Count);
					App->GDCL_Scene_Data->S_Object[Count]->Physics_Valid = 1;
				}

				if(App->GDCL_Scene_Data->S_Object[Count]->Shape == Enums::Cylinder)
				{
					Add_Physics_Static_Cylinder(false,Count);
					App->GDCL_Scene_Data->S_Object[Count]->Physics_Valid = 1;
				}

				if(App->GDCL_Scene_Data->S_Object[Count]->Shape == Enums::Cone)
				{
					Add_Physics_Static_Cone(false,Count);
					App->GDCL_Scene_Data->S_Object[Count]->Physics_Valid = 1;
				}
			}

			//---------------------- Tri_Mesh
			if(App->GDCL_Scene_Data->S_Object[Count]->Shape == Enums::Shape_TriMesh)
			{
				createTrimesh(App->GDCL_Scene_Data->S_Object[Count]->OgreEntity,Count);
				App->GDCL_Scene_Data->S_Object[Count]->Physics_Valid = 1;
			}

		}
		Count++;
	}


	App->Ogre17->PhysicsFrameListener->GD_Dubug_Physics = 1;
	return 1;
}

// *************************************************************************
//						Add_Physics_Static_Box Terry Bernie				   *
// *************************************************************************
void GD_Add_Objects::Add_Physics_Static_Box(bool Dynamic,int Object_Index)
{
	int Index = Object_Index;

	btTransform mStartTransform = Set_Physics_PosRot(Index); // Get Physics Position And Rotation Transform

	btScalar mass;
	mass = App->GDCL_Scene_Data->S_Object[Index]->Physics_Mass;
	
	btVector3 localInertia(0,0,0);
	
	Ogre::Vector3 Size = App->GDCL_Scene_Data->S_Object[Index]->Physics_Size; // --------- Size

	btCollisionShape *newRigidShape = new btBoxShape(btVector3(Size.x,Size.y,Size.z));
	newRigidShape->calculateLocalInertia(mass, localInertia);

	App->GDCL_Bullet->collisionShapes.push_back(newRigidShape);
	
	btDefaultMotionState *myMotionState = new btDefaultMotionState(mStartTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, newRigidShape, localInertia);
	
	App->GDCL_Scene_Data->S_Object[Index]->bt_body = new btRigidBody(rbInfo);
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setRestitution(1.0);
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setFriction(1.5);
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setUserPointer(App->GDCL_Scene_Data->S_Object[Index]->OgreNode);
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setWorldTransform(mStartTransform);

	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setCustomDebugColor(btVector3(0,1,1));
	
	int f = App->GDCL_Scene_Data->S_Object[Index]->bt_body->getCollisionFlags();
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setCollisionFlags(f|btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);

	Set_Physics_Scale(Index); // Set Physics Scale

	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setUserIndex(App->GDCL_Scene_Data->S_Object[Index]->Usage);
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setUserIndex2(Index);

	App->GDCL_Bullet->dynamicsWorld->addRigidBody(App->GDCL_Scene_Data->S_Object[Index]->bt_body);
}

// *************************************************************************
//						Add_Physics_Static_Sphere Terry Bernie			   *
// *************************************************************************
void GD_Add_Objects::Add_Physics_Static_Sphere(bool Dynamic,int Object_Index)
{
	int Index = Object_Index;

	btTransform mStartTransform = Set_Physics_PosRot(Index); // Get Physics Position And Rotation Transform

	btScalar mass;
	mass = App->GDCL_Scene_Data->S_Object[Index]->Physics_Mass;
	
	btVector3 localInertia(0,0,0);
	
	Ogre::Vector3 Size = App->GDCL_Scene_Data->S_Object[Index]->Physics_Size; // --------- Size

	btCollisionShape *newRigidShape = new btSphereShape(Size.x); // Radius
	newRigidShape->calculateLocalInertia(mass, localInertia);

	App->GDCL_Bullet->collisionShapes.push_back(newRigidShape);
	
	btDefaultMotionState *myMotionState = new btDefaultMotionState(mStartTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, newRigidShape, localInertia);
	
	App->GDCL_Scene_Data->S_Object[Index]->bt_body = new btRigidBody(rbInfo);
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setRestitution(1.0);
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setFriction(1.5);
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setUserPointer(App->GDCL_Scene_Data->S_Object[Index]->OgreNode);
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setWorldTransform(mStartTransform);

	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setCustomDebugColor(btVector3(0,1,1));
	
	int f = App->GDCL_Scene_Data->S_Object[Index]->bt_body->getCollisionFlags();
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setCollisionFlags(f|btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);

	Set_Physics_Scale(Index); // Set Physics Scale

	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setUserIndex(App->GDCL_Scene_Data->S_Object[Index]->Usage);
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setUserIndex2(Index);

	App->GDCL_Bullet->dynamicsWorld->addRigidBody(App->GDCL_Scene_Data->S_Object[Index]->bt_body);
}

// *************************************************************************
//						Add_Physics_Capsule_Capsule Terry Bernie		   *
// *************************************************************************
void GD_Add_Objects::Add_Physics_Static_Capsule(bool Dynamic,int Object_Index)
{
	int Index = Object_Index;

	btTransform mStartTransform = Set_Physics_PosRot(Index); // Get Physics Position And Rotation Transform

	btScalar mass;
	mass = App->GDCL_Scene_Data->S_Object[Index]->Physics_Mass;
	
	btVector3 localInertia(0,0,0);
	
	Ogre::Vector3 Size = App->GDCL_Scene_Data->S_Object[Index]->Physics_Size; // --------- Size

	btCollisionShape *newRigidShape = new btCapsuleShape(Size.x,Size.y); // Radius,Height
	newRigidShape->calculateLocalInertia(mass, localInertia);

	App->GDCL_Bullet->collisionShapes.push_back(newRigidShape);
	
	btDefaultMotionState *myMotionState = new btDefaultMotionState(mStartTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, newRigidShape, localInertia);
	
	App->GDCL_Scene_Data->S_Object[Index]->bt_body = new btRigidBody(rbInfo);
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setRestitution(1.0);
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setFriction(1.5);
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setUserPointer(App->GDCL_Scene_Data->S_Object[Index]->OgreNode);
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setWorldTransform(mStartTransform);

	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setCustomDebugColor(btVector3(0,1,1));
	
	int f = App->GDCL_Scene_Data->S_Object[Index]->bt_body->getCollisionFlags();
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setCollisionFlags(f|btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);

	Set_Physics_Scale(Index); // Set Physics Scale

	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setUserIndex(App->GDCL_Scene_Data->S_Object[Index]->Usage);
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setUserIndex2(Index);

	App->GDCL_Bullet->dynamicsWorld->addRigidBody(App->GDCL_Scene_Data->S_Object[Index]->bt_body);
}

// *************************************************************************
//						Add_Physics_Capsule_Cylinder Terry Bernie		   *
// *************************************************************************
void GD_Add_Objects::Add_Physics_Static_Cylinder(bool Dynamic,int Object_Index)
{
	int Index = Object_Index;

	btTransform mStartTransform = Set_Physics_PosRot(Index); // Get Physics Position And Rotation Transform

	btScalar mass;
	mass = App->GDCL_Scene_Data->S_Object[Index]->Physics_Mass;
	
	btVector3 localInertia(0,0,0);
	
	Ogre::Vector3 Size = App->GDCL_Scene_Data->S_Object[Index]->Physics_Size; // --------- Size

	btCollisionShape *newRigidShape = new btCylinderShape(btVector3(Size.x,Size.y,Size.z));
	newRigidShape->calculateLocalInertia(mass, localInertia);

	App->GDCL_Bullet->collisionShapes.push_back(newRigidShape);
	
	btDefaultMotionState *myMotionState = new btDefaultMotionState(mStartTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, newRigidShape, localInertia);
	
	App->GDCL_Scene_Data->S_Object[Index]->bt_body = new btRigidBody(rbInfo);
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setRestitution(1.0);
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setFriction(1.5);
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setUserPointer(App->GDCL_Scene_Data->S_Object[Index]->OgreNode);
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setWorldTransform(mStartTransform);

	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setCustomDebugColor(btVector3(0,1,1));
	
	int f = App->GDCL_Scene_Data->S_Object[Index]->bt_body->getCollisionFlags();
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setCollisionFlags(f|btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);

	Set_Physics_Scale(Index); // Set Physics Scale

	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setUserIndex(App->GDCL_Scene_Data->S_Object[Index]->Usage);
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setUserIndex2(Index);

	App->GDCL_Bullet->dynamicsWorld->addRigidBody(App->GDCL_Scene_Data->S_Object[Index]->bt_body);
}

// *************************************************************************
//						Add_Physics_Static_Cone Terry Bernie			   *
// *************************************************************************
void GD_Add_Objects::Add_Physics_Static_Cone(bool Dynamic,int Object_Index)
{
	int Index = Object_Index;

	btTransform mStartTransform = Set_Physics_PosRot(Index); // Get Physics Position And Rotation Transform

	btScalar mass;
	mass = App->GDCL_Scene_Data->S_Object[Index]->Physics_Mass;
	
	btVector3 localInertia(0,0,0);
	
	Ogre::Vector3 Size = App->GDCL_Scene_Data->S_Object[Index]->Physics_Size; // --------- Size

	btCollisionShape *newRigidShape = new btConeShape(Size.x,Size.y); // Radius,Height
	newRigidShape->calculateLocalInertia(mass, localInertia);

	App->GDCL_Bullet->collisionShapes.push_back(newRigidShape);
	
	btDefaultMotionState *myMotionState = new btDefaultMotionState(mStartTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, newRigidShape, localInertia);
	
	App->GDCL_Scene_Data->S_Object[Index]->bt_body = new btRigidBody(rbInfo);
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setRestitution(1.0);
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setFriction(1.5);
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setUserPointer(App->GDCL_Scene_Data->S_Object[Index]->OgreNode);
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setWorldTransform(mStartTransform);

	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setCustomDebugColor(btVector3(0,1,1));
	
	int f = App->GDCL_Scene_Data->S_Object[Index]->bt_body->getCollisionFlags();
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setCollisionFlags(f|btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);

	Set_Physics_Scale(Index); // Set Physics Scale

	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setUserIndex(App->GDCL_Scene_Data->S_Object[Index]->Usage);
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setUserIndex2(Index);

	App->GDCL_Bullet->dynamicsWorld->addRigidBody(App->GDCL_Scene_Data->S_Object[Index]->bt_body);
}

// *************************************************************************
//						Add_SoundEntity Terry Bernie					   *
// *************************************************************************
bool GD_Add_Objects::Add_SoundEntity(int Object_Index)
{
	char ConNum[256];
	char ATest[256];
	char Name[255];
	int Index = Object_Index;

	App->GDCL_Scene_Data->S_Object[Index]->Type = Enums::Bullet_Type_Static;
	App->GDCL_Scene_Data->S_Object[Index]->Shape = Enums::Shape_Box;
	strcpy(Name,App->GDCL_Scene_Data->S_Object[Index]->Name);

	strcpy_s(ATest,"GDEnt_");
	itoa(Object_Index,ConNum,10);
	strcat(ATest,ConNum);

	//------------------ Add Ogre Mesh
	App->GDCL_Scene_Data->S_Object[Index]->OgreEntity = App->Ogre17->mSceneMgr->createEntity(ATest,"SoundEntity_GD.mesh",App->Ogre17->PermResourceGroup);
	App->GDCL_Scene_Data->S_Object[Index]->OgreNode = App->Ogre17->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	App->GDCL_Scene_Data->S_Object[Index]->OgreNode->attachObject(App->GDCL_Scene_Data->S_Object[Index]->OgreEntity); 
	App->GDCL_Scene_Data->S_Object[Index]->OgreNode->scale(App->GDCL_Scene_Data->S_Object[Index]->Mesh_Scale);

	Ogre::Vector3 Pos  = App->GDCL_Scene_Data->S_Object[Index]->Mesh_Pos;
	App->GDCL_Scene_Data->S_Object[Index]->OgreNode->setPosition(Pos);

	Ogre::Quaternion Rot = App->GDCL_Scene_Data->S_Object[Index]->Mesh_Quat;
	App->GDCL_Scene_Data->S_Object[Index]->OgreNode->setOrientation(Rot);
	//----------------------------------------------------------------------------------

	Ogre::Vector3 Size = App->GDCL_Scene_Data->S_Object[Index]->Physics_Size;
	
	btCollisionShape *newRigidShape = new btBoxShape(btVector3(Size.x,Size.y,Size.z));
	newRigidShape->calculateLocalInertia(0,btVector3(0,0,0));

	btTransform mStartTransform = Set_Physics_PosRot(Index); // Get Physics Position And Rotation Transform
	
	btDefaultMotionState *myMotionState = new btDefaultMotionState(mStartTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(0, myMotionState, newRigidShape,btVector3(0,0,0));
	
	App->GDCL_Scene_Data->S_Object[Index]->bt_body = new btRigidBody(rbInfo);
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setRestitution(1.0);
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setFriction(1.5);
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setUserPointer(App->GDCL_Scene_Data->S_Object[Index]->OgreNode);
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setWorldTransform(mStartTransform);

	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setCollisionFlags(btCollisionObject::CF_KINEMATIC_OBJECT|btCollisionObject::CF_NO_CONTACT_RESPONSE);

	App->GDCL_Scene_Data->S_Object[Index]->Usage = Enums::Usage_Sound;
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setUserIndex(Enums::Usage_Sound);
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setUserIndex2(Index);

	Set_Physics_Scale(Index); // Set Physics Scale

	App->GDCL_Bullet->dynamicsWorld->addRigidBody(App->GDCL_Scene_Data->S_Object[Index]->bt_body);

	App->GDCL_Scene_Data->S_Object[Index]->Folder = Enums::Folder_Sound_Entity;
	App->GDCL_Scene_Data->S_Object[Index]->Physics_Valid = 1;

	return 1;
}

// *************************************************************************
//						Add_MessageEntity Terry Bernie					   *
// *************************************************************************
bool GD_Add_Objects::Add_MessageEntity(int Object_Index)
{
	char ConNum[256];
	char ATest[256];
	char Name[255];
	int Index = Object_Index;

	App->GDCL_Scene_Data->S_Object[Index]->Type = Enums::Bullet_Type_Static;
	App->GDCL_Scene_Data->S_Object[Index]->Shape = Enums::Shape_Box;
	strcpy(Name,App->GDCL_Scene_Data->S_Object[Index]->Name);

	strcpy_s(ATest,"GDEnt_");
	itoa(Object_Index,ConNum,10);
	strcat(ATest,ConNum);

	//------------------ Add Ogre Mesh
	App->GDCL_Scene_Data->S_Object[Index]->OgreEntity = App->Ogre17->mSceneMgr->createEntity(ATest,"Test_cube.mesh",App->Ogre17->PermResourceGroup);
	App->GDCL_Scene_Data->S_Object[Index]->OgreNode = App->Ogre17->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	App->GDCL_Scene_Data->S_Object[Index]->OgreNode->attachObject(App->GDCL_Scene_Data->S_Object[Index]->OgreEntity); 
	App->GDCL_Scene_Data->S_Object[Index]->OgreNode->scale(App->GDCL_Scene_Data->S_Object[Index]->Mesh_Scale);

	Ogre::Vector3 Pos  = App->GDCL_Scene_Data->S_Object[Index]->Mesh_Pos;
	App->GDCL_Scene_Data->S_Object[Index]->OgreNode->setPosition(Pos);

	Ogre::Quaternion Rot = App->GDCL_Scene_Data->S_Object[Index]->Mesh_Quat;
	App->GDCL_Scene_Data->S_Object[Index]->OgreNode->setOrientation(Rot);
	//----------------------------------------------------------------------------------

	Ogre::Vector3 Size = App->GDCL_Scene_Data->S_Object[Index]->Physics_Size;
	
	btCollisionShape *newRigidShape = new btBoxShape(btVector3(Size.x,Size.y,Size.z));
	newRigidShape->calculateLocalInertia(0,btVector3(0,0,0));

	btTransform mStartTransform = Set_Physics_PosRot(Index); // Get Physics Position And Rotation Transform
	

	btDefaultMotionState *myMotionState = new btDefaultMotionState(mStartTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(0, myMotionState, newRigidShape,btVector3(0,0,0));
	
	App->GDCL_Scene_Data->S_Object[Index]->bt_body = new btRigidBody(rbInfo);
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setRestitution(1.0);
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setFriction(1.5);
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setUserPointer(App->GDCL_Scene_Data->S_Object[Index]->OgreNode);
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setWorldTransform(mStartTransform);

	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setCollisionFlags(btCollisionObject::CF_KINEMATIC_OBJECT|btCollisionObject::CF_NO_CONTACT_RESPONSE);

	App->GDCL_Scene_Data->S_Object[Index]->Usage = Enums::Usage_Message;
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setUserIndex(Enums::Usage_Message);
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setUserIndex2(Index);

	int f = App->GDCL_Scene_Data->S_Object[Index]->bt_body->getCollisionFlags();
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setCollisionFlags(f|btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);

	Set_Physics_Scale(Index); // Set Physics Scale

	App->GDCL_Bullet->dynamicsWorld->addRigidBody(App->GDCL_Scene_Data->S_Object[Index]->bt_body);

	App->GDCL_Scene_Data->S_Object[Index]->Folder = Enums::Folder_Message_Entity;
	App->GDCL_Scene_Data->S_Object[Index]->Physics_Valid = 1;

	return 1;
}

// *************************************************************************
//						Add_MoveEntity Terry Bernie						   *
// *************************************************************************
bool GD_Add_Objects::Add_MoveEntity(int Object_Index)
{
	char ConNum[256];
	char ATest[256];
	char Name[255];
	int Index = Object_Index;

	App->GDCL_Scene_Data->S_Object[Index]->Type = Enums::Bullet_Type_Static;
	App->GDCL_Scene_Data->S_Object[Index]->Shape = Enums::Shape_Box;
	strcpy(Name,App->GDCL_Scene_Data->S_Object[Index]->Name);

	strcpy_s(ATest,"GDEnt_");
	itoa(Object_Index,ConNum,10);
	strcat(ATest,ConNum);

	//------------------ Add Ogre Mesh
	App->GDCL_Scene_Data->S_Object[Index]->OgreEntity = App->Ogre17->mSceneMgr->createEntity(ATest,"DoorEntity_GD.mesh",App->Ogre17->PermResourceGroup);
	App->GDCL_Scene_Data->S_Object[Index]->OgreNode = App->Ogre17->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	App->GDCL_Scene_Data->S_Object[Index]->OgreNode->attachObject(App->GDCL_Scene_Data->S_Object[Index]->OgreEntity); 
	App->GDCL_Scene_Data->S_Object[Index]->OgreNode->scale(App->GDCL_Scene_Data->S_Object[Index]->Mesh_Scale);

	Ogre::Vector3 Pos  = App->GDCL_Scene_Data->S_Object[Index]->Mesh_Pos;
	App->GDCL_Scene_Data->S_Object[Index]->OgreNode->setPosition(Pos);

	Ogre::Quaternion Rot = App->GDCL_Scene_Data->S_Object[Index]->Mesh_Quat;
	App->GDCL_Scene_Data->S_Object[Index]->OgreNode->setOrientation(Rot);
	//----------------------------------------------------------------------------------

	Ogre::Vector3 Size = App->GDCL_Scene_Data->S_Object[Index]->Physics_Size;
	
	btCollisionShape *newRigidShape = new btBoxShape(btVector3(Size.x,Size.y,Size.z));
	newRigidShape->calculateLocalInertia(0,btVector3(0,0,0));

	btTransform mStartTransform = Set_Physics_PosRot(Index); // Get Physics Position And Rotation Transform
	

	btDefaultMotionState *myMotionState = new btDefaultMotionState(mStartTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(0, myMotionState, newRigidShape,btVector3(0,0,0));
	
	App->GDCL_Scene_Data->S_Object[Index]->bt_body = new btRigidBody(rbInfo);
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setRestitution(1.0);
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setFriction(1.5);
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setUserPointer(App->GDCL_Scene_Data->S_Object[Index]->OgreNode);
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setWorldTransform(mStartTransform);

	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setCollisionFlags(btCollisionObject::CF_KINEMATIC_OBJECT|btCollisionObject::CF_NO_CONTACT_RESPONSE);

	App->GDCL_Scene_Data->S_Object[Index]->Usage = Enums::Usage_Move;
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setUserIndex(Enums::Usage_Move);
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setUserIndex2(Index);

	int f = App->GDCL_Scene_Data->S_Object[Index]->bt_body->getCollisionFlags();
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setCollisionFlags(f|btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);

	Set_Physics_Scale(Index); // Set Physics Scale

	App->GDCL_Bullet->dynamicsWorld->addRigidBody(App->GDCL_Scene_Data->S_Object[Index]->bt_body);

	App->GDCL_Scene_Data->S_Object[Index]->Folder = Enums::Folder_None;
	App->GDCL_Scene_Data->S_Object[Index]->Physics_Valid = 1;

	return 1;
}

// *************************************************************************
//						Add_CollectableEntity Terry Bernie				   *
// *************************************************************************
bool GD_Add_Objects::Add_CollectableEntity(int Object_Index)
{
	char ConNum[256];
	char ATest[256];
	char Name[255];
	int Count = Object_Index;
	char Mesh_File[255];

	strcpy_s(ATest, "GDEnt_");
	itoa(Count, ConNum, 10);
	strcat(ATest, ConNum);

	strcpy(Name, App->GDCL_Scene_Data->S_Object[Count]->Name);
	strcpy(Mesh_File, App->GDCL_Scene_Data->S_Object[Count]->MeshName);

	App->GDCL_Scene_Data->S_Object[Count]->OgreEntity = App->Ogre17->mSceneMgr->createEntity(ATest, Mesh_File, App->Ogre17->PermResourceGroup);
	App->GDCL_Scene_Data->S_Object[Count]->OgreNode = App->Ogre17->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	App->GDCL_Scene_Data->S_Object[Count]->OgreNode->attachObject(App->GDCL_Scene_Data->S_Object[Count]->OgreEntity);

	App->GDCL_Scene_Data->S_Object[Count]->OgreNode->setVisible(true);
	App->GDCL_Scene_Data->S_Object[Count]->OgreNode->setScale(App->GDCL_Scene_Data->S_Object[Count]->Mesh_Scale);

	Ogre::Vector3 Pos = App->GDCL_Scene_Data->S_Object[Count]->Mesh_Pos;
	Ogre::Quaternion Rot = App->GDCL_Scene_Data->S_Object[Count]->Mesh_Quat;

	App->GDCL_Scene_Data->S_Object[Count]->OgreNode->setOrientation(Rot);
	App->GDCL_Scene_Data->S_Object[Count]->OgreNode->setPosition(Pos);

	//---------------------- Static and Dynamic
	if (App->GDCL_Scene_Data->S_Object[Count]->Type == Enums::Bullet_Type_Static || App->GDCL_Scene_Data->S_Object[Count]->Type == Enums::Bullet_Type_Dynamic)
	{
		if (App->GDCL_Scene_Data->S_Object[Count]->Shape == Enums::Shape_Box)
		{
			Add_Physics_Static_Box(false, Count);
			App->GDCL_Scene_Data->S_Object[Count]->Physics_Valid = 1;
		}

		if (App->GDCL_Scene_Data->S_Object[Count]->Shape == Enums::Sphere)
		{
			Add_Physics_Static_Sphere(false, Count);
			App->GDCL_Scene_Data->S_Object[Count]->Physics_Valid = 1;
		}

		if (App->GDCL_Scene_Data->S_Object[Count]->Shape == Enums::Capsule)
		{
			Add_Physics_Static_Capsule(false, Count);
			App->GDCL_Scene_Data->S_Object[Count]->Physics_Valid = 1;
		}

		if (App->GDCL_Scene_Data->S_Object[Count]->Shape == Enums::Cylinder)
		{
			Add_Physics_Static_Cylinder(false, Count);
			App->GDCL_Scene_Data->S_Object[Count]->Physics_Valid = 1;
		}

		if (App->GDCL_Scene_Data->S_Object[Count]->Shape == Enums::Cone)
		{
			Add_Physics_Static_Cone(false, Count);
			App->GDCL_Scene_Data->S_Object[Count]->Physics_Valid = 1;
		}
	}

	return 1;
}

// *************************************************************************
//						Add_TeleportEntity Terry Bernie					   *
// *************************************************************************
bool GD_Add_Objects::Add_TeleportEntity(int Object_Index)
{
	char ConNum[256];
	char ATest[256];
	char Name[255];
	int Count = Object_Index;
	char Mesh_File[255];

	strcpy_s(ATest, "GDEnt_");
	itoa(Count, ConNum, 10);
	strcat(ATest, ConNum);

	strcpy(Name, App->GDCL_Scene_Data->S_Object[Count]->Name);
	strcpy(Mesh_File, App->GDCL_Scene_Data->S_Object[Count]->MeshName);

	App->GDCL_Scene_Data->S_Object[Count]->OgreEntity = App->Ogre17->mSceneMgr->createEntity(ATest, Mesh_File, App->Ogre17->PermResourceGroup);
	App->GDCL_Scene_Data->S_Object[Count]->OgreNode = App->Ogre17->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	App->GDCL_Scene_Data->S_Object[Count]->OgreNode->attachObject(App->GDCL_Scene_Data->S_Object[Count]->OgreEntity);

	App->GDCL_Scene_Data->S_Object[Count]->OgreNode->setVisible(true);
	App->GDCL_Scene_Data->S_Object[Count]->OgreNode->setScale(App->GDCL_Scene_Data->S_Object[Count]->Mesh_Scale);

	Ogre::Vector3 Pos = App->GDCL_Scene_Data->S_Object[Count]->Mesh_Pos;
	Ogre::Quaternion Rot = App->GDCL_Scene_Data->S_Object[Count]->Mesh_Quat;

	App->GDCL_Scene_Data->S_Object[Count]->OgreNode->setOrientation(Rot);
	App->GDCL_Scene_Data->S_Object[Count]->OgreNode->setPosition(Pos);

	//---------------------- Static and Dynamic
	if (App->GDCL_Scene_Data->S_Object[Count]->Type == Enums::Bullet_Type_Static || App->GDCL_Scene_Data->S_Object[Count]->Type == Enums::Bullet_Type_Dynamic)
	{
		if (App->GDCL_Scene_Data->S_Object[Count]->Shape == Enums::Shape_Box)
		{
			Add_Physics_Static_Box(false, Count);
			App->GDCL_Scene_Data->S_Object[Count]->Physics_Valid = 1;
		}

		if (App->GDCL_Scene_Data->S_Object[Count]->Shape == Enums::Sphere)
		{
			Add_Physics_Static_Sphere(false, Count);
			App->GDCL_Scene_Data->S_Object[Count]->Physics_Valid = 1;
		}

		if (App->GDCL_Scene_Data->S_Object[Count]->Shape == Enums::Capsule)
		{
			Add_Physics_Static_Capsule(false, Count);
			App->GDCL_Scene_Data->S_Object[Count]->Physics_Valid = 1;
		}

		if (App->GDCL_Scene_Data->S_Object[Count]->Shape == Enums::Cylinder)
		{
			Add_Physics_Static_Cylinder(false, Count);
			App->GDCL_Scene_Data->S_Object[Count]->Physics_Valid = 1;
		}

		if (App->GDCL_Scene_Data->S_Object[Count]->Shape == Enums::Cone)
		{
			Add_Physics_Static_Cone(false, Count);
			App->GDCL_Scene_Data->S_Object[Count]->Physics_Valid = 1;
		}
	}

	return 1;
}

// *************************************************************************
//							createTrimeshTerry Bernie					   *
// *************************************************************************
btBvhTriangleMeshShape* GD_Add_Objects::createTrimesh ( Ogre::Entity* ent,int Object_Index ) 
{
	int Index = Object_Index;

	// Get the mesh from the entity
	Ogre::MeshPtr myMesh = ent->getMesh();
	Ogre::Mesh::SubMeshIterator SubMeshIter = myMesh->getSubMeshIterator();

	// Create the triangle mesh
	btTriangleMesh* triMesh = NULL;
	btVector3 vert0, vert1, vert2;
	int i=0;

	while(SubMeshIter.hasMoreElements()) 
	{
		i=0;
		Ogre::SubMesh* subMesh = SubMeshIter.getNext();
		Ogre::IndexData*  indexData = subMesh->indexData;
		Ogre::VertexData* vertexData = subMesh->vertexData;

		// -------------------------------------------------------
		// Get the position element
		const Ogre::VertexElement* posElem = vertexData->vertexDeclaration->findElementBySemantic ( Ogre::VES_POSITION );
		// Get a pointer to the vertex buffer
		Ogre::HardwareVertexBufferSharedPtr vBuffer = vertexData->vertexBufferBinding->getBuffer ( posElem->getSource() );
		// Get a pointer to the index buffer
		Ogre::HardwareIndexBufferSharedPtr iBuffer = indexData->indexBuffer;

		// -------------------------------------------------------
		// The vertices and indices used to create the triangle mesh
		std::vector<Ogre::Vector3> vertices;
		vertices.reserve ( vertexData->vertexCount );
		std::vector<unsigned long> indices;
		indices.reserve ( indexData->indexCount );

		// -------------------------------------------------------
		// Lock the Vertex Buffer (READ ONLY)
		unsigned char* vertex = static_cast<unsigned char*> ( vBuffer->lock ( Ogre::HardwareBuffer::HBL_READ_ONLY ) );
		float* pReal = NULL;

		for ( size_t j = 0; j < vertexData->vertexCount; ++j, vertex += vBuffer->getVertexSize() ) {
			posElem->baseVertexPointerToElement ( vertex, &pReal );
			Ogre::Vector3 pt ( pReal[0], pReal[1], pReal[2] );

			vertices.push_back ( pt );
		}
		vBuffer->unlock();
		// -------------------------------------------------------
		bool use32bitindexes = ( iBuffer->getType() == Ogre::HardwareIndexBuffer::IT_32BIT );

		// -------------------------------------------------------
		// Lock the Index Buffer (READ ONLY)
		unsigned long* pLong = static_cast<unsigned long*> ( iBuffer->lock ( Ogre::HardwareBuffer::HBL_READ_ONLY ) );
		unsigned short* pShort = reinterpret_cast<unsigned short*> ( pLong );

		if ( use32bitindexes ) {
			for ( size_t k = 0; k < indexData->indexCount; ++k ) {
				//
				indices.push_back ( pLong[k] );
			}
		} else {
			for ( size_t k = 0; k < indexData->indexCount; ++k ) {
				//
				indices.push_back ( static_cast<unsigned long> ( pShort[k] ) );
			}
		}
		iBuffer->unlock();

		// -------------------------------------------------------
		// We now have vertices and indices ready to go
		// ----

		if(triMesh == nullptr) 
		{
			triMesh = new btTriangleMesh ( use32bitindexes);
		}

		for ( size_t y=0; y<indexData->indexCount/3; y++ ) {
			// Set each vertex
			vert0.setValue ( vertices[indices[i]].x, vertices[indices[i]].y, vertices[indices[i]].z );
			vert1.setValue ( vertices[indices[i+1]].x, vertices[indices[i+1]].y, vertices[indices[i+1]].z );
			vert2.setValue ( vertices[indices[i+2]].x, vertices[indices[i+2]].y, vertices[indices[i+2]].z );

			// Add the triangle into the triangle mesh
			triMesh->addTriangle ( vert0, vert1, vert2);

			// Increase index count
			i += 3;
		}
	}

	const bool useQuantizedAABB = true;
	btBvhTriangleMeshShape* mShape = new btBvhTriangleMeshShape ( triMesh, false,true );
	//mShape->buildOptimizedBvh();

	float x = App->GDCL_Scene_Data->S_Object[Index]->Mesh_Pos.x;
	float y = App->GDCL_Scene_Data->S_Object[Index]->Mesh_Pos.y;
	float z = App->GDCL_Scene_Data->S_Object[Index]->Mesh_Pos.z;

	//------------ Rotation
	float rw = App->GDCL_Scene_Data->S_Object[Index]->Physics_Quat.w;
	float rx = App->GDCL_Scene_Data->S_Object[Index]->Physics_Quat.x;
	float ry = App->GDCL_Scene_Data->S_Object[Index]->Physics_Quat.y;
	float rz = App->GDCL_Scene_Data->S_Object[Index]->Physics_Quat.z;

	btVector3 inertia(0, 0, 0);
	mShape->calculateLocalInertia(0.0, inertia);

	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setRotation(btQuaternion(rx,ry,rz,rw));
	btVector3 initialPosition(x,y,z);
	startTransform.setOrigin(initialPosition);

	btDefaultMotionState *myMotionState = new btDefaultMotionState(startTransform);

	//myMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));

	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI
		(
		0,  // mass
		myMotionState,// initial position
		mShape,      // collision shape of body
		inertia   // local inertia
		);

	App->GDCL_Scene_Data->S_Object[Index]->bt_body = new btRigidBody(rigidBodyCI);
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->clearForces();
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setLinearVelocity(btVector3(0, 0, 0));
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setAngularVelocity(btVector3(0, 0, 0));
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setWorldTransform(startTransform);

	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setCustomDebugColor(btVector3(0,1,1));
	int f = App->GDCL_Scene_Data->S_Object[Index]->bt_body->getCollisionFlags();
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setCollisionFlags(f|btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);
	
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setUserIndex(123);
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->setUserIndex2(Index);

	App->GDCL_Bullet->dynamicsWorld->addRigidBody(App->GDCL_Scene_Data->S_Object[Index]->bt_body);

	return mShape;
}

// *************************************************************************
// *	  				GetMesh_Center Terry Bernie						   *
// *************************************************************************
Ogre::Vector3 GD_Add_Objects::GetMesh_Center(int Index,SceneNode* mNode)
{
	AxisAlignedBox aab = mNode->getAttachedObject(0)->getBoundingBox();//getBoundingBox(); 
	Ogre::Vector3 min = aab.getMinimum()*mNode->getScale();
	Ogre::Vector3 max = aab.getMaximum()*mNode->getScale();
	Ogre::Vector3 center = aab.getCenter()*mNode->getScale();
	Ogre::Vector3 size(fabs(max.x-min.x),fabs(max.y-min.y),fabs(max.z-min.z));
	float radius = (size.x>size.z)?size.z/2.0f:size.x/2.0f;

	return center;
}

// *************************************************************************
// *	  				GetMesh_BB_Data Terry Bernie					   *
// *************************************************************************
bool GD_Add_Objects::GetMesh_BB_Data(int SL,Ogre::SceneNode *Node)
{
	Ogre::Vector3 Dimen = GetMesh_BB_Size(Node);
	
	App->GDCL_Scene_Data->S_Object[SL]->Mesh_BB_Width=Dimen.x;
	App->GDCL_Scene_Data->S_Object[SL]->Mesh_BB_Height=Dimen.y;
	App->GDCL_Scene_Data->S_Object[SL]->Mesh_BB_Depth=Dimen.z;

	App->GDCL_Scene_Data->S_Object[SL]->Mesh_BB_Quat=Node->getOrientation();

	Ogre::Vector3 Cent = GetMesh_Center(SL,Node);
	App->GDCL_Scene_Data->S_Object[SL]->Mesh_BB_Center = Cent;
	return 1;
}

// *************************************************************************
// *	  				GetMesh_BB_Size Terry Bernie					   *
// *************************************************************************
Ogre::Vector3 GD_Add_Objects::GetMesh_BB_Size(SceneNode* mNode)
{
	AxisAlignedBox aab = mNode->getAttachedObject(0)->getBoundingBox(); 
	Ogre::Vector3 min = aab.getMinimum()*mNode->getScale();
	Ogre::Vector3 max = aab.getMaximum()*mNode->getScale();
	Ogre::Vector3 center = aab.getCenter()*mNode->getScale();
	Ogre::Vector3 size(fabs(max.x-min.x),fabs(max.y-min.y),fabs(max.z-min.z));
	float radius = (size.x>size.z)?size.z/2.0f:size.x/2.0f;

	return size;
}

// *************************************************************************
// *	  				GetMesh_BB_Radius Terry Bernie					   *
// *************************************************************************
float GD_Add_Objects::GetMesh_BB_Radius(SceneNode* mNode)
{
	AxisAlignedBox aab = mNode->getAttachedObject(0)->getBoundingBox(); 
	Ogre::Vector3 min = aab.getMinimum()*mNode->getScale();
	Ogre::Vector3 max = aab.getMaximum()*mNode->getScale();
	Ogre::Vector3 center = aab.getCenter()*mNode->getScale();
	Ogre::Vector3 size(fabs(max.x-min.x),fabs(max.y-min.y),fabs(max.z-min.z));
	float radius = (size.x>size.z)?size.z/2.0f:size.x/2.0f;

	return radius;
}

// *************************************************************************
//						Set_Physics_PosRot Terry Bernie					   *
// *************************************************************************
btTransform GD_Add_Objects::Set_Physics_PosRot(int Object_Index)
{
	int Index = Object_Index;

	btTransform startTransform;
	startTransform.setIdentity();

	//------------ Position
	float x = App->GDCL_Scene_Data->S_Object[Index]->Physics_Pos.x;
	float y = App->GDCL_Scene_Data->S_Object[Index]->Physics_Pos.y;
	float z = App->GDCL_Scene_Data->S_Object[Index]->Physics_Pos.z;
	startTransform.setOrigin(btVector3(x,y,z));

	//------------ Rotation
	float rw = App->GDCL_Scene_Data->S_Object[Index]->Physics_Quat.w;
	float rx = App->GDCL_Scene_Data->S_Object[Index]->Physics_Quat.x;
	float ry = App->GDCL_Scene_Data->S_Object[Index]->Physics_Quat.y;
	float rz = App->GDCL_Scene_Data->S_Object[Index]->Physics_Quat.z;
	startTransform.setRotation(btQuaternion(rx,ry,rz,rw));

	return startTransform;
}

// *************************************************************************
//						Set_Physics_Scale Terry Bernie					   *
// *************************************************************************
void GD_Add_Objects::Set_Physics_Scale(int Object_Index)
{
	int Index = Object_Index;

	//------------ Scale
	float sx = App->GDCL_Scene_Data->S_Object[Index]->Physics_Scale.x;
	float sy = App->GDCL_Scene_Data->S_Object[Index]->Physics_Scale.y;
	float sz = App->GDCL_Scene_Data->S_Object[Index]->Physics_Scale.z;
	App->GDCL_Scene_Data->S_Object[Index]->bt_body->getCollisionShape()->setLocalScaling(btVector3(sx,sy,sz));
}
