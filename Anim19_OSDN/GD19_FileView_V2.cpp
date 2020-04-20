#include "stdafx.h"
#include "GD19_App.h"
#include "resource.h"
#include "GD19_FileView_V2.h"


GD19_FileView_V2::GD19_FileView_V2()
{
	Object_Names_Count = 0;
	Sound_Names_Count = 0;
	Message_Names_Count = 0;
	MoveEntities_Names_Count = 0;
	Collectables_Names_Count = 0;
	Teleporters_Names_Count = 0;
	Areas_Names_Count = 0;
	Players_Names_Count = 0;

	Block = 0;
	OpenObjects = 0;
	SelectObject = 0;
	Chosen_Object_Index = 0;
	RightMouseDown = 0;
}


GD19_FileView_V2::~GD19_FileView_V2()
{
}

// *************************************************************************
// *	  				ImGui_FileView2 Terry Bernie					   *
// *************************************************************************
void GD19_FileView_V2::ImGui_FileView2(void)
{

	//static int selected_Object = -1;
	//static int selected_Sounds = -1;
	//static int selected_Messages = -1;
	//static int selected_MoveEntities = -1;
	//static int selected_Collectables = -1;
	//static int selected_Teleporters = -1;
	//static int selected_Areas = -1;
	//static int selected_Players = -1;

	//ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
	//ImGui::SetNextWindowSize(ImVec2(200, 550), ImGuiCond_FirstUseEver);

	//if (!ImGui::Begin("File_View", &App->Cl_ImGui->Show_ImGui_FileView, ImGuiWindowFlags_NoSavedSettings))
	//{
	//	ImGui::End();
	//	return;
	//}
	//else
	//{
	//	//ImGui::PushFont(App->Cl_ImGui->fontDroid);
	//	ImGui::Text("Test Project");
	//	ImGui::Separator();
	//	ImGui::Spacing();

	//	if (ImGui::CollapsingHeader("Camera"))
	//	{

	//	}
	//	
	//	// --------------------------------------------- Player
	//	ImGui::Spacing();
	//	if (ImGui::CollapsingHeader("Player"))
	//	{
	//		ImGui::Indent();
	//		int Count = 0;
	//		while (Count < Players_Names_Count)
	//		{
	//			ImGui::Bullet();
	//			if (ImGui::Selectable(Players_Names_Vec[Count].c_str(), selected_Players == Count))
	//			{

	//				selected_Players = Count;
	//				strcpy(Selected_Players_Name, Players_Names_Vec[Count].c_str());

	//				selected_Object = -1;
	//				selected_Sounds = -1;
	//				selected_Messages = -1;
	//				selected_MoveEntities = -1;
	//				selected_Collectables = -1;
	//				selected_Teleporters = -1;
	//				selected_Areas = -1;

	//				Block = 1;
	//			}
	//			Count++;
	//		}

	//		if (Block == 1)
	//		{
	//			Update_Properties_Players(Selected_Players_Name);
	//		}

	//		ImGui::Unindent();

	//	}

	//	// --------------------------------------------- Areas
	//	ImGui::Spacing();
	//	if (ImGui::CollapsingHeader("Area"))
	//	{
	//		ImGui::Indent();
	//		int Count = 0;
	//		while (Count < Areas_Names_Count)
	//		{
	//			ImGui::Bullet();
	//			if (ImGui::Selectable(Areas_Names_Vec[Count].c_str(), selected_Areas == Count))
	//			{

	//				selected_Areas = Count;
	//				strcpy(Selected_Areas_Name, Areas_Names_Vec[Count].c_str());

	//				selected_Object = -1;
	//				selected_Sounds = -1;
	//				selected_Messages = -1;
	//				selected_MoveEntities = -1;
	//				selected_Collectables = -1;
	//				selected_Teleporters = -1;
	//				selected_Players = -1;

	//				Block = 1;
	//			}
	//			Count++;
	//		}

	//		if (Block == 1)
	//		{
	//			Update_Properties_Areas(Selected_Areas_Name);
	//		}

	//		ImGui::Unindent();
	//		
	//	}

	////	ImGui::Text("(You can also right-click me to open the same popup as above.)");
	////	ImGui::OpenPopupOnItemClick("item context menu", 1);

	//	// When used after an item that has an ID (here the Button), we can skip providing an ID to BeginPopupContextItem().
	//	// BeginPopupContextItem() will use the last item ID as the popup ID.
	//	// In addition here, we want to include your editable label inside the button label. We use the ### operator to override the ID (read FAQ about ID for details)
	//	//static char name[32] = "Label1";
	//	//char buf[64]; sprintf(buf, "Button: %s###Button", name); // ### operator override ID ignoring the preceding label
	//	//ImGui::Selectable(buf);
	//	//if (RightMouseDown == 1 && ImGui::BeginPopupContextItem(buf, 0))
	//	//{
	//	//	ImGui::Text("Edit name:");
	//	//	ImGui::InputText("##edit", name, IM_ARRAYSIZE(name));
	//	//	if (ImGui::Button("Close"))
	//	//	{
	//	//		ImGui::CloseCurrentPopup();
	//	//	}

	//	//	ImGui::EndPopup();
	//	//}
	//	
	//	// --------------------------------------------- Objects
	//	ImGui::Spacing();
	//	if (SelectObject == 1)
	//	{
	//		ImGui::SetNextItemOpen(OpenObjects);
	//	}

	//	if (ImGui::CollapsingHeader("Objects"))
	//	{

	//		ImGui::Indent();
	//		int Count = 0;
	//		while (Count < Object_Names_Count)
	//		{
	//			if (SelectObject == 1)
	//			{
	//				selected_Object = Chosen_Object_Index;
	//				strcpy(Selected_Object_Name, Object_Names_Vec[Chosen_Object_Index].c_str());
	//				Update_Properties_Objects(Selected_Object_Name);
	//				selected_Sounds = -1;
	//				selected_Messages = -1;
	//				selected_MoveEntities = -1;
	//				selected_Collectables = -1;
	//				selected_Teleporters = -1;
	//				selected_Areas = -1;
	//				selected_Players = -1;
	//			}

	//			ImGui::Bullet();
	//			
	//			if (ImGui::Selectable(Object_Names_Vec[Count].c_str(), selected_Object == Count))
	//			{
	//		
	//				if (SelectObject == 0)
	//				{
	//					selected_Object = Count;
	//				}

	//				char buff[255];
	//				_itoa(Count,buff,10);

	//				static char name[32] = "Label1";
	//				char buf[64]; sprintf(buf, "Button: %s###Button", name);

	//				if (ImGui::BeginPopupContextItem())
	//				{
	//				
	//					ImGui::Text("Edit name:");
	//					ImGui::InputText("##edit", buff, IM_ARRAYSIZE(buff));
	//					if (ImGui::Button("Close"))
	//					{
	//						ImGui::CloseCurrentPopup();
	//					}

	//					ImGui::EndPopup();
	//				}


	//				strcpy(Selected_Object_Name, Object_Names_Vec[Count].c_str());
	//				selected_Sounds = -1;
	//				selected_Messages = -1;
	//				selected_MoveEntities = -1;
	//				selected_Collectables = -1;
	//				selected_Teleporters = -1;
	//				selected_Areas = -1;
	//				selected_Players = -1;
	//				Block = 1;

	//			}
	//			Count++;
	//		}

	//		if (Block == 1)
	//		{
	//			App->Cl_FileView_V2->RightMouseDown = 0;
	//			Update_Properties_Objects(Selected_Object_Name);
	//		}

	//		// ------------------------------------------------- PoP Up
	//		
	//		SelectObject = 0;
	//		ImGui::Unindent();
	//	}

	//	// ------------------------------------------- Entities
	//	ImGui::Spacing();
	//	if (ImGui::CollapsingHeader("Entities"))
	//	{

	//		// --------------------------------------------- Sounds
	//		ImGui::Indent();
	//		if (ImGui::CollapsingHeader("Sounds"))
	//		{
	//			ImGui::Indent();
	//			int Count = 0;
	//			while (Count < Sound_Names_Count)
	//			{
	//				ImGui::Bullet();
	//				if (ImGui::Selectable(Sound_Names_Vec[Count].c_str(), selected_Sounds == Count))
	//				{

	//					selected_Sounds = Count;
	//					strcpy(Selected_Sound_Name, Sound_Names_Vec[Count].c_str());
	//					selected_Object = -1;
	//					selected_Messages = -1;
	//					selected_MoveEntities = -1;
	//					selected_Collectables = -1;
	//					selected_Teleporters = -1;
	//					selected_Areas = -1;
	//					selected_Players = -1;
	//					Block = 1;
	//				}
	//				Count++;
	//			}

	//			if (Block == 1)
	//			{
	//				Update_Properties_Sounds(Selected_Sound_Name);
	//			}

	//			ImGui::Unindent();

	//		}

	//		// --------------------------------------------- Messages
	//		if (ImGui::CollapsingHeader("Messages"))
	//		{
	//			ImGui::Indent();
	//			int Count = 0;
	//			while (Count < Message_Names_Count)
	//			{
	//				ImGui::Bullet();
	//				if (ImGui::Selectable(Message_Names_Vec[Count].c_str(), selected_Messages == Count))
	//				{
	//					//Null_Selected();
	//					selected_Messages = Count;
	//					strcpy(Selected_Message_Name, Message_Names_Vec[Count].c_str());
	//					selected_Object = -1;
	//					selected_Sounds = -1;
	//					selected_MoveEntities = -1;
	//					selected_Collectables = -1;
	//					selected_Teleporters = -1;
	//					selected_Areas = -1;
	//					selected_Players = -1;
	//					Block = 1;
	//				}
	//				Count++;
	//			}

	//			if (Block == 1)
	//			{
	//				Update_Properties_Messages(Selected_Message_Name);
	//			}

	//			ImGui::Unindent();
	//		}

	//		// --------------------------------------------- Move Enitities
	//		if (ImGui::CollapsingHeader("Move Enitities"))
	//		{
	//			ImGui::Indent();
	//			int Count = 0;
	//			while (Count < MoveEntities_Names_Count)
	//			{
	//				ImGui::Bullet();
	//				if (ImGui::Selectable(MoveEntities_Names_Vec[Count].c_str(), selected_MoveEntities == Count))
	//				{
	//					selected_MoveEntities = Count;
	//					strcpy(Selected_MoveEntities_Name, MoveEntities_Names_Vec[Count].c_str());
	//					selected_Object = -1;
	//					selected_Sounds = -1;
	//					selected_Messages = -1;
	//					selected_Collectables = -1;
	//					selected_Teleporters = -1;
	//					selected_Areas = -1;
	//					selected_Players = -1;
	//					Block = 1;
	//				}
	//				Count++;
	//			}

	//			if (Block == 1)
	//			{
	//				Update_Properties_MoveEntities(Selected_MoveEntities_Name);
	//			}

	//			ImGui::Unindent();
	//		}

	//		// --------------------------------------------- Collectables
	//		if (ImGui::CollapsingHeader("Collectables"))
	//		{
	//			ImGui::Indent();
	//			int Count = 0;
	//			while (Count < Collectables_Names_Count)
	//			{
	//				ImGui::Bullet();
	//				if (ImGui::Selectable(Collectables_Names_Vec[Count].c_str(), selected_Collectables == Count))
	//				{
	//					selected_Collectables = Count;
	//					strcpy(Selected_Collectables_Name, Collectables_Names_Vec[Count].c_str());

	//					selected_Object = -1;
	//					selected_Sounds = -1;
	//					selected_Messages = -1;
	//					selected_MoveEntities = -1;
	//					selected_Teleporters = -1;
	//					selected_Areas = -1;
	//					selected_Players = -1;

	//					Block = 1;
	//				}
	//				Count++;
	//			}

	//			if (Block == 1)
	//			{
	//				Update_Properties_Collectables(Selected_Collectables_Name);
	//			}

	//			ImGui::Unindent();
	//			
	//		}

	//		// --------------------------------------------- Teleporters
	//		if (ImGui::CollapsingHeader("Teleporters"))
	//		{
	//			ImGui::Indent();
	//			int Count = 0;
	//			while (Count < Teleporters_Names_Count)
	//			{
	//				ImGui::Bullet();
	//				if (ImGui::Selectable(Teleporters_Names_Vec[Count].c_str(), selected_Teleporters == Count))
	//				{
	//					selected_Teleporters = Count;
	//					strcpy(Selected_Teleporters_Name, Teleporters_Names_Vec[Count].c_str());

	//					selected_Object = -1;
	//					selected_Sounds = -1;
	//					selected_Messages = -1;
	//					selected_MoveEntities = -1;
	//					selected_Collectables = -1;
	//					selected_Areas = -1;
	//					selected_Players = -1;

	//					Block = 1;
	//				}
	//				Count++;
	//			}

	//			if (Block == 1)
	//			{
	//				Update_Properties_Teleporters(Selected_Teleporters_Name);
	//			}

	//			ImGui::Unindent();
	//			
	//		}

	//		ImGui::Unindent();
	//	}

	//	
	//	ImGui::PopFont();
	//	//ImGui::PushFont(App->Cl_ImGui->font1);
	//	ImGui::End();
	//}

}

