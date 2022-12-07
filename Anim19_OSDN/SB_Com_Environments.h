/*
Copyright (c) 2021 GameDirectorSB and EquityME -- HGTInflanite Software W.T.Flanigan H.C.Flanigan

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
class SB_Com_Environments
{
public:
	SB_Com_Environments();
	~SB_Com_Environments();

	void Rename_Environ(int Index);
	void GameMode(bool Is_On);
	bool Add_New_Environ_Entity(bool FirstOne);
	bool Create_Environ_Entity(int Index);
	void Set_Environ_Defaults(int Index);
	void Set_First_Environment(int Index);
	void Mark_As_Altered_Environ(int Index);

	int Set_Environment_By_Index(bool PlayMusic, int Index);

	int Get_First_Environ();

	bool EnableFog(bool SetFog);
	void EnableFog_Collision(bool SetFog, int Index);

	void Set_Environment_From_Environ(int Index);
};

