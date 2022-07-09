/*
Copyright (c) 2022 Equity_ME Model Editor -- Inflanite Software W.T.Flanigan H.C.Flanigan

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

#include "stdafx.h"
#include "ME_App.h"
#include "ME_Render.h"


ME_Render::ME_Render()
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

	//TestLight();
}


ME_Render::~ME_Render()
{
}

// *************************************************************************
// *						Reset_Class Terry Bernie					   *
// *************************************************************************
void ME_Render::Reset_Class(void)
{
	RX = 0;
	RZ = 0;

	Hair_1PosX = 0;
	Hair_1PosY = 0;
	Hair_1PosZ = 0;

	Hair_1RotX = 0;
	Hair_1RotY = 0;
	Hair_1RotZ = 0;

	ShowFaces = 1;
	ShowTextured = 0;
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
void ME_Render::TestLight(void)
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
void ME_Render::renderQueueStarted(Ogre::uint8 queueGroupId, const String& invocation, bool& skipThisInvocation)
{
}
// *************************************************************************
// *					renderQueueEnded Terry Bernie					   *
// *************************************************************************
void ME_Render::renderQueueEnded(Ogre::uint8 queueGroupId, const String& invocation, bool& repeatThisInvocation)
{
	/*if (App->CL_Vm_ImGui->Show_Progress_Bar == 1)
	{
		return;
	}*/

	if (queueGroupId != RENDER_QUEUE_MAIN)
	{
		return;
	}

	
	PreRender();


	Render_Loop();


	PostRender();
}
// *************************************************************************
// *				PreRender   Terry Bernie							   *
// *************************************************************************
void ME_Render::PreRender()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glMatrixMode(GL_TEXTURE);
	glPushMatrix();
	glLoadIdentity(); //Texture addressing should start out as direct.

	RenderSystem* renderSystem = App->CL_Ogre->manObj->_getManager()->getDestinationRenderSystem();
	Node* parentNode = App->CL_Ogre->manObj->getParentNode();
	renderSystem->_setWorldMatrix(parentNode->_getFullTransform());
	renderSystem->_setViewMatrix(App->CL_Ogre->mCamera->getViewMatrix());
	renderSystem->_setProjectionMatrix(App->CL_Ogre->mCamera->getProjectionMatrixRS());

	static Pass* clearPass = NULL;
	if (!clearPass)
	{
		MaterialPtr clearMat = MaterialManager::getSingleton().getByName("BaseWhite");
		clearPass = clearMat->getTechnique(0)->getPass(0);
	}
	//Set a clear pass to give the renderer a clear renderstate
	App->CL_Ogre->mSceneMgr->_setPass(clearPass, true, false);

	// save attribs
	glPushAttrib(GL_ALL_ATTRIB_BITS);
}
// *************************************************************************
// *				PostRender   Terry Bernie							   *
// *************************************************************************
void ME_Render::PostRender()
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
void ME_Render::Render_Loop()
{
	GLboolean depthTestEnabled = glIsEnabled(GL_DEPTH_TEST);
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


	 //---------------------- Textured
	if (App->CL_Model->Model_Loaded == 1 && ShowTextured == 1)
	{
		glEnable(GL_DEPTH_TEST);
		glShadeModel(GL_SMOOTH);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		if (App->CL_Model->Model_Type == Enums::LoadedFile_Actor)
		{
			RenderByTexture();
		}

		if (App->CL_Model->Model_Type == Enums::LoadedFile_Assimp)
		{
			Assimp_Render_Textures();
		}
	}

	// ---------------------- Mesh
	if (App->CL_Model->Model_Loaded == 1 && ShowFaces == 1)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		if (App->CL_Model->Model_Type == Enums::LoadedFile_Actor)
		{
			RF_Render_Faces();
		}

		if (App->CL_Model->Model_Type == Enums::LoadedFile_Assimp)
		{
			Assimp_Render_Faces();
		}
	}

	// ---------------------- Points
	if (App->CL_Model->Model_Loaded == 1 && ShowPoints == 1)
	{
		if (App->CL_Model->Model_Type == Enums::LoadedFile_Assimp)
		{
			Assimp_Render_Points();
		}
	}

	//// ---------------------- Normals
	if (App->CL_Model->Model_Loaded == 1 && ShowNormals == 1)
	{
		if (App->CL_Model->Model_Type == Enums::LoadedFile_Actor)
		{
			RF_Render_Normals();
		}

		if (App->CL_Model->Model_Type == Enums::LoadedFile_Assimp)
		{
			Assimp_Render_Normals();
		}
	}

	// ---------------------- Bounding Box
	if (App->CL_Model->Model_Loaded == 1 && ShowBoundingBox == 1)
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

	//// ---------------------- Bones
	if (App->CL_Model->Model_Loaded == 1 && ShowBones == 1)
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
void ME_Render::Translate(void)
{

	glRotatef(RX, 1.0, 0.0, 0.0); // Rotations of the object 

	glRotatef(RZ, 0.0, 1.0, 0.0);
	glRotatef(0.0, 0.0, 0.0, 1.0);
}

