#include "stdafx.h"
#include "GD19_App.h"
#include "EQ15_WE_Listener.h"


EQ15_WE_Listener::EQ15_WE_Listener()
{
	mMoveScale = 0;
	mMoveSensitivity = 50;
	Wheel = 0;

	Show_Model_Data = 0;

	Pl_DeltaMouse = 0;
	Pl_MouseX = 0;
	Pl_MouseY = 0;
	Pl_Cent500X = 500;
	Pl_Cent500Y = 500;

	mMoveSensitivityMouse = 50;

	Pl_LeftMouseDown = 0;
	Pl_RightMouseDown = 0;

	WE_Cam = nullptr;

	View_Height = 0;
	View_Width = 0;
}


EQ15_WE_Listener::~EQ15_WE_Listener()
{
}

// *************************************************************************
// *				frameStarted   Terry Bernie							   *
// *************************************************************************
bool EQ15_WE_Listener::frameStarted(const FrameEvent& evt)
{

	if (App->Cl19_Ogre->OgreListener->Equity_Running == 1)
	{
		if (App->SBC_Equity->Use_Imgui == 1)
		{
			App->SBC_Equity->Get_View_Height_Width();
			App->SBC_Equity->EB_imgui.NewFrame(evt.timeSinceLastFrame, (float)View_Width, (float)View_Height);

			if (App->SBC_Equity->Show_Gui_Debug == 1)
			{
				Render_ImGui();
			}

		}

		return true;
	}

	return true;
}

// *************************************************************************
// *			WE_RenderingQueued   Terry Flanigan						   *
// *************************************************************************
bool EQ15_WE_Listener::WE_RenderingQueued(const FrameEvent& evt)
{
	ModelMode(evt.timeSinceLastFrame);
	return 1;
}

// *************************************************************************
// *							ModelMode   							   *
// *************************************************************************
void EQ15_WE_Listener::ModelMode(float DeltaTime)
{
	mRotX = 0;
	mRotY = 0;
	mTranslateVector = Ogre::Vector3::ZERO;

	mMoveScale = mMoveSensitivity  * DeltaTime;

	if (GetAsyncKeyState(69) < 0) // Q key Down in Fly Mode
	{
		Ogre::Real Rate;
		Rate = (mMoveSensitivity / 1000) * 4;    //0.1;//FlyRate;

		Ogre::Vector3 OldPos;
		OldPos = WE_Cam->getPosition();

		OldPos.y += Rate;
		WE_Cam->setPosition(OldPos);
	}
	//------------------------------------------------
	if (GetAsyncKeyState(81) < 0) // E key Up in Fly Mode
	{
		Ogre::Real Rate;
		Rate = (mMoveSensitivity / 1000) * 4;// 0.1;//FlyRate;

		Ogre::Vector3 OldPos;
		OldPos = WE_Cam->getPosition();

		OldPos.y -= Rate;
		WE_Cam->setPosition(OldPos);
	}
	//------------------------------------------------
	if (Wheel < 0) // Mouse Wheel Forward
	{
		mTranslateVector.z = -mMoveScale * 30;
	}
	if (GetAsyncKeyState(87) < 0) // W Key
	{
		mTranslateVector.z = -mMoveScale;
	}
	//------------------------------------------------
	// back
	if (Wheel > 0) // Mouse Wheel Back
	{
		mTranslateVector.z = mMoveScale * 30;
	}
	if (GetAsyncKeyState(83) < 0) // S Key	
	{
		mTranslateVector.z = mMoveScale;
	}
	//------------------------------------------------
	// Right
	if (GetAsyncKeyState(65) < 0)
	{
		mTranslateVector.x = mMoveScale;
	}
	// Left
	if (GetAsyncKeyState(68) < 0)
	{
		mTranslateVector.x = -mMoveScale;
	}

	if (GetAsyncKeyState(VK_ESCAPE) < 0) // Back to full Screen;
	{
		if (App->FullScreen == 1)
		{
			App->FullScreen = 0;
			App->Cl19_Ogre->ExitFullScreen();
		}
	}

	// Left Mouse
	if (Pl_LeftMouseDown == 1 && Pl_RightMouseDown == 0)
	{
		Capture_LeftMouse_Model();
	}

	// Right Mouse
	if (Pl_LeftMouseDown == 0 && Pl_RightMouseDown == 1)
	{
		Capture_RightMouse_Model();
	}

	MoveCamera();
}

// *************************************************************************
// *				moveCamera   Terry Bernie							   *
// *************************************************************************
void EQ15_WE_Listener::MoveCamera(void)
{
	WE_Cam->yaw(mRotX);
	WE_Cam->pitch(mRotY);
	WE_Cam->moveRelative(mTranslateVector); // Position Relative
	Wheel = 0;
}

