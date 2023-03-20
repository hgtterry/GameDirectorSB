/*
Copyright (c) 2022 - 2023 GameDirectorSB and EquityME -- HGTInflanite Software W.T.Flanigan H.C.Flanigan

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
#include "GD19_App.h"
#include "SB_Logger.h"

SB_Logger::SB_Logger()
{
	Show_Log_Data_F = 0;

	ReadLogFile = nullptr;
}

SB_Logger::~SB_Logger()
{
}


// *************************************************************************
// *			Log_Message_To_File:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void SB_Logger::Log_Message_To_File(char* Message)
{
	if (App->Debug_App == 1)
	{
		Ogre::LogManager::getSingleton().setDefaultLog(Ogre::LogManager::getSingleton().getLog("App.log"));
		Ogre::LogManager::getSingleton().logMessage(Message);
		Ogre::LogManager::getSingleton().setDefaultLog(Ogre::LogManager::getSingleton().getLog("EquitySB.log"));

	}
}

// *************************************************************************
// *			Show_Data:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
void SB_Logger::Show_Data(int int_Number, float float_Number, char* Message, Ogre::Vector3 Vector3)
{
	char Temp[MAX_PATH] = { 0 };

	Temp[0] = 0;
	_itoa(int_Number, Temp, 10);
	strcpy(LogMessage_Int, Temp);

	Temp[0] = 0;
	sprintf(Temp, "%f", float_Number);
	strcpy(LogMessage_Float, Temp);

	strcpy(LogMessage_Text, Message);

	Temp[0] = 0;
	sprintf(Temp, "%f %f %f", Vector3.x, Vector3.y, Vector3.z);
	strcpy(LogMessage_Vector3, Temp);
	

	Show_Log_Data_F = 1;
}


// *************************************************************************
// *			Log_Data_GUI:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_Logger::Log_Data_GUI(void)
{

	ImGui::SetNextWindowPos(ImVec2(500, 100), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin("Log Data", &Show_Log_Data_F, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize
		| ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar))
	{
		ImGui::End();
	}
	else
	{
		ImGui::Spacing();
		ImGui::Text("Show");
		ImGui::Separator();
	
		int Lines = Log_Lines_v.size();
		int Count = 0;

		ImGui::Text("Int:- %s", LogMessage_Int);
		ImGui::Text("Float:- %s", LogMessage_Float);
		ImGui::Text("Text:- %s", LogMessage_Text);
		ImGui::Text("Vec3:- %s", LogMessage_Vector3);

		ImGui::Text(" ");

		ImGui::Separator();

		if (ImGui::Button("Close"))
		{
			Close_Log();
		}

		ImGui::End();
	}
}

// *************************************************************************
// *				Close_Log:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_Logger::Close_Log(void)
{
	//App->CL_Panels->Enable_Panels(1);
	Show_Log_Data_F = 0;
}

// *************************************************************************
// *			 Show_Log:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
void SB_Logger::Show_Log()
{
	Log_Lines_v.reserve(100);

	ReadLogFile = nullptr;
	char FileLine[MAX_PATH] = { 0 }; // init this to be NULL terminated

	char Log_Path[MAX_PATH];
	strcpy(Log_Path, App->EquityDirecory_FullPath);
	strcat(Log_Path, "\\App.log");

	ReadLogFile = fopen(Log_Path, "rt");

	if (ReadLogFile == NULL)
	{
		App->Say_Win("Error");
	}

	while (fgets(FileLine, MAX_PATH, ReadLogFile) != NULL)
	{
		Log_Lines_v.push_back(FileLine);
	}

	fclose(ReadLogFile);

	Show_Log_Data_F = 1;
}
