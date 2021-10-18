#include "stdafx.h"
#include "GD19_App.h"
#include "resource.h"
#include "VM_MeshDesign.h"


VM_MeshDesign::VM_MeshDesign()
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

	ColourHairZ = ColourValue(1, 0, 0, 1);
	ColourHairX = ColourValue(0, 0, 1, 1);
	ColourHairY = ColourValue(0, 1, 0, 1);
	ColourMain = ColourValue(0.7, 0.7, 0, 0.6);
	ColourDivision = ColourValue(1, 1, 1, 0.4);
}


VM_MeshDesign::~VM_MeshDesign()
{
}

// *************************************************************************
// *				StartMeshDesign  Terry	Bernie						   *
// *************************************************************************
bool VM_MeshDesign::StartMeshDesign()
{
	App->RenderBackGround = 1;

	DialogBox(App->hInst, (LPCTSTR)IDD_MESHDESIGN, App->Fdlg, (DLGPROC)MeshDesign_Proc);

	App->RenderBackGround = 0;
	App->Cl19_Ogre->OgreListener->GD_MeshViewer_Running = 0;
	Close_OgreWindow();
	return 1;
}

// *************************************************************************
// *						MeshDesign_Proc Terry Bernie				   *
// *************************************************************************
LRESULT CALLBACK VM_MeshDesign::MeshDesign_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{

		HWND Ogre_Hwnd = GetDlgItem(hDlg, IDC_OGREWIN2);

		App->Cl_Vm_MeshDesign->MeshView_Hwnd = GetDlgItem(hDlg, IDC_OGREWIN2);
		App->Cl_Vm_MeshDesign->MeshViewDialog_Hwnd = hDlg;

		App->Cl_Vm_MeshDesign->Set_OgreWindow();

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

			SetCapture(App->Cl_Vm_MeshDesign->MeshViewDialog_Hwnd);// Bernie
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
			App->Cl_Vm_MeshDesign->Update_Model();
			return TRUE;
		}

		if (LOWORD(wParam) == ID_IMPORT_WORLDEDITOR)
		{
			App->CL_Importer->WorldEditor_Loader();
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
// *				Set_OgreWindow Terry Bernie							   *
// *************************************************************************
bool VM_MeshDesign::Set_OgreWindow(void)
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
void VM_MeshDesign::Grid_Update(bool Create)
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
void VM_MeshDesign::Hair_Update(bool Create)
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
void VM_MeshDesign::Close_OgreWindow(void)
{
	App->Cl19_Ogre->mRoot->detachRenderTarget("MeshViewWin");
	MeshView_Window->destroy();
	App->Cl19_Ogre->mRoot->destroySceneManager(mSceneMgrMeshView);
}

// *************************************************************************
// *				Update_Model (Terry Bernie)							   *
// *************************************************************************
void VM_MeshDesign::Update_Model(void)
{
	App->Debug_Text();
}