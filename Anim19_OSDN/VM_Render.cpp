/*
Copyright (c) Vima19 Inflanite Software W.T.Flanigan H.C.Flanigan

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
#include "VM_Render.h"

#pragma warning( disable : 4305)


VM_Render::VM_Render(void)
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
	ShowFaces = 0;
	ShowBones = 0;
	ShowPoints = 0;
	ShowNormals = 0;
	ShowBoundingBox = 0;
	PlayActive = 0;
	Light_Activated = 0;
	ShowOnlySubMesh = 0;
	Show_HideGroup = 0;
	Show_Crosshair = 0;

	TestLight();
}


VM_Render::~VM_Render(void)
{
	
}

// *************************************************************************
// *						Reset_Class Terry Bernie					   *
// *************************************************************************
void VM_Render::Reset_Class(void)
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
	ShowFaces = 0;
	ShowBones = 0;
	ShowPoints = 0;
	ShowNormals = 0;
	ShowBoundingBox = 0;
	PlayActive = 0;
	Light_Activated = 0;
	ShowOnlySubMesh = 0;
	Show_HideGroup = 0;
	Show_Crosshair = 0;

}

// *************************************************************************
// *						TestLight Terry Bernie						   *
// *************************************************************************
void VM_Render::TestLight(void)
{ 
	//glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	float ld[4] = { (float) 0.4,(float) 0.4, (float)0.4,(float)0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ld);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, ld);
	glLightfv(GL_LIGHT0, GL_SPECULAR, ld);

	
	/*GLfloat a[4] = { 1, 1, 1, 1 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, a);
	GLfloat d[4] = { 0, 0, 0, 1 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, d);
	glMaterialfv(GL_FRONT, GL_SPECULAR, d);
	glMaterialf(GL_FRONT, GL_SHININESS, 128);*/
	
	//glEnable(GL_LIGHTING);
	//Light_Activated = 1;
}
// *************************************************************************
// *					renderQueueStarted Terry Bernie					   *
// *************************************************************************
void VM_Render::renderQueueStarted(Ogre::uint8 queueGroupId, const String& invocation,bool& skipThisInvocation)
{ 
}
// *************************************************************************
// *					renderQueueEnded Terry Bernie					   *
// *************************************************************************
void VM_Render::renderQueueEnded(Ogre::uint8 queueGroupId, const String& invocation, bool& repeatThisInvocation)
{
	if (App->CL_Vm_ImGui->Show_Progress_Bar == 1)
	{
		return;
	}

	if (queueGroupId != RENDER_QUEUE_MAIN)
	{
		return;
	}

	if (PlayActive == 1)
	{
		if (App->CL_Vm_Model->Model_Type == LoadedFile_Actor)
		{
			

			/*if (App->Cl_Ogre->RenderListener->Show_Crosshair == 1)
			{
				App->Cl_Bones->Move_BoneCrosshair();
			}*/
		}
	}

	PreRender();

	
	Render_Loop();
	

	PostRender();
}
// *************************************************************************
// *				PreRender   Terry Bernie							   *
// *************************************************************************
void VM_Render::PreRender()
{
	if (App->Cl19_Ogre->OgreListener->Equity_Running == 0)
	{
		return;
	}

	// save matrices
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glMatrixMode(GL_TEXTURE);
	glPushMatrix();
	glLoadIdentity(); //Texture addressing should start out as direct.

	if (App->Cl19_Ogre->OgreListener->Equity_Running == 1)
	{
		/*RenderSystem* renderSystem = App->SBC_Equity->manObj->_getManager()->getDestinationRenderSystem();
		Node* parentNode = App->SBC_Equity->manObj->getParentNode();
		renderSystem->_setWorldMatrix(parentNode->_getFullTransform());
		renderSystem->_setViewMatrix(App->EBC_Listener->WE_Cam->getViewMatrix());
		renderSystem->_setProjectionMatrix(App->EBC_Listener->WE_Cam->getProjectionMatrixRS());*/
	}
	else
	{
		/*RenderSystem* renderSystem = App->Cl19_Ogre->manObj->_getManager()->getDestinationRenderSystem();
		Node* parentNode = App->Cl19_Ogre->manObj->getParentNode();
		renderSystem->_setWorldMatrix(parentNode->_getFullTransform());
		renderSystem->_setViewMatrix(App->Cl19_Ogre->mCamera->getViewMatrix());
		renderSystem->_setProjectionMatrix(App->Cl19_Ogre->mCamera->getProjectionMatrixRS());*/
	}

	static Pass* clearPass = NULL;
	if (!clearPass)
	{
		MaterialPtr clearMat = MaterialManager::getSingleton().getByName("BaseWhite");
		clearPass = clearMat->getTechnique(0)->getPass(0);
	}

	//Set a clear pass to give the renderer a clear renderstate
	if (App->Cl19_Ogre->OgreListener->Equity_Running == 1)
	{
		App->SBC_Equity->mSceneMgrMeshView->_setPass(clearPass, true, false);
	}
	else
	{
		/*App->Cl19_Ogre->mSceneMgr->_setPass(clearPass, true, false);*/
	}

	// save attribs
	glPushAttrib(GL_ALL_ATTRIB_BITS);
}
// *************************************************************************
// *				PostRender   Terry Bernie							   *
// *************************************************************************
void VM_Render::PostRender()
{
	// restore original state
	glPopAttrib();

	// restore matrices
	glMatrixMode(GL_TEXTURE);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

// *************************************************************************
// *					Render_Loop   Terry Bernie						   *
// *************************************************************************
void VM_Render::Render_Loop()
{
	if (App->Cl19_Ogre->OgreListener->Equity_Running == 0)
	{
		return;
	}
	GLboolean depthTestEnabled=glIsEnabled(GL_DEPTH_TEST);
	glDisable(GL_DEPTH_TEST);
	GLboolean stencilTestEnabled = glIsEnabled(GL_STENCIL_TEST);
	glDisable(GL_STENCIL_TEST);

	if (Light_Activated == 0)
	{
		glDisable(GL_LIGHTING);
	}
	else
	{
		glEnable(GL_LIGHTING);
	}

	glColor3f(0.8f, 0.8f, 0.8f);
	Translate();


	// ---------------------- Textured
	if (App->CL_Vm_Model->Model_Loaded == 1 && ShowTextured == 1)
	{
		glEnable(GL_DEPTH_TEST);
		glShadeModel(GL_SMOOTH);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		if (App->CL_Vm_Model->Model_Type == LoadedFile_Actor)
		{
			if (ShowOnlySubMesh == 1)
			{
				RF_Render_Just_Group();
			}
			else
			{
				RF_Render_All_Groups();
			}
		}

		if (App->CL_Vm_Model->Model_Type == LoadedFile_Assimp)
		{
			Assimp_Render_Textures();
		}
	}

	// ---------------------- Mesh
	if (App->CL_Vm_Model->Model_Loaded == 1 && ShowFaces == 1)
	{
		glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);

		if (App->CL_Vm_Model->Model_Type == LoadedFile_Assimp)
		{
			Assimp_Render_Faces();
		}

		if (App->CL_Vm_Model->Model_Type == LoadedFile_Actor)
		{
			RenderMeshOnly();
		}
	}

	// ---------------------- Points
	if (App->CL_Vm_Model->Model_Loaded == 1 && ShowPoints == 1)
	{
		//glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);

		if (App->CL_Vm_Model->Model_Type == LoadedFile_Assimp)
		{
			Assimp_Render_Points();
		}

		if (App->CL_Vm_Model->Model_Type == LoadedFile_Actor)
		{
			RenderPoints();
		}
	}

	// ---------------------- Normals
	if (App->CL_Vm_Model->Model_Loaded == 1 && ShowNormals == 1)
	{
		//glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);

		if (App->CL_Vm_Model->Model_Type == LoadedFile_Assimp)
		{
			Assimp_Render_Normals();
		}

		if (App->CL_Vm_Model->Model_Type == LoadedFile_Actor)
		{
			RF_Render_Normals();
		}
	}

	// ---------------------- Bounding Box
	if (App->CL_Vm_Model->Model_Loaded == 1 && ShowBoundingBox == 1)
	{
		//if (App->CL_Vm_Model->Model_Type == LoadedFile_Obj)
		{
			Render_BoundingBoxModel();
		}
		/*if (App->CL_Vm_Model->Model_Type == LoadedFile_Actor)
		{
			RenderPoints();
		}*/
	}

	// ---------------------- Bones
	if (App->CL_Vm_Model->Model_Loaded == 1 && ShowBones == 1)
	{
		As_RenderBones();	
	}

	// ---------------------- Crosshair
	if (Show_Crosshair == 1)
	{
		RenderCrossHair();	
	}


	if (depthTestEnabled)
	{
		glEnable(GL_DEPTH_TEST);
	}
	if (stencilTestEnabled)
	{
		glEnable(GL_STENCIL_TEST);
	}
}

