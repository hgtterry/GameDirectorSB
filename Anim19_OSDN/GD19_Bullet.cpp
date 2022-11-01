#include "StdAfx.h"
#include "GD19_App.h"
#include "resource.h"
#include "GD19_Bullet.h"

//#include "GD_Debug.h"


GD19_Bullet::GD19_Bullet(void)
{
	//M_Debug = NULL;
	collisionConfiguration = NULL;
	dispatcher = NULL;
	overlappingPairCache = NULL;
	solver = NULL;
	dynamicsWorld = NULL;

	GD_Physics_On = 1;
	GD_Reset_Player = 1;
	Physics_Dlg_Active = 0;
}


GD19_Bullet::~GD19_Bullet(void)
{
}

// *************************************************************************
// *						Init_Bullet Terry Bernie   			 	 	   *
// *************************************************************************
bool GD19_Bullet::Init_Bullet()
{
	collisionConfiguration = new btDefaultCollisionConfiguration();

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	dispatcher = new	btCollisionDispatcher(collisionConfiguration);

	///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
	overlappingPairCache = new btDbvtBroadphase();

	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	solver = new btSequentialImpulseConstraintSolver;

	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,overlappingPairCache,solver,collisionConfiguration);

	//dynamicsWorld->getDebugDrawer()->setDebugMode( btIDebugDraw::DBG_DrawWireframe);
	
	dynamicsWorld->setGravity(btVector3(0,-30,0));
	dynamicsWorld->getDispatchInfo().m_allowedCcdPenetration = 0.00001f;

	btAlignedObjectArray<btCollisionShape*> collisionShapes;

	return 0;
}
//void QuaternionToEuler(const btQuaternion &TQuat, btVector3 &TEuler) {
//	btScalar W = TQuat.getW();
//	btScalar X = TQuat.getX();
//	btScalar Y = TQuat.getY();
//	btScalar Z = TQuat.getZ();
//	float WSquared = W * W;
//	float XSquared = X * X;
//	float YSquared = Y * Y;
//	float ZSquared = Z * Z;
//
//	TEuler.setX(atan2f(2.0f * (Y * Z + X * W), -XSquared - YSquared + ZSquared + WSquared));
//	TEuler.setY(asinf(-2.0f * (X * Z - Y * W)));
//	TEuler.setZ(atan2f(2.0f * (X * Y + Z * W), XSquared - YSquared - ZSquared + WSquared));
//	TEuler *= core::RADTODEG;
//}


// *************************************************************************
// *	  				Start_Physics_Consol Terry Bernie				   *
// *************************************************************************
void GD19_Bullet::Start_Physics_Console(void)
{
	if(Physics_Dlg_Active == 1)
	{
		return;
	}

	Physics_Dlg_Active = 1;

	CheckMenuItem(App->mMenu, ID_WINDOWS_SHOWPHYSICSPANEL, MF_BYCOMMAND | MF_CHECKED);

	App->Physics_Console_Hwnd = CreateDialog(App->hInst,(LPCTSTR)IDD_PHYSICS_CONSOLE,App->Fdlg,(DLGPROC)Physics_Console_Proc);
}
// *************************************************************************
// *        			Physics_Console_Proc  Terry	Bernie				   *
// *************************************************************************
LRESULT CALLBACK GD19_Bullet::Physics_Console_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
				
	switch (message)
	{
	case WM_INITDIALOG:
		{	
			return TRUE;
		}
		
		case WM_CTLCOLORDLG:
			{
				return (LONG)App->DialogBackGround;
			}

		case WM_NOTIFY:
		{
			LPNMHDR some_item = (LPNMHDR)lParam;
			
			if (some_item->idFrom == IDC_RESETPHYSICS && some_item->code == NM_CUSTOMDRAW)
            {
                LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
				App->Custom_Button_Normal(item);
                return CDRF_DODEFAULT;
            }

			if (some_item->idFrom == IDC_RESETTRIGGERS && some_item->code == NM_CUSTOMDRAW)
            {
                LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
				App->Custom_Button_Normal(item);
                return CDRF_DODEFAULT;
            }

			if (some_item->idFrom == IDC_PHYSICS_ON && some_item->code == NM_CUSTOMDRAW)
            {
                LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
				App->Custom_Button_Toggle(item,App->Cl_Bullet->GD_Physics_On);
                return CDRF_DODEFAULT;
            }

			return CDRF_DODEFAULT;
		}
		case WM_COMMAND:
			
			if (LOWORD(wParam)== IDC_RESETTRIGGERS) 
			{
				if(App->SBC_Scene->Scene_Loaded == 1)
				{
					App->SBC_Physics->Reset_Triggers();
				}
				return TRUE;
			}

			if (LOWORD(wParam)== IDC_RESETPHYSICS) 
			{
				if(App->SBC_Scene->Scene_Loaded == 1)
				{
					//App->Cl_Bullet->Reset_Physics();
				}
				return TRUE;
			}

			if (LOWORD(wParam)== IDC_PHYSICS_ON) 
			{
				if(App->SBC_Scene->Scene_Loaded == 1)
				{
					if(App->Cl_Bullet->GD_Physics_On == 1)
					{
						App->Cl_Bullet->GD_Physics_On = 0;
						App->Cl19_Ogre->OgreListener->GD_Run_Physics = 0;
					}
					else
					{
						App->Cl_Bullet->GD_Physics_On = 1;
						App->Cl19_Ogre->OgreListener->GD_Run_Physics = 1;
					}
				}
				return TRUE;
			}

			if (LOWORD(wParam)== IDCANCEL) 
			{
				App->Cl_Bullet->Physics_Dlg_Active = 0;
				CheckMenuItem(App->mMenu, ID_WINDOWS_SHOWPHYSICSPANEL, MF_BYCOMMAND | MF_UNCHECKED);
				ShowWindow(App->Physics_Console_Hwnd, 0);
				//EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}

			break;
	}
    return FALSE;
}