// *************************************************************************
// *					Add_ObjectName Terry Bernie						   *
// *************************************************************************
bool GD19_FileView_V2::Add_ObjectName(char* File)
{
	Object_Names_Vec.push_back(File);
	Object_Names_Count = Object_Names_Vec.size();
	return 1;
}

// *************************************************************************
// *					Add_SoundName Terry Bernie						   *
// *************************************************************************
bool GD19_FileView_V2::Add_SoundName(char* File)
{
	Sound_Names_Vec.push_back(File);
	Sound_Names_Count = Sound_Names_Vec.size();
	return 1;
}

// *************************************************************************
// *					Add_MessageName Terry Bernie					   *
// *************************************************************************
bool GD19_FileView_V2::Add_MessageName(char* File)
{
	Message_Names_Vec.push_back(File);
	Message_Names_Count = Message_Names_Vec.size();
	return 1;
}

// *************************************************************************
// *					Add_MoveEntities Terry Bernie					   *
// *************************************************************************
bool GD19_FileView_V2::Add_MoveEntities(char* File)
{
	MoveEntities_Names_Vec.push_back(File);
	MoveEntities_Names_Count = MoveEntities_Names_Vec.size();
	return 1;
}

// *************************************************************************
// *					Add_Collectable_Name Terry Bernie				   *
// *************************************************************************
bool GD19_FileView_V2::Add_Collectable_Name(char* File)
{
	Collectables_Names_Vec.push_back(File);
	Collectables_Names_Count = Collectables_Names_Vec.size();
	return 1;
}