// *************************************************************************
// *					Translate Terry Bernie							   *
// *************************************************************************
void VM_Render::Translate(void)
{
	
	glRotatef(RX,1.0,0.0,0.0); // Rotations of the object 

	glRotatef(RZ,0.0,1.0,0.0);
	glRotatef(0.0,0.0,0.0,1.0);
}

// *************************************************************************
// *						Assimp_Render_Faces Terry Bernie	   		   *
// *************************************************************************
bool VM_Render::Assimp_Render_Faces(void)
{
	int Count=0;

	glColor3f(1,1,1);
	
	while (Count<App->CL_Vm_Model->GroupCount)
	{
		Assimp_Face_Parts(Count);
		Count++;
	}

	return 1;
}
// *************************************************************************
// *					Assimp_Face_Parts Terry Bernie		   			   *
// *************************************************************************
bool VM_Render::Assimp_Face_Parts(int Count)
{
	int FaceCount=0;
	int A = 0;
	int B = 0;
	int C = 0;

	glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);

	while (FaceCount<App->CL_Vm_Model->S_MeshGroup[Count]->GroupFaceCount)
	{
		A = App->CL_Vm_Model->S_MeshGroup[Count]->Face_Data[FaceCount].a;
		B = App->CL_Vm_Model->S_MeshGroup[Count]->Face_Data[FaceCount].b;
		C = App->CL_Vm_Model->S_MeshGroup[Count]->Face_Data[FaceCount].c;

		glBegin(GL_POLYGON);

		//-----------------------------------------------
		glVertex3fv(&App->CL_Vm_Model->S_MeshGroup[Count]->vertex_Data[A].x);
		
		//-----------------------------------------------
		glVertex3fv(&App->CL_Vm_Model->S_MeshGroup[Count]->vertex_Data[B].x);
		
		//-----------------------------------------------
		glVertex3fv(&App->CL_Vm_Model->S_MeshGroup[Count]->vertex_Data[C].x);
		FaceCount++;
		//-----------------------------------------------

		glEnd();
	}

	return 1;
}

