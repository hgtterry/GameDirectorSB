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

#pragma once
class SB_Display
{
public:
	SB_Display();
	~SB_Display();

	void Add_New_Counter();
	void Add_New_Message();

	void Set_Counter_Defaults(int Index);
	void Set_TextMessage_Defaults(int Index);

	bool Add_Counters_From_File();
	bool Add_TextMessages_From_File();

	void Delete_Counter();

	void Mark_As_Altered_Counter(int Index);
	void Mark_As_Altered_TextMessage(int Index);

	int GetIndex_By_Name(char* Name);
};

