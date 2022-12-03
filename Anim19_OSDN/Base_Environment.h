/*
Copyright (c) 2022 GameDirectorSB and EquityME -- HGTInflanite Software W.T.Flanigan H.C.Flanigan

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
class Base_Environment
{
public:
	Base_Environment();
	~Base_Environment();

	void Set_Environment_Defaults();

	bool Deleted;
	bool Altered;

	int This_Object_ID;  // Unique Number
	char Name[MAX_PATH];				
	HTREEITEM FileViewItem;

	//--------------- Sound
	irrklang::ISound* SndFile;
	Ogre::Real SndVolume;
	char Sound_File[MAX_PATH];
	bool Play;
	bool Loop;

	//--------------- Light
	Ogre::Vector3 AmbientColour;
	Ogre::Vector3 DiffuseColour;
	Ogre::Vector3 SpecularColour;
	Ogre::Vector3 Light_Position;

	//--------------- Sky
	bool Enabled;
	int type;
	char Material[MAX_PATH];
	float Curvature;
	float Tiling;
	float Distance;

	//--------------- Fog
	int Fog_On;
	int Fog_Mode;
	Ogre::Vector3 Fog_Colour;
	float Fog_Start;
	float Fog_End;
	float Fog_Density;
};