// *************************************************************************
// *						Assimp_Render_Points Terry Bernie	   		   *
// *************************************************************************
bool VM_Render::Assimp_Render_Points(void)
{
	int Count=0;

	glColor3f(1.0f, 1.0f, 0.0f);
	
	while (Count<App->CL_Vm_Model->GroupCount)
	{
		Render_As_Points_Parts(Count);
		Count++;
	}

	return 1;
}
// *************************************************************************
// *					Render_As_Points_Parts Terry Bernie	   			   *
// *************************************************************************
bool VM_Render::Render_As_Points_Parts(int Count)
{
	glPointSize(5);

	int VertCount=0;

	glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);

	while (VertCount<App->CL_Vm_Model->S_MeshGroup[Count]->GroupVertCount)
	{
		glBegin(GL_POINTS);

		glVertex3fv(&App->CL_Vm_Model->S_MeshGroup[Count]->vertex_Data[VertCount].x);
		
		glEnd();

		VertCount++;
	}

	return 1;
}


// *************************************************************************
// *						Assimp_Render_Textures_Terry Bernie	   		   *
// *************************************************************************
bool VM_Render::Assimp_Render_Textures(void)
{
	int Count=0;
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);
	glColor3f(1,1,1);

	//glLineWidth(10);

	if (ShowOnlySubMesh == 1) // Show Only Selected SubMesh
	{
		//Assimp_Textured_Parts(App->EBC_Groups->SelectedGroup);
		glDisable(GL_TEXTURE_2D);
		return 1;
	}

	//if (Show_HideGroup == 1) // Hide Selected SubMesh
	//{
	//	while (Count<App->CL_Vm_Model->GroupCount)
	//	{
	//		if (App->CL_Right_Groups->SelectedGroup == Count)
	//		{
	//		}
	//		else
	//		{
	//			Render_As_Textured_Parts(Count);
	//		}
	//		Count++;
	//	}

	//	glDisable(GL_TEXTURE_2D);
	//	return 1;
	//}

	while (Count<App->CL_Vm_Model->GroupCount)
	{
		Assimp_Textured_Parts(Count);
		Count++;
	}

	glDisable(GL_TEXTURE_2D);

	return 1;
}
// *************************************************************************
// *					Assimp_Textured_Parts Terry Bernie		 		   *
// *************************************************************************
bool VM_Render::Assimp_Textured_Parts(int Count)
{
	int VertCount=0;
	int A = 0;
	int B = 0;
	int C = 0;

	if (App->CL_Vm_Model->S_MeshGroup[Count]->MaterialIndex>-1)
	{
		glEnable(GL_TEXTURE_2D);
		glColor3f(1,1,1);

		glBindTexture(GL_TEXTURE_2D, App->CL_Vm_Textures->g_Texture[App->CL_Vm_Model->S_MeshGroup[Count]->MaterialIndex]);
	}
	else
	{
		glDisable(GL_TEXTURE_2D);
	}
	
	while (VertCount<App->CL_Vm_Model->S_MeshGroup[Count]->GroupFaceCount)
	{
		A = App->CL_Vm_Model->S_MeshGroup[Count]->Face_Data[VertCount].a;
		B = App->CL_Vm_Model->S_MeshGroup[Count]->Face_Data[VertCount].b;
		C = App->CL_Vm_Model->S_MeshGroup[Count]->Face_Data[VertCount].c;

		glBegin(GL_POLYGON);

		//-----------------------------------------------
		glTexCoord2f(App->CL_Vm_Model->S_MeshGroup[Count]->MapCord_Data[A].u,App->CL_Vm_Model->S_MeshGroup[Count]->MapCord_Data[A].v);
		glNormal3fv(&App->CL_Vm_Model->S_MeshGroup[Count]->Normal_Data[A].x);
		glVertex3fv(&App->CL_Vm_Model->S_MeshGroup[Count]->vertex_Data[A].x);
		//VertCount++;

		//-----------------------------------------------
		glTexCoord2f(App->CL_Vm_Model->S_MeshGroup[Count]->MapCord_Data[B].u,App->CL_Vm_Model->S_MeshGroup[Count]->MapCord_Data[B].v);
		glNormal3fv(&App->CL_Vm_Model->S_MeshGroup[Count]->Normal_Data[B].x);
		glVertex3fv(&App->CL_Vm_Model->S_MeshGroup[Count]->vertex_Data[B].x);
		//VertCount++;

		//-----------------------------------------------
		glTexCoord2f(App->CL_Vm_Model->S_MeshGroup[Count]->MapCord_Data[C].u,App->CL_Vm_Model->S_MeshGroup[Count]->MapCord_Data[C].v);
		glNormal3fv(&App->CL_Vm_Model->S_MeshGroup[Count]->Normal_Data[C].x);
		glVertex3fv(&App->CL_Vm_Model->S_MeshGroup[Count]->vertex_Data[C].x);
		VertCount++;
		//-----------------------------------------------

		glEnd();

	}

	return 1;
}

