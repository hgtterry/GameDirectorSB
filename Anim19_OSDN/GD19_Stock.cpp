#include "StdAfx.h"
#include "GD19_App.h"
#include "resource.h"
#include "GD19_Stock.h"

#pragma warning( disable : 4700)

GD19_Stock::GD19_Stock(void)
{
	ListIndex = 0;
	mListType = 0;
	Selected_Panel_Index = 0;
	Selected_Stock_Index = 0;
	Selected_Stock_Index2 = 0;
	ItemToSelect = 0;
	Selected_Stock_Type = Enums::Stock_Type_None;
	Stock_Dialog_hWnd = nullptr;
	OptionsDlgHwnd = NULL;
	mImageList = NULL;
	hBitMap = NULL;
	Stock_Properties_hLV = NULL;
	ItemList_Hwnd = NULL;
}


GD19_Stock::~GD19_Stock(void)
{
}

// *************************************************************************
// *			ListView_OnClickOptions  Terry Bernie			 		   *
// *************************************************************************
void GD19_Stock::ListView_OnClickOptions(LPARAM lParam)
{

	if (Selected_Stock_Type == Enums::Stock_Type_Sound)
	{
		
		Edit_Sound_Stock(lParam);
		
		return;
	}

	if (Selected_Stock_Type == Enums::Stock_Type_Message)
	{
			
			Edit_Message_Stock(lParam);
	
		return;
	}

	if (Selected_Stock_Type == Enums::Stock_Type_Panel)
	{

		Edit_Panel_Stock(lParam);
		return;
	}

	return;
}

// *************************************************************************
// *					Update_Message_Properties Terry Bernie   	 	   *
// *************************************************************************
void GD19_Stock::Update_Message_Properties(void)
{
	int Index = Selected_Stock_Index2;
	
	char buf[255];
	strcpy(buf,App->Cl_Scene_Data->Cl_Object[Index]->Name);
	
	char chr_FontSize[100];
	char chr_TextColour[100];
	char chr_PosVert[100];
	char chr_PosHoz[100];

	sprintf(chr_FontSize,"%i ",App->Cl_Scene_Data->S_Messages[Index]->Font_Size);
	sprintf(chr_TextColour,"%.2f %.2f %.2f",App->Cl_Scene_Data->S_Messages[Index]->Colour.x,App->Cl_Scene_Data->S_Messages[Index]->Colour.y,App->Cl_Scene_Data->S_Messages[Index]->Colour.z);
	sprintf(chr_PosVert,"%.2f ",App->Cl_Scene_Data->S_Messages[Index]->Pos_Vert);
	sprintf(chr_PosHoz,"%.2f ",App->Cl_Scene_Data->S_Messages[Index]->Pos_Hoz);


	const int NUM_ITEMS = 14;
	const int NUM_COLS = 2;
	std::string grid[NUM_COLS][NUM_ITEMS]; // string table
	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	grid[0][0] = "Name",				grid[1][0] = App->Cl_Scene_Data->S_Messages[Index]->Name;
	grid[0][1] = "Default Text",		grid[1][1] = App->Cl_Scene_Data->S_Messages[Index]->Default_Text;
	grid[0][2] = "Font Size",			grid[1][2] = chr_FontSize;
	grid[0][3] = "Text Colour",			grid[1][3] = chr_TextColour;
	grid[0][4] = " ",					grid[1][4] = " ";//chr_PosY;
	grid[0][5] = "Pos Vertical",		grid[1][5] = chr_PosVert;
	grid[0][6] = "Pos Horizontal",		grid[1][6] = chr_PosHoz;
	grid[0][7] = " ",					grid[1][7] = " ";//chr_RotX;
	grid[0][8] = " ",					grid[1][8] = " ";//chr_RotY;
	grid[0][9] = " ",					grid[1][9] = " ";//chr_RotZ;
	grid[0][10] = " ",					grid[1][10] = " ";
	grid[0][11] = " ",					grid[1][11] = " ";//chr_ScaleX;
	grid[0][12] = " ",					grid[1][12] = " ";//chr_ScaleY;
	grid[0][13] = " ",					grid[1][13] = " ";//chr_ScaleZ;

	ListView_DeleteAllItems(Stock_Properties_hLV);

	for (DWORD row = 0; row < NUM_ITEMS; row++)
	{
		pitem.iItem = row;
		pitem.pszText = const_cast<char*>(grid[0][row].c_str());
		ListView_InsertItem(Stock_Properties_hLV, &pitem);

		//ListView_SetItemText

		for (DWORD col = 1; col < NUM_COLS; col++)
		{
			ListView_SetItemText(Stock_Properties_hLV, row, col,
				const_cast<char*>(grid[col][row].c_str()));
		}
	}
}

// *************************************************************************
// *					Update_Sound_Properties Terry Bernie		 	   *
// *************************************************************************
void GD19_Stock::Update_Sound_Properties(void)
{
	int Index = Selected_Stock_Index2;

	char buf[255];
	strcpy(buf,App->Cl_Scene_Data->Cl_Object[Index]->Name);

	char chr_Volume[100];
	sprintf(chr_Volume, "%.3f", App->Cl_Scene_Data->St_Sounds[Index]->Volume * 100);
	
	const int NUM_ITEMS = 3;
	const int NUM_COLS = 2;
	std::string grid[NUM_COLS][NUM_ITEMS]; // string table
	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	grid[0][0] = "Name",				grid[1][0] = App->Cl_Scene_Data->St_Sounds[Index]->Name;
	grid[0][1] = "Sound",				grid[1][1] = App->Cl_Scene_Data->St_Sounds[Index]->SoundFile;
	grid[0][2] = "Volume",				grid[1][2] = chr_Volume;
	
	ListView_DeleteAllItems(Stock_Properties_hLV);

	for (DWORD row = 0; row < NUM_ITEMS; row++)
	{
		pitem.iItem = row;
		pitem.pszText = const_cast<char*>(grid[0][row].c_str());
		ListView_InsertItem(Stock_Properties_hLV, &pitem);

		//ListView_SetItemText

		for (DWORD col = 1; col < NUM_COLS; col++)
		{
			ListView_SetItemText(Stock_Properties_hLV, row, col,
				const_cast<char*>(grid[col][row].c_str()));
		}
	}
}

