#include "StdAfx.h"
#include "AB_App.h"
#include "resource.h"
#include "SB_Bullet.h"


SB_Bullet::SB_Bullet(void)
{
	collisionConfiguration = NULL;
	dispatcher = NULL;
	overlappingPairCache = NULL;
	solver = NULL;
	dynamicsWorld = NULL;

	GD_Physics_On = 1;
	Physics_Dlg_Active = 0;

	Phys_Body = NULL;
}


SB_Bullet::~SB_Bullet(void)
{
}

// *************************************************************************
// *						Init_Bullet Terry Bernie   			 	 	   *
// *************************************************************************
bool SB_Bullet::Init_Bullet()
{
	collisionConfiguration = new btDefaultCollisionConfiguration();

	//use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	dispatcher = new	btCollisionDispatcher(collisionConfiguration);

	//btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
	overlappingPairCache = new btDbvtBroadphase();

	//the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	solver = new btSequentialImpulseConstraintSolver;

	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,overlappingPairCache,solver,collisionConfiguration);

	//dynamicsWorld->getDebugDrawer()->setDebugMode( btIDebugDraw::DBG_DrawWireframe);
	
	dynamicsWorld->setGravity(btVector3(0,-30,0));
	dynamicsWorld->getDispatchInfo().m_allowedCcdPenetration = 0.00001f;

	btAlignedObjectArray<btCollisionShape*> collisionShapes;

	//Debug
	return 0;
}

// *************************************************************************
//			Create_Brush_Trimesh:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
btBvhTriangleMeshShape* SB_Bullet::Create_Brush_Trimesh(int Index)
{

	// Create the triangle mesh
	btTriangleMesh* triMesh = NULL;
	btVector3 vert0, vert1, vert2;
	int i = 0;

	if (triMesh == nullptr)
	{
		triMesh = new btTriangleMesh(true);
	}

	int BrushCount = App->CLSB_Model->XBrushCount;
	int Count = 0;
	while (Count < BrushCount)
	{
		bool test = strcmp(App->CLSB_Model->B_XBrush[Count]->BrushName, "XYZ");
		if (App->Centre_Debug == 1 && test == 0)
		{

		}
		else
		{

			int A = 0;
			int B = 0;
			int C = 0;

			int BrushLoop = 0;
			int SubBrushCount = App->CLSB_Model->B_XBrush[Count]->Brush_Count;

			while (BrushLoop < SubBrushCount)
			{
				int FaceCount = 0;
				while (FaceCount < App->CLSB_Model->B_XBrush[Count]->B_Brush[BrushLoop]->Face_Count)
				{
					A = App->CLSB_Model->B_XBrush[Count]->B_Brush[BrushLoop]->Face_Data[FaceCount].a;
					B = App->CLSB_Model->B_XBrush[Count]->B_Brush[BrushLoop]->Face_Data[FaceCount].b;
					C = App->CLSB_Model->B_XBrush[Count]->B_Brush[BrushLoop]->Face_Data[FaceCount].c;

					vert0.setValue(App->CLSB_Model->B_XBrush[Count]->B_Brush[BrushLoop]->vertex_Data[A].x, App->CLSB_Model->B_XBrush[Count]->B_Brush[BrushLoop]->vertex_Data[A].y, App->CLSB_Model->B_XBrush[Count]->B_Brush[BrushLoop]->vertex_Data[A].z);
					vert1.setValue(App->CLSB_Model->B_XBrush[Count]->B_Brush[BrushLoop]->vertex_Data[B].x, App->CLSB_Model->B_XBrush[Count]->B_Brush[BrushLoop]->vertex_Data[B].y, App->CLSB_Model->B_XBrush[Count]->B_Brush[BrushLoop]->vertex_Data[B].z);
					vert2.setValue(App->CLSB_Model->B_XBrush[Count]->B_Brush[BrushLoop]->vertex_Data[C].x, App->CLSB_Model->B_XBrush[Count]->B_Brush[BrushLoop]->vertex_Data[C].y, App->CLSB_Model->B_XBrush[Count]->B_Brush[BrushLoop]->vertex_Data[C].z);

					triMesh->addTriangle(vert0, vert1, vert2);

					FaceCount++;
				}

				BrushLoop++;
			}
		}
		
		Count++;
	}

	const bool useQuantizedAABB = true;
	btBvhTriangleMeshShape* mShape = new btBvhTriangleMeshShape(triMesh, false, true);
	//mShape->buildOptimizedBvh();

	float x = 0; 
	float y = 0; 
	float z = 0; 

	btVector3 inertia(0, 0, 0);
	mShape->calculateLocalInertia(0.0, inertia);

	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setRotation(btQuaternion(0.0f, 0.0f, 0.0f, 1));
	btVector3 initialPosition(x, y, z);
	startTransform.setOrigin(initialPosition);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI
	(
		0,  // mass
		myMotionState,// initial position
		mShape,      // collision shape of body
		inertia   // local inertia
	);

	if (Phys_Body)
	{
		dynamicsWorld->removeCollisionObject(Phys_Body);
		Phys_Body = NULL;
	}

	Phys_Body = new btRigidBody(rigidBodyCI);
	Phys_Body->clearForces();
	Phys_Body->setLinearVelocity(btVector3(0, 0, 0));
	Phys_Body->setAngularVelocity(btVector3(0, 0, 0));
	Phys_Body->setWorldTransform(startTransform);

	int f = Phys_Body->getCollisionFlags();
	Phys_Body->setCollisionFlags(f | btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);

	//Phys_Body->setCollisionFlags(f & (~(1 << 5)));
	
	Phys_Body->setUserIndex(123);
	Phys_Body->setUserIndex2(Index);

	dynamicsWorld->addRigidBody(Phys_Body);

	return mShape;
}