//*************************************************************************
// *					Assimp_Render_Normals Terry Bernie	   			   *
// *************************************************************************
void VM_Render::Assimp_Render_Normals(void)
{
	int Count=0;

	glColor3f(1,1,1);
	
	while (Count < App->CL_Vm_Model->GroupCount)
	{
		Render_As_Normals_Parts(Count);
		Count++;
	}
}
// *************************************************************************
// *					Render_AsNormals_Part Terry Bernie	   			   *
// *************************************************************************
void VM_Render::Render_As_Normals_Parts(int Count)
{
	#define Scaler 2

	int VertCount=0;

	glPointSize(3);
	glBegin(GL_LINES);

	while (VertCount<App->CL_Vm_Model->S_MeshGroup[Count]->GroupVertCount)
	{
		//-----------------------------------------------
		glVertex3fv(&App->CL_Vm_Model->S_MeshGroup[Count]->vertex_Data[VertCount].x);

		glVertex3f(App->CL_Vm_Model->S_MeshGroup[Count]->vertex_Data[VertCount].x+App->CL_Vm_Model->S_MeshGroup[Count]->Normal_Data[VertCount].x*Scaler,
			App->CL_Vm_Model->S_MeshGroup[Count]->vertex_Data[VertCount].y+App->CL_Vm_Model->S_MeshGroup[Count]->Normal_Data[VertCount].y*Scaler,
			App->CL_Vm_Model->S_MeshGroup[Count]->vertex_Data[VertCount].z+App->CL_Vm_Model->S_MeshGroup[Count]->Normal_Data[VertCount].z*Scaler);
		VertCount++;

	}

	glEnd();
}

