#pragma once
class GD19_Collision
{
public:
	GD19_Collision(void);
	~GD19_Collision(void);

	bool Sound_Entity(int Index);
	bool Message_Entity(int Index);
	bool Move_Entity(int Index);

	bool Do_Collectable(int Index);
	bool Do_Teleport(int Index);

	bool Do_Environment(int Index);

	void MoveObject(Ogre::Real Time);

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

