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
class Bass_Front_Dialog
{
public:
	Bass_Front_Dialog();
	~Bass_Front_Dialog();

	void Render_Front_Dlg(void);

	bool Use_Front_Dlg_Flag;
	bool Show_Front_Dlg_Flag;

	float PosX; 
	float PosY;

	bool Game_Running_Flag;

	Ogre::Vector4 Text_Colour;
	Ogre::Vector4 BackGround_Colour;

};

