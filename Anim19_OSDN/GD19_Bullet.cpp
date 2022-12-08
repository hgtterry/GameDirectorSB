#include "StdAfx.h"
#include "GD19_App.h"
#include "resource.h"
#include "GD19_Bullet.h"


SB_Bullet::SB_Bullet(void)
{
	collisionConfiguration = NULL;
	dispatcher = NULL;
	overlappingPairCache = NULL;
	solver = NULL;
	dynamicsWorld = NULL;

	GD_Physics_On = 1;
	Physics_Dlg_Active = 0;
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

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	dispatcher = new	btCollisionDispatcher(collisionConfiguration);

	///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
	overlappingPairCache = new btDbvtBroadphase();

	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	solver = new btSequentialImpulseConstraintSolver;

	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,overlappingPairCache,solver,collisionConfiguration);

	//dynamicsWorld->getDebugDrawer()->setDebugMode( btIDebugDraw::DBG_DrawWireframe);
	
	dynamicsWorld->setGravity(btVector3(0,-30,0));
	dynamicsWorld->getDispatchInfo().m_allowedCcdPenetration = 0.00001f;

	btAlignedObjectArray<btCollisionShape*> collisionShapes;

	return 0;
}



