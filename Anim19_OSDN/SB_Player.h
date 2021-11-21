/*
Copyright (c) 2021 Scene Builder and Equity -- Inflanite Software W.T.Flanigan H.C.Flanigan

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

#pragma once
class SB_Player
{
public:
	SB_Player();
	~SB_Player();

	bool Start_Player_PropsPanel();
	void Hide_Player_Dlg(bool Show);

	void SetUp(void);
	void Load_Player(void);

	void Move_Right(void);
	void Move_Left(void);

	void Stop(void);
	void Forward(float delta);
	void Back(void);
	void Rotate(const Ogre::Vector3 axis, bool normalize);
	void Rotate_FromCam(const Ogre::Vector3 axis, float delta, bool normalize);
	void Jump(const Ogre::Vector3 axis, float force);
	bool OnGround() const;

	void Adjust_Capsule(void);

	void PostStep(btCollisionWorld *collisionWorld);
	void Check_Collisions(void);

	void Save_Location(char* name);
	void Goto_Location(int Index);

	btRigidBody *mObject;
	btCollisionShape *mShape;

	Ogre::Camera*		CameraPitch;
	Ogre::Entity*		Player_Ent;
	Ogre::SceneNode*	Player_Node;

	char Player_Name[255];	// Player Name [211121]
	bool mOnGround;
	bool IsMOving;
	bool IsMOving_Back;
	bool IsMOving_Right;
	bool IsMOving_Left;

	int Round;
	float Distance;
	int Life_Time;
	int ColisionIndex;
	int Last_ColisionIndex;

	Ogre::Vector3 StartPos;

	bool is_Animated;

	bool Toggle_Objects_Flag;
	bool Toggle_Physics_Flag;

	bool ShowDebug;
	bool PlayerAdded;
	float Ground_speed;

	float PlayerHeight;
	float TurnRate;

	float Capsule_Mass;
	float Capsule_Radius;
	float Capsule_Height;

	float Forward_Timer;

	HWND Player_Props_HWND;

	// Strucure to be
	Ogre::Vector3 Current_Position;
	btVector3 Physics_Position;
	btQuaternion Physics_Rotation;

	HTREEITEM ListViewItem;


protected:

	static LRESULT CALLBACK Player_PropsPanel_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	void Initialize(const Ogre::Vector3 p, float mass, float radius, float height);
	
};

