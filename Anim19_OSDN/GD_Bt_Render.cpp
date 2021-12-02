/*	
	Copyright (c) Equity10 2016 HGT Software W.T.Flanigan B.Parkin H.C.Flanigan

	This software is provided 'as-is', without any express or implied
	warranty. In no event will the authors be held liable for any damages
	arising from the use of this software.

	Permission is granted to anyone to use this software for any purpose,
	including commercial applications, and to alter it and redistribute it
	freely, subject to the following restrictions:

	1. The origin of this software must not be misrepresented; you must not
	claim that you wrote the original software. If you use this software
	in a product, an acknowledgment in the product documentation would be
	appreciated but is not required.

	2. Altered source versions must be plainly marked as such, and must not be
	misrepresented as being the original software.

	3. This notice may not be removed or altered from any source
	distribution.
*/

#include "StdAfx.h"
#include "GD19_App.h"
#include "GD_Bt_Render.h"

//#include <d3d9.h>

#pragma warning( disable : 4305)


GD_Bt_Render::GD_Bt_Render(void)
{
	RX = 0;				
	RZ = 0;

	Hair_1PosX = 0;
	Hair_1PosY = 0;
	Hair_1PosZ = 0;

	Hair_1RotX = 0;
	Hair_1RotY = 0;
	Hair_1RotZ = 0;

	ShowTextured = 1;
	ShowMesh = 0;
	ShowBones = 0;
	ShowPoints = 0;
	ShowNormals = 0;
	ShowBoundingBox = 0;
	PlayActive = 0;
	Light_Activated = 0;
	ShowOnlySubMesh = 0;
	Show_HideGroup = 0;
	Show_Crosshair = 0;

	ShowDebug = 0;
	FirstDebug = 0;

	TestLight();

	/*mLines = new ManualObject("physics lines");
	mLines->setDynamic(true);

	 mLines->begin( "BaseWhiteAlphaBlended",RenderOperation::OT_LINE_LIST );
	 mLines->position( Vector3::ZERO );
	 mLines->colour( ColourValue::Blue );
	 mLines->position( Vector3::ZERO );
	 mLines->colour( ColourValue::Blue );*/

	ColourMain = ColourValue(1,1,1,1);

	 btDebug_Manual = App->Cl19_Ogre->mSceneMgr->createManualObject("btManual");
	 btDebug_Manual->setRenderQueueGroup(RENDER_QUEUE_MAX);

	 btDebug_Manual->setDynamic(true);
	 btDebug_Manual->estimateVertexCount(2000);
	
	 btDebug_Manual->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_LIST);
	 btDebug_Manual->position(10,10,10);
	 btDebug_Manual->colour(ColourMain);
	 btDebug_Manual->position(30,30,30);
	 btDebug_Manual->colour(ColourMain);
	 btDebug_Manual->end();

	 btDebug_Node = App->Cl19_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	 btDebug_Node->attachObject(btDebug_Manual);


	 vertex_From.resize(100000);
	 vertex_To.resize(100000);
	 vertex_Colour.resize(100000);
	 V_Count = 0;
}


GD_Bt_Render::~GD_Bt_Render(void)
{
}

void GD_Bt_Render::drawSphere(const btVector3& p, btScalar radius, const btVector3& color)
{
	//FlashWindow(App->MainHwnd,true);
}

void GD_Bt_Render::drawLine(const btVector3& from, const btVector3& to, const btVector3& fromColor, const btVector3& toColor)
{
	
}

void GD_Bt_Render::drawLine (const btVector3 &from, const btVector3 &to, const btVector3 &color)
{

	vertex_Colour[V_Count].x = color.getX();
	vertex_Colour[V_Count].y = color.getY();
	vertex_Colour[V_Count].z = color.getZ();

	vertex_From[V_Count].x = from.getX();
	vertex_From[V_Count].y = from.getY();
	vertex_From[V_Count].z = from.getZ();

	vertex_To[V_Count].x = to.getX();
	vertex_To[V_Count].y = to.getY();
	vertex_To[V_Count].z = to.getZ();
	V_Count++;
	
}

void GD_Bt_Render::drawTriangle (const btVector3 &v0, const btVector3 &v1, const btVector3 &v2, const btVector3 &color, btScalar)
{
	//FlashWindow(App->MainHwnd,true);
}

void GD_Bt_Render::drawContactPoint (const btVector3 &PointOnB, const btVector3 &normalOnB, btScalar distance, int lifeTime, const btVector3 &color)
{
	FlashWindow(App->MainHwnd,true);
}

void GD_Bt_Render::reportErrorWarning (const char *warningString)
{
	//FlashWindow(App->MainHwnd,true);
}

void GD_Bt_Render::draw3dText (const btVector3 &location, const char *textString)
{
	//FlashWindow(App->MainHwnd,true);
}

