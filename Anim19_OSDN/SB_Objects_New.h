/*
	Copyright (c) GD10 (GameDirector) 2019 Inflanite Software W.T.Flanigan H.C.Flanigan B.Parkin

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
class SB_Objects_New
{
public:
	SB_Objects_New(void);
	~SB_Objects_New(void);

	bool Add_New_CollectableEntity();
	bool Add_New_MessageEntity();
	bool Add_New_MoveEntity();
	bool Add_New_SoundEntity();
	bool Add_New_TeleportEntity();
	bool Add_New_EnvironmentEntity();
	bool Add_New_Area_Change();
	bool Add_New_Change_Level();

	bool Add_New_Area(void);

	bool Add_New_Particle();

	void Add_New_Physics_Static_Box(bool Dynamic);
	void Add_New_Physics_Static_Sphere(bool Dynamic);
	void Add_New_Physics_Static_Capsule(bool Dynamic);
	void Add_New_Physics_Static_Cylinder(bool Dynamic);
	void Add_New_Physics_Static_Cone(bool Dynamic);

	void Add_Stock_Message();
	void Add_Stock_Sound();
	void Add_Stock_Panel();

	Ogre::Vector3 Get_BoundingBox_World_Centre(int Object_Index);
	void Add_Physics_Volume_Box();
};

