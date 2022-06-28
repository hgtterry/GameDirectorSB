#pragma once
class ME_Panels
{
public:
	ME_Panels();
	~ME_Panels();

	bool Move_FileView_Window(void);
	bool Place_GlobalGroups(void);

	bool Resize(void);

	void Enable_Panels(int show);
private:

};

