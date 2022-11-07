#pragma once
class GD_SoundMgr
{
public:
	GD_SoundMgr(void);
	~GD_SoundMgr(void);

	
	bool InitSound_Defaults(int Index);
	bool GetSoundFiles(HWND hDlg);

	char mSoundFile[255];

	char Default_Folder[1024];

	bool IsObject;

	irrklang::ISoundEngine* SoundEngine; 
	irrklang::ISound* SndFile;
	Ogre::Real SndVolume;
};

