#include "stdafx.h"
#include "GD19_App.h"
#include "resource.h"
#include "SB_Equity.h"


SB_Equity::SB_Equity()
{
	MeshView_Hwnd = nullptr;
	MeshViewDialog_Hwnd = nullptr;

	MeshView_Window = nullptr;
	mSceneMgrMeshView = nullptr;
	CamNode = nullptr;

	MvNode = nullptr;
	MvEnt = nullptr;

	GridManual = nullptr;
	GridNode = nullptr;

	HairManual = nullptr;
	HairNode = nullptr;

	ShowGridFlag = 1;
	ShowDivisions = 1;
	ShowHair = 1;

	YAxis_min = -8;
	YAxis_max = 8;

	ZAxis_min = -8;
	ZAxis_max = 8;

	XAxis_min = -8;
	XAxis_max = 8;

	HairExtend = 8;

	Scale_X = 4;
	Scale_Y = 4;
	Scale_Z = 4;

	Division_X = 2;
	Division_Y = 2;
	Division_Z = 2;

	Model_Loaded = 0;

	ColourHairZ = ColourValue(1, 0, 0, 1);
	ColourHairX = ColourValue(0, 0, 1, 1);
	ColourHairY = ColourValue(0, 1, 0, 1);
	ColourMain = ColourValue(0.7, 0.7, 0, 0.6);
	ColourDivision = ColourValue(1, 1, 1, 0.4);
}


SB_Equity::~SB_Equity()
{
}

// *************************************************************************
// *				StartMeshDesign  Terry	Bernie						   *
// *************************************************************************
bool SB_Equity::StartMeshDesign()
{
	App->RenderBackGround = 1;

	DialogBox(App->hInst, (LPCTSTR)IDD_EQUITY, App->Fdlg, (DLGPROC)MeshDesign_Proc);

	App->RenderBackGround = 0;
	App->Cl19_Ogre->OgreListener->GD_MeshViewer_Running = 0;
	Close_OgreWindow();
	return 1;
}

