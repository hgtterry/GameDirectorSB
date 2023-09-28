#pragma once

/*
Copyright (c) 2023 World Editor -- HGT Software W.T.Flanigan H.C.Flanigan

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

class SB_Environment
{
public:
	SB_Environment(void);
	~SB_Environment(void);

	bool Add_New_Environ_Entity(bool FirstOne);
	void V_Set_Environ_Defaults(int Index);
	void Set_First_Environment(int Index);
	void Mark_As_Altered_Environ(int Index);
	int Set_Environment_By_Index(bool PlayMusic, int Index);
	int Get_First_Environ();



	void Start_Environment_Editor(int Index, bool IsTeleport);
	void Environ_PropertyEditor();
	void Close_Environment_Editor();
	void Set_To_PlayerView();
	void SetSky(bool Enable);
	bool EnableFog(bool SetFog);

	bool Show_PropertyEditor;

protected:

	int PropertyEditor_Page;

	// Ambient
	int Ambient_Int_Red;
	int Ambient_Int_Green;
	int Ambient_Int_Blue;
	ImVec4 Ambient_Colour_Copy;
	ImVec4 Ambient_Colour;

	// Fog Colour
	int Fog_Colour_Int_Red;
	int Fog_Colour_Int_Green;
	int Fog_Colour_Int_Blue;
	ImVec4 Fog_Colour_Copy;
	ImVec4 Fog_Colour;

	int Eviron_Index;

	bool Float_Exit;

	bool Is_Teleport;

	float Float_PosX;
	float Float_PosY;
	bool Float_StartPos;

	bool ClickOnTrack;
	bool ClickOnVolume;
	bool ClickOnPlay;
	bool ClickOnLoop;

	bool ClickOnFogVisible;
	bool ClickOnFogMode;
	bool ClickOnFogColour;
	bool ClickOnFogStart;
	bool ClickOnFogEnd;

	bool ClickOnSkyEnabled;
	bool ClickOnSkyTiling;
	bool ClickOnSkyCurve;
};

