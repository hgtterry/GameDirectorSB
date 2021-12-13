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

#include "Base_Player.h"

class SB_Scene
{
public:
	SB_Scene();
	~SB_Scene();

	Base_Player*			SBC_Base_Player[100];

	int Player_Count;		// Actual Player Count Zero Based

	bool Scene_Loaded;	// Is the Scene Loaded [131221]
	bool Player_Added;	// Is there a vaild player in the level [081221]
	bool Area_Added;	// Is there a vaild Area or Room [131221]
};