// *************************************************************************
// *						MeshDesign_Proc Terry Bernie				   *
// *************************************************************************
LRESULT CALLBACK SB_Equity::MeshDesign_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{

		HWND Ogre_Hwnd = GetDlgItem(hDlg, IDC_OGREWIN2);

		App->SBC_Equity->MeshView_Hwnd = GetDlgItem(hDlg, IDC_OGREWIN2);
		App->SBC_Equity->MeshViewDialog_Hwnd = hDlg;

		App->SBC_Equity->Init_Bmps_Globals();

		App->SBC_Equity->Set_OgreWindow();

		Ogre::Root::getSingletonPtr()->renderOneFrame();
		Ogre::Root::getSingletonPtr()->renderOneFrame();


		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{
		/*if (GetDlgItem(hDlg, IDC_STNAME) == (HWND)lParam)
		{
		SetBkColor((HDC)wParam, RGB(0, 255, 0));
		SetTextColor((HDC)wParam, RGB(0, 0, 255));
		SetBkMode((HDC)wParam, TRANSPARENT);
		return (UINT)App->AppBackground;
		}*/

		return FALSE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}
	case WM_HSCROLL:
	{


		return 1;
	}

	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		/*if (some_item->idFrom == IDC_CONE && some_item->code == NM_CUSTOMDRAW)
		{
		LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
		App->Custom_Button_Toggle(item, App->Cl_Mesh_Viewer->Selected_Shape_Cone);
		return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDOK && some_item->code == NM_CUSTOMDRAW)
		{
		LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
		App->Custom_Button_Normal(item);
		return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDCANCEL && some_item->code == NM_CUSTOMDRAW)
		{
		LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
		App->Custom_Button_Normal(item);
		return CDRF_DODEFAULT;
		}*/

		return CDRF_DODEFAULT;
	}

	case WM_MOUSEWHEEL:
	{
		int zDelta = (short)HIWORD(wParam);    // wheel rotation

		if (zDelta > 0)
		{
			App->CL_WE_Listener_E15->Wheel = -1;
		}
		else if (zDelta < 0)
		{
			App->CL_WE_Listener_E15->Wheel = 1;
		}

		return 1;
	}

	case WM_LBUTTONDOWN: // BERNIE_HEAR_FIRE 
	{

		if (App->OgreStarted == 1)
		{

			SetCapture(App->SBC_Equity->MeshViewDialog_Hwnd);// Bernie
			SetCursorPos(500, 500);
			App->CL_WE_Listener_E15->Pl_LeftMouseDown = 1;
			App->CUR = SetCursor(NULL);

			return 1;
		}

		return 1;
	}

	case WM_RBUTTONUP:
	{
		if (App->OgreStarted == 1)
		{
			ReleaseCapture();
			App->CL_WE_Listener_E15->Pl_RightMouseDown = 0;
			SetCursor(App->CUR);
			return 1;
		}

		return 1;
	}

	case WM_LBUTTONUP:
	{
		if (App->OgreStarted == 1)
		{
			ReleaseCapture();
			App->CL_WE_Listener_E15->Pl_LeftMouseDown = 0;
			SetCursor(App->CUR);
			return 1;
		}

		return 1;
	}

	case WM_COMMAND:

		if (LOWORD(wParam) == IDC_BTUPDATE)
		{
			App->SBC_Equity->Update_Model();
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BTEQCONVERT)
		{
			App->SBC_Equity->Convert_Model();
			return TRUE;
		}

		if (LOWORD(wParam) == ID_IMPORT_WORLDEDITOR)
		{
			App->CL_Importer->WorldEditor_Loader();
			App->SBC_Equity->Model_Loaded = 1;
			return TRUE;
		}

		if (LOWORD(wParam) == ID_IMPORT_EQ_WAVEFRONTOBJ)
		{
			App->CL_Importer->Assimp_Loader("Wavefront OBJ   *.obj\0*.obj\0", "Wavefront OBJ");
			return TRUE;
		}

		if (LOWORD(wParam) == ID_IMPORT_EQ_GENESIS3D)
		{
			App->CL_Importer->Genesis3D_Loader();
			return TRUE;
		}

		if (LOWORD(wParam) == ID_IMPORT_EQ_COLLADADAE)
		{
			App->CL_Importer->Assimp_Loader("Collada DAE   *.dae\0*.dae\0", "Collada DAE");
			return TRUE;
		}

		if (LOWORD(wParam) == ID_IMPORT_EQ_DOOM3MD5MESH)
		{
			App->CL_Importer->Assimp_Loader("Doom3  *.md5mesh\0*.md5mesh\0", "Doom3");
			return TRUE;
		}

		if (LOWORD(wParam) == ID_IMPORT_EQ_AUTODESK3DS)
		{
			App->CL_Importer->Assimp_Loader("Autodesk 3DS   *.3ds\0*.3ds\0", "Autodesk 3DS");
			return TRUE;
		}

		if (LOWORD(wParam) == ID_OGRE3D_EQ_MESH)
		{
			App->CL_Importer->Ogre_Loader("Ogre3D   *.mesh\0*.mesh\0", "Ogre3D");
			return TRUE;
		}
		
		if (LOWORD(wParam) == ID_OGRE3D_MESH32842)
		{
			App->CL_Vm_Exporter->Ogre3D_Model();
			return TRUE;
		}

		//-------------------------------------------------------- Show Hair
		if (LOWORD(wParam) == IDC_TBSHOWHAIR)
		{
			HWND Temp = GetDlgItem(hDlg, IDC_TBSHOWHAIR);

			if (App->Cl_Grid->ShowHair == 1)
			{
				App->Cl_Grid->ShowHair = 0;
				App->SBC_Equity->HairNode->setVisible(false);

				//App->CL_Vm_TopBar->Toggle_Hair_Flag = 0;

				SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_HairOff_Bmp);
			}
			else
			{
				App->Cl_Grid->ShowHair = 1;
				App->SBC_Equity->HairNode->setVisible(true);

				//App->CL_Vm_TopBar->Toggle_Hair_Flag = 1;

				SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_HairOn_Bmp);
			}
			return TRUE;
		}

		//-------------------------------------------------------- Show Textures
		if (LOWORD(wParam) == IDC_TBSHOWTEXTURE)
		{
			if (App->SBC_Equity->Model_Loaded == 1)
			{
				HWND Temp = GetDlgItem(hDlg, IDC_TBSHOWTEXTURE);

				if (App->SBC_Equity->RenderListener->ShowTextured == 1)
				{
					App->SBC_Equity->RenderListener->ShowTextured = 0;
					//App->CL_Vm_TopBar->Toggle_Textures_Flag = 0;

					SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_TexturesOff_Bmp);
				}
				else
				{
					App->SBC_Equity->RenderListener->ShowTextured = 1;
					//App->CL_Vm_TopBar->Toggle_Textures_Flag = 1;

					SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_TexturesOn_Bmp);
				}
			}
			return TRUE;
		}

		//-------------------------------------------------------- Show Faces
		if (LOWORD(wParam) == IDC_TBSHOWFACES)
		{
			if (App->SBC_Equity->Model_Loaded == 1)
			{
				HWND Temp = GetDlgItem(hDlg, IDC_TBSHOWFACES);

				if (App->SBC_Equity->RenderListener->ShowFaces == 1)
				{
					App->SBC_Equity->RenderListener->ShowFaces = 0;
					//App->CL_Vm_TopBar->Toggle_Faces_Flag = 0;

					SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_MeshOff_Bmp);
				}
				else
				{
					App->SBC_Equity->RenderListener->ShowFaces = 1;
					//App->CL_Vm_TopBar->Toggle_Faces_Flag = 1;

					SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_MeshOn_Bmp);
				}
			}
			return TRUE;
		}

		if (LOWORD(wParam) == IDOK)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		break;
	}
	return FALSE;
}