// *************************************************************************
//			Create_Brush_Trimesh_XX:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
btBvhTriangleMeshShape* SB_Bullet::Create_Brush_Trimesh_XX(int Index)
{

	// Create the triangle mesh
	btTriangleMesh* triMesh = NULL;
	btVector3 vert0, vert1, vert2;
	int i = 0;

	if (triMesh == nullptr)
	{
		triMesh = new btTriangleMesh(true);
	}

	int BrushCount = App->CLSB_Model->BrushCount;
	int Count = 0;
	while (Count < BrushCount)
	{
		int A = 0;
		int B = 0;
		int C = 0;
		int FaceCount = 0;


		while (FaceCount < App->CLSB_Model->B_Brush[Count]->Face_Count)
		{
			A = App->CLSB_Model->B_Brush[Count]->Face_Data[FaceCount].a;
			B = App->CLSB_Model->B_Brush[Count]->Face_Data[FaceCount].b;
			C = App->CLSB_Model->B_Brush[Count]->Face_Data[FaceCount].c;

			vert0.setValue(App->CLSB_Model->B_Brush[Count]->vertex_Data[A].x, App->CLSB_Model->B_Brush[Count]->vertex_Data[A].y, App->CLSB_Model->B_Brush[Count]->vertex_Data[A].z);
			vert1.setValue(App->CLSB_Model->B_Brush[Count]->vertex_Data[B].x, App->CLSB_Model->B_Brush[Count]->vertex_Data[B].y, App->CLSB_Model->B_Brush[Count]->vertex_Data[B].z);
			vert2.setValue(App->CLSB_Model->B_Brush[Count]->vertex_Data[C].x, App->CLSB_Model->B_Brush[Count]->vertex_Data[C].y, App->CLSB_Model->B_Brush[Count]->vertex_Data[C].z);

			triMesh->addTriangle(vert0, vert1, vert2);

			FaceCount++;
		}


		Count++;
	}

	const bool useQuantizedAABB = true;
	btBvhTriangleMeshShape* mShape = new btBvhTriangleMeshShape(triMesh, false, true);
	//mShape->buildOptimizedBvh();

	float x = 0; // Object->Object_Node->getPosition().x;
	float y = 0; //Object->Object_Node->getPosition().y;
	float z = 0; //Object->Object_Node->getPosition().z;


	btVector3 inertia(0, 0, 0);
	mShape->calculateLocalInertia(0.0, inertia);

	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setRotation(btQuaternion(0.0f, 0.0f, 0.0f, 1));
	btVector3 initialPosition(x, y, z);
	startTransform.setOrigin(initialPosition);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);


	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI
	(
		0,  // mass
		myMotionState,// initial position
		mShape,      // collision shape of body
		inertia   // local inertia
	);

	if (Phys_Body)
	{
		dynamicsWorld->removeCollisionObject(Phys_Body);
		Phys_Body = NULL;
	}

	Phys_Body = new btRigidBody(rigidBodyCI);
	Phys_Body->clearForces();
	Phys_Body->setLinearVelocity(btVector3(0, 0, 0));
	Phys_Body->setAngularVelocity(btVector3(0, 0, 0));
	Phys_Body->setWorldTransform(startTransform);

	int f = Phys_Body->getCollisionFlags();
	Phys_Body->setCollisionFlags(f | btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);

	//Phys_Body->setCollisionFlags(f & (~(1 << 5)));

	Phys_Body->setUserIndex(123);
	Phys_Body->setUserIndex2(Index);

	dynamicsWorld->addRigidBody(Phys_Body);

	return mShape;
}

