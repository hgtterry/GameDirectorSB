/*
Copyright (c) 2021 EquitySB and EquityME -- Inflanite Software W.T.Flanigan H.C.Flanigan

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

#include "stdafx.h"
#include "Base_Locations.h"

Base_Locations::Base_Locations()
{
	This_Object_ID = 0;
	Deleted = 0; // Internal
	Name[0] = 0;

	Current_Position.ZERO;

	Physics_Position.setZero();

	Physics_Rotation = (btQuaternion(0,0,0,1));
}

Base_Locations::~Base_Locations()
{
}