// *************************************************************************
// *						Init_Bmps_Globals Terry Bernie				   *
// *************************************************************************
void SB_Equity::Init_Bmps_Globals(void)
{
	HWND Temp = GetDlgItem(MeshViewDialog_Hwnd, IDC_TBSHOWFACES);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_MeshOff_Bmp);

	Temp = GetDlgItem(MeshViewDialog_Hwnd, IDC_TBPOINTS);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_MeshPointsOff_Bmp);

	Temp = GetDlgItem(MeshViewDialog_Hwnd, IDC_TBBOUNDBOX);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_BBOff_Bmp);

	Temp = GetDlgItem(MeshViewDialog_Hwnd, IDC_TBSHOWBONES);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_BonesOff_Bmp);

	Temp = GetDlgItem(MeshViewDialog_Hwnd, IDC_TBSHOWGRID);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_GridOn_Bmp);

	Temp = GetDlgItem(MeshViewDialog_Hwnd, IDC_TBSHOWHAIR);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_HairOn_Bmp);

	Temp = GetDlgItem(MeshViewDialog_Hwnd, IDC_TBINFO);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_ModelInfo_Bmp);

	Temp = GetDlgItem(MeshViewDialog_Hwnd, IDC_TBNORMALS);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_NormalsOff_Bmp);

	Temp = GetDlgItem(MeshViewDialog_Hwnd, IDC_TBSHOWTEXTURE);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_TexturesOff_Bmp);

	Temp = GetDlgItem(MeshViewDialog_Hwnd, IDC_TBLIGHT);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_LightsOff_Bmp);


	HWND hTooltip_TB_2 = CreateWindowEx(0, TOOLTIPS_CLASS, "", TTS_ALWAYSTIP | TTS_BALLOON, 0, 0, 0, 0, App->MainHwnd, 0, App->hInst, 0);

	Temp = GetDlgItem(MeshViewDialog_Hwnd, IDC_TBSHOWTEXTURE);
	TOOLINFO ti1 = { 0 };
	ti1.cbSize = sizeof(ti1);
	ti1.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti1.uId = (UINT_PTR)Temp;
	ti1.lpszText = "Toggle Textures";
	ti1.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti1);

	Temp = GetDlgItem(MeshViewDialog_Hwnd, IDC_TBSHOWFACES);
	TOOLINFO ti2 = { 0 };
	ti2.cbSize = sizeof(ti2);
	ti2.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti2.uId = (UINT_PTR)Temp;
	ti2.lpszText = "Toggle Faces";
	ti2.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti2);

	Temp = GetDlgItem(MeshViewDialog_Hwnd, IDC_TBPOINTS);
	TOOLINFO ti3 = { 0 };
	ti3.cbSize = sizeof(ti3);
	ti3.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti3.uId = (UINT_PTR)Temp;
	ti3.lpszText = "Toggle Points";
	ti3.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti3);

	Temp = GetDlgItem(MeshViewDialog_Hwnd, IDC_TBSHOWBONES);
	TOOLINFO ti4 = { 0 };
	ti4.cbSize = sizeof(ti4);
	ti4.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti4.uId = (UINT_PTR)Temp;
	ti4.lpszText = "Toggle Bones";
	ti4.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti4);

	Temp = GetDlgItem(MeshViewDialog_Hwnd, IDC_TBNORMALS);
	TOOLINFO ti5 = { 0 };
	ti5.cbSize = sizeof(ti5);
	ti5.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti5.uId = (UINT_PTR)Temp;
	ti5.lpszText = "Toggle Normals";
	ti5.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti5);

	Temp = GetDlgItem(MeshViewDialog_Hwnd, IDC_TBBOUNDBOX);
	TOOLINFO ti6 = { 0 };
	ti6.cbSize = sizeof(ti6);
	ti6.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti6.uId = (UINT_PTR)Temp;
	ti6.lpszText = "Toggle Bounding Box";
	ti6.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti6);

	Temp = GetDlgItem(MeshViewDialog_Hwnd, IDC_TBLIGHT);
	TOOLINFO ti7 = { 0 };
	ti7.cbSize = sizeof(ti7);
	ti7.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti7.uId = (UINT_PTR)Temp;
	ti7.lpszText = "Toggle Lights";
	ti7.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti7);

	Temp = GetDlgItem(MeshViewDialog_Hwnd, IDC_TBINFO);
	TOOLINFO ti8 = { 0 };
	ti8.cbSize = sizeof(ti8);
	ti8.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti8.uId = (UINT_PTR)Temp;
	ti8.lpszText = "Show Model Information";
	ti8.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti8);

	Temp = GetDlgItem(MeshViewDialog_Hwnd, IDC_TBSHOWHAIR);
	TOOLINFO ti9 = { 0 };
	ti9.cbSize = sizeof(ti9);
	ti9.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti9.uId = (UINT_PTR)Temp;
	ti9.lpszText = "Toggle Main Cross Hair";
	ti9.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti9);

	Temp = GetDlgItem(MeshViewDialog_Hwnd, IDC_TBSHOWGRID);
	TOOLINFO ti10 = { 0 };
	ti10.cbSize = sizeof(ti10);
	ti10.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti10.uId = (UINT_PTR)Temp;
	ti10.lpszText = "Toggle Main Grid";
	ti10.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti10);

}

