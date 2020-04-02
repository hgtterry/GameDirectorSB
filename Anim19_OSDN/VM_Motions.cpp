#include "stdafx.h"
#include "GD19_App.h"
#include "resource.h"
#include "VM_Motions.h"


VM_Motions::VM_Motions()
{
	Current_StartTime = 0;
	Current_EndTime = 0;
}


VM_Motions::~VM_Motions()
{
}


// *************************************************************************
// *					Play_SelectedMotion Terry Bernie				   *
// *************************************************************************
void VM_Motions::Play_SelectedMotion(void)
{
	//------------------------------------------------------- RF Model
	if (App->CL_Vm_Model->Model_Loaded == 0) { return; }
	if (App->CL_Vm_Model->MotionCount == 0) { return; }

	if (App->CL_Vm_Model->Model_Type == LoadedFile_Actor)
	{
		App->CL_Vm_Genesis3D->m_CurrentPose = 0; // Reset to frame 0;

		bool test = App->CL_Vm_Genesis3D->GetMotion(App->CL_Vm_Genesis3D->MotionName);
		if (test == 0)
		{
			App->Say("Can not Find Motion");
			return;
		}

		App->Cl19_Ogre->RenderListener->PlayActive = 1;

		//App->CL_Motions->PlayButtonActive = 1;
		//App->CL_Motions->TogglePlayBmp();
	}

	//------------------------------------------------------- Ogre3D Model
	//if (App->CL_Model_Data->ItsAnOgreModel == 1)
	//{
	//	App->Cl_Ogre->OgreListener->Animate_State = App->Cl_Ogre->OgreModel_Ent->getAnimationState(SelectedMotion);
	//	App->Cl_Ogre->OgreListener->Animate_State->setEnabled(true);
	//	App->Cl_Ogre->OgreListener->Animate_Ogre = 1;
	//	OgreMotionIsPlaying = 1;

	//	App->CL_Motions->AnimationExtract_Mesh(1); // Get Default Pose Mesh
	//	App->Cl_Ogre->OgreListener->Animate_Ogre = 1;
	//	App->CL_Motions->PlayButtonActive = 1;
	//	App->CL_Motions->TogglePlayBmp();
	//}
}

// *************************************************************************
// *					Stop_SelectedMotion Terry Bernie				   *
// *************************************************************************
void VM_Motions::Stop_SelectedMotion(void)
{
	if (App->CL_Vm_Model->Model_Loaded == 0) { return; }
	if (App->CL_Vm_Model->MotionCount == 0) { return; }

	//------------------------------------------------------- RF Model
	if (App->CL_Vm_Model->Model_Type == LoadedFile_Actor)
	{
		App->Cl19_Ogre->RenderListener->PlayActive = 0;
		/*App->CL_Motions->PlayButtonActive = 0;
		App->CL_Motions->TogglePlayBmp();*/
	}
	//------------------------------------------------------- Ogre3D Model
	/*if (App->CL_Model_Data->ItsAnOgreModel == 1)
	{
		App->Cl_Ogre->OgreListener->Animate_Ogre = 0;
		App->Cl_Ogre->OgreListener->Animate_State->setEnabled(false);
		OgreMotionIsPlaying = 0;

		App->CL_Motions->PlayButtonActive = 0;
		App->CL_Motions->TogglePlayBmp();
	}*/
}

// *************************************************************************
// *					Populate_Combo Terry Bernie						   *
// *************************************************************************
void VM_Motions::Populate_Combo(void)
{
	HWND temp = GetDlgItem(App->CL_Vm_TopBar->Motions_TB_hWnd, IDC_CBMOTIONS);

	char MotionName[255];
	int Count = 0;
	while (Count < App->CL_Vm_Model->MotionCount)
	{
		strcpy(MotionName, App->CL_Vm_Model->MotionNames_Data[Count].Name);

		SendMessage(temp, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)MotionName);

		Count++;
	}

	SendMessage(temp, CB_SETCURSEL, 0, 0);

	strcpy(App->CL_Vm_Genesis3D->MotionName, App->CL_Vm_Model->MotionNames_Data[0].Name);
}