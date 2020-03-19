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

#include "stdafx.h"
#include "GD19_App.h"
#include "GD19_Utilities.h"

#pragma warning( disable : 4267)

GD19_Utilities::GD19_Utilities(void)
{
	Return_Chr[0] = 0;
}

GD19_Utilities::~GD19_Utilities(void)
{
}

// *************************************************************************
// *				TestForBadCharactors  Terry Bernie			  	 	   *
// *************************************************************************
bool GD19_Utilities::TestForBadCharactors(char* buf)
{
	strcpy(Return_Chr, "");
	char bufnew[256];
	strcpy(bufnew, "");
	char seps[] = " /\\:*\n";
	char* token;
	bool tt = 0;

	token = strtok(buf, seps);
	while (token != NULL)
	{
		tt = 1;
		strcat(bufnew, token);
		strcat(bufnew, "_");
		token = strtok(NULL, seps);
	}

	if (tt == 1)
	{
		int len = strlen(bufnew);
		bufnew[len - 1] = 0;
		strcpy(Return_Chr, bufnew);
	}
	else
	{
		tt = 0;
		strcpy(Return_Chr, buf);
	}
	return 1;
}

// *************************************************************************
// *				ReverseBackSlash  Terry Bernie				  	 	   *
// *************************************************************************
bool GD19_Utilities::ReverseBackSlash(char* buf)
{
	strcpy(Return_Chr, "");
	char bufnew[256];
	strcpy(bufnew, "");
	char seps[] = "\\";
	char* token;
	bool tt = 0;

	token = strtok(buf, seps);
	while (token != NULL)
	{
		tt = 1;
		strcat(bufnew, token);
		strcat(bufnew, "/");
		token = strtok(NULL, seps);
	}

	if (tt == 1)
	{
		int len = strlen(bufnew);
		bufnew[len - 1] = 0;
		strcpy(Return_Chr, bufnew);
	}
	else
	{
		tt = 0;
		strcpy(Return_Chr, buf);
	}
	return 1;
}

// *************************************************************************
// *					OpenHTML Terry	Bernie							   *
// *************************************************************************
bool GD19_Utilities::OpenHTML(char* HelpTitle)
{
	char Path[1024];
	strcpy(Path, App->EquityDirecory_FullPath);
	strcat(Path, "\\");
	strcat(Path, HelpTitle);

	ShellExecute(0, "open", Path, 0, 0, SW_SHOW);
	return 1;
}

// *************************************************************************
// *					floatPercent Terry	Bernie						   *
// *************************************************************************
float GD19_Utilities::floatPercent(int Val)
{
	float fPercent = ((float)Val) / 100.0f;

	return fPercent;
}

// *************************************************************************
// *					DegreesToRadians Terry	Bernie					   *
// *************************************************************************
float GD19_Utilities::DegreesToRadians(float Degrees)
{
	float Radians = 0;//(Degrees * GE_PI)/180;
	return Radians;
}

// *************************************************************************
// *					RadiansToDegrees Terry	Bernie					   *
// *************************************************************************
float GD19_Utilities::RadiansToDegrees(float Radians)
{
	float Degrees = 0;//(Radians * 180)/GE_PI;
	return Degrees;
}
