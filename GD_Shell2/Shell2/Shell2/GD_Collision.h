#pragma once
class GD_Collision
{
public:
	GD_Collision(void);
	~GD_Collision(void);

	bool Sound_Entity(int Index);
	bool Message_Entity(int Index);

	bool Move_Entity(int Index);
	void MoveObject(Ogre::Real Time);

	bool Do_Collectable(int Index);

	bool Do_Teleport(int Index);

	float FinalPosition;
	int ObjectIndex;
	bool DoMove;

	float x;
	float y;
	float z;

	float px;
	float py;
	float pz;

protected:

	bool Play_Sound(int Index);
};

