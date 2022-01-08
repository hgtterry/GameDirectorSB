#pragma once
class ME_App
{
public:

	ME_App(void);
	~ME_App(void);

	char EquityDirecory_FullPath[MAX_PATH];
};

extern ME_App* App;

