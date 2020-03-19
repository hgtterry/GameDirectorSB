#pragma once
class GD19_Resources
{
public:
	GD19_Resources(void);
	~GD19_Resources(void);

	void Start_Resources(void);

	void Start_List_Folders(HWND List,char *FileName,bool ListDlg);
	void List_Folders(HWND List,char *StartFolder,char *FileName,bool ListDlg);

	void List_MeshMaterials(HWND List);

	void Unload_Materials(void);
	void Remove_OblectMesh(void);

protected:
	static LRESULT CALLBACK Resources_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	bool CreateListGeneral_FX(HWND hDlg);
	bool ShowAllMaterials();
	bool SearchFolders(char* File,char* StartFolder);
	bool FindPath(char* SubFolder,char* File,char* StartFolder);
	bool FindPath_New(char* File,char* Folder);

	bool ShowUsedMaterials();

	bool ShowAllTextures();
	bool ShowAllMeshes();

	char ResourcePath[2048];

	bool Active_MeshMaterials;
	bool Active_Textures;

	HWND FX_General_hLV;
};