// *************************************************************************
// *	  					Edit_Message_Stock Terry Bernie				   *
// *************************************************************************
int GD19_Stock::Edit_Message_Stock(LPARAM lParam)
{
	int Index = App->SBC_Properties->Current_Selected_Object; // Get Selected Object Index 
	int result = 1;
	int test;

	LPNMLISTVIEW poo = (LPNMLISTVIEW)lParam;
	test = poo->iItem;
	ListView_GetItemText(Stock_Properties_hLV, test, 0, btext, 20);
	

	result = strcmp(btext, "Default Text");
	if (result == 0)
	{
		strcpy(App->Cl_Dialogs->btext,"Change Default Text");
		strcpy(App->Cl_Dialogs->Chr_Text,App->Cl_Scene_Data->S_Messages[Selected_Stock_Index]->Default_Text);

		App->Cl_Dialogs->Dialog_Text(0);

		if (App->Cl_Dialogs->Canceled == 1)
		{
			return TRUE;
		}

		strcpy(App->Cl_Scene_Data->S_Messages[Selected_Stock_Index]->Default_Text,App->Cl_Dialogs->Chr_Text);
		strcpy(App->Cl_Dialogs->Chr_Text,App->Cl_Dialogs->Chr_Text);

		App->Cl_Scene_Data->S_Messages[Selected_Stock_Index]->textArea1->setCaption(App->Cl_Dialogs->Chr_Text);

		Update_Message_Properties();
		return 1;
	}

	result = strcmp(btext, "Font Size");
	if (result == 0)
	{
		char IntBuff[30];
		sprintf(IntBuff,"%i",App->Cl_Scene_Data->S_Messages[Selected_Stock_Index]->Font_Size);

		strcpy(App->Cl_Dialogs->btext,"Change Font Size");
		strcpy(App->Cl_Dialogs->Chr_Int,IntBuff);

		App->Cl_Dialogs->Dialog_Int();

		if (App->Cl_Dialogs->Canceled == 1)
		{
			return TRUE;
		}

		App->Cl_Scene_Data->S_Messages[Selected_Stock_Index]->Font_Size = App->Cl_Dialogs->mInt;
	
		App->Cl_Scene_Data->S_Messages[Selected_Stock_Index]->textArea1->setCharHeight(Ogre::Real(App->Cl_Dialogs->mInt));

		Update_Message_Properties();
		return 1;
	}

	result = strcmp(btext, "Text Colour");
	if (result == 0)
	{
		App->SBC_FileIO->GetColor();

		if (App->SBC_FileIO->Cannceled == 0)
		{

			float Red = (float)GetRValue(App->SBC_FileIO->color.rgbResult)/ 256;
			float Green = (float)GetGValue(App->SBC_FileIO->color.rgbResult)/ 256;
			float Blue = (float)GetBValue(App->SBC_FileIO->color.rgbResult)/ 256;

			App->Cl_Scene_Data->S_Messages[Selected_Stock_Index]->Colour.x = Red;
			App->Cl_Scene_Data->S_Messages[Selected_Stock_Index]->Colour.y = Green;
			App->Cl_Scene_Data->S_Messages[Selected_Stock_Index]->Colour.z = Blue;

			App->Cl_Scene_Data->S_Messages[Selected_Stock_Index]->textArea1->setColour(ColourValue(Red,Green,Blue));
			Update_Message_Properties();
		}
		return 1;
	}

	result = strcmp(btext, "Pos Horizontal");
	if (result == 0)
	{
		char IntBuff[30];
		sprintf(IntBuff,"%f",App->Cl_Scene_Data->S_Messages[Selected_Stock_Index]->Pos_Hoz);

		strcpy(App->Cl_Dialogs->btext,"Horizontal Position");
		
		strcpy(App->Cl_Dialogs->Chr_Float,IntBuff);

		App->Cl_Dialogs->Dialog_Float();

		if (App->Cl_Dialogs->Canceled == 1)
		{
			return TRUE;
		}

		App->Cl_Scene_Data->S_Messages[Selected_Stock_Index]->Pos_Hoz = App->Cl_Dialogs->mFloat;

		float Vert = App->Cl_Scene_Data->S_Messages[Selected_Stock_Index]->Pos_Vert;
		float Hoz = App->Cl_Scene_Data->S_Messages[Selected_Stock_Index]->Pos_Hoz;
	
		App->Cl_Scene_Data->S_Messages[Selected_Stock_Index]->textArea1->setPosition(Hoz,Vert);
		
		Update_Message_Properties();
		return 1;
	}

	result = strcmp(btext, "Pos Vertical");
	if (result == 0)
	{
		char IntBuff[30];
		sprintf(IntBuff,"%f",App->Cl_Scene_Data->S_Messages[Selected_Stock_Index]->Pos_Vert);

		strcpy(App->Cl_Dialogs->btext,"Vertical Position");
		
		strcpy(App->Cl_Dialogs->Chr_Float,IntBuff);

		App->Cl_Dialogs->Dialog_Float();

		if (App->Cl_Dialogs->Canceled == 1)
		{
			return TRUE;
		}

		App->Cl_Scene_Data->S_Messages[Selected_Stock_Index]->Pos_Vert = App->Cl_Dialogs->mFloat;

		float Vert = App->Cl_Scene_Data->S_Messages[Selected_Stock_Index]->Pos_Vert;
		float Hoz = App->Cl_Scene_Data->S_Messages[Selected_Stock_Index]->Pos_Hoz;
	
		App->Cl_Scene_Data->S_Messages[Selected_Stock_Index]->textArea1->setPosition(Hoz,Vert);
		
		Update_Message_Properties();
		return 1;
	}
	return -1;
}

