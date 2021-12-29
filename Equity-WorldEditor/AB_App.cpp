
#include "stdafx.h"
#include "AB_App.h"



AB_App::AB_App()
{

}

AB_App::~AB_App()
{

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