// *************************************************************************
// *					Add_Teleporter_Name Terry Bernie				   *
// *************************************************************************
bool GD19_FileView_V2::Add_Teleporter_Name(char* File)
{
	Teleporters_Names_Vec.push_back(File);
	Teleporters_Names_Count = Teleporters_Names_Vec.size();
	return 1;
}


// *************************************************************************
// *					Add_Area_Name Terry Bernie						   *
// *************************************************************************
bool GD19_FileView_V2::Add_Area_Name(char* File)
{
	Areas_Names_Vec.push_back(File);
	Areas_Names_Count = Areas_Names_Vec.size();
	return 1;
}

// *************************************************************************
// *					Add_Player_Name Terry Bernie					   *
// *************************************************************************
bool GD19_FileView_V2::Add_Player_Name(char* File)
{
	Players_Names_Vec.push_back(File);
	Players_Names_Count = Players_Names_Vec.size();
	return 1;
}

// *************************************************************************
// *	  			GetJustIndex_ByName Terry Bernie					   *
// *************************************************************************
int GD19_FileView_V2::GetJustIndex_ByName(char* Name)
{
	int Count = 0;
	int Total = App->Cl_Scene_Data->ObjectCount;

	while (Count < Total)
	{
		if (App->Cl_Scene_Data->Cl_Object[Count]->Deleted == 0)
		{
			int Result = 1;
			Result = strcmp(App->Cl_Scene_Data->Cl_Object[Count]->Name, Name);
			if (Result == 0)
			{
				return Count;
			}
		}

		Count++;
	}

	return -1;
}

