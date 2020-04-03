#include "stdafx.h"
#include "resource.h"
#include "GD19_App.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "GD_ImGui.h"

struct ExampleAppLog
{
	ImGuiTextBuffer     Buf;
	ImGuiTextFilter     Filter;
	ImVector<int>       LineOffsets;        // Index to lines offset. We maintain this with AddLog() calls, allowing us to have a random access on lines
	bool                AutoScroll;     // Keep scrolling if already at the bottom

	ExampleAppLog()
	{
		AutoScroll = true;
		Clear();
	}

	void    Clear()
	{
		Buf.clear();
		LineOffsets.clear();
		LineOffsets.push_back(0);
	}

	void    AddLog(const char* fmt, ...) IM_FMTARGS(2)
	{
		int old_size = Buf.size();
		va_list args;
		va_start(args, fmt);
		Buf.appendfv(fmt, args);
		va_end(args);
		for (int new_size = Buf.size(); old_size < new_size; old_size++)
			if (Buf[old_size] == '\n')
				LineOffsets.push_back(old_size + 1);
	}

	void    Draw(const char* title, bool* p_open = NULL)
	{
		if (!ImGui::Begin(title, p_open))
		{
			ImGui::End();
			return;
		}

		// Options menu
		if (ImGui::BeginPopup("Options"))
		{
			ImGui::Checkbox("Auto-scroll", &AutoScroll);
			ImGui::EndPopup();
		}

		// Main window
		bool clear = ImGui::Button("Clear");
		ImGui::SameLine();
		bool copy = ImGui::Button("Copy");
		ImGui::SameLine();
		Filter.Draw("Filter", -100.0f);

		ImGui::Separator();
		ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

		if (clear)
			Clear();
		if (copy)
			ImGui::LogToClipboard();

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
		const char* buf = Buf.begin();
		const char* buf_end = Buf.end();
		if (Filter.IsActive())
		{
			for (int line_no = 0; line_no < LineOffsets.Size; line_no++)
			{
				const char* line_start = buf + LineOffsets[line_no];
				const char* line_end = (line_no + 1 < LineOffsets.Size) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
				if (Filter.PassFilter(line_start, line_end))
					ImGui::TextUnformatted(line_start, line_end);
			}
		}
		else
		{
			ImGuiListClipper clipper;
			clipper.Begin(LineOffsets.Size);
			while (clipper.Step())
			{
				for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; line_no++)
				{
					const char* line_start = buf + LineOffsets[line_no];
					const char* line_end = (line_no + 1 < LineOffsets.Size) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
					ImGui::TextUnformatted(line_start, line_end);
				}
			}
			clipper.End();
		}
		ImGui::PopStyleVar();

		if (AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
			ImGui::SetScrollHereY(1.0f);

		ImGui::EndChild();
		ImGui::End();
	}
};

//static ExampleAppLog My_log;

GD_ImGui::GD_ImGui()
{
	ImGui::CreateContext();
	ImGui_Set_Colours();
	ImGuiStyle& style = ImGui::GetStyle();
	style.FrameBorderSize = 1.0;
	Load_Font();

	StartPos = 0;
	Show_OgreData = 1;
	Show_ImGui_Test = 0;
	Show_Object_Data = 0;
	Show_ImGui_Counters = 0;
	Show_ImGui_Dimensions = 0;
	Show_ImGui_Properties_Editor = 0;
	Show_ImGui_Debug_Player = 0;
	Show_ImGui_FileView = 0;
	Show_ImGui_Preferences = 0;
	Show_ImGui_Log = 0;
	Show_PhysicsConsole = 0;
	Show_Propertities = 0;
	Show_Camera_Object = 0;

	Block = 0;
	Add_Log = 0;

	BlockX = 0;
	BlockY = 0;
	BlockX = 0;
	Lock_Z = 0;
	Lock_Y = 0;
	Lock_Z = 0;

	SetAxis.setX(1);
	SetAxis.setY(1);
	SetAxis.setZ(1);

}


GD_ImGui::~GD_ImGui()
{
}

// *************************************************************************
// *						Load_Font  Terry Bernie						   *
// *************************************************************************
void GD_ImGui::Load_Font(void)
{
	ImGuiIO& io = ImGui::GetIO();
	font1 = io.Fonts->AddFontFromFileTTF("Roboto-Medium.ttf", 20);
	font2 = io.Fonts->AddFontFromFileTTF("Roboto-Medium.ttf", 48);
	font0 = io.Fonts->AddFontFromFileTTF("Roboto-Medium.ttf", 18);
	fontDroid = io.Fonts->AddFontFromFileTTF("DroidSans.ttf", 12);
}

// *************************************************************************
// *					Render_Main_Panels  Terry Bernie				   *
// *************************************************************************
void GD_ImGui::Render_Main_Panels(void)
{

	if (Show_OgreData == 1)
	{
		ImGui_FPS();
	}

	if (Show_ImGui_FileView == 1)
	{
		App->Cl_FileView_V2->ImGui_FileView2();
	}

	if (Show_PhysicsConsole == 1)
	{
		//ImGui_PhysicsConsole();
	}

	if (Show_Propertities == 1)
	{
		ImGui_Properties();
	}

	if (App->Cl_ImGui->Show_ImGui_Dimensions == 1)
	{
		ImGui_Dimensions();
	}

	if (Show_Camera_Object == 1)
	{
		Camera_Object();
	}

	if (App->Cl_ImGui->Show_ImGui_Counters == 1)
	{
		ImGui_Scene_Data();
	}

	if (Show_ImGui_Test == 1)
	{
		ImGui::ShowDemoWindow();
	}
	
}

// *************************************************************************
// *						Ogre_Data2  Terry Bernie					   *
// *************************************************************************
void GD_ImGui::Render_Panels(void)
{

	if (Show_OgreData == 1)
	{
		ImGui_FPS();
	}

	if (Show_ImGui_Test == 1)
	{
		ImGui::ShowDemoWindow();
	}

	if (Show_Object_Data == 1)
	{
		Object_Properties();
	}

	if (App->Cl_ImGui->Show_ImGui_Counters == 1)
	{
		ImGui_Scene_Data();
	}

	if (App->Cl_ImGui->Show_ImGui_Dimensions == 1)
	{
		ImGui_Dimensions();
	}

	if (App->Cl_ImGui->Show_ImGui_Properties_Editor == 1)
	{
		ShowExampleAppPropertyEditor(0);
	}

	if (App->Cl_ImGui->Show_ImGui_Debug_Player == 1)
	{
		Debug_Player(0);
	}

	if (Show_ImGui_FileView == 1)
	{
		App->Cl_FileView_V2->ImGui_FileView2();
	}

	if (Show_ImGui_Preferences == 1)
	{
		ImGui_Preferences();
	}

	if (Show_ImGui_Log == 1)
	{
		ShowExampleAppLog();
	}

	if (Show_PhysicsConsole == 1)
	{
		ImGui_PhysicsConsole();
	}

	if (Show_Propertities == 1)
	{
		ImGui_Properties();
	}
}

