#pragma once
class ME_Panels
{
public:
	ME_Panels();
	~ME_Panels();

	bool Move_FileView_Window(void);
	bool Place_GlobalGroups(void);

	bool Resize(void);

	bool ResizeOgre_Window(void);

	void Enable_Panels(int show);
	void Show_Panels(int show);
	void Hide_Panels();

private:

};

