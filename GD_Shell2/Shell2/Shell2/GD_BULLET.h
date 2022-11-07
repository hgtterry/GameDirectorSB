#pragma once
class GD_BULLET
{
public:
	GD_BULLET(void);
	~GD_BULLET(void);

	bool Init_Bullet();
	void Reset_Physics(void);
	
	//GD_Debug M_Debug;

	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btBroadphaseInterface* overlappingPairCache;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;
	std::vector<btCollisionShape *> collisionShapes;

	bool GD_Physics_On;
	bool GD_Reset_Player;

protected:
	
};

