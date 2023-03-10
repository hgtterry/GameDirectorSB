/*
Copyright (c) 2022 - 2023 GameDirectorSB and EquityME -- HGTInflanite Software W.T.Flanigan H.C.Flanigan

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
class SB_Com_Entity
{
public:
	SB_Com_Entity();
	~SB_Com_Entity();

	// ------------------------------------------ Teleporters
	bool Add_New_Teleporter();
	bool Create_Teleport_Entity(int Index);
	void Set_Teleports_Defaults(int Index);
	void V_Set_Teleports_Defaults(int Index);

	// ------------------------------------------ Sounds
	bool Add_New_Sound();
	bool Create_Sound_Entity(int Index);

	// ------------------------------------------ Messages
	bool Add_New_Message();
	bool Create_Message_Entity(int Index);
	void Set_Message_Defaults(int Index);
	void V_Set_Message_Defaults(int Index);

	// ------------------------------------------ Particles
	void Add_New_Particle(char* Script);
	void CreateParticle(int Index);
	void Set_Particle_Defaults(int Index);
	void V_Set_Particle_Defaults(int Index);

	// ------------------------------------------ Collectables
	bool Add_New_Collectable();
	bool Create_Collectable_Entity(int Index);
	void Set_Collectables_Defaults(int Index);
	void V_Set_Collectables_Defaults(int Index);

	// ------------------------------------------ User_Objects
	void Add_New_User_Object(void);
	void Create_User_Object(int Index);
	void Set_User_Objects_Defaults(int Index);
};

