
#include "stdafx.h"
#include "AB_App.h"

AB_App::AB_App()
{
	ABC_Export_RFW = NULL;
}

AB_App::~AB_App()
{

}

// *************************************************************************
// *						InitApp Inflanite							   *
// *************************************************************************
bool AB_App::InitApp(void)
{	
		ABC_Export_RFW  =			new AB_Export_RFW();

	return 1;
}

// *************************************************************************
// *									Say								   *
// *************************************************************************
void AB_App::Say(const char* Message)
{
	char text[1024];
	strcpy(text, Message);
	MessageBox(NULL,Message,"Message",MB_OK);

//	App->Cl_Dialogs->Message(text);
}

