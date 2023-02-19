/*
Copyright (c) 2022 - 2023 GameDirectorSB and EquityME -- HGTInflanite Software W.T.Flanigan H.C.Flanigan

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software. If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.

3. This notice may not be removed or altered from any source
distribution.
*/

#include "stdafx.h"
#include "GD19_App.h"
#include "SB_Gui_Properties.h"

#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"

SB_Gui_Properties::SB_Gui_Properties()
{
	Current_Object = -1;
	Properties_Panel_StartPos = 0;
	Show_Properties_Panel_Flag = 1;
	Props_Panel_PosX = 500;
	Props_Panel_PosY= 500;
}

SB_Gui_Properties::~SB_Gui_Properties()
{
}

bool SB_Gui_Properties::LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height)
{
//	// Load from file
//	int image_width = 0;
//	int image_height = 0;
//	unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
//	if (image_data == NULL)
//		return false;
//
//	// Create a OpenGL texture identifier
//	GLuint image_texture;
//	glGenTextures(1, &image_texture);
//	glBindTexture(GL_TEXTURE_2D, image_texture);
//
//	// Setup filtering parameters for display
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	
//
//	// Upload pixels into texture
//#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
//	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
//#endif
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
//	stbi_image_free(image_data);
//
//	*out_texture = image_texture;
//	*out_width = image_width;
//	*out_height = image_height;

	return true;
}
// *************************************************************************
// *		Start_Properties_Panel:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void SB_Gui_Properties::Start_Properties_Panel(void)
{
	Show_Properties_Panel_Flag = 1;
}

// *************************************************************************
// *		Properties_Panel_Gui:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void SB_Gui_Properties::Properties_Panel_Gui(void)
{
	ImGui::SetNextWindowPos(ImVec2(Props_Panel_PosX, Props_Panel_PosY),ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(320, 350), ImGuiCond_FirstUseEver);

	ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(208, 230, 252, 255));

	ImGuiStyle* style = &ImGui::GetStyle();

	if (!ImGui::Begin("Properties_Panel", &Show_Properties_Panel_Flag, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar))
	{
		ImGui::End();
	}
	else
	{
		Current_Object = App->SBC_Properties->Current_Selected_Object;
		
		if (App->SBC_Scene->Scene_Loaded == 1)
		{
			ImGui::Text("Name           %s", App->SBC_Scene->B_Object[Current_Object]->Mesh_Name);
			ImGui::Text("Mesh File     %s", App->SBC_Scene->B_Object[Current_Object]->Mesh_FileName);
			ImGui::Text("Material       %s", App->SBC_Scene->B_Object[Current_Object]->Material_File);

			//if (ImGui::Button("Test"))
			//{
			//	bool ret = LoadTextureFromFile("pole.jpg", &my_image_texture, &my_image_width, &my_image_height);
			//	if (ret == 0)
			//	{
			//		Debug
			//	}

			//	ImVec2 uv_min = ImVec2(0.0f, 0.0f);                 // Top-left
			//	ImVec2 uv_max = ImVec2(1.0f, 1.0f);                 // Lower-right
			//	ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);   // No tint
			//	ImVec4 border_col = ImVec4(1.0f, 1.0f, 1.0f, 0.5f); // 50% opaque white

			//	//ImDrawList::AddImage(my_image_texture);
			//	ImGui::GetBackgroundDrawList()->AddImage((void*)(intptr_t)my_image_texture, ImVec2(my_image_width, my_image_height), ImVec2(0, 0));
			//	ImGui::Text("pointer = %p", my_image_texture);
			//	ImGui::Text("size = %d x %d", my_image_width, my_image_height);

			//	//App->SBC_Ogre->m_imgui.
			//	//Ogre::ResourceHandle texHandle = Ogre::TextureManager::getSingleton().getByName("concrete.bmp")->getHandle();
			////	ImGui::Image((ImTextureID)texHandle, ImVec2(512, 512));
			//	//ImGui::Image((void*)(intptr_t)my_image_texture, ImVec2(my_image_width, my_image_height), uv_min, uv_max, tint_col, border_col);

			//	//(ImTextureID)
			//	//ImGui::Image(my_tex_id, ImVec2(my_tex_w, my_tex_h), uv_min, uv_max, tint_col, border_col);
			//}
			//Ogre::ResourceHandle texHandle = Ogre::TextureManager::getSingleton().getByName("concrete.bmp")->getHandle();
			//ImGui::Image((ImTextureID)texHandle, ImVec2(512, 512));

		}

		if (Properties_Panel_StartPos == 0)
		{
			ImVec2 Size = ImGui::GetWindowSize();
			Props_Panel_PosX = ((float)App->SBC_Ogre->OgreListener->View_Width) - (Size.x) - 250;
			Props_Panel_PosY = 10;// ((float)App->SBC_Ogre->OgreListener->View_Height) - (Size.y) - 590;
			ImGui::SetWindowPos("Properties_Panel", ImVec2(Props_Panel_PosX, Props_Panel_PosY));

			Properties_Panel_StartPos = 1;
		}

		ImGui::PopStyleColor();
		ImGui::End();
	}
}

// *************************************************************************
// *		Close_Properties_Panel:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void SB_Gui_Properties::Close_Properties_Panel(void)
{
	Show_Properties_Panel_Flag = 0;
}