// *************************************************************************
// *	  			Update_Properties_Objects Terry Bernie				   *
// *************************************************************************
void GD19_FileView_V2::Update_Properties_Objects(char* Name)
{
	int ItemIndex = GetJustIndex_ByName(Name);
	if (ItemIndex > -1)
	{
		App->Cl_Object_Props->Is_Player = 0; // Mark as Object selected

		App->Cl_Object_Props->Edit_Type = Enums::Edit_Mesh_Object;

		App->Cl_Properties->Edit_Category = Enums::Edit_Mesh_Object;
		App->Cl_Properties->Current_Selected_Object = ItemIndex;
		App->Cl_Properties->Update_Transform_Dlg();

		App->Cl_Properties->Update_ListView_Objects();
		App->Cl_Visuals->MarkerBB_Addjust(ItemIndex);
		Block = 0;
	}
}

// *************************************************************************
// *	  			Update_Properties_Sounds Terry Bernie				   *
// *************************************************************************
void GD19_FileView_V2::Update_Properties_Sounds(char* Name)
{
	int ItemIndex = GetJustIndex_ByName(Name);
	if (ItemIndex > -1)
	{
		//HideRightPanes();
		ShowWindow(App->GD_Properties_Hwnd, 1);

		App->Cl_Properties->Enable_Delete_Button(1);

		App->Cl_Object_Props->Is_Player = 0; // Mark as Object selected

		App->Cl_Properties->Is_Player = 0;
		App->Cl_Properties->Edit_Category = Enums::Edit_Sounds;
		App->Cl_Properties->Current_Selected_Object = ItemIndex;
		App->Cl_Properties->Update_Transform_Dlg();

		if (App->Cl_Properties->Edit_Physics == 0)
		{
			App->Cl_Properties->Update_ListView_Sounds();
		}
		else
		{
			App->Cl_Properties->Update_ListView_Physics();
		}

		App->Cl_Visuals->MarkerBB_Addjust(ItemIndex);

		Block = 0;
	}
}