// *************************************************************************
// *	  					Edit_Sound_Stock Terry Bernie				   *
// *************************************************************************
int GD19_Stock::Edit_Sound_Stock(LPARAM lParam)
{
	
	int Index = App->Cl_Stock->Selected_Stock_Index2; // Get Selected Object Index 
	int result = 1;
	int test;

	LPNMLISTVIEW poo = (LPNMLISTVIEW)lParam;
	test = poo->iItem;
	ListView_GetItemText(Stock_Properties_hLV, test, 0, btext, 20);

	// Name
	result = strcmp(btext, "Name");
	if (result == 0)
	{
		strcpy(App->Cl_Dialogs->btext, "Change Object Name");
		strcpy(App->Cl_Dialogs->Chr_Text, App->Cl_Scene_Data->St_Sounds[Index]->Name);

		App->Cl_Dialogs->Dialog_Text(Enums::Check_Names_Objects);

		if (App->Cl_Dialogs->Canceled == 1)
		{
			return TRUE;
		}

		strcpy(App->Cl_Scene_Data->St_Sounds[Index]->Name, App->Cl_Dialogs->Chr_Text);

//		App->Cl_FileView->ChangeItem_Name_Stock(NULL, App->Cl_Dialogs->Chr_Text);

		List_Sounds_Stock(App->Cl_Stock->ItemList_Hwnd);

		Update_Sound_Properties();
	}

	// Sound
	result = strcmp(btext, "Sound");
	if (result == 0)
	{

		strcpy(App->Cl_SoundMgr->Current_Object_Sound, App->Cl_Scene_Data->St_Sounds[Index]->SoundFile);

		App->Cl_SoundMgr->Dialog_SoundFile();

		if (App->Cl_SoundMgr->IsCancelled == 0)
		{
			strcpy(App->Cl_Scene_Data->St_Sounds[Index]->SoundFile, App->Cl_SoundMgr->mSoundFile);
			App->Cl_Scene_Data->St_Sounds[Index]->Volume = App->Cl_SoundMgr->SndVolume;
		}

		Update_Sound_Properties();

		return 1;
	}

	// Volume
	result = strcmp(btext, "Volume");
	if (result == 0)
	{

		strcpy(App->Cl_SoundMgr->Current_Object_Sound, App->Cl_Scene_Data->St_Sounds[Index]->SoundFile);

		App->Cl_SoundMgr->Dialog_SoundFile();

		if (App->Cl_SoundMgr->IsCancelled == 0)
		{
			strcpy(App->Cl_Scene_Data->St_Sounds[Index]->SoundFile, App->Cl_SoundMgr->mSoundFile);
			App->Cl_Scene_Data->St_Sounds[Index]->Volume = App->Cl_SoundMgr->SndVolume;
		}

		Update_Sound_Properties();

		return 1;
	}

	return -1;
}

// *************************************************************************************************************************************
// *													Panels																		   *
// *************************************************************************************************************************************

// *************************************************************************
// *						Add_Panel Terry Bernie						   *
// *************************************************************************
void GD19_Stock::Add_Panel(void)
{
	int Panel_Number = App->Cl_Panels_Com->Create_Panel();

	char Name[256];
	strcpy(Name, App->Cl_Panels_Com->Get_Panel_Name(Panel_Number));

}

