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

#pragma once
class SB_Gui_Properties
{
public:
	SB_Gui_Properties();
	~SB_Gui_Properties();

	void Start_Properties_Panel(void);
	void Properties_Panel_Gui(void);
	void Close_Properties_Panel(void);
	bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height);

	bool Show_Properties_Panel_Flag;
	bool Properties_Panel_StartPos;

	int Current_Object;

	float Props_Panel_PosX;
	float Props_Panel_PosY;

	int my_image_width = 0;
	int my_image_height = 0;
	GLuint my_image_texture = 0;
};