// *************************************************************************
// *						Assimp_Render_Faces Terry Bernie	   		   *
// *************************************************************************
bool ME_Render::Assimp_Render_Faces(void)
{
	int Count = 0;

	glColor3f(1, 1, 1);

	int GroupCount = App->CL_Model->Get_Groupt_Count();

	while (Count<GroupCount)
	{
		Assimp_Face_Parts(Count);
		Count++;
	}

	return 1;
}
// *************************************************************************
// *					Assimp_Face_Parts Terry Bernie		   			   *
// *************************************************************************
bool ME_Render::Assimp_Face_Parts(int Count)
{
	int FaceCount = 0;
	int A = 0;
	int B = 0;
	int C = 0;

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (FaceCount<App->CL_Model->Group[Count]->GroupFaceCount)
	{
		A = App->CL_Model->Group[Count]->Face_Data[FaceCount].a;
		B = App->CL_Model->Group[Count]->Face_Data[FaceCount].b;
		C = App->CL_Model->Group[Count]->Face_Data[FaceCount].c;

		glBegin(GL_POLYGON);

		//-----------------------------------------------
		glVertex3fv(&App->CL_Model->Group[Count]->vertex_Data[A].x);

		//-----------------------------------------------
		glVertex3fv(&App->CL_Model->Group[Count]->vertex_Data[B].x);

		//-----------------------------------------------
		glVertex3fv(&App->CL_Model->Group[Count]->vertex_Data[C].x);
		FaceCount++;
		//-----------------------------------------------

		glEnd();
	}

	return 1;
}

// *************************************************************************
// *						Assimp_Render_Points Terry Bernie	   		   *
// *************************************************************************
bool ME_Render::Assimp_Render_Points(void)
{
	int Count = 0;

	glColor3f(1.0f, 1.0f, 0.0f);

	int GroupCount = App->CL_Model->Get_Groupt_Count();

	while (Count < GroupCount)
	{
		Render_As_Points_Parts(Count);
		Count++;
	}

	return 1;
}
// *************************************************************************
// *					Render_As_Points_Parts Terry Bernie	   			   *
// *************************************************************************
bool ME_Render::Render_As_Points_Parts(int Count)
{
	glPointSize(5);

	int VertCount = 0;

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	int GroupVertCount = App->CL_Model->Group[Count]->GroupVertCount;

	while (VertCount < GroupVertCount)
	{
		glBegin(GL_POINTS);

		glVertex3fv(&App->CL_Model->Group[Count]->vertex_Data[VertCount].x);

		glEnd();

		VertCount++;
	}

	return 1;
}