// *************************************************************************
// *					Update_Panel_Properties Terry Bernie		 	   *
// *************************************************************************
void GD19_Stock::Update_Panel_Properties(void)
{
	int Index = Selected_Panel_Index;
	
	char chr_FontSize[100];
	sprintf(chr_FontSize, "%i ", App->Cl_Panels_Com->Get_Font_Size(Index));

	Panel_Colour_Strt Col = App->Cl_Panels_Com->Get_Text_Colour(Index);

	char chr_TextColour[100];
	sprintf(chr_TextColour, "%.2f %.2f %.2f", Col.Red, Col.Green, Col.Blue);

	App->Cl_Panels_Com->Get_Font_Name(Index);

	Ogre::Vector3 Pos = App->Cl_Panels_Com->Get_Text_Position(Index);

	// Text Position
	char chr_Text_Pos_X[100];
	sprintf(chr_Text_Pos_X, "%.2f", Pos.x);

	char chr_Text_Pos_Y[100];
	sprintf(chr_Text_Pos_Y, "%.2f", Pos.y);

	// Panel Position
	Ogre::Vector3 Panel_Pos = App->Cl_Panels_Com->Get_Panel_Position(Index);

	char chr_Panel_Pos_X[100];
	sprintf(chr_Panel_Pos_X, "%.2f", Panel_Pos.x);

	char chr_Panel_Pos_Y[100];
	sprintf(chr_Panel_Pos_Y, "%.2f", Panel_Pos.y);

	// Panel Dimensions
	Ogre::Vector3 Panel_Dimensions = App->Cl_Panels_Com->Get_Panel_Dimensions(Index);

	char chr_Width[100];
	sprintf(chr_Width, "%.2f", Panel_Dimensions.x);

	char chr_Height[100];
	sprintf(chr_Height, "%.2f", Panel_Dimensions.y);

	
	const int NUM_ITEMS = 16;
	const int NUM_COLS = 2;
	std::string grid[NUM_COLS][NUM_ITEMS]; // string table
	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	grid[0][0] = "Name",			grid[1][0] = App->Cl_Panels_Com->Get_Panel_Name(Index);
	grid[0][1] = "Text",			grid[1][1] = App->Cl_Panels_Com->Get_User_Text(Index);
	grid[0][2] = "",				grid[1][2] = " ";//chr_Play;
	grid[0][3] = "Font_Name",		grid[1][3] = App->Cl_Panels_Com->Font_Name;
	grid[0][4] = "Font_Size",		grid[1][4] = chr_FontSize;
	grid[0][5] = "Text_Colour",		grid[1][5] = chr_TextColour;
	grid[0][6] = " ",				grid[1][6] = " ";//chr_PosHoz;
	grid[0][7] = "Text_Pos_X",		grid[1][7] = chr_Text_Pos_X;
	grid[0][8] = "Text_Pos_Y",		grid[1][8] = chr_Text_Pos_Y;
	grid[0][9] = " ",				grid[1][9] = " ";//chr_RotZ;
	grid[0][10] = "Panel_Pos_X",	grid[1][10] = chr_Panel_Pos_X;
	grid[0][11] = "Panel_Pos_Y",	grid[1][11] = chr_Panel_Pos_Y;
	grid[0][12] = "Panel_Width",	grid[1][12] = chr_Width;
	grid[0][13] = "Panel_Height",	grid[1][13] = chr_Height;
	grid[0][14] = " ",				grid[1][14] = " ";//chr_ScaleY;
	grid[0][15] = " ",				grid[1][15] = " ";//chr_ScaleZ;

	
	ListView_DeleteAllItems(Stock_Properties_hLV);

	for (DWORD row = 0; row < NUM_ITEMS; row++)
	{
		pitem.iItem = row;
		pitem.pszText = const_cast<char*>(grid[0][row].c_str());
		ListView_InsertItem(Stock_Properties_hLV, &pitem);

		//ListView_SetItemText

		for (DWORD col = 1; col < NUM_COLS; col++)
		{
			ListView_SetItemText(Stock_Properties_hLV, row, col,
				const_cast<char*>(grid[col][row].c_str()));
		}
	}
}

