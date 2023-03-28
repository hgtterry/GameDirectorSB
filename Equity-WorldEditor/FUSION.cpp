/****************************************************************************************/
/*  Fusion.cpp                                                                          */
/*                                                                                      */
/*  Author:       Jim Mischel, Ken Baird, Jeff Lomax, John Moore, Bruce Cooner          */
/*  Description:  Top level mfc stuff here                                              */
/*                                                                                      */
/*  The contents of this file are subject to the Genesis3D Public License               */
/*  Version 1.01 (the "License"); you may not use this file except in                   */
/*  compliance with the License. You may obtain a copy of the License at                */
/*  http://www.genesis3d.com                                                            */
/*                                                                                      */
/*  Software distributed under the License is distributed on an "AS IS"                 */
/*  basis, WITHOUT WARRANTY OF ANY KIND, either express or implied.  See                */
/*  the License for the specific language governing rights and limitations              */
/*  under the License.                                                                  */
/*                                                                                      */
/*  The Original Code is Genesis3D, released March 25, 1999.                            */
/*  Copyright (C) 1996-1999 Eclipse Entertainment, L.L.C. All Rights Reserved           */
/*                                                                                      */
/****************************************************************************************/

#include "stdafx.h"
#include "FUSION.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "FUSIONDoc.h"
#include "FUSIONView.h"
#include "PreferencesDialog.h"

#include "FusionTabControls.h"
#include "about.h"
#include "FilePath.h"
#include "ram.h"
#include "util.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//#define TIME_OUT

/////////////////////////////////////////////////////////////////////////////
// CFusionApp

BEGIN_MESSAGE_MAP(CFusionApp, CWinApp)
	//{{AFX_MSG_MAP(CFusionApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
//	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND_EX_RANGE(ID_FILE_MRU_FILE1, ID_FILE_MRU_FILE16, OnOpenRecentFile)
	ON_COMMAND(IDM_PREFERENCES, OnPreferences)
	ON_UPDATE_COMMAND_UI(IDM_PREFERENCES, OnUpdatePreferences)
	ON_COMMAND(ID_HELP_HOWDOI, OnHelpHowdoi)

	// hgtterry Menu Commands
	ON_COMMAND(ID_EQUITYSB_TXLEDITOR, Open_TxlEditor)
	ON_COMMAND(ID_EQUITYSB_FACEPROPERTIES, Open_FaceProperties)

	//}}AFX_MSG_MAP
	ON_COMMAND(ID_HELP_INDEX, OnHelpIndex)
	ON_COMMAND(ID_HELP, OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, OnContextHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFusionApp construction

CFusionApp::CFusionApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	NumCopiedBrushes=0;
	NumCopiedEntities=0;
	CopiedBrushes=NULL;
	CopiedEntities=NULL;
}

