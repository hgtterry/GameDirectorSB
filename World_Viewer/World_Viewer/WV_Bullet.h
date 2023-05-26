#pragma once

class WV_Bullet
{
public:
	WV_Bullet(void);
	~WV_Bullet(void);

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