void GD_Bt_Render::setDebugMode (int debugMode)
{
	m_debugMode = (DebugDrawModes) DBG_DrawWireframe;
}

int GD_Bt_Render::getDebugMode() const{
	
    return DBG_DrawWireframe;
}
// *************************************************************************
// *						TestLight Terry Bernie						   *
// *************************************************************************
void GD_Bt_Render::TestLight(void) 
{ 
	////glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	//float ld[4] = { 0.4, 0.4, 0.4, 0 };
	//glLightfv(GL_LIGHT0, GL_AMBIENT, ld);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, ld);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, ld);

	//
	///*GLfloat a[4] = { 1, 1, 1, 1 };
	//glMaterialfv(GL_FRONT, GL_AMBIENT, a);
	//GLfloat d[4] = { 0, 0, 0, 1 };
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, d);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, d);
	//glMaterialf(GL_FRONT, GL_SHININESS, 128);*/
	
	//glEnable(GL_LIGHTING);
	//Light_Activated = 1;
}
// *************************************************************************
// *					renderQueueStarted Terry Bernie					   *
// *************************************************************************
void GD_Bt_Render::renderQueueStarted(Ogre::uint8 queueGroupId, const String& invocation,bool& skipThisInvocation) 
{ 
	Render_Debug_Bullet();
	
//	LPDIRECT3DDEVICE9       pd3dDevice = NULL; // Our rendering device
//	LPDIRECT3DVERTEXBUFFER9 pVB = NULL; // Buffer to hold vertices
//
//	RenderSystem* renderSystem = App->Cl19_Ogre->manObj->_getManager()->getDestinationRenderSystem();
//
//	App->Cl19_Ogre->mWindow->getCustomAttribute("D3DDEVICE", &pd3dDevice);
//
//
//	pd3dDevice->SetRenderState(D3DRS_LIGHTING, false);
//	pd3dDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, TVC_DIFFUSE);
//
//	// A structure for our custom vertex type
//	struct CUSTOMVERTEX
//	{
//		Vector3 FromPos;      // The untransformed, 3D position for the vertex
//	};
//
//	// Our custom FVF, which describes our custom vertex structure
//#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ)
//
//#define SCALE_FACTOR 30
//
//	// Initialize three vertices for rendering a triangle
//	CUSTOMVERTEX cubeVertices[200];
//	//{
//		int Count = 0;
//		int L_Count = V_Count;
//		while (Count < L_Count)
//		{
//			cubeVertices[Count].FromPos = { Vector3(vertex_From[Count].x, vertex_From[Count].y, vertex_From[Count].z) };
//			cubeVertices[Count+1].FromPos = { Vector3(vertex_To[Count].x, vertex_To[Count].y, vertex_To[Count].z) };
//			Count++;
//		}
//		V_Count = 0;
//		//// Bottom Face.  
//		//{ Vector3(-1.0f, -1.0f, -1.0f) * SCALE_FACTOR, Vector3(0.0f, -1.0f, 0.0f), 0xff000000, },
//		//{ Vector3(1.0f, -1.0f, -1.0f) * SCALE_FACTOR, Vector3(0.0f, -1.0f, 0.0f), 0xff000000, },
//		//{ Vector3(1.0f, -1.0f,  1.0f) * SCALE_FACTOR, Vector3(0.0f, -1.0f, 0.0f), 0xff000000, },
//		//{ Vector3(1.0f, -1.0f,  1.0f) * SCALE_FACTOR, Vector3(0.0f, -1.0f, 0.0f), 0xff000000, },
//		//{ Vector3(-1.0f, -1.0f,  1.0f) * SCALE_FACTOR, Vector3(0.0f, -1.0f, 0.0f), 0xff000000, },
//		//{ Vector3(-1.0f, -1.0f, -1.0f) * SCALE_FACTOR, Vector3(0.0f, -1.0f, 0.0f), 0xff000000, },
//
//	//	// Top Face.  
//	//	{ Vector3(-1.0f,  1.3f, -1.0f) * SCALE_FACTOR, Vector3(0.0f, 1.0f, 0.0f), 0xffffff00, },
//	//	{ Vector3(-1.0f,  1.3f,  1.0f) * SCALE_FACTOR, Vector3(0.0f, 1.0f, 0.0f), 0xffffff00, },
//	//	{ Vector3(1.0f,  1.3f,  1.0f) * SCALE_FACTOR, Vector3(0.0f, 1.0f, 0.0f), 0xffffff00, },
//	//	{ Vector3(1.0f,  1.3f,  1.0f) * SCALE_FACTOR, Vector3(0.0f, 1.0f, 0.0f), 0xffffff00, },
//	//	{ Vector3(1.0f,  1.3f, -1.0f) * SCALE_FACTOR, Vector3(0.0f, 1.0f, 0.0f), 0xffffff00, },
//	//	{ Vector3(-1.0f,  1.3f, -1.0f) * SCALE_FACTOR, Vector3(0.0f, 1.0f, 0.0f), 0xffffff00, },
//
//	//	// Far Face.  
//	//	{ Vector3(-1.0f, -1.0f, -1.3f) * SCALE_FACTOR, Vector3(0.0f, 0.0f,-1.0f), 0x00ff0000, },
//	//	{ Vector3(-1.0f,  1.0f, -1.3f) * SCALE_FACTOR, Vector3(0.0f, 0.0f,-1.0f), 0x00ff0000, },
//	//	{ Vector3(1.0f,  1.0f, -1.3f) * SCALE_FACTOR, Vector3(0.0f, 0.0f,-1.0f), 0x00ff0000, },
//	//	{ Vector3(1.0f,  1.0f, -1.3f) * SCALE_FACTOR, Vector3(0.0f, 0.0f,-1.0f), 0x00ff0000, },
//	//	{ Vector3(1.0f, -1.0f, -1.3f) * SCALE_FACTOR, Vector3(0.0f, 0.0f,-1.0f), 0x00ff0000, },
//	//	{ Vector3(-1.0f, -1.0f, -1.3f) * SCALE_FACTOR, Vector3(0.0f, 0.0f,-1.0f), 0x00ff0000, },
//
//	//	// Right Face.  
//	//	{ Vector3(1.0f, -1.0f, -1.0f) * SCALE_FACTOR, Vector3(1.0f, 0.0f, 0.0f), 0x0000ff00, },
//	//	{ Vector3(1.0f,  1.0f, -1.0f) * SCALE_FACTOR, Vector3(1.0f, 0.0f, 0.0f), 0x0000ff00, },
//	//	{ Vector3(1.0f,  1.0f,  1.0f) * SCALE_FACTOR, Vector3(1.0f, 0.0f, 0.0f), 0x0000ff00, },
//	//	{ Vector3(1.0f,  1.0f,  1.0f) * SCALE_FACTOR, Vector3(1.0f, 0.0f, 0.0f), 0x0000ff00, },
//	//	{ Vector3(1.0f, -1.0f,  1.0f) * SCALE_FACTOR, Vector3(1.0f, 0.0f, 0.0f), 0x0000ff00, },
//	//	{ Vector3(1.0f, -1.0f, -1.0f) * SCALE_FACTOR, Vector3(1.0f, 0.0f, 0.0f), 0x0000ff00, },
//
//	//	// Front Face.
//	//	{ Vector3(-1.0f, -1.0f,  1.3f) * SCALE_FACTOR, Vector3(0.0f, 0.0f, 1.0f), 0xff00ff00, },
//	//	{ Vector3(1.0f, -1.0f,  1.3f) * SCALE_FACTOR, Vector3(0.0f, 0.0f, 1.0f), 0x00ffff00, },
//	//	{ Vector3(1.0f,  1.0f,  1.3f) * SCALE_FACTOR, Vector3(0.0f, 0.0f, 1.0f), 0x0000ff00, },
//	//	{ Vector3(1.0f,  1.0f,  1.3f) * SCALE_FACTOR, Vector3(0.0f, 0.0f, 1.0f), 0x0000ff00, },
//	//	{ Vector3(-1.0f,  1.0f,  1.3f) * SCALE_FACTOR, Vector3(0.0f, 0.0f, 1.0f), 0xffffff00, },
//	//	{ Vector3(-1.0f, -1.0f,  1.3f) * SCALE_FACTOR, Vector3(0.0f, 0.0f, 1.0f), 0xff00ff00, },
//
//	//	// Left Face.  
//	//	{ Vector3(-1.3f, -1.0f, -1.0f) * SCALE_FACTOR, Vector3(-1.0f, 0.0f, 0.0f), 0xffff0000, },
//	//	{ Vector3(-1.3f, -1.0f,  1.0f) * SCALE_FACTOR, Vector3(-1.0f, 0.0f, 0.0f), 0xffff0000, },
//	//	{ Vector3(-1.3f,  1.0f,  1.0f) * SCALE_FACTOR, Vector3(-1.0f, 0.0f, 0.0f), 0xffff0000, },
//	//	{ Vector3(-1.3f,  1.0f,  1.0f) * SCALE_FACTOR, Vector3(-1.0f, 0.0f, 0.0f), 0xffff0000, },
//	//	{ Vector3(-1.3f,  1.0f, -1.0f) * SCALE_FACTOR, Vector3(-1.0f, 0.0f, 0.0f), 0xffff0000, },
//	//	{ Vector3(-1.3f, -1.0f, -1.0f) * SCALE_FACTOR, Vector3(-1.0f, 0.0f, 0.0f), 0xffff0000, },
//	//};
//
//
//	UINT primitiveCount = sizeof(cubeVertices) / sizeof(CUSTOMVERTEX);
//
//	// Create the vertex buffer.
//	if (FAILED(pd3dDevice->CreateVertexBuffer(sizeof(cubeVertices),
//		0, D3DFVF_CUSTOMVERTEX,
//		D3DPOOL_DEFAULT, &pVB, NULL)))
//	{
//		return;//E_FAIL;
//	}
//
//	// Fill the vertex buffer.
//	VOID* pVertices;
//	if (FAILED(pVB->Lock(0, sizeof(cubeVertices), (void**)&pVertices, 0)))
//		return;// E_FAIL;
//	memcpy(pVertices, cubeVertices, sizeof(cubeVertices));
//	pVB->Unlock();
//
//	//if (ShowDebug == 1)
//	//{
//	//	// Render the vertex buffer contents
//	//	pd3dDevice->SetStreamSource(0, pVB, 0, sizeof(CUSTOMVERTEX));
//	//	pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
//	//	pd3dDevice->DrawPrimitive(D3DPT_LINELIST, 0, primitiveCount);
//
//	//}
//	
//
//	pVB->Release();
}
// *************************************************************************
// *					renderQueueEnded Terry Bernie					   *
// *************************************************************************
void GD_Bt_Render::renderQueueEnded(Ogre::uint8 queueGroupId, const String& invocation, bool& repeatThisInvocation)
{
	/*if (queueGroupId != RENDER_QUEUE_MAIN)
	{
		return;
	}*/
	//mLines->end();
	//mLines->beginUpdate(0);
	
	PreRender();

	//Render_Debug_Bullet();
	//Render();

	PostRender();
}
// *************************************************************************
// *				PreRender   Terry Bernie							   *
// *************************************************************************
void GD_Bt_Render::PreRender()
{
	/*RenderSystem* renderSystem = App->Cl19_Ogre->manObj->_getManager()->getDestinationRenderSystem();
	Node* parentNode = App->Cl19_Ogre->manObj->getParentNode();
	renderSystem->_setWorldMatrix(parentNode->_getFullTransform());
	renderSystem->_setViewMatrix(App->Cl19_Ogre->mCamera->getViewMatrix());
	renderSystem->_setProjectionMatrix(App->Cl19_Ogre->mCamera->getProjectionMatrixRS());

	static Pass* clearPass = NULL;
	if (!clearPass)
	{
		MaterialPtr clearMat = MaterialManager::getSingleton().getByName("BaseWhite");
		clearPass = clearMat->getTechnique(0)->getPass(0);
	}
	Set a clear pass to give the renderer a clear renderstate
	App->Cl19_Ogre->mSceneMgr->_setPass(clearPass, true, false);*/
}
// *************************************************************************
// *				PostRender   Terry Bernie							   *
// *************************************************************************
void GD_Bt_Render::PostRender()
{
	
	

}

