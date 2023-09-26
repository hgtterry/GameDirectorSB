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
class SB_Grid
{
public:
	SB_Grid(void);
	~SB_Grid(void);

	void Reset_Class();

	void Load_Crosshair();

	void Grid_Update(bool Create);
	void Hair_Update(bool Create);
	
	void Grid_SetVisible(bool Option);
	void Hair_SetVisible(bool Option);

	void Face_Update(bool Create);

	Ogre::ColourValue ColourMain; 
	Ogre::ColourValue ColourHairZ;
	Ogre::ColourValue ColourHairX;
	Ogre::ColourValue ColourHairY;
	Ogre::ColourValue ColourDivision;

	int XAxis_min; 
	int	XAxis_max;
	int YAxis_min; 
	int	YAxis_max;
	int ZAxis_min; 
	int	ZAxis_max;
	int HairExtend;

	int Division_X;
	int Division_Y;
	int Division_Z;

	int Scale_X;
	int Scale_Y;
	int Scale_Z;

	ManualObject*		GridManual;
	SceneNode*			GridNode;

	ManualObject*		HairManual;
	SceneNode*			HairNode;

	ManualObject*		FaceManual;
	SceneNode*			FaceNode;

	SceneNode*			DummyNode;

	Ogre::Entity*		Crosshair_Ent; 
	Ogre::SceneNode*	Crosshair_Node;

	Ogre::Entity*		Selection_Ent; 
	Ogre::SceneNode*	Selection_Node;

	Ogre::Vector3 HitVertices[2];

	bool ShowGridFlag;
	bool ShowDivisions;
	bool ShowHair;

	char Message[1024];
};