// *************************************************************************
// *	  					Edit_Panel_Stock Terry Bernie				   *
// *************************************************************************
int GD19_Stock::Edit_Panel_Stock(LPARAM lParam)
{
	int Index = Selected_Panel_Index;
	int result = 1;
	int test;

	LPNMLISTVIEW poo = (LPNMLISTVIEW)lParam;
	test = poo->iItem;
	ListView_GetItemText(Stock_Properties_hLV, test, 0, btext, 20);

	result = strcmp(btext, "Name");
	if (result == 0)
	{
		strcpy(App->Cl_Dialogs->btext, "Change Name");
		strcpy(App->Cl_Dialogs->Chr_Text, App->Cl_Panels_Com->Get_Panel_Name(Index));

		App->Cl_Dialogs->Dialog_Text(0);

		if (App->Cl_Dialogs->Canceled == 1)
		{
			return TRUE;
		}

		App->Cl_Panels_Com->Set_Panel_Name(App->Cl_Dialogs->Chr_Text, Index);

		Update_Panel_Properties();
		return 1;
	}

	result = strcmp(btext, "Text");
	if (result == 0)
	{
		strcpy(App->Cl_Dialogs->btext, "Set_Text");
		strcpy(App->Cl_Dialogs->Chr_Text, App->Cl_Panels_Com->Get_User_Text(Index));

		App->Cl_Dialogs->Dialog_Text(0);

		if (App->Cl_Dialogs->Canceled == 1)
		{
			return TRUE;
		}

		App->Cl_Panels_Com->Set_User_Text(App->Cl_Dialogs->Chr_Text, Index);

		Update_Panel_Properties();
		return 1;
	}

	result = strcmp(btext, "Font_Size");
	if (result == 0)
	{
		char IntBuff[30];
		sprintf(IntBuff, "%i", App->Cl_Panels_Com->Get_Font_Size(Index));

		strcpy(App->Cl_Dialogs->btext, "Change Font Size");
		strcpy(App->Cl_Dialogs->Chr_Int, IntBuff);

		App->Cl_Dialogs->Dialog_Int();

		if (App->Cl_Dialogs->Canceled == 1)
		{
			return TRUE;
		}

		App->Cl_Panels_Com->Set_Font_Size(App->Cl_Dialogs->mInt, Index);

		Update_Panel_Properties();
		return 1;
	}

	result = strcmp(btext, "Text_Colour");
	if (result == 0)
	{
		App->SBC_FileIO->GetColor();

		if (App->SBC_FileIO->Cannceled == 0)
		{

			float Red = (float)GetRValue(App->SBC_FileIO->color.rgbResult) / 256;
			float Green = (float)GetGValue(App->SBC_FileIO->color.rgbResult) / 256;
			float Blue = (float)GetBValue(App->SBC_FileIO->color.rgbResult) / 256;

			App->Cl_Panels_Com->Set_Text_Colour(Red, Green, Blue, Index);

			Update_Panel_Properties();
		}
		return 1;
	}

	//          Text Position
	result = strcmp(btext, "Text_Pos_X");
	if (result == 0)
	{
		Ogre::Vector3 Pos = App->Cl_Panels_Com->Get_Text_Position(Index);
		char IntBuff[30];
		sprintf(IntBuff, "%.2f", Pos.x);
		
		strcpy(App->Cl_Dialogs->btext, "Horizontal Position");

		strcpy(App->Cl_Dialogs->Chr_Float, IntBuff);

		App->Cl_Dialogs->Dialog_Float();

		if (App->Cl_Dialogs->Canceled == 1)
		{
			return TRUE;
		}

		App->Cl_Panels_Com->Set_Text_Position(App->Cl_Dialogs->mFloat, Pos.y,Index);
	
		Update_Panel_Properties();
		return 1;
	}

	result = strcmp(btext, "Text_Pos_Y");
	if (result == 0)
	{
		
		Ogre::Vector3 Pos = App->Cl_Panels_Com->Get_Text_Position(Index);
		char IntBuff[30];
		sprintf(IntBuff, "%.2f", Pos.y);

		strcpy(App->Cl_Dialogs->btext, "Vertical Position");

		strcpy(App->Cl_Dialogs->Chr_Float, IntBuff);

		App->Cl_Dialogs->Dialog_Float();

		if (App->Cl_Dialogs->Canceled == 1)
		{
			return TRUE;
		}

		App->Cl_Panels_Com->Set_Text_Position(Pos.x, App->Cl_Dialogs->mFloat, Index);

		Update_Panel_Properties();
		return 1;
	}

	//          Panel Position
	result = strcmp(btext, "Panel_Pos_X");
	if (result == 0)
	{
		Ogre::Vector3 Pos = App->Cl_Panels_Com->Get_Panel_Position(Index);
		char IntBuff[30];
		sprintf(IntBuff, "%.2f", Pos.x);

		strcpy(App->Cl_Dialogs->btext, "Horizontal Position");

		strcpy(App->Cl_Dialogs->Chr_Float, IntBuff);

		App->Cl_Dialogs->Dialog_Float();

		if (App->Cl_Dialogs->Canceled == 1)
		{
			return TRUE;
		}

		App->Cl_Panels_Com->Set_Panel_Position(App->Cl_Dialogs->mFloat, Pos.y, Index);

		Update_Panel_Properties();
		return 1;
	}

	result = strcmp(btext, "Panel_Pos_Y");
	if (result == 0)
	{

		Ogre::Vector3 Pos = App->Cl_Panels_Com->Get_Panel_Position(Index);
		char IntBuff[30];
		sprintf(IntBuff, "%.2f", Pos.y);

		strcpy(App->Cl_Dialogs->btext, "Vertical Position");

		strcpy(App->Cl_Dialogs->Chr_Float, IntBuff);

		App->Cl_Dialogs->Dialog_Float();

		if (App->Cl_Dialogs->Canceled == 1)
		{
			return TRUE;
		}

		App->Cl_Panels_Com->Set_Panel_Position(Pos.x, App->Cl_Dialogs->mFloat, Index);

		Update_Panel_Properties();
		return 1;
	}

	//          Panel Position
	result = strcmp(btext, "Panel_Width");
	if (result == 0)
	{
		Ogre::Vector3 Pos = App->Cl_Panels_Com->Get_Panel_Dimensions(Index);
		char IntBuff[30];
		sprintf(IntBuff, "%.2f", Pos.x);

		strcpy(App->Cl_Dialogs->btext, "Horizontal Position");

		strcpy(App->Cl_Dialogs->Chr_Float, IntBuff);

		App->Cl_Dialogs->Dialog_Float();

		if (App->Cl_Dialogs->Canceled == 1)
		{
			return TRUE;
		}

		App->Cl_Panels_Com->Set_Panel_Dimensions(App->Cl_Dialogs->mFloat, Pos.y, Index);

		Update_Panel_Properties();
		return 1;
	}

	result = strcmp(btext, "Panel_Height");
	if (result == 0)
	{

		Ogre::Vector3 Pos = App->Cl_Panels_Com->Get_Panel_Dimensions(Index);
		char IntBuff[30];
		sprintf(IntBuff, "%.2f", Pos.y);

		strcpy(App->Cl_Dialogs->btext, "Vertical Position");

		strcpy(App->Cl_Dialogs->Chr_Float, IntBuff);

		App->Cl_Dialogs->Dialog_Float();

		if (App->Cl_Dialogs->Canceled == 1)
		{
			return TRUE;
		}

		App->Cl_Panels_Com->Set_Panel_Dimensions(Pos.x, App->Cl_Dialogs->mFloat, Index);

		Update_Panel_Properties();
		return 1;
	}

	return -1;
}

// *************************************************************************
// *						Test_Sound Terry Bernie						   *
// *************************************************************************
void GD19_Stock::Test_Sound(int Index)
{
	int mIndex = Index;

	char buff[1024];
	strcpy(buff, App->Cl_SoundMgr->Default_Folder);
	strcat(buff, "\\Media\\Sounds\\");
	strcat(buff, App->Cl_Scene_Data->St_Sounds[mIndex]->SoundFile);

	App->Cl_Scene_Data->St_Sounds[mIndex]->SndFile = App->Cl_SoundMgr->SoundEngine->play2D(buff, false, true, true);
	App->Cl_Scene_Data->St_Sounds[mIndex]->SndFile->setVolume(App->Cl_Scene_Data->St_Sounds[mIndex]->Volume);
	App->Cl_Scene_Data->St_Sounds[mIndex]->SndFile->setIsPaused(false);
	

}

