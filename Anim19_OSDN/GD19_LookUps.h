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
class GD19_LookUps
{
public:

	GD19_LookUps(void);
	~GD19_LookUps(void);

	// Check for duplicate names 1=Name found  0=No Name Found
	int Player_Location_CheckNames(char* Name);

	// Returns the Index to the Object referanced by its Name
	int Player_Location_GetIndex_ByName(char* Name);


	// Returns The real Count Minus Deleted Files
	int Player_Location_GetCount(void);
	int Stock_Sound_GetCount(void);

	// Check if been used by another Object
	bool Check_Usage(int Index);

	// Get the Current Object Index from the Object ID
	int GetIndex_From_ID(int Object_ID);

	// Get Real Count - Deleted
	int Get_AdjustedCount(void);

};

