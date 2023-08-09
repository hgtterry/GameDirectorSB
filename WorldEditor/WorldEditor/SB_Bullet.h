#pragma once

class SB_Bullet
{
public:
	SB_Bullet(void);
	~SB_Bullet(void);

	bool Init_Bullet();
	
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btBroadphaseInterface* overlappingPairCache;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;
	std::vector<btCollisionShape *> collisionShapes;

	bool GD_Physics_On;
	bool Physics_Dlg_Active;

protected:
	
};

