/*
Copyright (c) Vima19 Inflanite Software W.T.Flanigan H.C.Flanigan

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

class SB_SoundMgr
{
public:
	SB_SoundMgr(void);
	~SB_SoundMgr(void);

	static LRESULT CALLBACK Dialog_SoundFile_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	bool Dialog_SoundFile();
	bool InitSound_Defaults(int Index);
	bool GetSoundFiles(HWND hDlg,char *Extention);
	bool Remeber_SoundFile(char* File);

	char mSoundFile[255];
	char Current_Object_Sound[255];

	char Default_Folder[1024];

	bool IsObject;
	bool IsCancelled;

	irrklang::ISoundEngine* SoundEngine; 
	irrklang::ISound* SndFile;
	Ogre::Real SndVolume;

	int SoundFile_Count;
	std::vector<std::string> Sound_File;

protected:

	char m_Current_Sound_file[MAX_PATH];
};

