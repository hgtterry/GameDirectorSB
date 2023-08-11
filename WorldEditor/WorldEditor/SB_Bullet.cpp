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

	Debug
	return 0;
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
	Phys_Body->setCollisionFlags(f & (~(1 << 5)));
	//Object->Type = Enums::Bullet_Type_TriMesh;
	//Object->Shape = Enums::Shape_TriMesh;
	
	
	Phys_Body->setUserIndex(123);
	Phys_Body->setUserIndex2(Index);
	
	dynamicsWorld->addRigidBody(Phys_Body);
	
	//Object->Physics_Valid = 1;
	//App->SBC_Physics->Set_Physics(Index);

	return mShape;

}


