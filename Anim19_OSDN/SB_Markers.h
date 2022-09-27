/*
Copyright (c) 2021 Scene Builder and Equity -- Inflanite Software W.T.Flanigan H.C.Flanigan

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
class SB_Markers
{
public:
	SB_Markers(void);
	~SB_Markers(void);

	void Load_All_Axis();

	void Load_Red_Axis();
	void Load_Blue_Axis();

	void Update_Red_Axis_Marker(int Index);
	void Update_Blue_Axis_Marker(int Index);

	void Hide_Axis_Marker();

	Ogre::Entity*		RedAxis_Ent;
	Ogre::SceneNode*	RedAxis_Node;

	Ogre::Entity*		BlueAxis_Ent;
	Ogre::SceneNode*	BlueAxis_Node;
};