// *************************************************************************
// *				Set_OgreWindow Terry Bernie							   *
// *************************************************************************
bool SB_Equity::Set_OgreWindow(void)
{

	Ogre::NameValuePairList options;

	options["externalWindowHandle"] =
		Ogre::StringConverter::toString((size_t)MeshView_Hwnd);

	MeshView_Window = App->Cl19_Ogre->mRoot->createRenderWindow("MeshViewWin", 1024, 768, false, &options);

	mSceneMgrMeshView = App->Cl19_Ogre->mRoot->createSceneManager("DefaultSceneManager", "MeshViewGD");


	App->CL_WE_Listener_E15->WE_Cam = mSceneMgrMeshView->createCamera("CameraMV");
	App->CL_WE_Listener_E15->WE_Cam->setPosition(Ogre::Vector3(0, 0, 0));
	App->CL_WE_Listener_E15->WE_Cam->setNearClipDistance(0.1);
	App->CL_WE_Listener_E15->WE_Cam->setFarClipDistance(1000);

	Ogre::Viewport* vp = MeshView_Window->addViewport(App->CL_WE_Listener_E15->WE_Cam);
	App->CL_WE_Listener_E15->WE_Cam->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

	vp->setBackgroundColour(ColourValue(0.5, 0.5, 0.5));

	CamNode = mSceneMgrMeshView->getRootSceneNode()->createChildSceneNode("Camera_Node");
	CamNode->attachObject(App->CL_WE_Listener_E15->WE_Cam);

	//-------------------------------------------- 
	MvEnt = mSceneMgrMeshView->createEntity("MVTest", "axes.mesh");
	MvNode = mSceneMgrMeshView->getRootSceneNode()->createChildSceneNode();
	MvNode->attachObject(MvEnt);

	mSceneMgrMeshView->setAmbientLight(ColourValue(0.7, 0.7, 0.7));

	// add a bright light above the scene
	Light* light = mSceneMgrMeshView->createLight();
	light->setType(Light::LT_POINT);
	light->setPosition(-10, 40, 20);
	light->setSpecularColour(ColourValue::White);

	Ogre::Vector3 Centre = MvEnt->getBoundingBox().getCenter();
	Ogre::Real Radius = MvEnt->getBoundingRadius();

	App->CL_WE_Listener_E15->WE_Cam->setPosition(0, Centre.y, -Radius*(Real(2.5)));
	App->CL_WE_Listener_E15->WE_Cam->lookAt(0, Centre.y, 0);

	manObj = mSceneMgrMeshView->createManualObject("sampleArea2");
	ModelNode = mSceneMgrMeshView->getRootSceneNode()->createChildSceneNode();
	ModelNode->attachObject(manObj);

	Grid_Update(1);
	Hair_Update(1);

	RenderListener = new VM_Render();
	mSceneMgrMeshView->addRenderQueueListener(RenderListener);

	App->Cl19_Ogre->OgreListener->GD_MeshViewer_Running = 1; // Must be Last

	return 1;
}

