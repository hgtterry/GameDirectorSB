/*
Copyright (c) Vima19 Inflanite Software W.T.Flanigan H.C.Flanigan

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
class SB_Collision
{

public:
	SB_Collision();
	~SB_Collision();

	bool Message_Entity(int Index);
	bool Play_Sound(int Index);

	bool Move_Entity_Collision(int Index);
	void Set_Move_Entity(int Index);
	void MoveObject_Listener(Ogre::Real Time);

	bool Do_Teleport(int Index);
	bool Do_Collectable(int Index);
	bool Do_Environment(int Index);

	float FinalPosition;
	int ObjectIndex;
	bool DoMove;

	int Old_Sound_Index;

	float x;
	float y;
	float z;

	float px;
	float py;
	float pz;

};