// *************************************************************************
// *						Assimp_Render_Textures_Terry Bernie	   		   *
// *************************************************************************
bool ME_Render::Assimp_Render_Textures(void)
{
	int Count = 0;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);
	glColor3f(1, 1, 1);

	//glLineWidth(10);

	int GroupCount = App->CL_Model->Get_Groupt_Count();

	if (ShowOnlySubMesh == 1) // Show Only Selected SubMesh
	{
		Assimp_Textured_Parts(App->CL_Groups->Selected_Group);
		glDisable(GL_TEXTURE_2D);
		return 1;
	}

	Count = 0;
	if (Show_HideGroup == 1) // Hide Selected SubMesh
	{
		while (Count < GroupCount)
		{
			if (App->CL_Groups->Selected_Group == Count)
			{
			}
			else
			{
				Assimp_Textured_Parts(Count);
			}
			Count++;
		}

		glDisable(GL_TEXTURE_2D);
		return 1;
	}

	Count = 0;
	while (Count < GroupCount)
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
bool ME_Render::Assimp_Textured_Parts(int Count)
{
	int VertCount = 0;
	int A = 0;
	int B = 0;
	int C = 0;

	if (App->CL_Model->Group[Count]->MaterialIndex > -1)
	{
		glEnable(GL_TEXTURE_2D);
		glColor3f(1, 1, 1);

		glBindTexture(GL_TEXTURE_2D, App->CL_Textures->g_Texture[App->CL_Model->Group[Count]->MaterialIndex]);
	}
	else
	{
		glDisable(GL_TEXTURE_2D);
	}

	while (VertCount<App->CL_Model->Group[Count]->GroupFaceCount)
	{
		A = App->CL_Model->Group[Count]->Face_Data[VertCount].a;
		B = App->CL_Model->Group[Count]->Face_Data[VertCount].b;
		C = App->CL_Model->Group[Count]->Face_Data[VertCount].c;

		glBegin(GL_POLYGON);

		//-----------------------------------------------
		glTexCoord2f(App->CL_Model->Group[Count]->MapCord_Data[A].u, App->CL_Model->Group[Count]->MapCord_Data[A].v);
		glNormal3fv(&App->CL_Model->Group[Count]->Normal_Data[A].x);
		glVertex3fv(&App->CL_Model->Group[Count]->vertex_Data[A].x);
		//VertCount++;

		//-----------------------------------------------
		glTexCoord2f(App->CL_Model->Group[Count]->MapCord_Data[B].u, App->CL_Model->Group[Count]->MapCord_Data[B].v);
		glNormal3fv(&App->CL_Model->Group[Count]->Normal_Data[B].x);
		glVertex3fv(&App->CL_Model->Group[Count]->vertex_Data[B].x);
		//VertCount++;

		//-----------------------------------------------
		glTexCoord2f(App->CL_Model->Group[Count]->MapCord_Data[C].u, App->CL_Model->Group[Count]->MapCord_Data[C].v);
		glNormal3fv(&App->CL_Model->Group[Count]->Normal_Data[C].x);
		glVertex3fv(&App->CL_Model->Group[Count]->vertex_Data[C].x);
		VertCount++;
		//-----------------------------------------------

		glEnd();

	}

	return 1;
}

//*************************************************************************
// *					Assimp_Render_Normals Terry Bernie	   			   *
// *************************************************************************
void ME_Render::Assimp_Render_Normals(void)
{
	int Count = 0;

	glColor3f(1, 1, 1);

	int GroupCount = App->CL_Model->Get_Groupt_Count();

	while (Count < GroupCount)
	{
		Render_As_Normals_Parts(Count);
		Count++;
	}
}
// *************************************************************************
// *					Render_AsNormals_Part Terry Bernie	   			   *
// *************************************************************************
void ME_Render::Render_As_Normals_Parts(int Count)
{
#define Scaler 2

	int VertCount = 0;

	glPointSize(3);
	glBegin(GL_LINES);

	while (VertCount<App->CL_Model->Group[Count]->GroupVertCount)
	{
		//-----------------------------------------------
		glVertex3fv(&App->CL_Model->Group[Count]->vertex_Data[VertCount].x);

		glVertex3f(App->CL_Model->Group[Count]->vertex_Data[VertCount].x + App->CL_Model->Group[Count]->Normal_Data[VertCount].x*Scaler,
			App->CL_Model->Group[Count]->vertex_Data[VertCount].y + App->CL_Model->Group[Count]->Normal_Data[VertCount].y*Scaler,
			App->CL_Model->Group[Count]->vertex_Data[VertCount].z + App->CL_Model->Group[Count]->Normal_Data[VertCount].z*Scaler);
		VertCount++;

	}

	glEnd();
}