// *************************************************************************
// *	  				List_Stock_Dialog Terry Bernie					   *
// *************************************************************************
void GD19_Stock::List_Stock_Dialog(int ListType)
{
	mListType = ListType;

///	DialogBox(App->hInst, (LPCTSTR)IDD_GD_STOCK_LIST, App->Fdlg, (DLGPROC)List_Stock_Proc);
}

// *************************************************************************
// *					List_Stock_Proc Terry Bernie 					   *
// *************************************************************************
LRESULT CALLBACK GD19_Stock::List_Stock_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

	case WM_INITDIALOG:
	{
		HFONT Font;
		Font = CreateFont(-15, 0, 0, 0, 0, 0, 0, 0, 0, OUT_TT_ONLY_PRECIS, 0, 0, 0, "Aerial Black");
		///SendDlgItemMessage(hDlg, IDC_LIST1, WM_SETFONT, (WPARAM)Font, MAKELPARAM(TRUE, 0));

	///	HWND List = GetDlgItem(hDlg, IDC_LIST1);

		if (App->Cl_Stock->mListType == Enums::ListBox_Stock_Messages)
		{
			//App->Cl_Dialogs->List_Messages_Stock(List);
		}

		if (App->Cl_Stock->mListType == Enums::ListBox_Stock_Sounds)
		{
	///		App->Cl_Stock->List_Sounds_Stock(List);
		}

		return TRUE;
	}

	case WM_CTLCOLORSTATIC:
	{///
		/*if (GetDlgItem(hDlg, IDC_STSELECTION) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}*/
		
		return FALSE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}

	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDOK && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}
	
	case WM_COMMAND:
	{
	//	if (LOWORD(wParam) == IDC_LIST1)
		{
		//	char buff[256];
		///	App->Cl_Stock->ListIndex = SendDlgItemMessage(hDlg, IDC_LIST1, LB_GETCURSEL, (WPARAM)0, (LPARAM)0);

			if (App->Cl_Stock->ListIndex == -1)
			{
				return 1;
			}

		///	SendDlgItemMessage(hDlg, IDC_LIST1, LB_GETTEXT, (WPARAM)App->Cl_Stock->ListIndex, (LPARAM)buff);

		///	SetDlgItemText(hDlg, IDC_STSELECTION, (LPCTSTR)buff);
			App->Cl_Stock->Test_Sound(App->Cl_Stock->ListIndex);
			return TRUE;

		}

		if (LOWORD(wParam) == IDOK)
		{

			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		break;
	}
	}
	return FALSE;
}

// *************************************************************************
// *	  					List_Sounds_Stock Terry Bernie				   *
// *************************************************************************
void GD19_Stock::List_Sounds_Stock(HWND List)
{
	SendMessage(List, LB_RESETCONTENT, 0, 0);

	int Count = 0;
	while (Count < App->Cl_Scene_Data->Stock_Sound_Count)
	{
		SendMessage(List, LB_ADDSTRING, 0, (LPARAM)(LPCTSTR)App->Cl_Scene_Data->St_Sounds[Count]->Name);
		Count++;
	}
}

// *************************************************************************
// *	  					Select_Item Terry Bernie					   *
// *************************************************************************
void GD19_Stock::Select_Item(int Index)
{
	SendMessage(App->Cl_Stock->ItemList_Hwnd, LB_SETCURSEL, (WPARAM)Index, (LPARAM)(LPCTSTR)0);
}