// *************************************************************************
// *					RF_Render_Normals Terry Bernie		  			   *
// *************************************************************************
void VM_Render::RF_Render_Normals(void)
{
	
}

// *************************************************************************
// *				RenderBones 04/05/08   ( Terry Bernie ) 		  	   *
// *************************************************************************
bool VM_Render::As_RenderBones()
{

	glDisable (GL_TEXTURE_2D);
	glDisable (GL_DEPTH_TEST);
	int Start=0;

	glColor3f(1, 1, 0);
	glPointSize(6);//PointSize
	int Point=0;

	while (Start<App->CL_Vm_Model->BoneCount)
	{	

		if(App->CL_Vm_Model->S_Bones[Start]->Parent==-1)
		{
			glColor3f(1, 0, 0);			// Root Joint Colour
		}
		else{glColor3f(0,0 , 1);}		// Joint Colours
		
		glBegin(GL_POINTS); 
		glVertex3f(App->CL_Vm_Model->S_Bones[Start]->TranslationStart.X,
			App->CL_Vm_Model->S_Bones[Start]->TranslationStart.Y,
			App->CL_Vm_Model->S_Bones[Start]->TranslationStart.Z);   

		glEnd(); 
		Start++;
	}

	Start=0;
	while (Start<App->CL_Vm_Model->BoneCount)
	{	

		if(App->CL_Vm_Model->S_Bones[Start]->Parent==-1)
		{
			glColor3f(1, 0, 0);			// Root Joint Color Again Both the same
			glBegin(GL_POINTS); 
			glVertex3f(App->CL_Vm_Model->S_Bones[Start]->TranslationStart.X,
				App->CL_Vm_Model->S_Bones[Start]->TranslationStart.Y,
				App->CL_Vm_Model->S_Bones[Start]->TranslationStart.Z);  
			glEnd(); 
		}
		else
		{
			glLineWidth(3);
			glBegin(GL_LINES); 
			glColor3f(1,1,0);			// Bone Colours Between Joints
			glVertex3f(App->CL_Vm_Model->S_Bones[Start]->TranslationStart.X,
				App->CL_Vm_Model->S_Bones[Start]->TranslationStart.Y,
				App->CL_Vm_Model->S_Bones[Start]->TranslationStart.Z);   

			glVertex3f(App->CL_Vm_Model->S_Bones[App->CL_Vm_Model->S_Bones[Start]->Parent]->TranslationStart.X,
				App->CL_Vm_Model->S_Bones[App->CL_Vm_Model->S_Bones[Start]->Parent]->TranslationStart.Y,
				App->CL_Vm_Model->S_Bones[App->CL_Vm_Model->S_Bones[Start]->Parent]->TranslationStart.Z);  

			glEnd(); 
		}

		Start++;
	}

	return 1;
}

