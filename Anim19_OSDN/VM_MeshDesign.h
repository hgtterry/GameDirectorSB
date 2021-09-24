#pragma once
class VM_MeshDesign
{
public:
	VM_MeshDesign();
	~VM_MeshDesign();

	bool StartMeshDesign();

protected:

	static LRESULT CALLBACK MeshDesign_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
};

