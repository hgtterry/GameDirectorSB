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