// *************************************************************************
// *				Start_Stock_Dialog  Terry Bernie					   *
// *************************************************************************
void GD19_Stock::Start_Stock_Dialog(void)
{

	DialogBox(App->hInst, (LPCTSTR)IDD_SD_STOCK, App->Fdlg, (DLGPROC)Stock_Proc);
	
}
// *************************************************************************
// *        				Stock_Proc Terry Bernie						   *
// *************************************************************************
LRESULT CALLBACK GD19_Stock::Stock_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		App->SetTitleBar(hDlg);

		HFONT Font;
		HFONT Font2;
		Font = CreateFont(-13, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, OUT_TT_ONLY_PRECIS, 0, 0, 0, "Aerial Black");
		Font2 = CreateFont(-20, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, OUT_TT_ONLY_PRECIS, 0, 0, 0, "Aerial Black");

		SendDlgItemMessage(hDlg, IDC_STINFO, WM_SETFONT, (WPARAM)Font, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_ITEMSLIST, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_ST_SELECTED, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		SendDlgItemMessage(hDlg, IDC_USAGEBANNER, WM_SETFONT, (WPARAM)Font2, MAKELPARAM(TRUE, 0));
		//
		SetDlgItemText(hDlg, IDC_USAGEBANNER, (LPCTSTR)"Stock Manager");

		///HWND Temp = GetDlgItem(hDlg, IDC_BTHELP);
		///SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_Info_Bmp);

		App->Cl_Stock->Stock_Dialog_hWnd = hDlg;

		App->Cl_Stock->Init_Stock_FileView();

		App->Cl_Stock->OptionsDlgHwnd = hDlg;

		
		// File View
		SendDlgItemMessage(hDlg, IDC_ST_LIST1, TVM_SETIMAGELIST, 0, (LPARAM)App->Cl_Stock->mImageList); // put it onto the tree control
		
		HWND Temp = GetDlgItem(hDlg, IDC_ST_LIST1);
		TreeView_DeleteAllItems(Temp);

		App->Cl_Stock->AddOptions();

		App->Cl_Stock->ItemList_Hwnd = GetDlgItem(hDlg, IDC_ITEMSLIST);

		App->Cl_Stock->List_Sounds_Stock(App->Cl_Stock->ItemList_Hwnd);
		App->Cl_Stock->Select_Item(App->Cl_Stock->ItemToSelect);
		App->Cl_Stock->ListIndex = App->Cl_Stock->ItemToSelect;

		App->Cl_Stock->Stock_Create_Properties_hLV();

		// Start Up
		App->Cl_Stock->Selected_Stock_Type = Enums::Stock_Type_Sound;
		App->Cl_Stock->Selected_Stock_Index2 = 0;
		App->Cl_Stock->Update_Sound_Properties();

		SetDlgItemText(hDlg, IDC_ST_SELECTED, (LPCTSTR)App->Cl_Scene_Data->St_Sounds[0]->Name);

		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{
		
		if (GetDlgItem(hDlg, IDC_USAGEBANNER) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 255));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}
	///	if(GetDlgItem(hDlg, IDC_ST_SELECTED) == (HWND)lParam)
		{
			SetBkColor((HDC) wParam, RGB(0, 255, 0));
			SetTextColor((HDC) wParam, RGB(0,0,0));
			SetBkMode((HDC) wParam, TRANSPARENT);
			return (UINT) App->Brush_White;
		}
		/*if(GetDlgItem(hDlg,IDC_STSCENENAME) == (HWND)lParam)
		{
			SetBkColor((HDC) wParam, RGB(0, 255, 0));
			SetTextColor((HDC) wParam, RGB(0,0,255));
			SetBkMode((HDC) wParam, TRANSPARENT);
			return (UINT) App->AppBackground;
		}
		if(GetDlgItem(hDlg,IDC_SCENESELECTION) == (HWND)lParam)
		{
			SetBkColor((HDC) wParam, RGB(0, 255, 0));
			SetTextColor((HDC) wParam, RGB(0,0,0));
			SetBkMode((HDC) wParam, TRANSPARENT);
			return (UINT) App->AppBackground;
		}
		if(GetDlgItem(hDlg,IDC_STTEST) == (HWND)lParam)
		{
			SetBkColor((HDC) wParam, RGB(0, 255, 0));
			SetTextColor((HDC) wParam, RGB(0,0,0));
			SetBkMode((HDC) wParam, TRANSPARENT);
			return (UINT) App->AppBackground;
		}*/

		return FALSE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}
	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDOK && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BTADD && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BTTEST && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDCANCEL && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->hwndFrom == App->Cl_Stock->Stock_Properties_hLV)
		{
			switch (some_item->code)
			{
			case NM_CLICK:
			{

				App->Cl_Stock->ListView_OnClickOptions(lParam);
			}
			}
		}
		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:

		

		/*if (LOWORD(wParam) == IDC_BTHELP)
		{
			App->Cl_Utilities->OpenHTML("Help\\SoundStock.html");
			return TRUE;
		}*/

		if (LOWORD(wParam) == IDC_BTTEST)
		{
			
			App->Cl_Stock->Test_Sound(App->Cl_Stock->Selected_Stock_Index2);

			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BTADD)
		{
			/*App->Cl_Dialogs->YesNo("Add Object", "Do you want to add a new Stock Sound now");
			bool Doit = App->Cl_Dialogs->Canceled;
			if (Doit == 0)
			{
				App->SBC_Objects_New->Add_Stock_Sound();
				App->Cl_Stock->List_Sounds_Stock(App->Cl_Stock->ItemList_Hwnd);

				int SI = App->Cl_Scene_Data->Stock_Sound_Count - 1;

				App->Cl_Stock->Select_Item(SI);
				App->Cl_Stock->Selected_Stock_Index2 = SI;
				App->Cl_Stock->Selected_Stock_Index = SI;
				App->Cl_Stock->ListIndex = SI;

				SetDlgItemText(hDlg, IDC_ST_SELECTED, (LPCTSTR)App->Cl_Scene_Data->St_Sounds[SI]->Name);

				App->Cl_Stock->Update_Sound_Properties();

			}*/
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_ITEMSLIST)
		{
			char buff[256];
			App->Cl_Stock->ListIndex = SendDlgItemMessage(hDlg, IDC_ITEMSLIST, LB_GETCURSEL, (WPARAM)0, (LPARAM)0);

			if (App->Cl_Stock->ListIndex == -1)
			{
				return 1;
			}

			if (App->Cl_Stock->ListIndex == App->Cl_Stock->ListIndex_Old)
			{
				return 1;
			}

			App->Cl_Stock->Selected_Stock_Type = Enums::Stock_Type_Sound;

			App->Cl_Stock->Selected_Stock_Index2 = App->Cl_Stock->ListIndex;

			SendDlgItemMessage(hDlg, IDC_ITEMSLIST, LB_GETTEXT, (WPARAM)App->Cl_Stock->ListIndex, (LPARAM)buff);

			SetDlgItemText(hDlg, IDC_ST_SELECTED, (LPCTSTR)buff);
			App->Cl_Stock->Update_Sound_Properties();

			App->Cl_Stock->ListIndex_Old = App->Cl_Stock->ListIndex;
			return FALSE;

		}

		if (LOWORD(wParam) == IDOK)
		{

			//App->GDCL_Environment->Environment_Dlg_Active = 0;
			EndDialog(hDlg, LOWORD(wParam));
			//App->GDCL_Environment->Environment_hWnd = NULL;
			return TRUE;
		}

		if (LOWORD(wParam) == IDCANCEL)
		{
			//App->Cl_Environment->Environment_Dlg_Active = 0;
			EndDialog(hDlg, LOWORD(wParam));
			//App->Cl_Environment->Environment_hWnd = NULL;
			return TRUE;
		}

		break;
	}
	return FALSE;
}

