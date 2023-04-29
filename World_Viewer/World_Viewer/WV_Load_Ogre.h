#pragma once

/*
Copyright (c) World_Viewer 2023 Inflanite Software W.T.Flanigan H.C.Flanigan

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
*/ // :- Terry and Hazel Flanigan 2023

class WV_Load_Ogre
{
public:
	WV_Load_Ogre(void);
	~WV_Load_Ogre(void);

	void AddToScene(void);

	btBvhTriangleMeshShape* Create_Area_Trimesh(int Index, Base_Area* Object);

	void Set_Physics(int Index);
	void Set_Area_Defaults(int Index);

	char ResourcePath[MAX_PATH];
	char ModelName[MAX_PATH];

	Ogre::String TempResourceGroup;   // Tempory Reosource Group
};

