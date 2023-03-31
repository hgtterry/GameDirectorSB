#pragma once

/*
Copyright (c) 2023 Equity_ME Model Editor -- Inflanite Software W.T.Flanigan H.C.Flanigan

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

class ME_Logger
{
public:
	ME_Logger();
	~ME_Logger();

	void Log_Message_To_File(char* Message);

	void Show(int int_Number, float float_Number, char* Message, Ogre::Vector3 Vector3 = Ogre::Vector3(0, 0, 0));

	void Show_Log();
	void Log_Data_GUI(void);
	void Close_Log(void);

	bool Show_Log_Data_F;

	char LogMessage_Text[MAX_PATH];
	char LogMessage_Int[MAX_PATH];
	char LogMessage_Float[MAX_PATH];
	char LogMessage_Vector3[MAX_PATH];


	std::vector<std::string> Log_Lines_v;

	FILE* ReadLogFile;
};