// *************************************************************************
//			Create_New_Trimesh:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
btBvhTriangleMeshShape* SB_Bullet::create_New_Trimesh(int Index)
{

	// Create the triangle mesh
	btTriangleMesh* triMesh = NULL;
	btVector3 vert0, vert1, vert2;
	int i = 0;

	// -------------------------------------------------------
	// We now have vertices and indices ready to go
	// ----

	if (triMesh == nullptr)
	{
		triMesh = new btTriangleMesh(true);
	}

	int Count = 0;
	int GroupCount = App->CLSB_Model->Get_Groupt_Count();
	while (Count < GroupCount)
	{
		int A = 0;
		int B = 0;
		int C = 0;
		int FaceCount = 0;

		if (App->Centre_Debug == 1 && App->CLSB_Model->Group[Count]->Dont_Use == 1)
		{

		}
		else
		{
			while (FaceCount < App->CLSB_Model->Group[Count]->GroupFaceCount)
			{
				A = App->CLSB_Model->Group[Count]->Face_Data[FaceCount].a;
				B = App->CLSB_Model->Group[Count]->Face_Data[FaceCount].b;
				C = App->CLSB_Model->Group[Count]->Face_Data[FaceCount].c;

				vert0.setValue(App->CLSB_Model->Group[Count]->vertex_Data[A].x, App->CLSB_Model->Group[Count]->vertex_Data[A].y, App->CLSB_Model->Group[Count]->vertex_Data[A].z);
				vert1.setValue(App->CLSB_Model->Group[Count]->vertex_Data[B].x, App->CLSB_Model->Group[Count]->vertex_Data[B].y, App->CLSB_Model->Group[Count]->vertex_Data[B].z);
				vert2.setValue(App->CLSB_Model->Group[Count]->vertex_Data[C].x, App->CLSB_Model->Group[Count]->vertex_Data[C].y, App->CLSB_Model->Group[Count]->vertex_Data[C].z);

				triMesh->addTriangle(vert0, vert1, vert2);

				FaceCount++;
			}
		}

		Count++;
	}

	const bool useQuantizedAABB = true;
	btBvhTriangleMeshShape* mShape = new btBvhTriangleMeshShape(triMesh, false, true);
	//mShape->buildOptimizedBvh();

	float x = 0; // Object->Object_Node->getPosition().x;
	float y = 0; //Object->Object_Node->getPosition().y;
	float z = 0; //Object->Object_Node->getPosition().z;


	btVector3 inertia(0, 0, 0);
	mShape->calculateLocalInertia(0.0, inertia);

	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setRotation(btQuaternion(0.0f, 0.0f, 0.0f, 1));
	btVector3 initialPosition(x, y, z);
	startTransform.setOrigin(initialPosition);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);


	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI
	(
		0,  // mass
		myMotionState,// initial position
		mShape,      // collision shape of body
		inertia   // local inertia
	);

	if (Phys_Body)
	{
		dynamicsWorld->removeCollisionObject(Phys_Body);
		Phys_Body = NULL;
	}

	Phys_Body = new btRigidBody(rigidBodyCI);
	Phys_Body->clearForces();
	Phys_Body->setLinearVelocity(btVector3(0, 0, 0));
	Phys_Body->setAngularVelocity(btVector3(0, 0, 0));
	Phys_Body->setWorldTransform(startTransform);
	
	int f = Phys_Body->getCollisionFlags();
	Phys_Body->setCollisionFlags(f | btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);

	//Phys_Body->setCollisionFlags(f & (~(1 << 5)));
	//Object->Type = Enums::Bullet_Type_TriMesh;
	//Object->Shape = Enums::Shape_TriMesh;
	
	
	Phys_Body->setUserIndex(123);
	Phys_Body->setUserIndex2(Index);
	
	dynamicsWorld->addRigidBody(Phys_Body);
	
	//Object->Physics_Valid = 1;
	//App->SBC_Physics->Set_Physics(Index);

	return mShape;

}

