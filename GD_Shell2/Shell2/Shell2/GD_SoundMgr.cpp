#include "StdAfx.h"
#include "BT_App.h"
#include "GD_SoundMgr.h"


GD_SoundMgr::GD_SoundMgr(void)
{

	SoundEngine = irrklang::createIrrKlangDevice();
	SndFile = NULL;
	SndVolume=0.5;
	IsObject = 0;
	strcpy(mSoundFile,"");
	strcpy(Default_Folder,App->EquityDirecory_FullPath);
	
}

GD_SoundMgr::~GD_SoundMgr(void)
{
}

// *************************************************************************
// *	  			InitSound_Defaults Terry Bernie						   *
// *************************************************************************
bool GD_SoundMgr::InitSound_Defaults(int Index)
{
	//S_Object[Index]->Sound[0].Data0 = 0;
	//S_Object[Index]->Sound[0].Data1 = 0;
	//S_Object[Index]->Sound[0].Is3D = 0;
	//S_Object[Index]->Sound[0].Loop = 0;
	//S_Object[Index]->Sound[0].Pan = 0;
	//S_Object[Index]->Sound[0].Play = 1;
	//strcpy(S_Object[Index]->Sound[0].SoundFile,"None"); // Needs Lookind at
	//S_Object[Index]->Sound[0].Volume = 1;
	return 1;
}

// *************************************************************************
// *					GetSoundFiles Terry Bernie						   *
// *************************************************************************
bool GD_SoundMgr::GetSoundFiles(HWND hDlg)
{
	/*HWND ListHwnd = GetDlgItem(hDlg,IDC_SOUNDLIST); 

	WIN32_FIND_DATA ffd;
	HANDLE hFind = INVALID_HANDLE_VALUE;

	char SearchName[1024];
	strcpy(SearchName,Default_Folder);
	strcat(SearchName,"\\Media\\Sounds\\*.ogg");

	hFind = FindFirstFile(SearchName,&ffd);

	SendMessage(ListHwnd,LB_ADDSTRING, 0, (LPARAM) (LPCTSTR)ffd.cFileName);

	while (FindNextFile(hFind, &ffd) != 0)
	{
		SendMessage(ListHwnd,LB_ADDSTRING, 0, (LPARAM) (LPCTSTR)ffd.cFileName);
	}*/

	return 1;
}
