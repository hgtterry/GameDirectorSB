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

#pragma once
class SB_Camera_EQ
{
public:
	SB_Camera_EQ(void);
	~SB_Camera_EQ(void);

	void Reset_View(void);
	void Reset_Orientation(void);
	void Set_Camera_Mode(int Mode);
	void Zero_View(void);

	void Save_Camera_Pos(void);

	Ogre::Vector3 Saved_Pos;
	Ogre::Quaternion Saved_Rotation;

};