//	Destruction...
CFusionApp::~CFusionApp()
{
	if( pShutdownEvent != NULL )
	{
		pShutdownEvent->SetEvent();
		
		if( pWatcher != NULL )
			::WaitForSingleObject( pWatcher->m_hThread, INFINITE );

		delete pShutdownEvent;
		pShutdownEvent = NULL;
	}

	if( pNewInstanceEvent != NULL )
	{
		delete pNewInstanceEvent;
		pNewInstanceEvent = NULL;
	}

	CloseAllDocuments( TRUE );

	if (pPrefs != NULL)
	{
		Prefs_Save (pPrefs, m_pszProfileName);
		Prefs_Destroy (&pPrefs);
	}
	if (pResolvedPrefs != NULL)
	{
		Prefs_Destroy (&pResolvedPrefs);
	}

	ClearClipboard();
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CFusionApp object

CFusionApp theApp;

#pragma warning (disable:4100)
static	LONG	__stdcall xxHandler(LPEXCEPTION_POINTERS xcpt)
{
static	int	nested;

	if	(!nested)
	{
		nested = 1;
		::MessageBeep(1);
		exit(0);
	}

	return EXCEPTION_EXECUTE_HANDLER;
}
#pragma warning (default:4100)

void CFusionApp::ResolvePreferencesPaths (void)
{
	char AppDir[MAX_PATH];
	char WorkTxlSearch[2048];
	char Work[2048];	// hope that's big enough!!
	
	::Prefs_SetBackgroundColor (pResolvedPrefs, Prefs_GetBackgroundColor (pPrefs));
	::Prefs_SetGridColor (pResolvedPrefs, Prefs_GetGridColor (pPrefs));
	::Prefs_SetSnapGridColor (pResolvedPrefs, Prefs_GetSnapGridColor (pPrefs));
	::FilePath_GetNameAndExt (Prefs_GetTxlName (pPrefs), Work);
	::Prefs_SetTxlName (pResolvedPrefs, Work);

	WorkTxlSearch[0] = '\0';
	::GetCurrentDirectory (sizeof (WorkTxlSearch), WorkTxlSearch);
	if (::GetModuleFileName (NULL, AppDir, sizeof (AppDir)))
	{
		::FilePath_GetDriveAndDir (AppDir, AppDir);
	}
	else
	{
		AppDir[0] = '\0';
	}
	::FilePath_AppendSearchDir (WorkTxlSearch, AppDir);

	::FilePath_ResolveRelativePathList (Prefs_GetTxlSearchPath (pPrefs), Work);
	::FilePath_AppendSearchDir (WorkTxlSearch, Work);
	::Prefs_SetTxlSearchPath (pResolvedPrefs, WorkTxlSearch);

	::FilePath_ResolveRelativePath (Prefs_GetPreviewPath (pPrefs), Work);
	::Prefs_SetPreviewPath (pResolvedPrefs, Work);

	::FilePath_ResolveRelativePathList (Prefs_GetHeadersList (pPrefs), Work);
	::Prefs_SetHeadersList (pResolvedPrefs, Work);

	::FilePath_ResolveRelativePath (Prefs_GetObjectsDir (pPrefs), Work);
	::Prefs_SetObjectsDir (pResolvedPrefs, Work);
	
	::FilePath_ResolveRelativePath (Prefs_GetProjectDir (pPrefs), Work);
	::Prefs_SetProjectDir (pResolvedPrefs, Work);

// changed QD Actors
	::FilePath_ResolveRelativePathList (Prefs_GetActorsList (pPrefs), Work);
	::Prefs_SetActorsList (pResolvedPrefs, Work);

	::FilePath_ResolveRelativePathList (Prefs_GetPawnIni (pPrefs), Work);
	::Prefs_SetPawnIni (pResolvedPrefs, Work);
// end change
}


A_App* App = NULL;

// *************************************************************************
// *							InitInstance							   *
// *************************************************************************
BOOL CFusionApp::InitInstance() // hgtterry InitInstance
{
	App = new A_App();
	App->InitApp();

	char AppPath[MAX_PATH];
	::GetModuleFileName (NULL, AppPath, MAX_PATH);
	FilePath_GetDriveAndDir (AppPath, AppPath);

	strcpy(App->WorldEditor_Directory,AppPath);

	SetUnhandledExceptionFilter(xxHandler);

	//	Setup global environment...

	{
		// set up the help file
		char HelpFilePath[MAX_PATH];

		FilePath_AppendName (AppPath, "WRLDEDIT.HLP", HelpFilePath);
		//First free the string allocated by MFC at CWinApp startup.
		//The string is allocated before InitInstance is called.
		free ((void *)m_pszHelpFilePath);

		//The CWinApp destructor will free the memory.
		m_pszHelpFilePath=_tcsdup(_T(HelpFilePath));
	}

	// Initialize OLE 2.0 libraries
	/*if (!AfxOleInit())
	{
		AfxMessageBox("Cannot load OLE");
		return FALSE;
	}*/

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif


	{
		char IniFilePath[MAX_PATH] ;

		FilePath_AppendName (AppPath, FUSION_INIFILE_NAME, IniFilePath);

		// Set our INI file
		free( (void*)m_pszProfileName ) ;
		m_pszProfileName = _tcsdup( IniFilePath ) ;

	}

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// load the preferences from the INI file, and resolve any relative paths
	pPrefs = Prefs_Read (m_pszProfileName);
	pResolvedPrefs = Prefs_Create ();

	ResolvePreferencesPaths ();

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	pDocTemplate = new CMultiDocTemplate(
		IDR_FUSIONTYPE,
		RUNTIME_CLASS(CFusionDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CFusionView));
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	//	Preliminary command line error checking...

	//	Are there commands?
	int index = 0;
	CString CmdLine = m_lpCmdLine;
	CString Argument;
	if( ( index = CmdLine.Find( '-' )) != -1 )
	{
		//	Yep...

		//	Is there a .3dt file in there before the first command?
		Argument = CmdLine.Left( index - 1 );
		if( Argument.IsEmpty() )
		{
			//	Nope...
			AfxMessageBox( "Error: Unable to process command line. File not specified.", MB_OK + MB_ICONERROR);
			return FALSE;
		}
	}

	//	If there is a file name in cmdInfo, does it have a .3dt extension?
	//  If not, provide one...
	Argument = cmdInfo.m_strFileName;
	Argument.MakeLower();
	if( !Argument.IsEmpty() )
	{
		if( Argument.Find( ".3dt" ) == -1 )
		{
			//	Extension not present, add it to the end of file name
			Argument = Argument + ".3dt";
			cmdInfo.m_strFileName = Argument;
		}
	}

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
	{
		pMainFrame->IsDestroyingApp = 1;
		return FALSE;
	}

	//	Check to see if this is the first instance...
	if( !IsFirstInstance() )
		return FALSE;

	App->LoadProgramResource();

	//	Let's setup the brush/entities tab...
	pMainFrame->m_wndTabControls->UpdateTabs();

	//	Let's grab the active document and save it...
	CChildFrame* pActiveChild =(CChildFrame *)pMainFrame->MDIGetActive();
	CFusionDoc* pDoc;

	if (pActiveChild == NULL ||
	  (pDoc = (CFusionDoc*) pActiveChild->GetActiveDocument()) == NULL)
	{
		TRACE0("Warning: No active document for tab update command.\n");
		AfxMessageBox(AFX_IDP_COMMAND_FAILURE);
		return FALSE;     // command failed
	}
	pFusionDoc = pDoc;

	if( !ProcessCommandLine() )
	{
		return FALSE;
	}


	//	Setup user preferences...

	InitUserPreferences(pMainFrame);

	App->CL_Dialogs->Start_FrontPanel();
	
	//OnAppAbout();
	
	pMainFrame->IsStartingApp = 0;

	App->InitMFC();
	App->CL_World->Set_Paths();
	App->CL_TabsControl->Start_Tabs_Control_Dlg();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CFusionApp commands

BOOL CFusionApp::PreTranslateMessage(MSG* pMsg)
{
	return CWinApp::PreTranslateMessage(pMsg);
}

// App command to run the dialog
void CFusionApp::OnAppAbout()
{
	CAboutDlg aboutDlg;

	aboutDlg.DoModal() ;
}

void CFusionApp::Open_TxlEditor() // hgtterry void CFusionApp::Open_TxlEditor()
{
	App->CL_TxlEditor->Start_Texl_Dialog();
}

void CFusionApp::Open_FaceProperties() // hgtterry void CFusionApp::Open_FaceProperties()
{
	App->CL_FaceDialog->Start_FaceDialog();
}



//	CHANGE!	03/29/97	John Moore
void CFusionApp::InitUserPreferences(CMainFrame* pMainFrame)
{
	//	Get rid of the previous default view that is created...
//	pMainFrame->HideAllViews();

	// Let's show the window as maximized...
	m_nCmdShow = SW_MAXIMIZE;
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	//	Setup 4 views from the get-go...
//	pMainFrame->View4views();
}
//	End of CHANGE

BOOL CFusionApp::OnIdle(LONG lCount) 
{
	// TODO: Add your specialized code here and/or call the base class

	//	Let's grab the active document and save it...
	CChildFrame* pActiveChild =(CChildFrame *)pMainFrame->MDIGetActive();
	CFusionDoc* pDoc;

	if (pActiveChild == NULL ||
		(pDoc = (CFusionDoc*) pActiveChild->GetActiveDocument()) == NULL)
	{
		//TRACE0("Warning: No active document for tab update command.\n");
		//AfxMessageBox(AFX_IDP_COMMAND_FAILURE);
		//return FALSE;     // command failed

		//	We need to hide all tabs from display...
		if( pFusionDoc != NULL )
		{
			pMainFrame->m_wndTabControls->DisableAllTabDialogs();

			if (pMainFrame->mpBrushAttributes)
				pMainFrame->mpBrushAttributes->UpdateBrushFocus();

			if (pMainFrame->mpFaceAttributes)
				pMainFrame->mpFaceAttributes->UpdatePolygonFocus();

			pFusionDoc = NULL;
		}
	}
	else if( pFusionDoc != pDoc )
	{
		pFusionDoc = pDoc;
		pMainFrame->m_wndTabControls->UpdateTabs();
		pMainFrame->LoadComboBox() ;
	}
	
	return CWinApp::OnIdle(lCount);
}

BOOL CFusionApp::IsFirstInstance()
{
	pNewInstanceEvent = new CEvent( FALSE, FALSE, AfxGetAppName() );
	
	if( ::GetLastError() == ERROR_ALREADY_EXISTS )
	{
		pNewInstanceEvent->SetEvent();
		return FALSE;
	}

	pShutdownEvent = new CEvent;
	pWatcher = ( CActivationWatch* ) AfxBeginThread( RUNTIME_CLASS( CActivationWatch ) );

	return TRUE;
}

BOOL CFusionApp::ProcessCommandLine()
{
	CString CmdLine = m_lpCmdLine;
	CString Argument;
	CString Parameter;
	BOOL done = CmdLine.IsEmpty();
	int index = 0;
	int length = 0;

	while( !done )
	{
		if( ( index = CmdLine.Find( ' ' )) != -1 )
		{
			Argument = CmdLine.Left( index );
			length = CmdLine.GetLength() - index - 1;
			CmdLine = CmdLine.Right( length );
		}
		else
		{
			Argument = CmdLine;
			done = TRUE;
		}

		//	Is this a command?  If so, process it and its argument(s)...
		if( Argument.GetAt( 0 ) == '-' )
		{
			//	If there's a parameter, grab it...
			if( ( index = CmdLine.Find( ' ' )) != -1 )
			{
				Parameter = CmdLine.Left( index );
				length = CmdLine.GetLength() - index - 1;
				CmdLine = CmdLine.Right( length );
			}
			else
			{
				//	Is CmdLine empty?  If not, our last argument is the parameter...
				Parameter = CmdLine;
				done = TRUE;
			}

			if( Parameter == Argument )
				Parameter.Empty();

			//	Which command?
			Argument.MakeLower();

			if( Argument == "-export" )
			{
				// MAP file export.  Parameter indicates the file name...
				CommandLineExport( &Parameter );

				//	Request satisfied, exit the application...
				return FALSE;
			}
		}
	}

	return TRUE;
}

//	Executes command line request to export a quake map file...
void CFusionApp::CommandLineExport( CString* pMapFileName )
{
	if( !pMapFileName->IsEmpty() )
	{
		//	Does the file name have a .MAP extension?
		//  If not, provide one...
		CString Argument = *pMapFileName;
		Argument.MakeLower();
	
		if( Argument.Find( ".map" ) == -1 )
		{
			//	Extension not present, add it to the end of file name
			Argument = Argument + ".map";
			*pMapFileName = Argument;
		}

		//	Go ahead and export...
//		pFusionDoc->ExportToQuakeMap( FALSE, pMapFileName );
	}
	else
	{
		//	Problem! no MAP file specified...
		AfxMessageBox( "Error: Unable to export world file. No map file name specified.\n", MB_OK + MB_ICONERROR );
	}
}


// called when user creates a new file
void CFusionApp::OnFileNew() 
{
	// first call down to CWinApp::FileNew()
	CWinApp::OnFileNew();
	this->pMainFrame->UpdateActiveDoc ();
}

void CFusionApp::OnFileOpen() 
{
	// If the current document is unmodified and has no brushes, wipe it
	CFusionDoc* pDoc = GetActiveFusionDoc() ;
	if( pDoc && ( pDoc->IsModified() == FALSE ) && BrushList_Count( Level_GetBrushes (pDoc->pLevel), BRUSH_COUNT_ALL ) == 0 )
	{
		this->pMainFrame->SendMessage( WM_COMMAND, ID_FILE_CLOSE, 0 ) ;
	}
	CWinApp::OnFileOpen ();

	this->pMainFrame->UpdateActiveDoc ();
}

BOOL CFusionApp::OnOpenRecentFile (UINT nID)
{
	
	BOOL rslt;

	// If the current document is unmodified and has no brushes, wipe it
	CFusionDoc* pDoc = GetActiveFusionDoc() ;
	if( pDoc && ( pDoc->IsModified() == FALSE ) && BrushList_Count( Level_GetBrushes (pDoc->pLevel), BRUSH_COUNT_ALL ) == 0 )
	{
		this->pMainFrame->SendMessage( WM_COMMAND, ID_FILE_CLOSE, 0 ) ;
	}

	

	rslt = CWinApp::OnOpenRecentFile (nID);
	if (rslt != FALSE)
	{
		this->pMainFrame->UpdateActiveDoc ();

		// hgtterry
		CFusionDoc* pDoc2 = GetActiveFusionDoc() ;
		//strcpy(App->CL_Scene->Current_3DT_Path,pDoc2->GetPathName());
		//strcpy(App->CL_Scene->Current_3DT_File,pDoc2->GetTitle());
		//strcpy(App->CL_Scene->Current_TXL_FilePath,Level_GetWadPath (pDoc2->pLevel)); // hgtterry

		App->CL_World->Set_Paths();
	}

	return rslt;
}

CFusionDoc * CFusionApp::GetActiveFusionDoc( void ) const
{
	CFusionDoc* pDoc;
	CChildFrame* pActiveChild =(CChildFrame *)pMainFrame->MDIGetActive();

	if(	pActiveChild == NULL ||
	  (	pDoc = (CFusionDoc*) pActiveChild->GetActiveDocument()) == NULL )
	{
		return NULL ;
	}
	return  pDoc;
}

void CFusionApp::OnPreferences() 
{
	CPreferencesDialog PrefsDlg;

	CString OldObjectsDir;

	PrefsDlg.coBackground = Prefs_GetBackgroundColor (pPrefs);
	PrefsDlg.coGrid = Prefs_GetGridColor (pPrefs);
	PrefsDlg.coSnapGrid = Prefs_GetSnapGridColor (pPrefs);

	PrefsDlg.m_HeadersList = Prefs_GetHeadersList (pPrefs);
	PrefsDlg.m_ObjectsDir = Prefs_GetObjectsDir (pPrefs);
	PrefsDlg.m_PreviewPath = Prefs_GetPreviewPath (pPrefs);
	PrefsDlg.m_TxlName = Prefs_GetTxlName (pPrefs);
	PrefsDlg.m_TxlSearchPath = Prefs_GetTxlSearchPath (pPrefs);

	OldObjectsDir = PrefsDlg.m_ObjectsDir;

	if(	PrefsDlg.DoModal() == IDOK )
	{
		Prefs_SetBackgroundColor (pPrefs, PrefsDlg.coBackground);
		Prefs_SetGridColor (pPrefs, PrefsDlg.coGrid);
		Prefs_SetSnapGridColor (pPrefs, PrefsDlg.coSnapGrid);

		Prefs_SetHeadersList (pPrefs, PrefsDlg.m_HeadersList);
		Prefs_SetObjectsDir (pPrefs, PrefsDlg.m_ObjectsDir);
		Prefs_SetPreviewPath (pPrefs, PrefsDlg.m_PreviewPath);
		Prefs_SetTxlName (pPrefs, PrefsDlg.m_TxlName);
		Prefs_SetTxlSearchPath (pPrefs, PrefsDlg.m_TxlSearchPath);

#if 0 // This has been fixed: the directory was being set on opening a file
		/*
		  Something in this program has the disturbing tendency to change 
		  the current directory.  Until I can track that down, I don't want
		  to resolve the paths but once...
		*/
		Prefs_SetBackgroundColor (pResolvedPrefs, PrefsDlg.coBackground);
		Prefs_SetGridColor (pResolvedPrefs, PrefsDlg.coGrid);
		Prefs_SetSnapGridColor (pResolvedPrefs, PrefsDlg.coSnapGrid);
#else	
		ResolvePreferencesPaths ();
#endif			
		CFusionDoc* pDoc = GetActiveFusionDoc() ;
		if( pDoc != NULL )
		{
			pDoc->UpdateAllViews( UAV_ALL3DVIEWS, NULL );
		}
		if (OldObjectsDir != PrefsDlg.m_ObjectsDir)
		{
			if (pMainFrame)
				if (pMainFrame->m_wndTabControls)
					if (pMainFrame->m_wndTabControls->m_pBrushEntityDialog)
						pMainFrame->m_wndTabControls->m_pBrushEntityDialog->SetupObjectListCombo();
		}
	}
}

void CFusionApp::OnUpdatePreferences(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable() ;
}

afx_msg void CFusionApp::OnHelp( )
{
	WinHelp (0, HELP_FINDER);
}

afx_msg void CFusionApp::OnHelpIndex( )
{
	WinHelp ((LONG)"", HELP_PARTIALKEY);
}

void CFusionApp::OnHelpHowdoi() 
{
	// TODO: Add your command handler code here
	
}

void CFusionApp::ClearClipboard() 
{
	int i;

	if (CopiedBrushes)
	{
		for (i=0;i<NumCopiedBrushes;i++) {
			if (CopiedBrushes[i])
				Brush_Destroy(&(CopiedBrushes[i]));
		}

		free(CopiedBrushes);
	}

	if (CopiedEntities)
	{
// changed QD
//		for (i=0;i<NumCopiedBrushes;i++) {
		for (i=0;i<NumCopiedEntities;i++) {
// end change
			if (CopiedEntities[i])
				delete (CopiedEntities[i]);
		}

		free(CopiedEntities);
	}

	NumCopiedBrushes=0;
	NumCopiedEntities=0;
	CopiedBrushes=NULL;
	CopiedEntities=NULL;
}
