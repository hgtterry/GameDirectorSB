
#include "stdafx.h"
#include "AB_App.h"


A_App::A_App()
{
	ABC_Export_RFW = NULL;
	CL_FileIO = NULL;
	CL_Dialogs = NULL;
	CL_Scene = NULL;
	CL_Render_App = NULL;
	CL_TxlEditor = NULL;

	AppBackground = NULL;
	BlackBrush =	NULL;
	Brush_White =	NULL;
	Brush_Green =	NULL;

	Font_CB15 = 0;
	Font_CB18 = 0;
	Font_Arial20 = 0;

	// MFC
	m_pMainFrame = NULL;//(CMainFrame *)AfxGetMainWnd();
	pCFusionDoc = NULL;
}

A_App::~A_App()
{

}

// *************************************************************************
// *								InitMFC								   *
// *************************************************************************
void A_App::InitMFC(void)
{	
	m_pMainFrame = (CMainFrame *)AfxGetMainWnd();
}

// *************************************************************************
// *						InitApp Inflanite							   *
// *************************************************************************
bool A_App::InitApp(void)
{	
	ABC_Export_RFW  =			new AB_Export_RFW();
	CL_FileIO =					new	A_FileIO();
	CL_Dialogs =				new	A_Dialogs();
	CL_Scene =					new	A_Scene();
	CL_Render_App =				new	A_Render_App();
	CL_TxlEditor =				new	A_TxlEditor();

	hInst =NULL;
	MainHwnd = NULL;
	
	return 1;
}

// *************************************************************************
// *					SetBrushes_Fonts Inflanite						   *
// *************************************************************************
void A_App::SetBrushes_Fonts(void)
{
	AppBackground = CreateSolidBrush(RGB(213, 222, 242));

	BlackBrush = CreateSolidBrush(RGB(0, 0, 0));
	Brush_White = CreateSolidBrush(RGB(255, 255, 255));
	Brush_Green = CreateSolidBrush(RGB(0, 255, 0));

/*	Brush_But_Normal = CreateSolidBrush(RGB(255, 255, 150));
	Brush_But_Hover = CreateSolidBrush(RGB(255, 255, 200));
	Brush_But_Pressed = CreateSolidBrush(RGB(240, 240, 190));

	Brush_Tabs = CreateSolidBrush(RGB(255, 255, 255));
	Brush_Tabs_UnSelected = CreateSolidBrush(RGB(190, 190, 190));*/

	//Font_CB15 = CreateFont(-10, 0, 0, 0, 0, 0, 0, 0, 0, OUT_TT_ONLY_PRECIS, 0, 0, 0, "Arial");

	Font_CB15 = CreateFont(36,10,250,0,FW_DONTCARE,FALSE,TRUE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
                CLIP_DEFAULT_PRECIS,ANTIALIASED_QUALITY, VARIABLE_PITCH,TEXT("Arial"));

	Font_CB18 = CreateFont(-18, 0, 0, 0, 0, 0, 0, 0, 0, OUT_TT_ONLY_PRECIS, 0, 0, 0, "Courier Black");
	Font_Arial20 = CreateFont(-20, 0, 0, 0, 0, 0, 0, 0, 0, OUT_TT_ONLY_PRECIS, 0, 0, 0, "Arial");

}

// *************************************************************************
// *									Say								   *
// *************************************************************************
void A_App::Say(const char* Message)
{
	char text[1024];
	strcpy(text, Message);
	MessageBox(NULL,Message,"Message",MB_OK);
}

// *************************************************************************
// *								Say_Int								   *
// *************************************************************************
void A_App::Say_Int(int Value)
{
	char buf[255];
	itoa(Value, buf, 10);
	MessageBox(MainHwnd, buf, "Equity Notice", MB_OK);
}

// *************************************************************************
// *							Say_Float								   *
// *************************************************************************
void A_App::Say_Float(float Value)
{
	char buf[255];
	sprintf(buf, "%f", Value);
	MessageBox(MainHwnd, buf, "Equity Notice", MB_OK);
}