// *************************************************************************
// *					Render_Debug_Bullet   Terry Bernie				   *
// *************************************************************************
void GD_Bt_Render::Render_Debug_Bullet()
{
	
	Render_Debug();

}

// *************************************************************************
// *					Translate Terry Bernie							   *
// *************************************************************************
void GD_Bt_Render::Translate(void)
{
	
	//glRotatef(RX,1.0,0.0,0.0); // Rotations of the object 

	//glRotatef(RZ,0.0,1.0,0.0);
	//glRotatef(0.0,0.0,0.0,1.0);
}

// *************************************************************************
// *						Render_Debug Terry Bernie	   				   *
// *************************************************************************
bool GD_Bt_Render::Render_Debug(void)
{
	if (ShowDebug == 1)
	{
		
		if (V_Count > 0)
		{
			btDebug_Manual->beginUpdate(0);

			int Count = 0;
			while (Count < V_Count)
			{
				btDebug_Manual->position(vertex_From[Count].x, vertex_From[Count].y, vertex_From[Count].z);
				btDebug_Manual->colour(ColourMain);
				btDebug_Manual->position(vertex_To[Count].x, vertex_To[Count].y, vertex_To[Count].z);
				btDebug_Manual->colour(ColourMain);
				Count++;
			}

			btDebug_Manual->end();
			V_Count = 0;
		}

	}
	else
	{
		btDebug_Manual->beginUpdate(0);
		btDebug_Manual->position(0,0,0);
		btDebug_Manual->colour(ColourMain);
		btDebug_Manual->position(0,0,0);
		btDebug_Manual->colour(ColourMain);
		btDebug_Manual->end();
	}

	V_Count = 0;
	return 1;
}


// *************************************************************************
// *				Render_BoundingBoxModel Terry Bernie	  			   *
// *************************************************************************
void GD_Bt_Render::Render_BoundingBoxModel(void)
{
	
}
