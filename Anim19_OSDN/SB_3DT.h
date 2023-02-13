/*
Copyright (c) GameDirector 2019 Inflanite Software W.T.Flanigan H.C.Flanigan B.Parkin

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
class SB_3DT
{
public:
	SB_3DT();
	~SB_3DT();

	void Fire(float deltaTime);

	float timeUntilNextToggle;

	float DistanceToCollision;

	Ogre::Camera* Pl_mDummyCamera;
	Vector3		Pl_mDummyTranslateVector;
	Ogre::String Pl_Entity_Name;
	int	Selected_Entity_Index;
	char Selected_Object_Name[MAX_PATH];

	irrklang::ISound* SndFile;
};