// *************************************************************************
// *	  			Update_Properties_Messages Terry Bernie				   *
// *************************************************************************
void GD19_FileView_V2::Update_Properties_Messages(char* Name)
{
	int ItemIndex = GetJustIndex_ByName(Name);
	if (ItemIndex > -1)
	{
		//HideRightPanes();
		ShowWindow(App->GD_Properties_Hwnd, 1);

		App->Cl_Properties->Enable_Delete_Button(1);

		App->Cl_Object_Props->Edit_Type = Enums::Edit_Message;

		App->Cl_Properties->Is_Player = 0; // Mark as Object selected
		App->Cl_Properties->Edit_Category = Enums::Edit_Message;
		App->Cl_Properties->Current_Selected_Object = ItemIndex;
		App->Cl_Properties->Update_Transform_Dlg();

		if (App->Cl_Properties->Edit_Physics == 0)
		{
			App->Cl_Properties->Update_ListView_Messages();
		}
		else
		{
			App->Cl_Properties->Update_ListView_Physics();
		}

		App->Cl_Visuals->MarkerBB_Addjust(ItemIndex);

		Block = 0;
	}
}

// *************************************************************************
// *	  		Update_Properties_MoveEntities Terry Bernie				   *
// *************************************************************************
void GD19_FileView_V2::Update_Properties_MoveEntities(char* Name)
{
	int ItemIndex = GetJustIndex_ByName(Name);
	if (ItemIndex > -1)
	{
		//HideRightPanes();
		ShowWindow(App->GD_Properties_Hwnd, 1);

		App->Cl_Properties->Enable_Delete_Button(1);

		App->Cl_Object_Props->Edit_Type = Enums::Edit_Move_Entity;
		App->Cl_Object_Props->Is_Player = 0; // Mark as Object selected

		App->Cl_Properties->Enable_Test_Button(1);
		App->Cl_Properties->Is_Player = 0; // Mark as Object selected

		App->Cl_Properties->Edit_Category = Enums::Edit_Move_Entity;
		App->Cl_Properties->Current_Selected_Object = ItemIndex;
		App->Cl_Properties->Update_Transform_Dlg();


		if (App->Cl_Properties->Edit_Physics == 0)
		{
			App->Cl_Properties->Update_ListView_Move_Entities();
		}
		else
		{
			App->Cl_Properties->Update_ListView_Physics();
		}

		App->Cl_Visuals->MarkerBB_Addjust(ItemIndex);

		Block = 0;
	}
}

