#include "StdAfx.h"
#include "resource.h"
#include "GD19_App.h"
#include "GD19_SoundMgr.h"


GD19_SoundMgr::GD19_SoundMgr(void)
{
	SoundEngine = irrklang::createIrrKlangDevice();
	SndFile = NULL;
	SndVolume=0.5;
	IsObject = 0;
	strcpy(mSoundFile,"");
	strcpy(Default_Folder,App->EquityDirecory_FullPath);

	SoundFile_Count = 0;
	Current_Object_Sound[0] = 0;
	IsCancelled = 0;
}


GD19_SoundMgr::~GD19_SoundMgr(void)
{
}

// *************************************************************************
// *	  		Dialog_SoundFile()		Terry Bernie					   *
// *************************************************************************
bool GD19_SoundMgr::Dialog_SoundFile()
{
	IsCancelled = 0;

	DialogBox(App->hInst,(LPCTSTR)IDD_GD_SOUNDPLAYER,App->Fdlg,(DLGPROC)Dialog_SoundFile_Proc);
	return 1;
}
// *************************************************************************
// *			Dialog_SoundFile_Proc  	Terry Bernie					   *
// *************************************************************************
LRESULT CALLBACK GD19_SoundMgr::Dialog_SoundFile_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
				
	switch (message)
	{
	case WM_INITDIALOG:
		{
			App->SetTitleBar(hDlg);

			HFONT Font;
			Font = CreateFont( -15,0,0,0,FW_BOLD,0,0,0,0,OUT_TT_ONLY_PRECIS ,0,0,0, "Aerial Black");
			SendDlgItemMessage(hDlg,IDC_TITLENAME, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hDlg,IDC_SOUNDLIST, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hDlg,IDC_EDITINT, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

			SetDlgItemText(hDlg,IDC_TITLENAME,(LPCTSTR)"Sound Player");

			SetDlgItemText(hDlg,IDC_EDITINT,(LPCTSTR)App->Cl_SoundMgr->mSoundFile);

			App->Cl_SoundMgr->GetSoundFiles(hDlg,"*.ogg");
			App->Cl_SoundMgr->GetSoundFiles(hDlg,"*.wav");

			int Sel = SendMessage(GetDlgItem(hDlg, IDC_SOUNDLIST), LB_SELECTSTRING, -1, (LPARAM)App->Cl_SoundMgr->Current_Object_Sound);

			char buff[255];
			SendDlgItemMessage(hDlg, IDC_SOUNDLIST, LB_GETTEXT, (WPARAM)Sel, (LPARAM)buff);
			SetDlgItemText(hDlg, IDC_EDITINT, (LPTSTR)buff);

			int VolPer = int(App->Cl_SoundMgr->SndVolume*10);

			HWND Slider =GetDlgItem(hDlg,IDC_SLVOLUME);	
			SendMessage(Slider, TBM_SETRANGE, (WPARAM) TRUE,(LPARAM) MAKELONG(0,10));  
			SendMessage(Slider, TBM_SETPOS, (WPARAM) 1,(LPARAM)VolPer);

			VolPer = VolPer*10;

			char buf[10];
			sprintf(buf,"%i",VolPer);
			SetDlgItemText(hDlg,IDC_VOLBOX,(LPCTSTR)buf);
			return TRUE;
		}
		case WM_CTLCOLORSTATIC:
		{
			/*if(GetDlgItem(hDlg,IDC_STPER) == (HWND)lParam)
			{	
				SetBkColor((HDC) wParam, RGB(0, 255, 0));	
				SetTextColor((HDC) wParam, RGB(0,0,0));
				SetBkMode((HDC) wParam, TRANSPARENT);
				return (UINT) App->AppBackground;
			}*/
			if(GetDlgItem(hDlg,IDC_STVOLUME) == (HWND)lParam)
			{	
				SetBkColor((HDC) wParam, RGB(0, 255, 0));	
				SetTextColor((HDC) wParam, RGB(0,0,0));
				SetBkMode((HDC) wParam, TRANSPARENT);
				return (UINT) App->DialogBackGround;
			}
			if(GetDlgItem(hDlg,IDC_VOLBOX) == (HWND)lParam)
			{	
				SetBkColor((HDC) wParam, RGB(0, 255, 0));	
				SetTextColor((HDC) wParam, RGB(0,0,0));
				SetBkMode((HDC) wParam, TRANSPARENT);
				return (UINT) App->Brush_White;
			}
			if(GetDlgItem(hDlg,IDC_EDITINT) == (HWND)lParam)
			{	
				SetBkColor((HDC) wParam, RGB(0, 255, 0));	
				SetTextColor((HDC) wParam, RGB(0,0,0));
				SetBkMode((HDC) wParam, TRANSPARENT);
				return (UINT) App->Brush_White;
			}
			if(GetDlgItem(hDlg,IDC_SLVOLUME) == (HWND)lParam)
			{	
				SetBkColor((HDC) wParam, RGB(0, 255, 0));	
				SetTextColor((HDC) wParam, RGB(0,0,255));
				SetBkMode((HDC) wParam, TRANSPARENT);
				return (UINT) App->DialogBackGround;
			}
			if(GetDlgItem(hDlg,IDC_TITLENAME) == (HWND)lParam)
			{	
				SetBkColor((HDC) wParam, RGB(0, 255, 0));	
				SetTextColor((HDC) wParam, RGB(0,0,0));
				SetBkMode((HDC) wParam, TRANSPARENT);
				return (UINT) App->DialogBackGround;
			}
			return FALSE;
		}

		case WM_CTLCOLORDLG:
			{
				return (LONG)App->DialogBackGround;
			}
		case WM_HSCROLL :
		{
			HWND Slider = GetDlgItem(hDlg,IDC_SLVOLUME);
			int pos = 0;
			int Percent = 0;
			char buf[20];
			pos = SendMessage(Slider, TBM_GETPOS, (WPARAM) 0,(LPARAM)0); 
			Percent = pos*10;
			sprintf(buf,"%i",Percent);
			SetDlgItemText(hDlg,IDC_VOLBOX,(LPCTSTR)buf);

			float sum = float(pos)/10;
			App->Cl_SoundMgr->SndVolume = sum;
			return 1;
		}

		case WM_NOTIFY:
			{
				LPNMHDR nmhdr = (LPNMHDR) lParam;

				if (nmhdr->idFrom == IDC_PLAY && nmhdr->code == NM_CUSTOMDRAW)
				{
					LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)nmhdr;
					App->Custom_Button_Normal(item);
					return CDRF_DODEFAULT;
				}

				if (nmhdr->idFrom == IDOK && nmhdr->code == NM_CUSTOMDRAW)
				{
					LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)nmhdr;
					App->Custom_Button_Normal(item);
					return CDRF_DODEFAULT;
				}

				if (nmhdr->idFrom == IDCANCEL && nmhdr->code == NM_CUSTOMDRAW)
				{
					LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)nmhdr;
					App->Custom_Button_Normal(item);
					return CDRF_DODEFAULT;
				}

			}break;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDC_SOUNDLIST) 
			{
				char buff[256];
				int Index=0;
				Index = SendDlgItemMessage(hDlg,IDC_SOUNDLIST,LB_GETCURSEL, (WPARAM)0, (LPARAM)0);

				if (Index==-1)
				{
					return 1;
				}

				SendDlgItemMessage(hDlg,IDC_SOUNDLIST,LB_GETTEXT, (WPARAM)Index, (LPARAM)buff);

				SetDlgItemText(hDlg,IDC_EDITINT,(LPTSTR)buff);

				return TRUE;
			}
			
			if (LOWORD(wParam) == IDOK) 
			{
				if (App->Cl_SoundMgr->SndFile==NULL)
				{
				}
				else
				{
					App->Cl_SoundMgr->SndFile->stop();
					App->Cl_SoundMgr->SndFile=NULL;
				}

				App->Cl_SoundMgr->IsCancelled = 0;

				char file[256];
				GetDlgItemText(hDlg,IDC_EDITINT,(LPTSTR)file,256);
				strcpy(App->Cl_SoundMgr->mSoundFile,file);
				App->Cl_SoundMgr->Remeber_SoundFile(file);
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}

			if (LOWORD(wParam)== IDCANCEL) 
			{
				if (App->Cl_SoundMgr->SndFile == NULL)
				{
				}
				else
				{
					App->Cl_SoundMgr->SndFile->stop();
					App->Cl_SoundMgr->SndFile->drop();
					App->Cl_SoundMgr->SndFile = NULL;

				}

				App->Cl_SoundMgr->IsCancelled = 1;
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}

			if (LOWORD(wParam)== IDC_PLAY) 
			{
				char file[256];
				GetDlgItemText(hDlg,IDC_EDITINT,(LPTSTR)file,256);

				if (App->Cl_SoundMgr->SndFile==NULL)
				{
				}
				else
				{
					App->Cl_SoundMgr->SndFile->stop();
					App->Cl_SoundMgr->SndFile=NULL;
				}

				int result=1;
				result = strcmp(file,"");
				if (result == 0)
				{

				}
				else
				{
					result = strcmp(file,"None");
					if (result == 0)
					{

					}
					else
					{
						char buff[1024];
						strcpy(buff,App->Cl_SoundMgr->Default_Folder);
						strcat(buff,"\\Media\\Sounds\\");
						strcat(buff,file);

						App->Cl_SoundMgr->SndFile = App->Cl_SoundMgr->SoundEngine->play2D(buff,false,true,true);
						App->Cl_SoundMgr->SndFile->setVolume(App->Cl_SoundMgr->SndVolume);
						App->Cl_SoundMgr->SndFile->setIsPaused(false);
					}
				}
				return TRUE;
			}

			break;
			
	}
    return FALSE;
}
// *************************************************************************
// *	  			InitSound_Defaults Terry Bernie						   *
// *************************************************************************
bool GD19_SoundMgr::InitSound_Defaults(int Index)
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
bool GD19_SoundMgr::GetSoundFiles(HWND hDlg,char *Extention)
{
	HWND ListHwnd = GetDlgItem(hDlg,IDC_SOUNDLIST); 

	WIN32_FIND_DATA ffd;
	HANDLE hFind = INVALID_HANDLE_VALUE;

	char SearchName[1024];
	strcpy(SearchName,Default_Folder);
	strcat(SearchName,"\\Media\\Sounds\\");
	strcat(SearchName,Extention);

	hFind = FindFirstFile(SearchName,&ffd);

	SendMessage(ListHwnd,LB_ADDSTRING, 0, (LPARAM) (LPCTSTR)ffd.cFileName);

	while (FindNextFile(hFind, &ffd) != 0)
	{
		SendMessage(ListHwnd,LB_ADDSTRING, 0, (LPARAM) (LPCTSTR)ffd.cFileName);
	}
	
	return 1;
}

// *************************************************************************
// *					Remeber_SoundFile Terry Bernie					   *
// *************************************************************************
bool GD19_SoundMgr::Remeber_SoundFile(char* File)
{
	Sound_File.push_back(File);
	SoundFile_Count = Sound_File.size();
	return 1;
}