// *************************************************************************
// *					RF_Render_Normals Terry Bernie		  			   *
// *************************************************************************
void ME_Render::RF_Render_Normals(void)
{
#define t 2

	geBody_Index V1;
	geBody_Index V2;
	geBody_Index V3;

	const geBody_Triangle *SF;

	SF = App->CL_Genesis3D->ActorDef_Memory->Body->SkinFaces[GE_BODY_HIGHEST_LOD].FaceArray;

	int Start = 0;
	glPointSize(3);//PointSize
	glBegin(GL_LINES);

	while (Start < App->CL_Model->FaceCount)
	{

		glColor3f(1, 1, 0);

		int indexA = App->CL_Model->Face_Data[Start].a;
		int indexB = App->CL_Model->Face_Data[Start].b;
		int indexC = App->CL_Model->Face_Data[Start].c;

		V1 = SF[Start].NormalIndex[0];
		V2 = SF[Start].NormalIndex[1];
		V3 = SF[Start].NormalIndex[2];


		glVertex3f(App->CL_Model->vertex_Data[indexA].x, App->CL_Model->vertex_Data[indexA].y, App->CL_Model->vertex_Data[indexA].z);

		glVertex3f(App->CL_Model->vertex_Data[indexA].x + App->CL_Model->Normal_Data[V1].x*t,
			App->CL_Model->vertex_Data[indexA].y + App->CL_Model->Normal_Data[V1].y*t,
			App->CL_Model->vertex_Data[indexA].z + App->CL_Model->Normal_Data[V1].z*t);

		glVertex3f(App->CL_Model->vertex_Data[indexB].x, App->CL_Model->vertex_Data[indexB].y, App->CL_Model->vertex_Data[indexB].z);

		glVertex3f(App->CL_Model->vertex_Data[indexB].x + App->CL_Model->Normal_Data[V2].x*t,
			App->CL_Model->vertex_Data[indexB].y + App->CL_Model->Normal_Data[V2].y*t,
			App->CL_Model->vertex_Data[indexB].z + App->CL_Model->Normal_Data[V2].z*t);

		glVertex3f(App->CL_Model->vertex_Data[indexC].x, App->CL_Model->vertex_Data[indexC].y, App->CL_Model->vertex_Data[indexC].z);

		glVertex3f(App->CL_Model->vertex_Data[indexC].x + App->CL_Model->Normal_Data[V3].x*t,
			App->CL_Model->vertex_Data[indexC].y + App->CL_Model->Normal_Data[V3].y*t,
			App->CL_Model->vertex_Data[indexC].z + App->CL_Model->Normal_Data[V3].z*t);

		Start++;
	}

	glEnd();
}

// *************************************************************************
// *				RenderBones 04/05/08   ( Terry Bernie ) 		  	   *
// *************************************************************************
bool ME_Render::As_RenderBones()
{

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	int Start = 0;

	glColor3f(1, 1, 0);
	glPointSize(6);//PointSize
	int Point = 0;

	while (Start<App->CL_Model->BoneCount)
	{

		if (App->CL_Model->S_Bones[Start]->Parent == -1)
		{
			glColor3f(1, 0, 0);			// Root Joint Colour
		}
		else { glColor3f(0, 0, 1); }		// Joint Colours

		glBegin(GL_POINTS);
		glVertex3f(App->CL_Model->S_Bones[Start]->TranslationStart.X,
			App->CL_Model->S_Bones[Start]->TranslationStart.Y,
			App->CL_Model->S_Bones[Start]->TranslationStart.Z);

		glEnd();
		Start++;
	}

	Start = 0;
	while (Start<App->CL_Model->BoneCount)
	{

		if (App->CL_Model->S_Bones[Start]->Parent == -1)
		{
			glColor3f(1, 0, 0);			// Root Joint Color Again Both the same
			glBegin(GL_POINTS);
			glVertex3f(App->CL_Model->S_Bones[Start]->TranslationStart.X,
				App->CL_Model->S_Bones[Start]->TranslationStart.Y,
				App->CL_Model->S_Bones[Start]->TranslationStart.Z);
			glEnd();
		}
		else
		{
			glLineWidth(3);
			glBegin(GL_LINES);
			glColor3f(1, 1, 0);			// Bone Colours Between Joints
			glVertex3f(App->CL_Model->S_Bones[Start]->TranslationStart.X,
				App->CL_Model->S_Bones[Start]->TranslationStart.Y,
				App->CL_Model->S_Bones[Start]->TranslationStart.Z);

			glVertex3f(App->CL_Model->S_Bones[App->CL_Model->S_Bones[Start]->Parent]->TranslationStart.X,
				App->CL_Model->S_Bones[App->CL_Model->S_Bones[Start]->Parent]->TranslationStart.Y,
				App->CL_Model->S_Bones[App->CL_Model->S_Bones[Start]->Parent]->TranslationStart.Z);

			glEnd();
		}

		Start++;
	}

	return 1;
}