// *************************************************************************
// *	  		Update_Properties_Collectables Terry Bernie				   *
// *************************************************************************
void GD19_FileView_V2::Update_Properties_Collectables(char* Name)
{
	int ItemIndex = GetJustIndex_ByName(Name);
	if (ItemIndex > -1)
	{
		//HideRightPanes();
		ShowWindow(App->GD_Properties_Hwnd, 1);

		App->Cl_Properties->Enable_Delete_Button(1);

		App->Cl_Object_Props->Is_Player = 0; // Mark as Object selected

		App->Cl_Object_Props->Selected_Object_Index = ItemIndex;
		
		App->Cl_Properties->Edit_Category = Enums::Edit_Collectable;
		App->Cl_Properties->Current_Selected_Object = ItemIndex;
		App->Cl_Properties->Update_Transform_Dlg();

		if (App->Cl_Properties->Edit_Physics == 0)
		{
			App->Cl_Properties->Update_ListView_Collectables();
		}
		else
		{
			App->Cl_Properties->Update_ListView_Physics();
		}

		App->Cl_Visuals->MarkerBB_Addjust(ItemIndex);

		/*if (App->Cl_Object_Props->Edit_Type == Enums::Edit_Player)
		{
			App->Cl_Object_Props->Edit_Type = Enums::Edit_Mesh_Object;
			App->Cl_Object_Props->Update_Properties_Mesh();
			return;
		}

		if (App->Cl_Object_Props->Edit_Type == Enums::Edit_Mesh_Object)
		{
			App->Cl_Object_Props->Update_Properties_Mesh();
			return;
		}

		if (App->Cl_Object_Props->Edit_Type == Enums::Edit_Physics_Object)
		{
			App->Cl_Object_Props->Update_Properties_Physics();
			return;
		}*/

		Block = 0;
	}
}

// *************************************************************************
// *	  		Update_Properties_Teleporters Terry Bernie				   *
// *************************************************************************
void GD19_FileView_V2::Update_Properties_Teleporters(char* Name)
{
	int ItemIndex = GetJustIndex_ByName(Name);
	if (ItemIndex > -1)
	{
		//HideRightPanes();
		ShowWindow(App->GD_Properties_Hwnd, 1);

		App->Cl_Properties->Enable_Delete_Button(1);

		App->Cl_Object_Props->Is_Player = 0; // Mark as Object selected

		App->Cl_Object_Props->Selected_Object_Index = ItemIndex;
	
		App->Cl_Properties->Edit_Category = Enums::Edit_Teleport;
		App->Cl_Properties->Current_Selected_Object = ItemIndex;
		App->Cl_Properties->Update_Transform_Dlg();

		if (App->Cl_Properties->Edit_Physics == 0)
		{
			App->Cl_Properties->Update_ListView_Teleport();
		}
		else
		{
			App->Cl_Properties->Update_ListView_Physics();
		}

		App->Cl_Visuals->MarkerBB_Addjust(ItemIndex);

		Block = 0;
	}
}

// *************************************************************************
// *	  			Update_Properties_Areas Terry Bernie				   *
// *************************************************************************
void GD19_FileView_V2::Update_Properties_Areas(char* Name)
{
	int ItemIndex = GetJustIndex_ByName(Name);
	if (ItemIndex > -1)
	{
		//HideRightPanes();
		ShowWindow(App->GD_Properties_Hwnd, 1);

		App->Cl_Object_Props->Is_Player = 0; // Mark as Object selected

		App->Cl_Object_Props->Edit_Type = Enums::Edit_Mesh_Object;

		App->Cl_Properties->Edit_Category = Enums::Edit_Mesh_Object;
		App->Cl_Properties->Current_Selected_Object = ItemIndex;
		App->Cl_Properties->Update_Transform_Dlg();
	

		if (App->Cl_Properties->Edit_Physics == 0)
		{
			App->Cl_Properties->Update_ListView_Objects();
		}
		else
		{
			App->Cl_Properties->Update_ListView_Physics();
		}

		App->Cl_Visuals->MarkerBB_Addjust(ItemIndex);

		Block = 0;
	}
}