// *************************************************************************
// *	  					Grid_Update Terry Flanigan					   *
// *************************************************************************
void SB_Equity::Grid_Update(bool Create)
{
	int i = 0;
	Real r;

	if (Create == 1)
	{
		GridManual = mSceneMgrMeshView->createManualObject("GridManual");
		GridManual->setRenderQueueGroup(1);
	}

	GridManual->clear();
	GridManual->begin("BaseWhiteAlphaBlended", RenderOperation::OT_LINE_LIST);

	if (ShowGridFlag == 1)
	{
		for (int x = XAxis_min; x <= XAxis_max; ++x)
		{
			GridManual->position(x, 0, ZAxis_min);
			GridManual->colour(ColourMain);
			GridManual->position(x, 0, ZAxis_max);
			GridManual->colour(ColourMain);
			if (x < XAxis_max && ShowDivisions == 1)
			{
				for (int d = 0; d < Division_X; ++d)
				{
					r = x + (1.0 / Real(Division_X))*Real(d);
					GridManual->position(r, 0, ZAxis_min);
					GridManual->colour(ColourDivision);
					GridManual->position(r, 0, ZAxis_max);
					GridManual->colour(ColourDivision);
				}
			}
		}

		for (int z = ZAxis_min; z <= ZAxis_max; ++z)
		{
			GridManual->position(Ogre::Vector3(XAxis_min, 0, z));
			GridManual->colour(ColourMain);
			GridManual->position(Ogre::Vector3(XAxis_max, 0, z));
			GridManual->colour(ColourMain);
			if (z < ZAxis_max && ShowDivisions == 1)
			{
				for (int d = 1; d < Division_Y; ++d)
				{
					r = z + (1.0 / Real(Division_Y))*Real(d);
					GridManual->position(XAxis_min, 0, r);
					GridManual->colour(ColourDivision);
					GridManual->position(XAxis_max, 0, r);
					GridManual->colour(ColourDivision);
				}
			}
		}
	}

	GridManual->end();

	if (Create == 1)
	{
		GridNode = mSceneMgrMeshView->getRootSceneNode()->createChildSceneNode();
		GridNode->attachObject(GridManual);
	}

	GridNode->setPosition(0, 0, 0);
	GridNode->setVisible(true);
	GridNode->setScale(Scale_X, Scale_Y, Scale_Z);
}