// *************************************************************************
// *				Render_BoundingBoxModel Terry Bernie	  			   *
// *************************************************************************
void ME_Render::Render_BoundingBoxModel(void)
{
	float m_xMin = App->CL_Model->S_BoundingBox[0]->BB_Min[0].x;
	float m_yMin = App->CL_Model->S_BoundingBox[0]->BB_Min[0].y;
	float m_zMin = App->CL_Model->S_BoundingBox[0]->BB_Min[0].z;

	float m_xMax = App->CL_Model->S_BoundingBox[0]->BB_Max[0].x;
	float m_yMax = App->CL_Model->S_BoundingBox[0]->BB_Max[0].y;
	float m_zMax = App->CL_Model->S_BoundingBox[0]->BB_Max[0].z;

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
bool ME_Render::RF_Render_All_Groups()
{
	//const geBody_Triangle *SF;
	//SF = App->CL_Vm_Genesis3D->ActorDef_Memory->Body->SkinFaces[GE_BODY_HIGHEST_LOD].FaceArray;

	//int Count = 0;
	//int MatIndex;
	//int UVIndex = 0;

	//float x = 0;
	//float y = 0;
	//float z = 0;

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glEnable(GL_TEXTURE_2D);
	//glColor3f(1, 1, 1);
	//glEnable(GL_ALPHA_TEST);

	//while (Count < App->CL_Vm_Model->FaceCount)
	//{
	//	MatIndex = App->CL_Vm_Model->MatIndex_Data[Count];

	//	glBindTexture(GL_TEXTURE_2D, App->CL_Vm_Textures->g_Texture[MatIndex]);

	//	glBegin(GL_POLYGON);

	//	x = App->CL_Vm_Model->vertex_Data[App->CL_Vm_Model->Face_Data[Count].a].x;
	//	y = App->CL_Vm_Model->vertex_Data[App->CL_Vm_Model->Face_Data[Count].a].y;
	//	z = App->CL_Vm_Model->vertex_Data[App->CL_Vm_Model->Face_Data[Count].a].z;


	//	glNormal3f(App->CL_Vm_Model->Normal_Data[SF[Count].NormalIndex[0]].x, App->CL_Vm_Model->Normal_Data[SF[Count].NormalIndex[0]].y, App->CL_Vm_Model->Normal_Data[SF[Count].NormalIndex[0]].z);
	//	glTexCoord2f(App->CL_Vm_Model->MapCord_Data[App->CL_Vm_Model->Face_Data[Count].a].u, App->CL_Vm_Model->MapCord_Data[App->CL_Vm_Model->Face_Data[Count].a].v);
	//	glVertex3f(x, y, z);//Vertex definition

	//	x = App->CL_Vm_Model->vertex_Data[App->CL_Vm_Model->Face_Data[Count].b].x;
	//	y = App->CL_Vm_Model->vertex_Data[App->CL_Vm_Model->Face_Data[Count].b].y;
	//	z = App->CL_Vm_Model->vertex_Data[App->CL_Vm_Model->Face_Data[Count].b].z;


	//	glNormal3f(App->CL_Vm_Model->Normal_Data[SF[Count].NormalIndex[1]].x, App->CL_Vm_Model->Normal_Data[SF[Count].NormalIndex[1]].y, App->CL_Vm_Model->Normal_Data[SF[Count].NormalIndex[1]].z);
	//	glTexCoord2f(App->CL_Vm_Model->MapCord_Data[App->CL_Vm_Model->Face_Data[Count].b].u, App->CL_Vm_Model->MapCord_Data[App->CL_Vm_Model->Face_Data[Count].b].v);
	//	glVertex3f(x, y, z);

	//	x = App->CL_Vm_Model->vertex_Data[App->CL_Vm_Model->Face_Data[Count].c].x;
	//	y = App->CL_Vm_Model->vertex_Data[App->CL_Vm_Model->Face_Data[Count].c].y;
	//	z = App->CL_Vm_Model->vertex_Data[App->CL_Vm_Model->Face_Data[Count].c].z;

	//	glNormal3f(App->CL_Vm_Model->Normal_Data[SF[Count].NormalIndex[2]].x, App->CL_Vm_Model->Normal_Data[SF[Count].NormalIndex[2]].y, App->CL_Vm_Model->Normal_Data[SF[Count].NormalIndex[2]].z);
	//	glTexCoord2f(App->CL_Vm_Model->MapCord_Data[App->CL_Vm_Model->Face_Data[Count].c].u, App->CL_Vm_Model->MapCord_Data[App->CL_Vm_Model->Face_Data[Count].c].v);
	//	glVertex3f(x, y, z);

	//	glEnd();

	//	Count++;
	//}

	//glDisable(GL_TEXTURE_2D);
	//glDisable(GL_ALPHA_TEST);

	return 1;
}

// *************************************************************************
// *					RF_Render_Just_Group  ( Terry Bernie )			   *
// *************************************************************************
bool ME_Render::RF_Render_Just_Group()
{
	//const geBody_Triangle *SF;
	//SF = App->CL_Vm_Genesis3D->ActorDef_Memory->Body->SkinFaces[GE_BODY_HIGHEST_LOD].FaceArray;

	//int Count = 0;
	//int MatIndex;
	//int UVIndex = 0;

	//float x = 0;
	//float y = 0;
	//float z = 0;

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glEnable(GL_TEXTURE_2D);
	//glColor3f(1, 1, 1);
	//glEnable(GL_ALPHA_TEST);

	//int SelectedIndex = App->CL_Vm_Model->S_TextureInfo[App->EBC_Groups->SelectedGroup]->ActorMaterialIndex;

	//while (Count<App->CL_Vm_Model->FaceCount)
	//{
	//	MatIndex = App->CL_Vm_Model->MatIndex_Data[Count];

	//	if (MatIndex == SelectedIndex)
	//	{

	//		glBindTexture(GL_TEXTURE_2D, App->CL_Vm_Textures->g_Texture[MatIndex]);

	//		glBegin(GL_POLYGON);

	//		x = App->CL_Vm_Model->vertex_Data[App->CL_Vm_Model->Face_Data[Count].a].x;
	//		y = App->CL_Vm_Model->vertex_Data[App->CL_Vm_Model->Face_Data[Count].a].y;
	//		z = App->CL_Vm_Model->vertex_Data[App->CL_Vm_Model->Face_Data[Count].a].z;


	//		glNormal3f(App->CL_Vm_Model->Normal_Data[SF[Count].NormalIndex[0]].x, App->CL_Vm_Model->Normal_Data[SF[Count].NormalIndex[0]].y, App->CL_Vm_Model->Normal_Data[SF[Count].NormalIndex[0]].z);
	//		glTexCoord2f(App->CL_Vm_Model->MapCord_Data[App->CL_Vm_Model->Face_Data[Count].a].u, App->CL_Vm_Model->MapCord_Data[App->CL_Vm_Model->Face_Data[Count].a].v);
	//		glVertex3f(x, y, z);//Vertex definition

	//		x = App->CL_Vm_Model->vertex_Data[App->CL_Vm_Model->Face_Data[Count].b].x;
	//		y = App->CL_Vm_Model->vertex_Data[App->CL_Vm_Model->Face_Data[Count].b].y;
	//		z = App->CL_Vm_Model->vertex_Data[App->CL_Vm_Model->Face_Data[Count].b].z;


	//		glNormal3f(App->CL_Vm_Model->Normal_Data[SF[Count].NormalIndex[1]].x, App->CL_Vm_Model->Normal_Data[SF[Count].NormalIndex[1]].y, App->CL_Vm_Model->Normal_Data[SF[Count].NormalIndex[1]].z);
	//		glTexCoord2f(App->CL_Vm_Model->MapCord_Data[App->CL_Vm_Model->Face_Data[Count].b].u, App->CL_Vm_Model->MapCord_Data[App->CL_Vm_Model->Face_Data[Count].b].v);
	//		glVertex3f(x, y, z);

	//		x = App->CL_Vm_Model->vertex_Data[App->CL_Vm_Model->Face_Data[Count].c].x;
	//		y = App->CL_Vm_Model->vertex_Data[App->CL_Vm_Model->Face_Data[Count].c].y;
	//		z = App->CL_Vm_Model->vertex_Data[App->CL_Vm_Model->Face_Data[Count].c].z;

	//		glNormal3f(App->CL_Vm_Model->Normal_Data[SF[Count].NormalIndex[2]].x, App->CL_Vm_Model->Normal_Data[SF[Count].NormalIndex[2]].y, App->CL_Vm_Model->Normal_Data[SF[Count].NormalIndex[2]].z);
	//		glTexCoord2f(App->CL_Vm_Model->MapCord_Data[App->CL_Vm_Model->Face_Data[Count].c].u, App->CL_Vm_Model->MapCord_Data[App->CL_Vm_Model->Face_Data[Count].c].v);
	//		glVertex3f(x, y, z);

	//		glEnd();
	//	}

	//	Count++;
	//}

	//glDisable(GL_TEXTURE_2D);
	//glDisable(GL_ALPHA_TEST);

	return 1;
}

// *************************************************************************
// *					RF_Render_Faces Terry Bernie	   				   *
// *************************************************************************
bool ME_Render::RF_Render_Faces(void)
{
	int Count = 0;
	int MatIndex = 0;

	glColor3f(0.9f, 0.9f, 0.9f);
	while (Count < App->CL_Model->FaceCount)
	{
		glBegin(GL_POLYGON);
		glVertex3f(App->CL_Model->vertex_Data[App->CL_Model->Face_Data[Count].a].x, App->CL_Model->vertex_Data[App->CL_Model->Face_Data[Count].a].y, App->CL_Model->vertex_Data[App->CL_Model->Face_Data[Count].a].z);
		glVertex3f(App->CL_Model->vertex_Data[App->CL_Model->Face_Data[Count].b].x, App->CL_Model->vertex_Data[App->CL_Model->Face_Data[Count].b].y, App->CL_Model->vertex_Data[App->CL_Model->Face_Data[Count].b].z);
		glVertex3f(App->CL_Model->vertex_Data[App->CL_Model->Face_Data[Count].c].x, App->CL_Model->vertex_Data[App->CL_Model->Face_Data[Count].c].y, App->CL_Model->vertex_Data[App->CL_Model->Face_Data[Count].c].z);
		glEnd();

		Count++;
	}

	return 1;
}

// *************************************************************************
// *					RenderPoints Terry Bernie						   *
// *************************************************************************
bool ME_Render::RenderPoints(void)
{
	/*int Count = 0;
	glPointSize(5);

	glColor3f(1.0f, 1.0f, 0.0f);

	while (Count < App->CL_Vm_Model->VerticeCount)
	{
		glBegin(GL_POINTS);

		glVertex3fv(&App->CL_Vm_Model->vertex_Data[Count].x);

		glEnd();

		Count++;
	}*/

	return 1;
}

// **************************************************************************
// *					RenderCrossHair Terry Bernie						*
// **************************************************************************
void ME_Render::RenderCrossHair(void)
{
	glDisable(GL_TEXTURE_2D);
	//glDisable(GL_DEPTH_TEST);

	//float Length = App->CL_Model->S_BoundingBox[0]->radius * 2;
	float Length = 40;
	glLineWidth(3);

	glTranslatef(Hair_1PosX, Hair_1PosY, Hair_1PosZ);

	glRotatef(Hair_1RotX, 1.0, 0.0, 0.0); // Rotations of the object 
	glRotatef(Hair_1RotY, 0.0, 1.0, 0.0);
	glRotatef(Hair_1RotZ, 0.0, 0.0, 1.0);

	glScalef(1, 1, 1);

	//-------------------------------------------  x hair] Blue
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 1.0f); // Color
	glVertex3f(-Length, 0, 0);
	glVertex3f(0, 0, 0);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(Length, 0, 0);
	glEnd();

	//-------------------------------------------  z hair Red
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f); // Color
	glVertex3f(0, 0, -Length);
	glVertex3f(0, 0, 0);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, Length);
	glEnd();

	//-------------------------------------------  y hair Green
	glBegin(GL_LINES);
	glColor3f(0.0f, 1.0f, 0.0f); // Color
	glVertex3f(0, -Length, 0);
	glVertex3f(0, 0, 0);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, Length, 0);
	glEnd();
}