// *************************************************************************
// *	  			Update_Properties_Players Terry Bernie				   *
// *************************************************************************
void GD19_FileView_V2::Update_Properties_Players(char* Name)
{
	//int ItemIndex = GetJustIndex_ByName(Name);
	//if (ItemIndex > -1)
	{
		App->Cl_Object_Props->Is_Player = 1; // Mark as Player selected

		App->Cl_Properties->Enable_Delete_Button(0);

		App->Cl_Properties->Edit_Category = Enums::Edit_Player;
	//	App->Cl_Properties->Current_Selected_Object = ItemIndex;
		
		

		if (App->Cl_Properties->Edit_Physics == 0)
		{
			App->Cl_Properties->Update_ListView_Player();
		}
		else
		{
			App->Cl_Properties->Update_ListView_Player_Physics();
		}

		Block = 0;
	}
}

// *************************************************************************
// *					Select_ObjectFV Terry Bernie					   *
// *************************************************************************
bool GD19_FileView_V2::Select_ObjectFV(int Index)
{
	char Selected_Object_Name[1024];
	strcpy(Selected_Object_Name, App->Cl_Scene_Data->Cl_Object[Index]->Name);

	//App->Say(Selected_Object_Name); // See why it runs on load

	int Count = 0;
	int Total = Object_Names_Count;
	while (Count < Total)
	{
		int Result = 1;
		Result = strcmp(Selected_Object_Name, Object_Names_Vec[Count].c_str());
		if (Result == 0)
		{
			Chosen_Object_Index = Count;
			break;
		}
		Count++;
	}

	if (App->Cl_FileView_V2->OpenObjects == 1)
	{
		App->Cl_FileView_V2->SelectObject = 1;
	}
	else
	{
		App->Cl_FileView_V2->OpenObjects = 1;
		App->Cl_FileView_V2->SelectObject = 1;
	}

	return 1;
}

// *************************************************************************
// *					PopUp_AddObject Terry Bernie					   *
// *************************************************************************
void GD19_FileView_V2::PopUp_AddObject()
{

	App->Cl_Dialogs->YesNo("Add Object", "Do you want to add a new Object now");
	bool Doit = App->Cl_Dialogs->Canceled;
	if (Doit == 0)
	{
		App->Cl_Mesh_Viewer->Mesh_Viewer_Mode = Enums::Mesh_Viewer_Objects; // Objects
		App->Cl_Mesh_Viewer->StartMeshViewer();
		App->Cl_Object_Props->Is_Player = 0; // Mark as Object selected	
	}
}


// *************************************************************************
// *						PopUp_Rename Terry Bernie					   *
// *************************************************************************
void GD19_FileView_V2::PopUp_Rename(int Selected_Object)
{
	int Index = App->Cl_Properties->Current_Selected_Object; // Get Selected Object Index 

	strcpy(App->Cl_Dialogs->btext, "Change Object Name");
	strcpy(App->Cl_Dialogs->Chr_Text, App->Cl_Scene_Data->Cl_Object[Index]->Name);

	App->Cl_Dialogs->Dialog_Text(Enums::Check_Names_Objects);

	if (App->Cl_Dialogs->Canceled == 1)
	{
		return;
	}

	strcpy(App->Cl_Scene_Data->Cl_Object[Index]->Name, App->Cl_Dialogs->Chr_Text);

	App->Cl_FileView->ChangeItem_Name(NULL, App->Cl_Dialogs->Chr_Text);
	App->Cl_Properties->Update_ListView_Objects();

	Object_Names_Vec[Selected_Object] = App->Cl_Scene_Data->Cl_Object[Index]->Name;
}
