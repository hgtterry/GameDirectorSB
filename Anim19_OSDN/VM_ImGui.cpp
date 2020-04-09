#include "stdafx.h"
#include "GD19_App.h"
#include "VM_ImGui.h"


VM_ImGui::VM_ImGui()
{
	StartPos = 0;
	Show_FPS = 1;
	Show_ImGui_Test = 0;
	Show_Rotation = 0;
	Show_Position = 0;
	Show_Scale = 0;
	Show_Image = 0;
	Show_Group_List = 0;

	Model_XTranslate = 2;
	Model_YTranslate = 2;
	Model_ZTranslate = 2;

	Test = 180;

	Block = 0;
}


VM_ImGui::~VM_ImGui()
{
}

// *************************************************************************
// *					Reset_Class  Terry Bernie						   *
// *************************************************************************
void VM_ImGui::Reset_Class(void)
{
	StartPos = 0;
	Show_FPS = 1;
	Show_ImGui_Test = 0;
	Show_Rotation = 0;
	Show_Position = 0;
	Show_Scale = 0;

	Model_XTranslate = 2;
	Model_YTranslate = 2;
	Model_ZTranslate = 2;

	Test = 180;
}
// *************************************************************************
// *					Render_ImGui  Terry Bernie						   *
// *************************************************************************
void VM_ImGui::Render_ImGui(void)
{

	if (Show_FPS == 1)
	{
		ImGui_FPS();
	}

	if (Show_ImGui_Test == 1)
	{
		ImGui::ShowDemoWindow();
	}

	if (Show_Rotation == 1)
	{
		ImGui_Rotation();
	}

	if (Show_Position == 1)
	{
		ImGui_Position();
	}

	if (Show_Scale == 1)
	{
		ImGui_Scale();
	}

	if (Show_Image == 1)
	{
		ImGui_Image();
	}

	if (Show_Group_List == 1)
	{
		ImGui_GroupList();
	}

}

