// SB_App.cpp: implementation of the SB_App class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "fusion.h"
#include "SB_App.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SB_App::SB_App()
{

}

SB_App::~SB_App()
{

}

// *************************************************************************
// *									Say								   *
// *************************************************************************
void SB_App::Say(const char* Message)
{
	char text[1024];
	strcpy(text, Message);

	MessageBox (NULL,text, "Equity15", MB_ICONEXCLAMATION | MB_OK);
//	App->Cl_Dialogs->Message(text);
}
