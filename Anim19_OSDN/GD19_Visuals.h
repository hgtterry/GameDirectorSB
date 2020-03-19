#pragma once
class GD19_Visuals
{
public:
	GD19_Visuals(void);
	~GD19_Visuals(void);

	void Load_PickSight(void); // BERNIE_GUN_SIGHT
	bool MarkerBB_Setup(void);
	bool MarkerBB_Update(float Depth,float Height,float Width);
	void MarkerBB_Addjust(int Index);

	Ogre::Overlay*	mPickSight;

	ManualObject*	BoxManual;
	SceneNode*		BoxNode;
};