// *************************************************************************
// *	  		Reset_Physics:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void SB_Bullet::Reset_Physics(void)
{
	App->CLSB_Ogre->OgreListener->GD_Run_Physics = 0;

	float w = 1;
	float x = 0;
	float y = 0;
	float z = 0;

	int Count = 0;
	while (Count < App->CLSB_Scene->Object_Count)
	{
		if (App->CLSB_Scene->V_Object[Count]->Usage == Enums::Usage_Dynamic)
		{
			btVector3 zeroVector(0, 0, 0);

			x = 0; //App->CLSB_Scene->V_Object[Count]->Physics_Pos.x;
			y = -10; // App->CLSB_Scene->V_Object[Count]->Physics_Pos.y;
			z = -50;// App->CLSB_Scene->V_Object[Count]->Physics_Pos.z;
			btVector3 initialPosition(x, y, z);

			btTransform startTransform;
			startTransform.setIdentity();

			/*startTransform.setRotation(btQuaternion(App->CLSB_Scene->V_Object[Count]->Physics_Quat.x,
				App->CLSB_Scene->V_Object[Count]->Physics_Quat.y,
				App->CLSB_Scene->V_Object[Count]->Physics_Quat.z,
				App->CLSB_Scene->V_Object[Count]->Physics_Quat.w));*/

			startTransform.setOrigin(initialPosition);

			App->CLSB_Scene->V_Object[Count]->Phys_Body->clearForces();
			App->CLSB_Scene->V_Object[Count]->Phys_Body->setLinearVelocity(zeroVector);
			App->CLSB_Scene->V_Object[Count]->Phys_Body->setAngularVelocity(zeroVector);

			App->CLSB_Scene->V_Object[Count]->Phys_Body->setWorldTransform(startTransform);
			App->CLSB_Scene->V_Object[Count]->Phys_Body->getMotionState()->setWorldTransform(startTransform);
			App->CLSB_Scene->V_Object[Count]->Phys_Body->activate(true);

			App->CLSB_Scene->V_Object[Count]->Object_Node->setPosition(0, -10, -50);
			//App->CLSB_Scene->V_Object[Count]->Object_Node->setOrientation(App->CLSB_Scene->V_Object[Count]->Mesh_Quat);

		}

		Count++;
	}

	if (App->CLSB_Scene->Player_Added == 1)// && GD_Reset_Player == 1)
	{
		btVector3 zeroVector(0, 0, 0);

		x = App->CLSB_Scene->B_Player[0]->StartPos.x;
		y = App->CLSB_Scene->B_Player[0]->StartPos.y;
		z = App->CLSB_Scene->B_Player[0]->StartPos.z;

		btVector3 initialPosition(x, y, z);

		btTransform startTransform;
		startTransform.setIdentity();
		startTransform.setRotation(btQuaternion(1.0f, 0.0f, 0.0f, 0.0f));
		startTransform.setOrigin(initialPosition);

		App->CLSB_Scene->B_Player[0]->Phys_Body->clearForces();
		App->CLSB_Scene->B_Player[0]->Phys_Body->setLinearVelocity(zeroVector);
		App->CLSB_Scene->B_Player[0]->Phys_Body->setAngularVelocity(zeroVector);

		App->CLSB_Scene->B_Player[0]->Phys_Body->setWorldTransform(startTransform);
		App->CLSB_Scene->B_Player[0]->Phys_Body->getMotionState()->setWorldTransform(startTransform);
		App->CLSB_Scene->B_Player[0]->Phys_Body->activate(true);

		App->CLSB_Scene->B_Player[0]->Phys_Body->getWorldTransform().setRotation(App->CLSB_Scene->B_Player[0]->Physics_Rotation);
	}

	App->CLSB_Dialogs->YesNo("Physics", "Do you want to restart Physics");

	bool Doit = App->CLSB_Dialogs->Canceled;
	if (Doit == 0)
	{
		App->CLSB_Ogre->OgreListener->GD_Run_Physics = 1;
	}

}