// *************************************************************************
// *				Render_BoundingBoxModel Terry Bernie	  			   *
// *************************************************************************
void VM_Render::Render_BoundingBoxModel(void)
{
	float m_xMin = App->CL_Vm_Model->S_BoundingBox[0]->BB_Min[0].x;
	float m_yMin = App->CL_Vm_Model->S_BoundingBox[0]->BB_Min[0].y;
	float m_zMin = App->CL_Vm_Model->S_BoundingBox[0]->BB_Min[0].z;

	float m_xMax = App->CL_Vm_Model->S_BoundingBox[0]->BB_Max[0].x;
	float m_yMax = App->CL_Vm_Model->S_BoundingBox[0]->BB_Max[0].y;
	float m_zMax = App->CL_Vm_Model->S_BoundingBox[0]->BB_Max[0].z;

	glDisable(GL_TEXTURE_2D);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);

	glVertex3f(m_xMin, m_yMin, m_zMin);
	glVertex3f(m_xMin, m_yMin, m_zMax);

	glVertex3f(m_xMax, m_yMin, m_zMin);
	glVertex3f(m_xMax, m_yMin, m_zMax);

	glVertex3f(m_xMin, m_yMax, m_zMin);
	glVertex3f(m_xMin, m_yMax, m_zMax);

	glVertex3f(m_xMax, m_yMax, m_zMin);
	glVertex3f(m_xMax, m_yMax, m_zMax);

	glVertex3f(m_xMin, m_yMin, m_zMin);
	glVertex3f(m_xMax, m_yMin, m_zMin);

	glVertex3f(m_xMin, m_yMin, m_zMin);
	glVertex3f(m_xMin, m_yMax, m_zMin);

	glVertex3f(m_xMax, m_yMin, m_zMin);
	glVertex3f(m_xMax, m_yMax, m_zMin);

	glVertex3f(m_xMin, m_yMax, m_zMin);
	glVertex3f(m_xMax, m_yMax, m_zMin);

	glVertex3f(m_xMin, m_yMin, m_zMax);
	glVertex3f(m_xMax, m_yMin, m_zMax);

	glVertex3f(m_xMin, m_yMin, m_zMax);
	glVertex3f(m_xMin, m_yMax, m_zMax);

	glVertex3f(m_xMax, m_yMin, m_zMax);
	glVertex3f(m_xMax, m_yMax, m_zMax);

	glVertex3f(m_xMin, m_yMax, m_zMax);
	glVertex3f(m_xMax, m_yMax, m_zMax);

	glEnd();
	glEnable(GL_TEXTURE_2D);
}

// *************************************************************************
// *					RF_Render_All_Groups  ( Terry Bernie ) 			   *
// *************************************************************************
bool VM_Render::RF_Render_All_Groups()
{
	

	return 1;
}

// *************************************************************************
// *					RF_Render_Just_Group  ( Terry Bernie )			   *
// *************************************************************************
bool VM_Render::RF_Render_Just_Group()
{
	

	return 1;
}

