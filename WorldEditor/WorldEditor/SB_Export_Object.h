/*
Copyright (c) 2023 World Editor -- HGT Software W.T.Flanigan H.C.Flanigan

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

class SB_Export_Object
{
public:
	SB_Export_Object();
	~SB_Export_Object();

	bool Create_ObjectFile(void);

protected:

	void Write_ObjectFile(void);
	void Write_ObjectFile_Commit(void);
	bool WriteMTLFile(void);
	bool Export_Textures(void);

	char OutputFolder[1024];

	char Object_FileName[255];
	char mtl_FileName[255];
	char Just_mtl_FileName[255];

	FILE *Write_OBJECTFILE;
	FILE *Write_MTLFile;
};

