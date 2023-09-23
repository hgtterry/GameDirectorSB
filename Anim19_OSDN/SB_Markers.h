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
class SB_Markers
{
public:
	SB_Markers(void);
	~SB_Markers(void);

	void Set_Markers();

	bool MarkerBB_Setup(void);
	bool MarkerBB_Update(float Depth, float Height, float Width);
	void MarkerBB_Addjust(int Index);

	void Load_PickSight(void);
	void Load_Arrow();
	void Load_Target_Hit();
	void Load_All_Axis();

	void Load_Red_Axis();
	void Load_Green_Axis();
	void Load_Blue_Axis();

	void Load_Blue_Rot_Axis();


	void Update_Red_Axis_Marker(int Index);
	void Update_Green_Axis_Marker(int Index);
	void Update_Blue_Axis_Marker(int Index);

	void Hide_Axis_Marker();

	void Move_Arrow(Ogre::Vector3 pos);
	void Move_Target_Hit(Ogre::Vector3 pos);

	ManualObject*		BoxManual;
	SceneNode*			BoxNode;

	Ogre::Entity*		Target_Hit_Ent;
	Ogre::SceneNode*	Target_Hit_Node;

	Ogre::Entity*		Arrow_Ent;
	Ogre::SceneNode*	Arrow_Node;

	Ogre::Overlay*		mPickSight;

	Ogre::Entity*		RedAxis_Ent;
	Ogre::SceneNode*	RedAxis_Node;

	Ogre::Entity*		GreenAxis_Ent;
	Ogre::SceneNode*	GreenAxis_Node;

	Ogre::Entity*		BlueAxis_Ent;
	Ogre::SceneNode*	BlueAxis_Node;

	Ogre::Entity*		BlueRotAxis_Ent;
	Ogre::SceneNode*	BlueRotAxis_Node;

	Ogre::Entity* Sight_Entity;
	Ogre::SceneNode* Sight_Node;
};

