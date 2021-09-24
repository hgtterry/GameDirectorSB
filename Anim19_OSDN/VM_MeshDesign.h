#pragma once
class VM_MeshDesign
{
public:
	VM_MeshDesign();
	~VM_MeshDesign();

	bool StartMeshDesign();

	Ogre::SceneNode*		MvNode;

protected:

	static LRESULT CALLBACK MeshDesign_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	bool Set_OgreWindow(void);
	void Close_OgreWindow(void);

	HWND MeshView_Hwnd;

	Ogre::Entity*			MvEnt;

	Ogre::RenderWindow* MeshView_Window;
	Ogre::SceneManager* mSceneMgrMeshView;
	Ogre::Camera*		mCameraMeshView;
	Ogre::SceneNode*	CamNode;
};