// *************************************************************************
// *						Camera_Object  Terry Bernie					   *
// *************************************************************************
void GD_ImGui::Camera_Object(void)
{
	if (!ImGui::Begin("Camera Object", &Show_Camera_Object))
	{
		ImGui::End();
	}
	else
	{
		ImGui::Text("Follow Object Properties");
		ImGui::Separator();


		btVector3 AngleFactor;
		AngleFactor = App->Cl_Scene_Data->Cl_Object[1]->bt_body->getAngularFactor();
		ImGui::Text("AngleFactor %.3f %.3f %.3f", AngleFactor.getX(), AngleFactor.getY(), AngleFactor.getZ());

		// ------------------------------ X AngularFactor
		ImGui::Checkbox("Lock X", &Lock_X);
		if (Lock_X == 1)
		{
			if (BlockX == 0){Toggle_X(1,0,0);BlockX = 1;}
		}
		else
		{
			if (BlockX == 1){Toggle_X(1,0,0);BlockX = 0;}
		}
	
		// ------------------------------ Y AngularFactor
		ImGui::SameLine();
		ImGui::Checkbox("Lock Y", &Lock_Y);
		if (Lock_Y == 1)
		{
			if (BlockY == 0){Toggle_X(0, 1, 0);BlockY = 1;}
		}
		else
		{
			if (BlockY == 1){Toggle_X(0, 1, 0);BlockY = 0;}
		}

		// ------------------------------ Z AngularFactor
		ImGui::SameLine();
		ImGui::Checkbox("Lock Z", &Lock_Z);
		if (Lock_Z == 1)
		{
			if (BlockZ == 0){Toggle_X(0, 0, 1);BlockZ = 1;}
		}
		else
		{ 
			if (BlockZ == 1){Toggle_X(0, 0, 1);BlockZ = 0; }
		}

		// ----------------------------------------------------------

		ImGui::Separator();
		static float f1 = App->Cl_Scene_Data->Cl_Object[1]->bt_body->getRestitution();
		ImGui::Text("Restitution %.3f",f1);
		ImGui::SliderFloat("Restitution float", &f1, 0.0f, 5.0f, "ratio = %.3f");
		App->Cl_Scene_Data->Cl_Object[1]->bt_body->setRestitution(f1);

		ImGui::Separator();
		static float f2 = App->Cl_Scene_Data->Cl_Object[1]->bt_body->getFriction();
		ImGui::Text("Friction %.3f", f2);
		ImGui::SliderFloat("Friction float", &f2, 0.0f, 5.0f, "ratio = %.3f");
		App->Cl_Scene_Data->Cl_Object[1]->bt_body->setFriction(f2);


		/*ImGui::SliderFloat("slider float (curve)", &f2, -10.0f, 10.0f, "%.4f", 2.0f);

		static float angle = 0.0f;
		ImGui::SliderAngle("slider angle", &angle);*/

		ImGui::End();
	}
}

// *************************************************************************
// *					Toggle_X  Terry Bernie							   *
// *************************************************************************
void GD_ImGui::Toggle_X(bool x, bool y, bool z)
{
	if (x == 1)
	{
		if (SetAxis.getX() == 1)
		{
			SetAxis.setX(0);
		}
		else
		{
			SetAxis.setX(1);
		}
	}

	if (y == 1)
	{
		if (SetAxis.getY() == 1)
		{
			SetAxis.setY(0);
		}
		else
		{
			SetAxis.setY(1);
		}
	}

	if (z == 1)
	{
		if (SetAxis.getZ() == 1)
		{
			SetAxis.setZ(0);
		}
		else
		{
			SetAxis.setZ(1);
		}
	}

	App->Cl_Scene_Data->Cl_Object[1]->bt_body->setAngularFactor(SetAxis);
	//App->Cl_Scene_Data->Cl_Object[1]->bt_body->setMassProps(0.02,btVector3(10,10,10));

}


// *************************************************************************
// *					ImGui_Properties  Terry Bernie					   *
// *************************************************************************
void GD_ImGui::ImGui_Properties(void)
{
	if (!ImGui::Begin("Object Settings", &Show_Propertities, ImGuiWindowFlags_NoSavedSettings))
	{
		ImGui::End();
	}
	else
	{
		ImGui::Text("With border:");
		ImGui::Columns(2, "mycolumns"); // 4-ways, with border
		ImGui::Separator();
		ImGui::Text("ID"); ImGui::NextColumn();
		ImGui::Text("Name"); ImGui::NextColumn();
		//ImGui::Text("Path"); ImGui::NextColumn();
		//ImGui::Text("Hovered"); ImGui::NextColumn();
		ImGui::Separator();
		const char* names[3] = { "One", "Two", "Three" };
		const char* paths[3] = { "/path/one", "/path/two", "/path/three" };
		static int selected = -1;
		for (int i = 0; i < 3; i++)
		{
			char label[32];
			sprintf(label, "%04d", i);
			if (ImGui::Selectable(label, selected == i, ImGuiSelectableFlags_SpanAllColumns))
				selected = i;
			bool hovered = ImGui::IsItemHovered();
			ImGui::NextColumn();
			ImGui::Text(names[i]); ImGui::NextColumn();
			//ImGui::Text(paths[i]); ImGui::NextColumn();
			//ImGui::Text("%d", hovered); ImGui::NextColumn();
		}
		ImGui::Columns(1);

		ImGui::End();
	}

}
// *************************************************************************
// *						ImGui_PhysicsView  Terry Bernie				   *
// *************************************************************************
void GD_ImGui::ImGui_PhysicsConsole(void)
{
	ImGui::SetNextWindowPos(ImVec2(10, 610), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin("Physics Console", &Show_PhysicsConsole, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize))
	{
		ImGui::End();
	}
	else
	{
		if (ImGui::Button("Physics On", ImVec2(120, 0)))
		{
			if (App->Cl_Scene_Data->SceneLoaded == 1)
			{
				if (App->Cl_Bullet->GD_Physics_On == 1)
				{
					App->Cl_Bullet->GD_Physics_On = 0;
					App->Cl19_Ogre->OgreListener->GD_Run_Physics = 0;
				}
				else
				{
					App->Cl_Bullet->GD_Physics_On = 1;
					App->Cl19_Ogre->OgreListener->GD_Run_Physics = 1;
				}
			}
		}

		ImGui::SameLine();
		if (ImGui::Button("Reset Physics", ImVec2(120, 0)))
		{
			if (App->Cl_Scene_Data->SceneLoaded == 1)
			{
				App->Cl_Bullet->Reset_Physics();
			}
		}

		ImGui::SameLine();
		if (ImGui::Button("Reset Entities", ImVec2(120, 0)))
		{
			if (App->Cl_Scene_Data->SceneLoaded == 1)
			{
				App->Cl_Scene_Data->Reset_Triggers();
			}
		}

		ImGui::End();
	}

}

// *************************************************************************
// *	  				ShowExampleAppLog Terry Bernie					   *
// *************************************************************************
void GD_ImGui::ShowExampleAppLog()
{
	static ExampleAppLog log;

	ImGui::SetNextWindowPos(ImVec2(340, 150), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);

	ImGui::Begin("General: Log", &Show_ImGui_Log, ImGuiWindowFlags_NoSavedSettings);
	
	ImGui::End();

	// Actually call in the regular Log helper (which will Begin() into the same window as we just did)
	if (Add_Log == 1)
	{
		log.AddLog(Log_Message);
		Add_Log = 0;
	}

	log.Draw("General: Log", &Show_ImGui_Log);

}

// *************************************************************************
// *	  				ImGui_Test_Log Terry Bernie						   *
// *************************************************************************
void GD_ImGui::ImGui_Test_Log(char* Message)
{
	if (Show_ImGui_Log == 0)
	{
		Show_ImGui_Log = 1;
	}

	char Text[1024];
	strcpy(Text,Message);
	strcat(Text, "\n");

	strcpy(Log_Message, Text);
	Add_Log = 1;

	Ogre::Root::getSingletonPtr()->renderOneFrame();
	Ogre::Root::getSingletonPtr()->renderOneFrame();

}