// *************************************************************************
// *					Init_Stock_FileView Terry Bernie	           	   *
// *************************************************************************
void GD19_Stock::Init_Stock_FileView(void)
{
	mImageList = ImageList_Create(32, 32, ILC_COLOR24, 6, 0);
	
	// StartUp all
	hBitMap = LoadBitmap(App->hInst, MAKEINTRESOURCE(IDB_SOUNDOFF));
	ImageList_Add(mImageList, hBitMap, NULL);
	DeleteObject(hBitMap);

	hBitMap = LoadBitmap(App->hInst, MAKEINTRESOURCE(IDB_SOUNDON));
	ImageList_Add(mImageList, hBitMap, NULL);
	DeleteObject(hBitMap);

	/*hBitMap = LoadBitmap(App->hInst, MAKEINTRESOURCE(IDB_TEXTOFF));
	ImageList_Add(mImageList, hBitMap, NULL);
	DeleteObject(hBitMap);

	hBitMap = LoadBitmap(App->hInst, MAKEINTRESOURCE(IDB_TEXTON));
	ImageList_Add(mImageList, hBitMap, NULL);
	DeleteObject(hBitMap);

	hBitMap = LoadBitmap(App->hInst, MAKEINTRESOURCE(IDB_ENVOFF));
	ImageList_Add(mImageList, hBitMap, NULL);
	DeleteObject(hBitMap);

	hBitMap = LoadBitmap(App->hInst, MAKEINTRESOURCE(IDB_ENVON));
	ImageList_Add(mImageList, hBitMap, NULL);
	DeleteObject(hBitMap);*/
}

// *************************************************************************
// *						AddOptions Terry Bernie					 	   *
// *************************************************************************
void GD19_Stock::AddOptions(void)
{
	
	tvinsert.hParent = mRoot1;		// top most level no need handle
	tvinsert.hInsertAfter = TVI_LAST; // work as root level
	tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvinsert.item.pszText = "Sounds";
	tvinsert.item.iImage = 0;
	tvinsert.item.iSelectedImage = 1;
	mParent = (HTREEITEM)SendDlgItemMessage(OptionsDlgHwnd, IDC_ST_LIST1, TVM_INSERTITEM, 0, (LPARAM)& tvinsert);

	//tvinsert.hParent = mRoot1;		// top most level no need handle
	//tvinsert.hInsertAfter = TVI_LAST; // work as root level
	//tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	//tvinsert.item.pszText = "Panels";
	//tvinsert.item.iImage = 2;
	//tvinsert.item.iSelectedImage = 3;
	//mParent = (HTREEITEM)SendDlgItemMessage(OptionsDlgHwnd, IDC_ST_LIST1, TVM_INSERTITEM, 0, (LPARAM)& tvinsert);

	//tvinsert.hParent = mRoot1;		// top most level no need handle
	//tvinsert.hInsertAfter = TVI_LAST; // work as root level
	//tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	//tvinsert.item.pszText = "Environments";
	//tvinsert.item.iImage = 4;
	//tvinsert.item.iSelectedImage = 5;
	//mParent = (HTREEITEM)SendDlgItemMessage(OptionsDlgHwnd, IDC_ST_LIST1, TVM_INSERTITEM, 0, (LPARAM)& tvinsert);

	HWND TTemp = GetDlgItem(OptionsDlgHwnd, IDC_ST_LIST1);

	HTREEITEM root = TreeView_GetRoot(TTemp);

	TreeView_SelectItem(TTemp, root);
}

// *************************************************************************
// *					Create_Properties_hLV Terry Bernie				   *
// *************************************************************************
void GD19_Stock::Stock_Create_Properties_hLV(void)
{
	int NUM_COLS = 2;
	Stock_Properties_hLV = CreateWindowEx(0, WC_LISTVIEW, "",
		WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | WS_VSCROLL | LVS_REPORT | LVS_NOCOLUMNHEADER | LVS_SHOWSELALWAYS, 359, 62,
		230, 435, OptionsDlgHwnd, 0, App->hInst, NULL);

	DWORD exStyles = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;

	ListView_SetExtendedListViewStyleEx(Stock_Properties_hLV, exStyles, exStyles);

	ListView_SetBkColor(Stock_Properties_hLV, RGB(255, 255, 255));
	ListView_SetTextBkColor(Stock_Properties_hLV, RGB(255, 255, 255));

	LV_COLUMN lvC;
	memset(&lvC, 0, sizeof(LV_COLUMN));
	lvC.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvC.fmt = LVCFMT_LEFT;  // left-align the column
	std::string headers[] =
	{
		"", ""
	};
	int headerSize[] =
	{
		100, 120
	};

	for (int header = 0; header < NUM_COLS; header++)
	{
		lvC.iSubItem = header;
		lvC.cx = headerSize[header]; // width of the column, in pixels
		lvC.pszText = const_cast<char*>(headers[header].c_str());
		ListView_InsertColumn(Stock_Properties_hLV, header, &lvC);
	}
	//HFONT Font;
	//Font = CreateFont(-12, 0, 0, 0, FW_NORMAL, 0, 0, 0, 0, OUT_TT_ONLY_PRECIS, 0, 0, 0, "Aerial Black");
	SendMessage(Stock_Properties_hLV, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

	//Update_ListView_Objects();
	return;
}