// *************************************************************************
// *						ImGui_FPS  Terry Bernie						   *
// *************************************************************************
void VM_ImGui::ImGui_FPS(void)
{
	if (!ImGui::Begin("Ogre Data", &Show_FPS, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::End();
	}
	else
	{
		if (StartPos == 0)
		{
			ImGui::SetWindowPos("Ogre Data", ImVec2(10, 550));
			ImGui::SetWindowSize(ImVec2(350, 90));
			StartPos = 1;
		}

		ImGui::Spacing();
		ImGui::Text("FPS average %.1f ms/frame (%.0f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		//ImGui::PopFont();

		ImGui::End();
	}
}

// *************************************************************************
// *						ImGui_Rotation  Terry Bernie				   *
// *************************************************************************
void VM_ImGui::ImGui_Rotation(void)
{
	ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin("Rotation", &Show_Rotation, ImGuiWindowFlags_NoSavedSettings |ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::End();
	}
	else
	{

		ImGui::Text("  X    Y    Z");

		if (ImGui::Button("X+", ImVec2(70, 0)))
		{
		}
		ImGui::SameLine();
		if (ImGui::Button("Y+", ImVec2(70, 0)))
		{
		}
		ImGui::SameLine();
		if (ImGui::Button("Z+", ImVec2(70, 0)))
		{
		}
		
		ImGui::VSliderFloat("##RotationX", ImVec2(70, 260),  &App->CL_Vm_Genesis3D->Actor_Rotation.X, 0.0f, 360.0f, "%.2f\nDeg");
		ImGui::SameLine();
		ImGui::VSliderFloat("##RotationY", ImVec2(70, 260), &App->CL_Vm_Genesis3D->Actor_Rotation.Y, 0.0f, 360.0f, "%.2f\nDeg");
		ImGui::SameLine();
		ImGui::VSliderFloat("##RotationZ", ImVec2(70, 260), &App->CL_Vm_Genesis3D->Actor_Rotation.Z, 0.0f, 360.0f, "%.2f\nDeg");
		
		if (ImGui::Button("X-", ImVec2(70, 0)))
		{
		}
		ImGui::SameLine();
		if (ImGui::Button("Y-", ImVec2(70, 0)))
		{
		}
		ImGui::SameLine();
		if (ImGui::Button("Z-", ImVec2(70, 0)))
		{
		}

		if (App->CL_Vm_Genesis3D->Actor_Rotation.X > App->CL_Vm_Genesis3D->Actor_Rotation_Old.X || App->CL_Vm_Genesis3D->Actor_Rotation.X < App->CL_Vm_Genesis3D->Actor_Rotation_Old.X)
		{
			App->CL_Vm_Genesis3D->MoveActor();
			App->CL_Vm_Genesis3D->Actor_Rotation_Old.X = App->CL_Vm_Genesis3D->Actor_Rotation.X;
		}

		if (App->CL_Vm_Genesis3D->Actor_Rotation.Y > App->CL_Vm_Genesis3D->Actor_Rotation_Old.Y || App->CL_Vm_Genesis3D->Actor_Rotation.Y < App->CL_Vm_Genesis3D->Actor_Rotation_Old.Y)
		{
			App->CL_Vm_Genesis3D->MoveActor();
			App->CL_Vm_Genesis3D->Actor_Rotation_Old.Y = App->CL_Vm_Genesis3D->Actor_Rotation.Y;
		}

		if (App->CL_Vm_Genesis3D->Actor_Rotation.Z > App->CL_Vm_Genesis3D->Actor_Rotation_Old.Z || App->CL_Vm_Genesis3D->Actor_Rotation.Z < App->CL_Vm_Genesis3D->Actor_Rotation_Old.Z)
		{
			App->CL_Vm_Genesis3D->MoveActor();
			App->CL_Vm_Genesis3D->Actor_Rotation_Old.Z = App->CL_Vm_Genesis3D->Actor_Rotation.Z;
		}
		
		ImGui::End();
	}
}

// *************************************************************************
// *						ImGui_Position  Terry Bernie				   *
// *************************************************************************
void VM_ImGui::ImGui_Position(void)
{
	ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin("Position", &Show_Position, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::End();
	}
	else
	{

		geVec3d pos = App->CL_Vm_Genesis3D->Actor_Position;
		ImGui::Text("X %.3f Y %.3f Z %.3f", pos.X, pos.Y, pos.Z);
	
		ImGui::Spacing();

		// ------------------------------------------ Position X
		ImGui::Text("X ");
		ImGui::SameLine();

		float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
		ImGui::PushButtonRepeat(true);
		if (ImGui::ArrowButton("##left", ImGuiDir_Left))
		{
			App->CL_Vm_Genesis3D->Actor_Position.X += Model_XTranslate;
			App->CL_Vm_Genesis3D->MoveActor();
		}
		ImGui::SameLine(0.0f, spacing);
		if (ImGui::ArrowButton("##right", ImGuiDir_Right))
		{
			App->CL_Vm_Genesis3D->Actor_Position.X -= Model_XTranslate;
			App->CL_Vm_Genesis3D->MoveActor();
		}
		ImGui::PopButtonRepeat();

		ImGui::SameLine();
		ImGui::SetNextItemWidth(100);
		const char* XitemsX[] = { "1", "2", "5", "10", "20" };
		static int XitemX = 1;
		bool Changed = ImGui::Combo("Step X", &XitemX, XitemsX, IM_ARRAYSIZE(XitemsX));   // Combo using proper array. You can also pass a callback to retrieve array value, no need to create/copy an array just for that.
		if (Changed == 1)
		{
			Model_XTranslate = (float)atof(XitemsX[XitemX]);
		}

		// ------------------------------------------ Position y
		ImGui::Text("Y ");
		ImGui::SameLine();

		float spacing2 = ImGui::GetStyle().ItemInnerSpacing.x;
		ImGui::PushButtonRepeat(true);
		if (ImGui::ArrowButton("##leftY", ImGuiDir_Left))
		{
			App->CL_Vm_Genesis3D->Actor_Position.Y += Model_YTranslate;
			App->CL_Vm_Genesis3D->MoveActor();
		}
		ImGui::SameLine(0.0f, spacing2);
		if (ImGui::ArrowButton("##rightY", ImGuiDir_Right))
		{
			App->CL_Vm_Genesis3D->Actor_Position.Y -= Model_YTranslate;
			App->CL_Vm_Genesis3D->MoveActor();
		}
		ImGui::PopButtonRepeat();

		ImGui::SameLine();
		ImGui::SetNextItemWidth(100);
		const char* XitemsY[] = { "1", "2", "5", "10", "20" };
		static int XitemY = 1;
		bool ChangedY = ImGui::Combo("Step Y", &XitemY, XitemsY, IM_ARRAYSIZE(XitemsY));   // Combo using proper array. You can also pass a callback to retrieve array value, no need to create/copy an array just for that.
		if (ChangedY == 1)
		{
			Model_YTranslate = (float)atof(XitemsY[XitemY]);
		}

		// ------------------------------------------ Position z
		ImGui::Text("Z ");
		ImGui::SameLine();

		float spacing3 = ImGui::GetStyle().ItemInnerSpacing.x;
		ImGui::PushButtonRepeat(true);
		if (ImGui::ArrowButton("##leftZ", ImGuiDir_Left))
		{
			App->CL_Vm_Genesis3D->Actor_Position.Z += Model_ZTranslate;
			App->CL_Vm_Genesis3D->MoveActor();
		}
		ImGui::SameLine(0.0f, spacing3);
		if (ImGui::ArrowButton("##rightZ", ImGuiDir_Right))
		{
			App->CL_Vm_Genesis3D->Actor_Position.Z -= Model_ZTranslate;
			App->CL_Vm_Genesis3D->MoveActor();
		}
		ImGui::PopButtonRepeat();

		ImGui::SameLine();
		ImGui::SetNextItemWidth(100);
		const char* XitemsZ[] = { "1", "2", "5", "10", "20" };
		static int XitemZ = 1;
		bool ChangedZ = ImGui::Combo("Step Z", &XitemZ, XitemsZ, IM_ARRAYSIZE(XitemsZ));   // Combo using proper array. You can also pass a callback to retrieve array value, no need to create/copy an array just for that.
		if (ChangedZ == 1)
		{
			Model_ZTranslate = (float)atof(XitemsZ[XitemZ]);
		}
	
		ImGui::End();
	}
}

// *************************************************************************
// *						ImGui_Scale  Terry Bernie					   *
// *************************************************************************
void VM_ImGui::ImGui_Scale(void)
{
	ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin("Scale", &Show_Scale , ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::End();
	}
	else
	{
		//ImGui::Text("Scale");

		ImGui::SameLine();
		ImGui::Checkbox("Lock Axis", &App->Cl_Dimensions->Set_ScaleLock);
		if (App->Cl_Dimensions->Set_ScaleLock == 1)
		{
			/*Ogre::Vector3 scale = App->Cl_Scene_Data->Cl_Object[index]->OgreNode->getScale();
			ImGui::Text("X %.3f Y %.3f Z %.3f", scale.x, scale.y, scale.z);*/
			ImGui::Spacing();

			ImGui::Text("All ");
			ImGui::SameLine();

			float spacingSX = ImGui::GetStyle().ItemInnerSpacing.x;
			ImGui::PushButtonRepeat(true);
			if (ImGui::ArrowButton("##LeftSX", ImGuiDir_Left))
			{
				float Delta = 0.5;// App->Cl_Dimensions->Model_XScale;

				App->CL_Vm_Genesis3D->ScaleActor(Delta, Delta, Delta);
				//Ogre::Vector3 Scale = App->Cl_Scene_Data->Cl_Object[index]->Mesh_Scale;
				//Scale.x += Delta;
				//Scale.y += Delta;
				//Scale.z += Delta;
				//App->Cl_Scene_Data->Cl_Object[index]->Mesh_Scale = Scale;
				//App->Cl_Scene_Data->Cl_Object[index]->OgreNode->setScale(Scale);

				//Scale = App->Cl_Scene_Data->Cl_Object[index]->Physics_Scale;
				//Scale.x += Delta;
				//Scale.y += Delta;
				//Scale.z += Delta;
				//App->Cl_Scene_Data->Cl_Object[index]->Physics_Scale = Scale;
				//App->Cl_Scene_Data->Cl_Object[index]->bt_body->getCollisionShape()->setLocalScaling(btVector3(Scale.x, Scale.y, Scale.z));

				////App->Cl_Dimensions->Set_Physics_Position(index);
				//App->Cl_Dimensions->UpDate_Physics_And_Visuals(index);
			}
			ImGui::SameLine(0.0f, spacingSX);
			if (ImGui::ArrowButton("##rightSX", ImGuiDir_Right))
			{
				float Delta = 1;// App->Cl_Dimensions->Model_XScale;

				App->CL_Vm_Genesis3D->ScaleActor(Delta, Delta, Delta);
				//Scale.x -= Delta;
				//Scale.y -= Delta;
				//Scale.z -= Delta;
				//App->Cl_Scene_Data->Cl_Object[index]->Mesh_Scale = Scale;
				//App->Cl_Scene_Data->Cl_Object[index]->OgreNode->setScale(Scale);

				//Scale = App->Cl_Scene_Data->Cl_Object[index]->Physics_Scale;
				//Scale.x -= Delta;
				//Scale.y -= Delta;
				//Scale.z -= Delta;
				//App->Cl_Scene_Data->Cl_Object[index]->Physics_Scale = Scale;
				//App->Cl_Scene_Data->Cl_Object[index]->bt_body->getCollisionShape()->setLocalScaling(btVector3(Scale.x, Scale.y, Scale.z));

				////App->Cl_Dimensions->Set_Physics_Position(index);
				//App->Cl_Dimensions->UpDate_Physics_And_Visuals(index);
			}
			ImGui::PopButtonRepeat();
		}
		else
		{
			/*Ogre::Vector3 scale = App->Cl_Scene_Data->Cl_Object[index]->OgreNode->getScale();
			ImGui::Text("X %.3f Y %.3f Z %.3f", scale.x, scale.y, scale.z);*/
			ImGui::Spacing();

			// Scale X
			ImGui::Text("X ");
			ImGui::SameLine();

			if (ImGui::Button("SX + "))
			{
				//float Delta = 0.2;// App->Cl_Dimensions->Model_XScale;
				//Ogre::Vector3 Scale = App->Cl_Scene_Data->Cl_Object[index]->Mesh_Scale;
				//Scale.x += Delta;
				//App->Cl_Scene_Data->Cl_Object[index]->Mesh_Scale = Scale;
				//App->Cl_Scene_Data->Cl_Object[index]->OgreNode->setScale(Scale);

				//Scale = App->Cl_Scene_Data->Cl_Object[index]->Physics_Scale;
				//Scale.x += Delta;
				//App->Cl_Scene_Data->Cl_Object[index]->Physics_Scale = Scale;
				//App->Cl_Scene_Data->Cl_Object[index]->bt_body->getCollisionShape()->setLocalScaling(btVector3(Scale.x, Scale.y, Scale.z));

				//App->Cl_Dimensions->Set_Physics_Position(index);
				//App->Cl_Dimensions->UpDate_Physics_And_Visuals(index);
			}

			ImGui::SameLine();

			if (ImGui::Button("SX - "))
			{
				//float Delta = 0.2;// App->Cl_Dimensions->Model_XScale;
				//Ogre::Vector3 Scale = App->Cl_Scene_Data->Cl_Object[index]->Mesh_Scale;
				//Scale.x -= Delta;
				//App->Cl_Scene_Data->Cl_Object[index]->Mesh_Scale = Scale;
				//App->Cl_Scene_Data->Cl_Object[index]->OgreNode->setScale(Scale);

				//Scale = App->Cl_Scene_Data->Cl_Object[index]->Physics_Scale;
				//Scale.x -= Delta;
				//App->Cl_Scene_Data->Cl_Object[index]->Physics_Scale = Scale;
				//App->Cl_Scene_Data->Cl_Object[index]->bt_body->getCollisionShape()->setLocalScaling(btVector3(Scale.x, Scale.y, Scale.z));

				//App->Cl_Dimensions->Set_Physics_Position(index);
				//App->Cl_Dimensions->UpDate_Physics_And_Visuals(index);

			}

			// Scale Y
			ImGui::Text("Y ");
			ImGui::SameLine();

			if (ImGui::Button("SY + "))
			{
				//float Delta = 0.2;// App->Cl_Dimensions->Model_XScale;
				//Ogre::Vector3 Scale = App->Cl_Scene_Data->Cl_Object[index]->Mesh_Scale;
				//Scale.y += Delta;
				//App->Cl_Scene_Data->Cl_Object[index]->Mesh_Scale = Scale;
				//App->Cl_Scene_Data->Cl_Object[index]->OgreNode->setScale(Scale);

				//Scale = App->Cl_Scene_Data->Cl_Object[index]->Physics_Scale;
				//Scale.y += Delta;
				//App->Cl_Scene_Data->Cl_Object[index]->Physics_Scale = Scale;
				//App->Cl_Scene_Data->Cl_Object[index]->bt_body->getCollisionShape()->setLocalScaling(btVector3(Scale.x, Scale.y, Scale.z));

				//App->Cl_Dimensions->Set_Physics_Position(index);
				//App->Cl_Dimensions->UpDate_Physics_And_Visuals(index);
			}

			ImGui::SameLine();

			if (ImGui::Button("SY - "))
			{
				//float Delta = 0.2;// App->Cl_Dimensions->Model_XScale;
				//Ogre::Vector3 Scale = App->Cl_Scene_Data->Cl_Object[index]->Mesh_Scale;
				//Scale.y -= Delta;
				//App->Cl_Scene_Data->Cl_Object[index]->Mesh_Scale = Scale;
				//App->Cl_Scene_Data->Cl_Object[index]->OgreNode->setScale(Scale);

				//Scale = App->Cl_Scene_Data->Cl_Object[index]->Physics_Scale;
				//Scale.y -= Delta;
				//App->Cl_Scene_Data->Cl_Object[index]->Physics_Scale = Scale;
				//App->Cl_Scene_Data->Cl_Object[index]->bt_body->getCollisionShape()->setLocalScaling(btVector3(Scale.x, Scale.y, Scale.z));

				//App->Cl_Dimensions->Set_Physics_Position(index);
				//App->Cl_Dimensions->UpDate_Physics_And_Visuals(index);
			}

			// Scale Z
			ImGui::Text("Z ");
			ImGui::SameLine();

			if (ImGui::Button("SZ + "))
			{
				//float Delta = 0.2;// App->Cl_Dimensions->Model_XScale;
				//Ogre::Vector3 Scale = App->Cl_Scene_Data->Cl_Object[index]->Mesh_Scale;
				//Scale.z += Delta;
				//App->Cl_Scene_Data->Cl_Object[index]->Mesh_Scale = Scale;
				//App->Cl_Scene_Data->Cl_Object[index]->OgreNode->setScale(Scale);

				//Scale = App->Cl_Scene_Data->Cl_Object[index]->Physics_Scale;
				//Scale.z += Delta;
				//App->Cl_Scene_Data->Cl_Object[index]->Physics_Scale = Scale;
				//App->Cl_Scene_Data->Cl_Object[index]->bt_body->getCollisionShape()->setLocalScaling(btVector3(Scale.x, Scale.y, Scale.z));

				//App->Cl_Dimensions->Set_Physics_Position(index);
				//App->Cl_Dimensions->UpDate_Physics_And_Visuals(index);
			}

			ImGui::SameLine();

			if (ImGui::Button("SZ - "))
			{
				//float Delta = 0.2;// App->Cl_Dimensions->Model_XScale;
				//Ogre::Vector3 Scale = App->Cl_Scene_Data->Cl_Object[index]->Mesh_Scale;
				//Scale.z -= Delta;
				//App->Cl_Scene_Data->Cl_Object[index]->Mesh_Scale = Scale;
				//App->Cl_Scene_Data->Cl_Object[index]->OgreNode->setScale(Scale);

				//Scale = App->Cl_Scene_Data->Cl_Object[index]->Physics_Scale;
				//Scale.z -= Delta;
				//App->Cl_Scene_Data->Cl_Object[index]->Physics_Scale = Scale;
				//App->Cl_Scene_Data->Cl_Object[index]->bt_body->getCollisionShape()->setLocalScaling(btVector3(Scale.x, Scale.y, Scale.z));

				//App->Cl_Dimensions->Set_Physics_Position(index);
				//App->Cl_Dimensions->UpDate_Physics_And_Visuals(index);
			}
		}
		ImGui::End();
	}
}


// *************************************************************************
// *						ImGui_Image  Terry Bernie					   *
// *************************************************************************
void VM_ImGui::ImGui_Image(void)
{
	//ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin("Image", &Show_Image, ImGuiWindowFlags_NoSavedSettings))
	{
		ImGui::End();
	}
	else
	{
		if (App->CL_Vm_Textures->g_Texture[0] == NULL)
		{

		}
		else
		{
			
			/*int MatIndex = App->CL_Vm_Model->MatIndex_Data[0];
			glBindTexture(GL_TEXTURE_2D, App->CL_Vm_Textures->g_Texture[MatIndex]);

			ImGui::Text("pointer = %p", App->CL_Vm_Textures->g_Texture[MatIndex]);
			ImGui::Text("size = %d x %d", 256, 256);
			ImGui::Image((void*)(intptr_t)App->CL_Vm_Textures->g_Texture[MatIndex], ImVec2(256.0f, 256.0f));
			ImGui::End();*/
		}
	}
}

// *************************************************************************
// *						ImGui_GroupList  Terry Bernie				   *
// *************************************************************************
void VM_ImGui::ImGui_GroupList(void)
{
	static int selected_Players = -1;

	ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin("Groups", &Show_Group_List, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::End();
	}
	else
	{
		int GroupCount = App->CL_Vm_Model->GroupCount;
		ImGui::Text("Group Count %i", GroupCount);

		ImGui::Separator();
		ImGui::Spacing();

		int Count = 0;
		while (Count < GroupCount)
		{
			ImGui::Bullet();
			if (ImGui::Selectable(App->CL_Vm_Model->S_MeshGroup[Count]->GroupName, selected_Players == Count))
			{
				selected_Players = Count;
				Block = 1;
			}

			Count++;
		}

		if (Block == 1)
		{
			App->CL_Vm_Groups->Update_Groups_Dialog(selected_Players);
			Block = 0;
		}

		ImGui::End();

	}
}
