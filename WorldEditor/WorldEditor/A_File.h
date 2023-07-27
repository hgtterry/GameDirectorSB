#pragma once

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

class SB_File_WE
{
public:
	SB_File_WE(void);
	~SB_File_WE(void);

	bool  ImportFile (const char *PathName, const geVec3d *location);
	Level* Level_CreateFromFile (const char *FileName, const char **ErrMsg, const char *DefaultHeadersDir,const char *DefaultActorsDir, const char *DefaultPawnIni);

	bool Load(const char *FileName);
	bool Save(const char* FileName);

	bool Open_3dt_File(bool UseDialogLoader);

	char FileName_3dt[MAX_PATH];
	char PathFileName_3dt[MAX_PATH];

private:

	bool Open_File_Dialog(char* Extension, char* Title, char* StartDirectory);

	void CreateNewTemplateBrush(Brush *pBrush);
	void AddCameraEntityToLevel(void);
	bool Level_WriteToFile2(Level* pLevel, const char* Filename);

	void Get_CurrentDocument();

	CFusionDoc			*m_pDoc;
};
