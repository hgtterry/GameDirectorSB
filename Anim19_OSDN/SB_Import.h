/*
Copyright (c) 2021 Stage Builder and Equity -- Inflanite Software W.T.Flanigan H.C.Flanigan

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
class SB_Import
{
public:
	SB_Import();
	~SB_Import();

	bool Assimp_Loader(char* Extension, char* Extension2);
	bool Genesis3D_Loader(void);
	bool WorldEditor_Loader(void);
	bool Ogre_Loader(char* Extension, char* Extension2);

	bool Bullet_Load_Room(char* Extension, char* Extension2);

	void Reload_FromResentFiles(char* ResentPathAndFile);
};