// *************************************************************************
// *	  					Hair_Update Terry Bernie					   *
// *************************************************************************
void SB_Equity::Hair_Update(bool Create)
{
	if (Create == 1)
	{
		HairManual = mSceneMgrMeshView->createManualObject("HairManual");
		HairManual->setRenderQueueGroup(5);
	}

	HairManual->clear();
	HairManual->begin("BaseWhiteAlphaBlended", RenderOperation::OT_LINE_LIST);

	// X Axis
	HairManual->position(Ogre::Vector3(YAxis_min - HairExtend, 0, 0));
	HairManual->colour(ColourHairX);
	HairManual->position(Ogre::Vector3(YAxis_max + HairExtend, 0, 0));
	HairManual->colour(ColourHairX);
	// Y Axis
	HairManual->position(Ogre::Vector3(0, YAxis_min - HairExtend, 0));
	HairManual->colour(ColourHairY);
	HairManual->position(Ogre::Vector3(0, YAxis_max + HairExtend, 0));
	HairManual->colour(ColourHairY);
	// Z Axis
	HairManual->position(Ogre::Vector3(0, 0, ZAxis_min - HairExtend));
	HairManual->colour(ColourHairZ);
	HairManual->position(Ogre::Vector3(0, 0, ZAxis_max + HairExtend));
	HairManual->colour(ColourHairZ);

	HairManual->end();

	if (Create == 1)
	{
		HairNode = mSceneMgrMeshView->getRootSceneNode()->createChildSceneNode();
		HairNode->attachObject(HairManual);
	}

	HairNode->setPosition(0, 0, 0);
	HairNode->setVisible(true);
	HairNode->setScale(Scale_X, Scale_Y, Scale_Z);
}

// *************************************************************************
// *				CloseMeshView (Terry Bernie)						   *
// *************************************************************************
void SB_Equity::Close_OgreWindow(void)
{
	App->Cl19_Ogre->mRoot->detachRenderTarget("MeshViewWin");
	MeshView_Window->destroy();
	App->Cl19_Ogre->mRoot->destroySceneManager(mSceneMgrMeshView);
}

// *************************************************************************
// *				Update_Model (Terry Bernie)							   *
// *************************************************************************
void SB_Equity::Update_Model(void)
{
	App->Cl_Vm_Assimp->SelectedPreset = 8 + 8388608 + 64 + aiProcess_PreTransformVertices;

	bool Test = App->Cl_Vm_Assimp->LoadFile(App->Cl_Vm_Preferences->Pref_WE_Path_FileName);
	if (Test == 0)
	{
		App->Say("Failed To Load");
		return;
	}

	App->CL_Vm_Model->Model_Type = LoadedFile_Assimp;

	App->Cl_Vm_WorldEditor->LoadTextures_TXL();

	App->Cl_Vm_WorldEditor->Adjust();

	App->Say("Model Updated");
}

// *************************************************************************
// *					Convert_Model Terry Flanigan					   *
// *************************************************************************
void SB_Equity::Convert_Model(void)
{
	App->CL_Vm_Exporter->Ogre3D_Model();

	App->Say("Converted");
}