// *************************************************************************
// *					RenderByTexture  ( Terry Bernie ) 				   *
// *************************************************************************
bool ME_Render::RenderByTexture()
{
	const geBody_Triangle *SF;
	SF = App->CL_Genesis3D->ActorDef_Memory->Body->SkinFaces[GE_BODY_HIGHEST_LOD].FaceArray;

	int Count = 0;
	int MatIndex;
	int UVIndex = 0;

	float x = 0;
	float y = 0;
	float z = 0;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);
	glColor3f(1, 1, 1);
	glEnable(GL_ALPHA_TEST);

	while (Count<App->CL_Model->FaceCount)
	{
		//MatIndex = App->CL_Genesis_Import->ActorDef_Memory->Body->SkinFaces[GE_BODY_HIGHEST_LOD].FaceArray[Count].MaterialIndex;
		MatIndex = App->CL_Model->MatIndex_Data[Count];

		glBindTexture(GL_TEXTURE_2D, App->CL_Textures->g_Texture[MatIndex]);

		glBegin(GL_POLYGON);

		x = App->CL_Model->vertex_Data[App->CL_Model->Face_Data[Count].a].x;
		y = App->CL_Model->vertex_Data[App->CL_Model->Face_Data[Count].a].y;
		z = App->CL_Model->vertex_Data[App->CL_Model->Face_Data[Count].a].z;


		glNormal3f(App->CL_Model->Normal_Data[SF[Count].NormalIndex[0]].x, App->CL_Model->Normal_Data[SF[Count].NormalIndex[0]].y, App->CL_Model->Normal_Data[SF[Count].NormalIndex[0]].z);
		glTexCoord2f(App->CL_Model->MapCord_Data[App->CL_Model->Face_Data[Count].a].u, App->CL_Model->MapCord_Data[App->CL_Model->Face_Data[Count].a].v);
		glVertex3f(x, y, z);//Vertex definition

		x = App->CL_Model->vertex_Data[App->CL_Model->Face_Data[Count].b].x;
		y = App->CL_Model->vertex_Data[App->CL_Model->Face_Data[Count].b].y;
		z = App->CL_Model->vertex_Data[App->CL_Model->Face_Data[Count].b].z;


		glNormal3f(App->CL_Model->Normal_Data[SF[Count].NormalIndex[1]].x, App->CL_Model->Normal_Data[SF[Count].NormalIndex[1]].y, App->CL_Model->Normal_Data[SF[Count].NormalIndex[1]].z);
		glTexCoord2f(App->CL_Model->MapCord_Data[App->CL_Model->Face_Data[Count].b].u, App->CL_Model->MapCord_Data[App->CL_Model->Face_Data[Count].b].v);
		glVertex3f(x, y, z);

		x = App->CL_Model->vertex_Data[App->CL_Model->Face_Data[Count].c].x;
		y = App->CL_Model->vertex_Data[App->CL_Model->Face_Data[Count].c].y;
		z = App->CL_Model->vertex_Data[App->CL_Model->Face_Data[Count].c].z;

		glNormal3f(App->CL_Model->Normal_Data[SF[Count].NormalIndex[2]].x, App->CL_Model->Normal_Data[SF[Count].NormalIndex[2]].y, App->CL_Model->Normal_Data[SF[Count].NormalIndex[2]].z);
		glTexCoord2f(App->CL_Model->MapCord_Data[App->CL_Model->Face_Data[Count].c].u, App->CL_Model->MapCord_Data[App->CL_Model->Face_Data[Count].c].v);
		glVertex3f(x, y, z);

		glEnd();

		Count++;
	}

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_ALPHA_TEST);

	return 1;
}