// *************************************************************************
// *						ImGui_FPS  Terry Bernie						   *
// *************************************************************************
void GD_ImGui::ImGui_FPS(void)
{
	if (!ImGui::Begin("Ogre Data", &Show_OgreData, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::End();
	}
	else
	{
		if (StartPos == 0)
		{
			ImGui::SetWindowPos("Ogre Data",ImVec2(10, 550));
			ImGui::SetWindowSize(ImVec2(350, 90));
			StartPos = 1;
		}

		ImGui::Spacing();
		//ImGui::PushFont(font1);
		ImGui::Text("FPS average %.1f ms/frame (%.0f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		//ImGui::PopFont();

		//ImGui::Spacing();
		//if (ImGui::CollapsingHeader("Camera Position"))
		//{
		//	Ogre::Vector3 campos = App->Cl19_Ogre->mCamera->getPosition();
		//	//ImGui::PushFont(font2);
		//	ImGui::Text("Cam Pos X %.3f Y %.3f Z %.3f", campos.x, campos.y , campos.z);
		//	//ImGui::PopFont();
		//}

		ImGui::Separator();

		//ImGui::ShowTestWindow();
		ImGui::End();
	}

}

// *************************************************************************
// *						Debug_Properties  Terry Bernie				   *
// *************************************************************************
void GD_ImGui::Object_Properties(void)
{
	ImGui::SetNextWindowPos(ImVec2(340, 150), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin("Object Properties", &Show_Object_Data, ImGuiWindowFlags_NoSavedSettings))
	{
		ImGui::End();
	}
	else
	{
		int index = App->Cl_Properties->Current_Selected_Object;
		ImGui::Text("Current Selected Object = %.i", App->Cl_Properties->Current_Selected_Object);
		ImGui::Text("Object Name: = %s", App->Cl_Scene_Data->Cl_Object[index]->Name);
		ImGui::Separator();
	
		ImGui::Spacing();
		if (ImGui::CollapsingHeader("Internal"))
		{
			ImGui::Text("Edit Category: = %s", Edit_Category_Str);// App->Cl_Properties->Edit_Category);
			ImGui::Text("Type: = %s (%i)", Edit_Type_Str, App->Cl_Scene_Data->Cl_Object[index]->Type);
			ImGui::Text("Usage: = %s", Edit_Usage_Str);// App->Cl_Scene_Data->Cl_Object[index]->Usage);
		}

		// ------------------------------------------- Mesh
		ImGui::Spacing();
		if (ImGui::CollapsingHeader("Mesh"))
		{
			ImGui::Text("Mesh File: = %s", App->Cl_Scene_Data->Cl_Object[index]->MeshName);

			Ogre::Vector3 pos = App->Cl_Scene_Data->Cl_Object[index]->OgreNode->getPosition();
			ImGui::Text("Position = X %.3f Y %.3f Z %.3f",pos.x, pos.y, pos.z);

			Ogre::Vector3 scale = App->Cl_Scene_Data->Cl_Object[index]->OgreNode->getScale();
			ImGui::Text("Scale = X %.3f Y %.3f Z %.3f", scale.x, scale.y, scale.z);

			Ogre::Quaternion rotation = App->Cl_Scene_Data->Cl_Object[index]->OgreNode->getOrientation();
			ImGui::Text("Rotaion = W %.3f  X %.3f Y %.3f Z %.3f", rotation.w, rotation.x, rotation.y, rotation.z);
			
			// ------------------------------------------- Materials
			ImGui::Indent();
			if (ImGui::CollapsingHeader("Materials"))
			{
				char buf[255];
				static int selected = -1;
				Ogre::SubEntity* subEntity;
				
				int NumSubMesh = App->Cl_Scene_Data->Cl_Object[index]->OgreEntity->getMesh()->getNumSubMeshes();
				int Count = 0;
				while (Count < NumSubMesh)
				{
					subEntity = App->Cl_Scene_Data->Cl_Object[index]->OgreEntity->getSubEntity(Count);
					
					//sprintf(buf, "Material Name: = %s", subEntity->getMaterialName().c_str());

					if (ImGui::Selectable(subEntity->getMaterialName().c_str(), selected == Count))
					{
						selected = Count;
						/*strcpy(buf, subEntity->getMaterialName().c_str());
						App->Say(buf);*/
					}

					Count++;
				}

				/*ImGui::Text("%i", selected);
				ImGui::Text(buf);*/

			}

			ImGui::Unindent();
		}

		// ------------------------------------------- Physics
		ImGui::Spacing();
		if (ImGui::CollapsingHeader("Physics"))
		{
			btVector3 pos = App->Cl_Scene_Data->Cl_Object[index]->bt_body->getWorldTransform().getOrigin();
			ImGui::Text("Position = X %.3f Y %.3f Z %.3f", pos.getX(), pos.getY(), pos.getZ());

			/*Ogre::Vector3 scale = App->Cl_Scene_Data->Cl_Object[index]->bt_body->getWorldTransform().getRotation();
			ImGui::Text("Scale = X %.3f Y %.3f Z %.3f", scale.x, scale.y, scale.z);*/

			btQuaternion rotation = App->Cl_Scene_Data->Cl_Object[index]->bt_body->getWorldTransform().getRotation();
			ImGui::Text("Rotation = W %.3f  X %.3f Y %.3f Z %.3f", rotation.getW(), rotation.getX(), rotation.getY(), rotation.getZ());
		}

		ImGui::End();
	}
}

// *************************************************************************
// *						Debug_Player  Terry Bernie					   *
// *************************************************************************
void GD_ImGui::Debug_Player(bool* p_open)
{
	if (!ImGui::Begin("Player Debug", &Show_ImGui_Debug_Player))
	{
		ImGui::End();
	}
	else
	{
		int index = App->Cl_Properties->Current_Selected_Object;
		/*if (StartPos == 0)
		{
		ImGui::SetWindowPos(ImVec2(400, 40));
		ImGui::SetWindowSize(ImVec2(350, 90));
		StartPos = 1;
		}*/

		ImGui::Text("Name = %s", App->Cl_Player->PlayerName);
		ImGui::Text("Game Mode: = %s", "1st_Person");
		ImGui::Separator();
		ImGui::Text("Ground Speed: = %.3f", App->Cl_Player->Ground_speed);
		ImGui::Text("Player Height: = %.3f", App->Cl_Player->PlayerHeight);
		ImGui::Text("Start Position: = %.3f %.3f %.3f", App->Cl_Player->StartPos.x, App->Cl_Player->StartPos.y, App->Cl_Player->StartPos.z);

		ImGui::Spacing();
		if (ImGui::CollapsingHeader("Player Ogre Mesh"))
		{
			Ogre::Vector3 pos = App->Cl_Scene_Data->Cl_Object[index]->OgreNode->getPosition();
			ImGui::Text("Position = X %.3f Y %.3f Z %.3f", pos.x, pos.y, pos.z);

			Ogre::Vector3 scale = App->Cl_Scene_Data->Cl_Object[index]->OgreNode->getScale();
			ImGui::Text("Scale = X %.3f Y %.3f Z %.3f", scale.x, scale.y, scale.z);

			Ogre::Quaternion rotation = App->Cl_Scene_Data->Cl_Object[index]->OgreNode->getOrientation();
			ImGui::Text("Rotaion = W %.3f  X %.3f Y %.3f Z %.3f", rotation.w, rotation.x, rotation.y, rotation.z);
		}

		ImGui::Spacing();
		if (ImGui::CollapsingHeader("Player Bullet Physics"))
		{
			ImGui::Text("Type: %s", "Dynamic");
			ImGui::Text("Shape: %s", "Capsule");
			ImGui::Text("Mass: %.3f", App->Cl_Player->Capsule_Mass);
			ImGui::Text("Radius: %.3f", App->Cl_Player->Capsule_Radius);
			ImGui::Text("Height: %.3f", App->Cl_Player->Capsule_Height);

			btVector3 L_Vel = App->Cl_Player->mObject->getLinearVelocity();
			ImGui::Text("Linear Velocity = X %.3f Y %.3f Z %.3f", L_Vel[0], L_Vel[1], L_Vel[2]);

			btScalar rot = App->Cl_Scene_Data->Cl_Object[index]->bt_body->getRestitution();
			ImGui::Text("Restitution = %.3f", rot);

		}

		ImGui::End();
	}
}

// *************************************************************************
// *						ImGui_Preferences  Terry Bernie				   *
// *************************************************************************
void GD_ImGui::ImGui_Preferences(void)
{
	ImGui::OpenPopup("Preferences");

	if (!ImGui::BeginPopupModal("Preferences", &Show_ImGui_Preferences))
	{
		ImGui::EndPopup();
	}
	else
	{
		//ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
		ImGui::Checkbox("Start Full Screen", &App->FullScreen_App);
		//ImGui::PopStyleVar();

		if (ImGui::Button("OK", ImVec2(120, 0)))
		{
			Show_ImGui_Preferences = 0;
			ImGui::EndPopup();
		}

		ImGui::SetItemDefaultFocus();
		ImGui::SameLine();

		if (ImGui::Button("Cancel", ImVec2(120, 0)))
		{
			Show_ImGui_Preferences = 0;
			ImGui::EndPopup();
		}

		ImGui::EndPopup();
	}
}

// *************************************************************************
// *					ImGui_Scene_Data  Terry Bernie					   *
// *************************************************************************
void GD_ImGui::ImGui_Scene_Data(void)
{
	ImGui::SetNextWindowSize(ImVec2(530, 250), ImGuiCond_FirstUseEver);

	ImGui::OpenPopup("Model Data");

	if (!ImGui::BeginPopupModal("Model Data", &Show_ImGui_Counters, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::EndPopup();
	}
	else
	{
		
		//ImGui::SetWindowPos(ImVec2(400, 40));
		//ImGui::SetWindowSize(ImVec2(350, 90));
		
	

		ImGui::Text("Model Name: = %s", App->CL_Vm_Model->JustName);
		ImGui::Text("Model File Name: = %s", App->CL_Vm_Model->FileName);
		ImGui::Text("Model Path: = %s", App->CL_Vm_Model->Model_FolderPath);
		ImGui::Text("Texture Path: = %s", App->CL_Vm_Model->Texture_FolderPath);

		ImGui::Spacing();

		ImGui::Text("Vertices: = %i", App->CL_Vm_Model->VerticeCount);
		ImGui::Text("Faces: = %i", App->CL_Vm_Model->FaceCount);
		ImGui::Text("Normals: = %i", App->CL_Vm_Model->NormalsCount);

		ImGui::Spacing();

		ImGui::Text("Textures: = %i", App->CL_Vm_Model->TextureCount);

		// ----------------------------- Textures
		char Header[255];
		int TextureCount = App->CL_Vm_Model->TextureCount;

		sprintf(Header, "%s %i", "Textures", TextureCount);

		if (ImGui::CollapsingHeader(Header))
		{
			int Count = 0;
			while (Count < TextureCount)
			{
				ImGui::Text("%s", App->CL_Vm_Model->TextureNames_Data[Count].Name);
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
		sprintf(Header, "%s %i", "Groupd", GroupCount);

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
			Show_ImGui_Counters = 0;
		}
		
		ImGui::EndPopup();
	}

}

// *************************************************************************
// *					ImGui_Dimensions  Terry Bernie					   *
// *************************************************************************
void GD_ImGui::ImGui_Dimensions(void)
{
	if (!ImGui::Begin("Dimensions", &Show_ImGui_Dimensions, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::End();
	}
	else
	{
		int index = App->Cl_Properties->Current_Selected_Object;

		/*if (StartPos == 0)
		{
		ImGui::SetWindowPos(ImVec2(400, 40));
		ImGui::SetWindowSize(ImVec2(350, 90));
		StartPos = 1;
		}*/

		ImGui::Text("Current Selected Object = %.i", App->Cl_Properties->Current_Selected_Object);
		ImGui::Text("Object Name: = %s", App->Cl_Scene_Data->Cl_Object[index]->Name);
		ImGui::Separator();

		ImGui::Spacing();

		//---------------------------------------- Header Position
		ImGui::Spacing();
		if (ImGui::CollapsingHeader("Position")) // Position
		{
			ImGui::Text("Position");

			Ogre::Vector3 pos = App->Cl_Scene_Data->Cl_Object[index]->OgreNode->getPosition();
			ImGui::Text("X %.3f Y %.3f Z %.3f", pos.x, pos.y, pos.z);
			/*ImGui::Text("X %.3f", pos.x);
			ImGui::Text("Y %.3f", pos.y);
			ImGui::Text("Z %.3f", pos.z);*/
			ImGui::Spacing();

			// ------------------------------------------ Position X
			ImGui::Text("X ");
			ImGui::SameLine();

			float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
			ImGui::PushButtonRepeat(true);
			if (ImGui::ArrowButton("##left", ImGuiDir_Left))
			{
				Ogre::Vector3 Pos = App->Cl_Scene_Data->Cl_Object[index]->Mesh_Pos;
				Pos.x += App->Cl_Dimensions->Model_XTranslate;// Delta;
				App->Cl_Scene_Data->Cl_Object[index]->Mesh_Pos = Pos;
				App->Cl_Scene_Data->Cl_Object[index]->OgreNode->setPosition(Pos);
				App->Cl_Dimensions->UpDate_Physics_And_Visuals(index);
			}
			ImGui::SameLine(0.0f, spacing);
			if (ImGui::ArrowButton("##right", ImGuiDir_Right))
			{
				Ogre::Vector3 Pos = App->Cl_Scene_Data->Cl_Object[index]->Mesh_Pos;
				Pos.x -= App->Cl_Dimensions->Model_XTranslate;// Delta;
				App->Cl_Scene_Data->Cl_Object[index]->Mesh_Pos = Pos;
				App->Cl_Scene_Data->Cl_Object[index]->OgreNode->setPosition(Pos);
				//App->Cl_Dimensions->Select_Properties_Update();
				App->Cl_Dimensions->UpDate_Physics_And_Visuals(index);
			}
			ImGui::PopButtonRepeat();

			ImGui::SameLine();
			ImGui::SetNextItemWidth(100);
			const char* XitemsX[] = { "1", "2", "5", "10", "20" };
			static int XitemX = 1;
			bool Changed = ImGui::Combo("Step X", &XitemX, XitemsX, IM_ARRAYSIZE(XitemsX));   // Combo using proper array. You can also pass a callback to retrieve array value, no need to create/copy an array just for that.
			if (Changed == 1)
			{
				App->Cl_Dimensions->Model_XTranslate = (float)atof(XitemsX[XitemX]);
			}

			// ------------------------------------------ Position y
			ImGui::Text("Y ");
			ImGui::SameLine();

			float spacing2 = ImGui::GetStyle().ItemInnerSpacing.x;
			ImGui::PushButtonRepeat(true);
			if (ImGui::ArrowButton("##leftY", ImGuiDir_Left))
			{
				Ogre::Vector3 Pos = App->Cl_Scene_Data->Cl_Object[index]->Mesh_Pos;
				Pos.y += App->Cl_Dimensions->Model_YTranslate;// Delta;
				App->Cl_Scene_Data->Cl_Object[index]->Mesh_Pos = Pos;
				App->Cl_Scene_Data->Cl_Object[index]->OgreNode->setPosition(Pos);
				App->Cl_Dimensions->UpDate_Physics_And_Visuals(index);
			}
			ImGui::SameLine(0.0f, spacing2);
			if (ImGui::ArrowButton("##rightY", ImGuiDir_Right))
			{
				Ogre::Vector3 Pos = App->Cl_Scene_Data->Cl_Object[index]->Mesh_Pos;
				Pos.y -= App->Cl_Dimensions->Model_YTranslate;// Delta;
				App->Cl_Scene_Data->Cl_Object[index]->Mesh_Pos = Pos;
				App->Cl_Scene_Data->Cl_Object[index]->OgreNode->setPosition(Pos);
				//App->Cl_Dimensions->Select_Properties_Update();
				App->Cl_Dimensions->UpDate_Physics_And_Visuals(index);
			}
			ImGui::PopButtonRepeat();

			ImGui::SameLine();
			ImGui::SetNextItemWidth(100);
			const char* XitemsY[] = { "1", "2", "5", "10", "20" };
			static int XitemY = 1;
			bool ChangedY = ImGui::Combo("Step Y", &XitemY, XitemsY, IM_ARRAYSIZE(XitemsY));   // Combo using proper array. You can also pass a callback to retrieve array value, no need to create/copy an array just for that.
			if (ChangedY == 1)
			{
				App->Cl_Dimensions->Model_YTranslate = (float)atof(XitemsY[XitemY]);
			}

			// ------------------------------------------ Position z
			ImGui::Text("Z ");
			ImGui::SameLine();

			float spacing3 = ImGui::GetStyle().ItemInnerSpacing.x;
			ImGui::PushButtonRepeat(true);
			if (ImGui::ArrowButton("##leftZ", ImGuiDir_Left))
			{
				Ogre::Vector3 Pos = App->Cl_Scene_Data->Cl_Object[index]->Mesh_Pos;
				Pos.z += App->Cl_Dimensions->Model_ZTranslate;// Delta;
				App->Cl_Scene_Data->Cl_Object[index]->Mesh_Pos = Pos;
				App->Cl_Scene_Data->Cl_Object[index]->OgreNode->setPosition(Pos);
				App->Cl_Dimensions->UpDate_Physics_And_Visuals(index);
			}
			ImGui::SameLine(0.0f, spacing3);
			if (ImGui::ArrowButton("##rightZ", ImGuiDir_Right))
			{
				Ogre::Vector3 Pos = App->Cl_Scene_Data->Cl_Object[index]->Mesh_Pos;
				Pos.z -= App->Cl_Dimensions->Model_ZTranslate;// Delta;
				App->Cl_Scene_Data->Cl_Object[index]->Mesh_Pos = Pos;
				App->Cl_Scene_Data->Cl_Object[index]->OgreNode->setPosition(Pos);
				//App->Cl_Dimensions->Select_Properties_Update();
				App->Cl_Dimensions->UpDate_Physics_And_Visuals(index);
			}
			ImGui::PopButtonRepeat();

			ImGui::SameLine();
			ImGui::SetNextItemWidth(100);
			const char* XitemsZ[] = { "1", "2", "5", "10", "20" };
			static int XitemZ = 1;
			bool ChangedZ = ImGui::Combo("Step Z", &XitemZ, XitemsZ, IM_ARRAYSIZE(XitemsZ));   // Combo using proper array. You can also pass a callback to retrieve array value, no need to create/copy an array just for that.
			if (ChangedZ == 1)
			{
				App->Cl_Dimensions->Model_ZTranslate = (float)atof(XitemsZ[XitemZ]);
			}
		}

		//---------------------------------------- Header Rotation
		ImGui::Spacing();
		if (ImGui::CollapsingHeader("Rotation"))
		{
			ImGui::Text("Rotation");
			Ogre::Quaternion rotation = App->Cl_Scene_Data->Cl_Object[index]->OgreNode->getOrientation();
			ImGui::Text("W %.3f  X %.3f Y %.3f Z %.3f", rotation.w, rotation.x, rotation.y, rotation.z);

			// Rotation X
			ImGui::Spacing();
			ImGui::Text("X ");
			ImGui::SameLine();

			// ---------- Rotation X
			float spacing3 = ImGui::GetStyle().ItemInnerSpacing.x;
			ImGui::PushButtonRepeat(true);
			if (ImGui::ArrowButton("##LeftRX", ImGuiDir_Left))
			{
				App->Cl_Scene_Data->Cl_Object[index]->OgreNode->pitch(Radian(Ogre::Degree(App->Cl_Dimensions->Model_XRotate)));
				App->Cl_Scene_Data->Cl_Object[index]->Mesh_Rot.x += App->Cl_Dimensions->Model_XRotate;
				App->Cl_Scene_Data->Cl_Object[index]->Mesh_Quat = App->Cl_Scene_Data->Cl_Object[index]->OgreNode->getOrientation();

				App->Cl_Scene_Data->Cl_Object[index]->Physics_Rot.x += App->Cl_Dimensions->Model_XRotate;
				App->Cl_Scene_Data->Cl_Object[index]->Physics_Quat = App->Cl_Scene_Data->Cl_Object[index]->OgreNode->getOrientation();
				float w = App->Cl_Scene_Data->Cl_Object[index]->Physics_Quat.w;
				float x = App->Cl_Scene_Data->Cl_Object[index]->Physics_Quat.x;
				float y = App->Cl_Scene_Data->Cl_Object[index]->Physics_Quat.y;
				float z = App->Cl_Scene_Data->Cl_Object[index]->Physics_Quat.z;
				App->Cl_Scene_Data->Cl_Object[index]->bt_body->getWorldTransform().setRotation(btQuaternion(x, y, z, w));

				App->Cl_Dimensions->UpDate_Physics_And_Visuals(index);
			}
			ImGui::SameLine(0.0f, spacing3);
			if (ImGui::ArrowButton("##rightRX", ImGuiDir_Right))
			{
				App->Cl_Scene_Data->Cl_Object[index]->OgreNode->pitch(Radian(Ogre::Degree(-App->Cl_Dimensions->Model_XRotate)));
				App->Cl_Scene_Data->Cl_Object[index]->Mesh_Rot.x -= App->Cl_Dimensions->Model_XRotate;
				App->Cl_Scene_Data->Cl_Object[index]->Mesh_Quat = App->Cl_Scene_Data->Cl_Object[index]->OgreNode->getOrientation();

				App->Cl_Scene_Data->Cl_Object[index]->Physics_Rot.x -= App->Cl_Dimensions->Model_XRotate;
				App->Cl_Scene_Data->Cl_Object[index]->Physics_Quat = App->Cl_Scene_Data->Cl_Object[index]->OgreNode->getOrientation();
				float w = App->Cl_Scene_Data->Cl_Object[index]->Physics_Quat.w;
				float x = App->Cl_Scene_Data->Cl_Object[index]->Physics_Quat.x;
				float y = App->Cl_Scene_Data->Cl_Object[index]->Physics_Quat.y;
				float z = App->Cl_Scene_Data->Cl_Object[index]->Physics_Quat.z;
				App->Cl_Scene_Data->Cl_Object[index]->bt_body->getWorldTransform().setRotation(btQuaternion(x, y, z, w));

				App->Cl_Dimensions->UpDate_Physics_And_Visuals(index);
			}
			ImGui::PopButtonRepeat();


			// ---------- Rotation y
			ImGui::Text("Y ");
			ImGui::SameLine();

			float spacingY = ImGui::GetStyle().ItemInnerSpacing.x;
			ImGui::PushButtonRepeat(true);
			if (ImGui::ArrowButton("##LeftRY", ImGuiDir_Left))
			{
				App->Cl_Scene_Data->Cl_Object[index]->OgreNode->yaw(Radian(Ogre::Degree(App->Cl_Dimensions->Model_XRotate)));
				App->Cl_Scene_Data->Cl_Object[index]->Mesh_Rot.y += App->Cl_Dimensions->Model_XRotate;
				App->Cl_Scene_Data->Cl_Object[index]->Mesh_Quat = App->Cl_Scene_Data->Cl_Object[index]->OgreNode->getOrientation();

				App->Cl_Scene_Data->Cl_Object[index]->Physics_Rot.y += App->Cl_Dimensions->Model_XRotate;
				App->Cl_Scene_Data->Cl_Object[index]->Physics_Quat = App->Cl_Scene_Data->Cl_Object[index]->OgreNode->getOrientation();
				float w = App->Cl_Scene_Data->Cl_Object[index]->Physics_Quat.w;
				float x = App->Cl_Scene_Data->Cl_Object[index]->Physics_Quat.x;
				float y = App->Cl_Scene_Data->Cl_Object[index]->Physics_Quat.y;
				float z = App->Cl_Scene_Data->Cl_Object[index]->Physics_Quat.z;
				App->Cl_Scene_Data->Cl_Object[index]->bt_body->getWorldTransform().setRotation(btQuaternion(x, y, z, w));

				App->Cl_Dimensions->UpDate_Physics_And_Visuals(index);
			}
			ImGui::SameLine(0.0f, spacingY);
			if (ImGui::ArrowButton("##rightRY", ImGuiDir_Right))
			{
				App->Cl_Scene_Data->Cl_Object[index]->OgreNode->yaw(Radian(Ogre::Degree(-App->Cl_Dimensions->Model_XRotate)));
				App->Cl_Scene_Data->Cl_Object[index]->Mesh_Rot.y -= App->Cl_Dimensions->Model_XRotate;
				App->Cl_Scene_Data->Cl_Object[index]->Mesh_Quat = App->Cl_Scene_Data->Cl_Object[index]->OgreNode->getOrientation();

				App->Cl_Scene_Data->Cl_Object[index]->Physics_Rot.y -= App->Cl_Dimensions->Model_XRotate;
				App->Cl_Scene_Data->Cl_Object[index]->Physics_Quat = App->Cl_Scene_Data->Cl_Object[index]->OgreNode->getOrientation();
				float w = App->Cl_Scene_Data->Cl_Object[index]->Physics_Quat.w;
				float x = App->Cl_Scene_Data->Cl_Object[index]->Physics_Quat.x;
				float y = App->Cl_Scene_Data->Cl_Object[index]->Physics_Quat.y;
				float z = App->Cl_Scene_Data->Cl_Object[index]->Physics_Quat.z;
				App->Cl_Scene_Data->Cl_Object[index]->bt_body->getWorldTransform().setRotation(btQuaternion(x, y, z, w));

				App->Cl_Dimensions->UpDate_Physics_And_Visuals(index);
			}
			ImGui::PopButtonRepeat();

			// Rotation Z
			ImGui::Text("Z ");
			ImGui::SameLine();

			float spacingZ = ImGui::GetStyle().ItemInnerSpacing.x;
			ImGui::PushButtonRepeat(true);
			if (ImGui::ArrowButton("##LeftRZ", ImGuiDir_Left))
			{
				App->Cl_Scene_Data->Cl_Object[index]->OgreNode->roll(Radian(Ogre::Degree(App->Cl_Dimensions->Model_XRotate)));
				App->Cl_Scene_Data->Cl_Object[index]->Mesh_Rot.z += App->Cl_Dimensions->Model_XRotate;
				App->Cl_Scene_Data->Cl_Object[index]->Mesh_Quat = App->Cl_Scene_Data->Cl_Object[index]->OgreNode->getOrientation();

				App->Cl_Scene_Data->Cl_Object[index]->Physics_Rot.z += App->Cl_Dimensions->Model_XRotate;
				App->Cl_Scene_Data->Cl_Object[index]->Physics_Quat = App->Cl_Scene_Data->Cl_Object[index]->OgreNode->getOrientation();
				float w = App->Cl_Scene_Data->Cl_Object[index]->Physics_Quat.w;
				float x = App->Cl_Scene_Data->Cl_Object[index]->Physics_Quat.x;
				float y = App->Cl_Scene_Data->Cl_Object[index]->Physics_Quat.y;
				float z = App->Cl_Scene_Data->Cl_Object[index]->Physics_Quat.z;
				App->Cl_Scene_Data->Cl_Object[index]->bt_body->getWorldTransform().setRotation(btQuaternion(x, y, z, w));

				App->Cl_Dimensions->UpDate_Physics_And_Visuals(index);
			}
			ImGui::SameLine(0.0f, spacingZ);
			if (ImGui::ArrowButton("##rightRZ", ImGuiDir_Right))
			{
				App->Cl_Scene_Data->Cl_Object[index]->OgreNode->roll(Radian(Ogre::Degree(-App->Cl_Dimensions->Model_XRotate)));
				App->Cl_Scene_Data->Cl_Object[index]->Mesh_Rot.z -= App->Cl_Dimensions->Model_XRotate;
				App->Cl_Scene_Data->Cl_Object[index]->Mesh_Quat = App->Cl_Scene_Data->Cl_Object[index]->OgreNode->getOrientation();

				App->Cl_Scene_Data->Cl_Object[index]->Physics_Rot.z -= App->Cl_Dimensions->Model_XRotate;
				App->Cl_Scene_Data->Cl_Object[index]->Physics_Quat = App->Cl_Scene_Data->Cl_Object[index]->OgreNode->getOrientation();
				float w = App->Cl_Scene_Data->Cl_Object[index]->Physics_Quat.w;
				float x = App->Cl_Scene_Data->Cl_Object[index]->Physics_Quat.x;
				float y = App->Cl_Scene_Data->Cl_Object[index]->Physics_Quat.y;
				float z = App->Cl_Scene_Data->Cl_Object[index]->Physics_Quat.z;
				App->Cl_Scene_Data->Cl_Object[index]->bt_body->getWorldTransform().setRotation(btQuaternion(x, y, z, w));

				App->Cl_Dimensions->UpDate_Physics_And_Visuals(index);
			}
			ImGui::PopButtonRepeat();
		}

		//---------------------------------------- Header Scale
		ImGui::Spacing();
		if (ImGui::CollapsingHeader("Scale"))
		{
			ImGui::Text("Scale");

			ImGui::SameLine();
			ImGui::Checkbox("Lock Axis", &App->Cl_Dimensions->Set_ScaleLock);
			if (App->Cl_Dimensions->Set_ScaleLock == 1)
			{
				Ogre::Vector3 scale = App->Cl_Scene_Data->Cl_Object[index]->OgreNode->getScale();
				ImGui::Text("X %.3f Y %.3f Z %.3f", scale.x, scale.y, scale.z);
				ImGui::Spacing();

				ImGui::Text("All ");
				ImGui::SameLine();

				float spacingSX = ImGui::GetStyle().ItemInnerSpacing.x;
				ImGui::PushButtonRepeat(true);
				if (ImGui::ArrowButton("##LeftSX", ImGuiDir_Left))
				{
					float Delta = 0.2;// App->Cl_Dimensions->Model_XScale;
					Ogre::Vector3 Scale = App->Cl_Scene_Data->Cl_Object[index]->Mesh_Scale;
					Scale.x += Delta;
					Scale.y += Delta;
					Scale.z += Delta;
					App->Cl_Scene_Data->Cl_Object[index]->Mesh_Scale = Scale;
					App->Cl_Scene_Data->Cl_Object[index]->OgreNode->setScale(Scale);

					Scale = App->Cl_Scene_Data->Cl_Object[index]->Physics_Scale;
					Scale.x += Delta;
					Scale.y += Delta;
					Scale.z += Delta;
					App->Cl_Scene_Data->Cl_Object[index]->Physics_Scale = Scale;
					App->Cl_Scene_Data->Cl_Object[index]->bt_body->getCollisionShape()->setLocalScaling(btVector3(Scale.x, Scale.y, Scale.z));

					//App->Cl_Dimensions->Set_Physics_Position(index);
					App->Cl_Dimensions->UpDate_Physics_And_Visuals(index);
				}
				ImGui::SameLine(0.0f, spacingSX);
				if (ImGui::ArrowButton("##rightSX", ImGuiDir_Right))
				{
					float Delta = 0.2;// App->Cl_Dimensions->Model_XScale;
					Ogre::Vector3 Scale = App->Cl_Scene_Data->Cl_Object[index]->Mesh_Scale;
					Scale.x -= Delta;
					Scale.y -= Delta;
					Scale.z -= Delta;
					App->Cl_Scene_Data->Cl_Object[index]->Mesh_Scale = Scale;
					App->Cl_Scene_Data->Cl_Object[index]->OgreNode->setScale(Scale);

					Scale = App->Cl_Scene_Data->Cl_Object[index]->Physics_Scale;
					Scale.x -= Delta;
					Scale.y -= Delta;
					Scale.z -= Delta;
					App->Cl_Scene_Data->Cl_Object[index]->Physics_Scale = Scale;
					App->Cl_Scene_Data->Cl_Object[index]->bt_body->getCollisionShape()->setLocalScaling(btVector3(Scale.x, Scale.y, Scale.z));

					//App->Cl_Dimensions->Set_Physics_Position(index);
					App->Cl_Dimensions->UpDate_Physics_And_Visuals(index);
				}
				ImGui::PopButtonRepeat();
			}
			else
			{
				Ogre::Vector3 scale = App->Cl_Scene_Data->Cl_Object[index]->OgreNode->getScale();
				ImGui::Text("X %.3f Y %.3f Z %.3f", scale.x, scale.y, scale.z);
				ImGui::Spacing();

				// Scale X
				ImGui::Text("X ");
				ImGui::SameLine();

				if (ImGui::Button("SX + "))
				{
					float Delta = 0.2;// App->Cl_Dimensions->Model_XScale;
					Ogre::Vector3 Scale = App->Cl_Scene_Data->Cl_Object[index]->Mesh_Scale;
					Scale.x += Delta;
					App->Cl_Scene_Data->Cl_Object[index]->Mesh_Scale = Scale;
					App->Cl_Scene_Data->Cl_Object[index]->OgreNode->setScale(Scale);

					Scale = App->Cl_Scene_Data->Cl_Object[index]->Physics_Scale;
					Scale.x += Delta;
					App->Cl_Scene_Data->Cl_Object[index]->Physics_Scale = Scale;
					App->Cl_Scene_Data->Cl_Object[index]->bt_body->getCollisionShape()->setLocalScaling(btVector3(Scale.x, Scale.y, Scale.z));

					App->Cl_Dimensions->Set_Physics_Position(index);
					App->Cl_Dimensions->UpDate_Physics_And_Visuals(index);
				}

				ImGui::SameLine();

				if (ImGui::Button("SX - "))
				{
					float Delta = 0.2;// App->Cl_Dimensions->Model_XScale;
					Ogre::Vector3 Scale = App->Cl_Scene_Data->Cl_Object[index]->Mesh_Scale;
					Scale.x -= Delta;
					App->Cl_Scene_Data->Cl_Object[index]->Mesh_Scale = Scale;
					App->Cl_Scene_Data->Cl_Object[index]->OgreNode->setScale(Scale);

					Scale = App->Cl_Scene_Data->Cl_Object[index]->Physics_Scale;
					Scale.x -= Delta;
					App->Cl_Scene_Data->Cl_Object[index]->Physics_Scale = Scale;
					App->Cl_Scene_Data->Cl_Object[index]->bt_body->getCollisionShape()->setLocalScaling(btVector3(Scale.x, Scale.y, Scale.z));

					App->Cl_Dimensions->Set_Physics_Position(index);
					App->Cl_Dimensions->UpDate_Physics_And_Visuals(index);

				}

				// Scale Y
				ImGui::Text("Y ");
				ImGui::SameLine();

				if (ImGui::Button("SY + "))
				{
					float Delta = 0.2;// App->Cl_Dimensions->Model_XScale;
					Ogre::Vector3 Scale = App->Cl_Scene_Data->Cl_Object[index]->Mesh_Scale;
					Scale.y += Delta;
					App->Cl_Scene_Data->Cl_Object[index]->Mesh_Scale = Scale;
					App->Cl_Scene_Data->Cl_Object[index]->OgreNode->setScale(Scale);

					Scale = App->Cl_Scene_Data->Cl_Object[index]->Physics_Scale;
					Scale.y += Delta;
					App->Cl_Scene_Data->Cl_Object[index]->Physics_Scale = Scale;
					App->Cl_Scene_Data->Cl_Object[index]->bt_body->getCollisionShape()->setLocalScaling(btVector3(Scale.x, Scale.y, Scale.z));

					App->Cl_Dimensions->Set_Physics_Position(index);
					App->Cl_Dimensions->UpDate_Physics_And_Visuals(index);
				}

				ImGui::SameLine();

				if (ImGui::Button("SY - "))
				{
					float Delta = 0.2;// App->Cl_Dimensions->Model_XScale;
					Ogre::Vector3 Scale = App->Cl_Scene_Data->Cl_Object[index]->Mesh_Scale;
					Scale.y -= Delta;
					App->Cl_Scene_Data->Cl_Object[index]->Mesh_Scale = Scale;
					App->Cl_Scene_Data->Cl_Object[index]->OgreNode->setScale(Scale);

					Scale = App->Cl_Scene_Data->Cl_Object[index]->Physics_Scale;
					Scale.y -= Delta;
					App->Cl_Scene_Data->Cl_Object[index]->Physics_Scale = Scale;
					App->Cl_Scene_Data->Cl_Object[index]->bt_body->getCollisionShape()->setLocalScaling(btVector3(Scale.x, Scale.y, Scale.z));

					App->Cl_Dimensions->Set_Physics_Position(index);
					App->Cl_Dimensions->UpDate_Physics_And_Visuals(index);
				}

				// Scale Z
				ImGui::Text("Z ");
				ImGui::SameLine();

				if (ImGui::Button("SZ + "))
				{
					float Delta = 0.2;// App->Cl_Dimensions->Model_XScale;
					Ogre::Vector3 Scale = App->Cl_Scene_Data->Cl_Object[index]->Mesh_Scale;
					Scale.z += Delta;
					App->Cl_Scene_Data->Cl_Object[index]->Mesh_Scale = Scale;
					App->Cl_Scene_Data->Cl_Object[index]->OgreNode->setScale(Scale);

					Scale = App->Cl_Scene_Data->Cl_Object[index]->Physics_Scale;
					Scale.z += Delta;
					App->Cl_Scene_Data->Cl_Object[index]->Physics_Scale = Scale;
					App->Cl_Scene_Data->Cl_Object[index]->bt_body->getCollisionShape()->setLocalScaling(btVector3(Scale.x, Scale.y, Scale.z));

					App->Cl_Dimensions->Set_Physics_Position(index);
					App->Cl_Dimensions->UpDate_Physics_And_Visuals(index);
				}

				ImGui::SameLine();

				if (ImGui::Button("SZ - "))
				{
					float Delta = 0.2;// App->Cl_Dimensions->Model_XScale;
					Ogre::Vector3 Scale = App->Cl_Scene_Data->Cl_Object[index]->Mesh_Scale;
					Scale.z -= Delta;
					App->Cl_Scene_Data->Cl_Object[index]->Mesh_Scale = Scale;
					App->Cl_Scene_Data->Cl_Object[index]->OgreNode->setScale(Scale);

					Scale = App->Cl_Scene_Data->Cl_Object[index]->Physics_Scale;
					Scale.z -= Delta;
					App->Cl_Scene_Data->Cl_Object[index]->Physics_Scale = Scale;
					App->Cl_Scene_Data->Cl_Object[index]->bt_body->getCollisionShape()->setLocalScaling(btVector3(Scale.x, Scale.y, Scale.z));

					App->Cl_Dimensions->Set_Physics_Position(index);
					App->Cl_Dimensions->UpDate_Physics_And_Visuals(index);
				}
			}
		}
		

		ImGui::End();
	}
}

void GD_ImGui::ShowExampleAppPropertyEditor(bool* p_open)
{
	ImGui::SetNextWindowSize(ImVec2(430, 450), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin("Example: Property editor", p_open))
	{
		ImGui::End();
		return;
	}

	//ShowHelpMarker("This example shows how you may implement a property editor using two columns.\nAll objects/fields data are dummies here.\nRemember that in many simple cases, you can use ImGui::SameLine(xxx) to position\nyour cursor horizontally instead of using the Columns() API.");

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
	ImGui::Columns(2);
	ImGui::Separator();

	//struct funcs
	//{
		//static void ShowDummyObject(const char* prefix, int uid)
		//{
			int uid = 0;
			ImGui::PushID(uid);                      // Use object uid as identifier. Most commonly you could also use the object pointer as a base ID.
			ImGui::AlignTextToFramePadding();  // Text and Tree nodes are less high than regular widgets, here we add vertical spacing to make the tree lines equal high.
			bool node_open = ImGui::TreeNode("Camera", "%s_%u", "Test Project", uid);
			ImGui::NextColumn();
			ImGui::AlignTextToFramePadding();
			ImGui::Text("my sailor is rich");
			ImGui::NextColumn();
			if (node_open)
			{
				static float dummy_members[8] = { 0.0f,0.0f,1.0f,3.1416f,100.0f,999.0f };
				//for (int i = 0; i < 8; i++)
				//{
				//	ImGui::PushID(i); // Use field index as identifier.
					//if (i < 2)
					{
						int uid = 1;
						ImGui::PushID(uid);                      // Use object uid as identifier. Most commonly you could also use the object pointer as a base ID.
						ImGui::AlignTextToFramePadding();  // Text and Tree nodes are less high than regular widgets, here we add vertical spacing to make the tree lines equal high.
						bool node_open = ImGui::TreeNode("Camera", "%s_%u", "Level Name", uid);
						ImGui::NextColumn();
						ImGui::AlignTextToFramePadding();
						ImGui::Text("my sailor is rich");
						ImGui::NextColumn();
						if (node_open)
						{
							uid = 2;
							ImGui::PushID(uid);                      // Use object uid as identifier. Most commonly you could also use the object pointer as a base ID.
							ImGui::AlignTextToFramePadding();  // Text and Tree nodes are less high than regular widgets, here we add vertical spacing to make the tree lines equal high.
							bool node_open2 = ImGui::TreeNode("Camera2", "%s_%u", "Camerax", uid);
							ImGui::NextColumn();
							ImGui::AlignTextToFramePadding();
							ImGui::Text("my sailor is rich");
							ImGui::NextColumn();
							if (node_open2)
							{
								int i = 1;
								ImGui::AlignTextToFramePadding();
								// Here we use a Selectable (instead of Text) to highlight on hover
								//ImGui::Text("Field_%d", i);
								char label[32];
								sprintf(label, "Field_%d", i);
								ImGui::Bullet();
								bool test = ImGui::Selectable(label);
								if (test == 1)
								{
									ImGui::NextColumn();
									ImGui::PushItemWidth(-1);
									if (i >= 5)
										ImGui::InputFloat("##value", &dummy_members[i], 1.0f);
									else
										ImGui::DragFloat("##value", &dummy_members[i], 0.01f);
									ImGui::PopItemWidth();
									ImGui::NextColumn();
								}
							}

							
						}
					}
			//		else
			//		{
			//			//ImGui::AlignTextToFramePadding();
			//			//// Here we use a Selectable (instead of Text) to highlight on hover
			//			////ImGui::Text("Field_%d", i);
			//			//char label[32];
			//			//sprintf(label, "Field_%d", i);
			//			//ImGui::Bullet();
			//			//ImGui::Selectable(label);
			//			//ImGui::NextColumn();
			//			//ImGui::PushItemWidth(-1);
			//			//if (i >= 5)
			//			//	ImGui::InputFloat("##value", &dummy_members[i], 1.0f);
			//			//else
			//			//	ImGui::DragFloat("##value", &dummy_members[i], 0.01f);
			//			//ImGui::PopItemWidth();
			//			//ImGui::NextColumn();
			//		}
					//ImGui::PopID();
				//}
				//ImGui::TreePop();
			}
			//ImGui::PopID();
		//}
	//};

	// Iterate dummy objects with dummy members (all the same data)
	/*for (int obj_i = 0; obj_i < 3; obj_i++)
		funcs::ShowDummyObject("Object", obj_i);*/

	ImGui::Columns(1);
	ImGui::Separator();
	ImGui::PopStyleVar();
	ImGui::End();
}

// *************************************************************************
// *	  				ImGui_FileView Terry Bernie						   *
// *************************************************************************
void GD_ImGui::ImGui_FileView(void)
{
	//static int selected = -1;
	//static int selected2 = -1;
	//ImGui::SetNextWindowSize(ImVec2(430, 450), ImGuiCond_FirstUseEver);

	//if (!ImGui::Begin("File_View", &Show_ImGui_FileView))
	//{
	//	ImGui::End();
	//	return;
	//}

	//ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
	//ImGui::Separator();
	//ImGui::Text("Test");
	//
	//int uid = 10;
	//ImGui::PushID(uid);                      // Use object uid as identifier. Most commonly you could also use the object pointer as a base ID.
	//ImGui::AlignTextToFramePadding();  // Text and Tree nodes are less high than regular widgets, here we add vertical spacing to make the tree lines equal high.
	//bool node_open = ImGui::TreeNode("Camera", "%s_%u", "Test Project", uid);
	//if (node_open)
	//{
	//	char Name[32];
	//	int Count = 0;
	//	while (Count < 10)
	//	{
	//		sprintf(Name, "Field_%i", Count);
	//		ImGui::Bullet();
	//		
	//		if (ImGui::Selectable(Name, selected == Count))
	//		{
	//			selected = Count;
	//		}

	//		Count++;
	//	}

	//}
	//ImGui::TreePop();
	//uid = 20;
	//bool node_open2 = ImGui::TreeNode("poo", "%s_%u", "Objects", uid);
	//if (node_open2)
	//{
	//	char Name[32];
	//	int Count = 0;
	//	while (Count < 10)
	//	{
	//		sprintf(Name, "Object_%i", Count);
	//		ImGui::Bullet();

	//		if (ImGui::Selectable(Name, selected2 == Count))
	//		{
	//			selected2 = Count;
	//		}

	//		Count++;
	//	}

	//}
	//ImGui::TreePop();




	//char buff[255];
	//_itoa(selected, buff, 10);
	//ImGui::Text(buff);

	//_itoa(selected2, buff, 10);
	//ImGui::Text(buff);

	//ImGui::End();
}

// *************************************************************************
// *	  				Update_StaticData Terry Bernie					   *
// *************************************************************************
void GD_ImGui::Update_StaticData(void)
{
	strcpy(Edit_Category_Str, App->Cl_LookUps->Get_Edit_Category_String());
	strcpy(Edit_Type_Str, App->Cl_LookUps->Get_Type_Category_String());
	strcpy(Edit_Usage_Str, App->Cl_LookUps->Get_Usage_Category_String());
}

// *************************************************************************
// *	  				ImGui_Set_Colours Terry Bernie					   *
// *************************************************************************
void GD_ImGui::ImGui_Set_Colours(void)
{
	ImGuiStyle* style = &ImGui::GetStyle();
	ImVec4* colors = style->Colors;

	colors[ImGuiCol_Text] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.94f, 0.94f, 0.94f, 1.00f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.94f, 0.94f, 0.94f, 1.00f);
	colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.30f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.98f, 0.98f, 0.98f, 0.53f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.69f, 0.69f, 0.69f, 0.80f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.49f, 0.49f, 0.49f, 0.80f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.46f, 0.54f, 0.80f, 0.60f);
	colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_Separator] = ImVec4(0.39f, 0.39f, 0.39f, 0.62f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.14f, 0.44f, 0.80f, 0.78f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.14f, 0.44f, 0.80f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.80f, 0.80f, 0.80f, 0.56f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	colors[ImGuiCol_Tab] = ImLerp(colors[ImGuiCol_Header], colors[ImGuiCol_TitleBgActive], 0.90f);
	colors[ImGuiCol_TabHovered] = colors[ImGuiCol_HeaderHovered];
	colors[ImGuiCol_TabActive] = ImLerp(colors[ImGuiCol_HeaderActive], colors[ImGuiCol_TitleBgActive], 0.60f);
	colors[ImGuiCol_TabUnfocused] = ImLerp(colors[ImGuiCol_Tab], colors[ImGuiCol_TitleBg], 0.80f);
	colors[ImGuiCol_TabUnfocusedActive] = ImLerp(colors[ImGuiCol_TabActive], colors[ImGuiCol_TitleBg], 0.40f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.45f, 0.00f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	colors[ImGuiCol_NavHighlight] = colors[ImGuiCol_HeaderHovered];
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.70f, 0.70f, 0.70f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.20f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
}

// *************************************************************************
// *	  				ImGui_Selection_Dlg Terry Bernie				   *
// *************************************************************************
void GD_ImGui::ImGui_Selection_Dlg(void)
{
	DialogBox(App->hInst, (LPCTSTR)IDD_IMGUIDLG, App->Fdlg, (DLGPROC)ImGui_Selection_Dlg_Proc);
}
// *************************************************************************
// *        		ImGui_Selection_Dlg_Proc  Terry	Bernie				   *
// *************************************************************************
LRESULT CALLBACK GD_ImGui::ImGui_Selection_Dlg_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		App->SetTitleBar(hDlg);
		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{

		return FALSE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}

	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDC_BUTSELECTEDITEM && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->Cl_ImGui->Show_Object_Data);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_IMGUI_COUNTERS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->Cl_ImGui->Show_ImGui_Counters);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{

		if (LOWORD(wParam) == IDC_BUTSELECTEDITEM)
		{
			if (App->Cl_ImGui->Show_Object_Data == 1)
			{
				App->Cl_ImGui->Show_Object_Data = 0;
			}
			else
			{
				App->Cl_ImGui->Update_StaticData();
				App->Cl_ImGui->Show_Object_Data = 1;
			}

			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_IMGUI_COUNTERS)
		{
			if (App->Cl_ImGui->Show_ImGui_Counters == 1)
			{
				App->Cl_ImGui->Show_ImGui_Counters = 0;
			}
			else
			{
				App->Cl_ImGui->Show_ImGui_Counters = 1;
			}

			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BUT_PROPEDITOR)
		{
			if (App->Cl_ImGui->Show_ImGui_Properties_Editor == 1)
			{
				App->Cl_ImGui->Show_ImGui_Properties_Editor = 0;
			}
			else
			{
				App->Cl_ImGui->Show_ImGui_Properties_Editor = 1;
			}

			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BUTPLAYER)
		{
			if (App->Cl_ImGui->Show_ImGui_Debug_Player == 1)
			{
				App->Cl_ImGui->Show_ImGui_Debug_Player = 0;
			}
			else
			{
				App->Cl_ImGui->Show_ImGui_Debug_Player = 1;
			}

			EndDialog(hDlg, LOWORD(wParam));
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
	}

	break;
	}
	return FALSE;
}


