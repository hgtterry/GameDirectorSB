#pragma once

//#include "GD_Debug.h"


class SB_Bullet
{
public:
	SB_Bullet(void);
	~SB_Bullet(void);

	bool Init_Bullet();
	void Start_Physics_Console(void);
	
	//GD_Debug M_Debug;

	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btBroadphaseInterface* overlappingPairCache;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;
	std::vector<btCollisionShape *> collisionShapes;

	bool GD_Physics_On;
	bool GD_Reset_Player;
	bool Physics_Dlg_Active;

protected:
	static LRESULT CALLBACK Physics_Console_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

};