// *************************************************************************
// *					Capture_LeftMouse_Model							   *
// *************************************************************************
bool EQ15_WE_Listener::Capture_LeftMouse_Model(void)
{
	GetCursorPos(&Pl_pt);

	Pl_MouseX = (int(Pl_pt.x));
	Pl_MouseY = (int(Pl_pt.y));

	//// Left Right
	if (Pl_MouseX < Pl_Cent500X)
	{
		long test = Pl_Cent500X - Pl_MouseX; // Positive

		if (test > 2)
		{
			Pl_DeltaMouse = float(Pl_Cent500X - Pl_MouseX);
			App->SBC_Equity->GridNode->yaw(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_LOCAL);
			App->SBC_Equity->HairNode->yaw(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_LOCAL);
			App->SBC_Equity->RenderListener->RZ = App->SBC_Equity->RenderListener->RZ - (Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2);
			SetCursorPos(500, 500);
		}
	}
	else if (Pl_MouseX > Pl_Cent500X)
	{
		long test = Pl_MouseX - Pl_Cent500X; // Positive

		if (test > 2)
		{
			Pl_DeltaMouse = float(Pl_MouseX - Pl_Cent500X);
			App->SBC_Equity->GridNode->yaw(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_LOCAL);
			App->SBC_Equity->HairNode->yaw(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_LOCAL);
			App->SBC_Equity->RenderListener->RZ = App->SBC_Equity->RenderListener->RZ + (Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2);
			SetCursorPos(500, 500);
		}
	}

	// Up Down
	if (Pl_MouseY < Pl_Cent500Y)
	{
		long test = Pl_Cent500Y - Pl_MouseY; // Positive

		if (test > 2)
		{
			Pl_DeltaMouse = float(Pl_Cent500Y - Pl_MouseY);
			App->SBC_Equity->GridNode->pitch(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_PARENT);
			App->SBC_Equity->HairNode->pitch(Ogre::Degree(-Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_PARENT);
			App->SBC_Equity->RenderListener->RX = App->SBC_Equity->RenderListener->RX - (Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2);
			SetCursorPos(500, 500);
		}
	}
	else if (Pl_MouseY > Pl_Cent500Y)
	{
		long test = Pl_MouseY - Pl_Cent500Y; // Positive

		if (test > 2)
		{
			Pl_DeltaMouse = float(Pl_MouseY - Pl_Cent500Y);
			App->SBC_Equity->GridNode->pitch(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_PARENT);
			App->SBC_Equity->HairNode->pitch(Ogre::Degree(Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2), Ogre::Node::TS_PARENT);
			App->SBC_Equity->RenderListener->RX = App->SBC_Equity->RenderListener->RX + (Pl_DeltaMouse * (mMoveSensitivityMouse / 1000) * 2);
			SetCursorPos(500, 500);
		}
	}

	return 1;
}

// *************************************************************************
// *					Capture_RightMouse_Model Terry					   *
// *************************************************************************
bool EQ15_WE_Listener::Capture_RightMouse_Model(void)
{
	GetCursorPos(&Pl_pt);

	Pl_MouseX = (int(Pl_pt.x));
	Pl_MouseY = (int(Pl_pt.y));

	//// Left Right
	if (Pl_MouseX < Pl_Cent500X)
	{
		long test = Pl_Cent500X - Pl_MouseX; // Positive

		if (test > 2)
		{
			Pl_DeltaMouse = float(Pl_Cent500X - Pl_MouseX);
			mTranslateVector.x = Pl_DeltaMouse * (mMoveSensitivityMouse / 1000);
			SetCursorPos(500, 500);
		}
	}
	else if (Pl_MouseX > Pl_Cent500X)
	{
		long test = Pl_MouseX - Pl_Cent500X; // Positive

		if (test > 2)
		{
			Pl_DeltaMouse = float(Pl_MouseX - Pl_Cent500X);
			mTranslateVector.x = -Pl_DeltaMouse * (mMoveSensitivityMouse / 1000);
			SetCursorPos(500, 500);
		}
	}

	//// Up Down
	if (Pl_MouseY < Pl_Cent500Y)
	{
		long test = Pl_Cent500Y - Pl_MouseY; // Positive

		if (test > 2)
		{
			Pl_DeltaMouse = float(Pl_Cent500Y - Pl_MouseY);

			Ogre::Real Rate;
			Rate = Pl_DeltaMouse * (mMoveSensitivityMouse / 1000);

			Ogre::Vector3 OldPos;
			OldPos = WE_Cam->getPosition();

			OldPos.y -= Rate;
			WE_Cam->setPosition(OldPos);
			SetCursorPos(500, 500);
		}

	}
	else if (Pl_MouseY > Pl_Cent500Y)
	{
		long test = Pl_MouseY - Pl_Cent500Y; // Positive

		if (test > 2)
		{
			Pl_DeltaMouse = float(Pl_MouseY - Pl_Cent500Y);

			Ogre::Real Rate;
			Rate = Pl_DeltaMouse * (mMoveSensitivityMouse / 1000);

			Ogre::Vector3 OldPos;
			OldPos = WE_Cam->getPosition();

			OldPos.y += Rate;
			WE_Cam->setPosition(OldPos);
			SetCursorPos(500, 500);
		}

	}

	return 1;
}

// *************************************************************************
// *					Render_ImGui  Terry Bernie						   *
// *************************************************************************
void EQ15_WE_Listener::Render_ImGui(void)
{
	if (Show_Model_Data == 1)
	{
		ImGui_Model_Data();
	}

}
// *************************************************************************
// *					ImGui_Model_Data  Terry Bernie					   *
// *************************************************************************
void EQ15_WE_Listener::ImGui_Model_Data(void)
{
	ImGui::SetNextWindowSize(ImVec2(530, 250), ImGuiCond_FirstUseEver);

	ImGui::OpenPopup("Model Data");

	if (!ImGui::BeginPopupModal("Model Data", &Show_Model_Data, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::EndPopup();
	}
	else
	{

		ImGui::Text("Model Name: = %s", App->CL_Vm_Model->JustName);
		ImGui::Text("Model File Name: = %s", App->CL_Vm_Model->FileName);
		ImGui::Text("Model Path: = %s", App->CL_Vm_Model->Model_FolderPath);
		ImGui::Text("Texture Path: = %s", App->CL_Vm_Model->Texture_FolderPath);

		ImGui::Spacing();

		ImGui::Text("Vertices: = %i", App->CL_Vm_Model->VerticeCount);
		ImGui::Text("Faces: = %i", App->CL_Vm_Model->FaceCount);
		ImGui::Text("Normals: = %i", App->CL_Vm_Model->NormalsCount);
		ImGui::Text("UVs: = %i", App->CL_Vm_Model->UVCount);

		ImGui::Spacing();

		ImGui::Text("Textures: = %i", App->CL_Vm_Model->TextureCount);

		// ----------------------------- Textures
		char Header[255];
		int TextureCount = App->CL_Vm_Model->S_Texture[0]->UsedTextureCount;

		sprintf(Header, "%s %i", "Textures", TextureCount);

		if (ImGui::CollapsingHeader(Header))
		{
			int Count = 0;
			while (Count < App->CL_Vm_Model->S_Texture[0]->UsedTextureCount)
			{
				//ImGui::Text("%s", App->CL_Vm_Model->S_TextureInfo[Count]->Text_FileName);
				ImGui::Text("%s", App->CL_Vm_Model->S_MeshGroup[Count]->Text_FileName);
				Count++;
			}
		}



		ImGui::Spacing();

		// ----------------------------- Motions
		int MotionCount = App->CL_Vm_Model->MotionCount;
		sprintf(Header, "%s %i", "Motions", MotionCount);

		if (ImGui::CollapsingHeader(Header))
		{
			int Count = 0;
			while (Count < MotionCount)
			{
				ImGui::Text("%s", App->CL_Vm_Model->MotionNames_Data[Count].Name);
				Count++;
			}
		}

		ImGui::Spacing();

		// ----------------------------- Bones
		int BoneCount = App->CL_Vm_Model->BoneCount;
		sprintf(Header, "%s %i", "Bones", BoneCount);

		if (ImGui::CollapsingHeader(Header))
		{
			int Count = 0;
			while (Count < BoneCount)
			{
				ImGui::Text("%s", App->CL_Vm_Model->S_Bones[Count]->BoneName);
				Count++;
			}
		}

		// ----------------------------- Groups
		int GroupCount = App->CL_Vm_Model->GroupCount;
		sprintf(Header, "%s %i", "Groups", GroupCount);

		if (ImGui::CollapsingHeader(Header))
		{
			/*int Count = 0;
			while (Count < BoneCount)
			{
			ImGui::Text("%s", App->CL_Vm_Model->S_Bones[Count]->BoneName);
			Count++;
			}*/
		}


		if (ImGui::Button("Close"))
		{
			Show_Model_Data = 0;
		}

		ImGui::EndPopup();
	}
}