// *************************************************************************
// *					RenderMeshPartOnly Terry Bernie	   				   *
// *************************************************************************
bool VM_Render::RenderMeshOnly(void)
{
	int Count=0;
	int MatIndex=0;

	glColor3f(0.9f, 0.9f, 0.9f);
	while (Count<App->CL_Vm_Model->FaceCount)
	{
		//MatIndex = App->CL_Vm_Model->MatIndex_Data[Count];

		//if (MatIndex == App->CL_Vm_Groups->SelectedGroup)
		{
			glBegin(GL_POLYGON);
			glVertex3f(App->CL_Vm_Model->vertex_Data[App->CL_Vm_Model->Face_Data[Count].a].x, App->CL_Vm_Model->vertex_Data[App->CL_Vm_Model->Face_Data[Count].a].y, App->CL_Vm_Model->vertex_Data[App->CL_Vm_Model->Face_Data[Count].a].z);
			glVertex3f(App->CL_Vm_Model->vertex_Data[App->CL_Vm_Model->Face_Data[Count].b].x, App->CL_Vm_Model->vertex_Data[App->CL_Vm_Model->Face_Data[Count].b].y, App->CL_Vm_Model->vertex_Data[App->CL_Vm_Model->Face_Data[Count].b].z);
			glVertex3f(App->CL_Vm_Model->vertex_Data[App->CL_Vm_Model->Face_Data[Count].c].x, App->CL_Vm_Model->vertex_Data[App->CL_Vm_Model->Face_Data[Count].c].y, App->CL_Vm_Model->vertex_Data[App->CL_Vm_Model->Face_Data[Count].c].z);
			glEnd();
		}

		Count++;
	}

	return 1;
}

// *************************************************************************
// *					RenderPoints Terry Bernie						   *
// *************************************************************************
bool VM_Render::RenderPoints(void)
{
	int Count=0;
	glPointSize(5);

	glColor3f(1.0f, 1.0f, 0.0f);

	while (Count < App->CL_Vm_Model->VerticeCount)
	{
		glBegin(GL_POINTS);

		glVertex3fv(&App->CL_Vm_Model->vertex_Data[Count].x);
		
		glEnd();

		Count++;
	}

	return 1;
}

// **************************************************************************
// *					RenderCrossHair Terry Bernie						*
// **************************************************************************
void VM_Render::RenderCrossHair(void)
{
	glDisable (GL_TEXTURE_2D);
	glDisable (GL_DEPTH_TEST);

	float Length = 40;
	glLineWidth(3);

	glTranslatef(Hair_1PosX,Hair_1PosY,Hair_1PosZ);

	glRotatef(Hair_1RotX,1.0,0.0,0.0); // Rotations of the object 
	glRotatef(Hair_1RotY,0.0,1.0,0.0);
	glRotatef(Hair_1RotZ,0.0,0.0,1.0);

	glScalef(1,1,1);

	//-------------------------------------------  x hair] Blue
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f,1.0f); // Color
	glVertex3f(-Length,0,0);
	glVertex3f(0,0,0);
	glEnd();

	glBegin(GL_LINES);	
	glVertex3f(0,0,0);
	glVertex3f(Length,0,0);
	glEnd();

	//-------------------------------------------  z hair Red
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f,0.0f); // Color
	glVertex3f(0,0,-Length);
	glVertex3f(0,0,0);
	glEnd();

	glBegin(GL_LINES);	
	glVertex3f(0,0,0);
	glVertex3f(0,0,Length);
	glEnd();

	//-------------------------------------------  y hair Green
	glBegin(GL_LINES);
	glColor3f(0.0f, 1.0f,0.0f); // Color
	glVertex3f(0,-Length,0);
	glVertex3f(0,0,0);
	glEnd();

	glBegin(GL_LINES);	
	glVertex3f(0,0,0);
	glVertex3f(0,Length,0);
	glEnd();
}