/*
Copyright (c) 2022 Equity_ME Model Editor -- HGT Software W.T.Flanigan H.C.Flanigan

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
#include "ME_Export_Milkshape.h"


ME_Export_Milkshape::ME_Export_Milkshape()
{
	OutputFolder[0] = 0;

	WriteMILK = nullptr;
}


ME_Export_Milkshape::~ME_Export_Milkshape()
{
}

// *************************************************************************
// *					Assimp_To_Milk Terry Bernie					 	   *
// *************************************************************************
bool ME_Export_Milkshape::Export_To_Milk(bool DoMotions)
{
	strcpy(App->CL_FileIO->BrowserMessage, "Select Folder To Place Milk Files a sub folder will be created");
	int Test = App->CL_FileIO->StartBrowser("");

	if (Test == 0)
	{
		return 0;
	}

	OutputFolder[0] = 0;

	char buff[1024];
	strcpy(buff, App->CL_FileIO->szSelectedDir);
	strcat(buff, "\\");
	strcat(buff, App->CL_Model->JustName);
	strcat(buff, "_Milkshape");
	strcat(buff, "\\");

	strcpy(OutputFolder, buff);

	CreateDirectory(OutputFolder, NULL);


	if (App->CL_Model->Model_Type == Enums::LoadedFile_Assimp)
	{
		App->CL_Textures->DecompileTextures(OutputFolder);

		Write_MILKFile_Assimp();
	}

	//CleanUp();

	return 1;
}

// *************************************************************************
// *					Write_MILKFile_Assimp   Terry Flanigan		 	   *
// *************************************************************************
bool ME_Export_Milkshape::Write_MILKFile_Assimp(void)
{
	char buf[244];
	strcpy(buf, OutputFolder);
	strcat(buf, "\\");
	strcat(buf, App->CL_Model->JustName);
	strcat(buf, ".ms3d");

	WriteMILK = fopen(buf, "wb");
	if (!WriteMILK)
	{
		return 0;
	}

	word Zero = 0;

	Write_MILKHeader();

	float mFrames = 0;
	float CurrentTime = 0;

	int TotalFrames = 0;

	App->CL_Model->Convert_To_GlobalMesh();

	WriteMILKMesh_Assimp();
//	WriteMILKGroups_Assimp();
//	WriteMILKTexures_Assimp();

	fwrite(&mFrames, sizeof(float), 1, WriteMILK);
	fwrite(&CurrentTime, sizeof(float), 1, WriteMILK);
	fwrite(&TotalFrames, sizeof(int), 1, WriteMILK);

	fwrite(&Zero, sizeof(word), 1, WriteMILK);

	fclose(WriteMILK);

	return 1;
}

// *************************************************************************
// *					Write_MILKHeader Terry Flanigan				 	   *
// *************************************************************************
void ME_Export_Milkshape::Write_MILKHeader(void)
{
	Cms3d_header_t header;

	strcpy(header.id, "MS3D000000");
	header.version = 4;
	fwrite(&header, sizeof(Cms3d_header_t), 1, WriteMILK);
}

// *************************************************************************
// *					WriteMILKMesh   Terry Bernie					 	   *
// *************************************************************************
bool ME_Export_Milkshape::WriteMILKMesh_Assimp(void)
{

	word numMesh = App->CL_Model->VerticeCount;

	fwrite(&numMesh, 2, 1, WriteMILK);

	//-------------------------------------------- Vertices
	Cms3d_Vector3_t Mesh;

	int Count = 0;
	while (Count < App->CL_Model->VerticeCount)
	{
		Mesh.Vector3[0] = App->CL_Model->vertex_Data[Count].x;
		Mesh.Vector3[1] = App->CL_Model->vertex_Data[Count].y;
		Mesh.Vector3[2] = App->CL_Model->vertex_Data[Count].z;;

		Mesh.flags = 0;

		Mesh.jointId = -1;

		Mesh.referenceCount = 0;

		fwrite(&Mesh, sizeof(Cms3d_Vector3_t), 1, WriteMILK);
		Count++;
	}

	//-------------------------------------------- Faces
	word numFaces = App->CL_Model->FaceCount;

	fwrite(&numFaces, 2, 1, WriteMILK);

	Cms3d_triangle_t Face;
	Count = 0;

	//App->Say_Int(App->CL_Model_Data->FaceCount);

	while (Count < App->CL_Model->FaceCount)
	{
		int A = App->CL_Model->Face_Data[Count].a;
		int B = App->CL_Model->Face_Data[Count].b;
		int C = App->CL_Model->Face_Data[Count].c;

		Face.Vector3Indices[0] = App->CL_Model->Face_Data[Count].a;
		Face.Vector3Indices[1] = App->CL_Model->Face_Data[Count].b;
		Face.Vector3Indices[2] = App->CL_Model->Face_Data[Count].c;

		Face.flags = 0;

		// 3 Face UVs for Face
		Face.s[0] = App->CL_Model->MapCord_Data[A].u;
		Face.t[0] = 1 - App->CL_Model->MapCord_Data[A].v;

		Face.s[1] = App->CL_Model->MapCord_Data[B].u;
		Face.t[1] = 1 - App->CL_Model->MapCord_Data[B].v;

		Face.s[2] = App->CL_Model->MapCord_Data[C].u;
		Face.t[2] = 1 - App->CL_Model->MapCord_Data[C].v;


		// 3 Face Normals for Face
		Face.Vector3Normals[0][0] = App->CL_Model->Normal_Data[A].x;
		Face.Vector3Normals[0][1] = App->CL_Model->Normal_Data[A].y;
		Face.Vector3Normals[0][2] = App->CL_Model->Normal_Data[A].z;

		Face.Vector3Normals[1][0] = App->CL_Model->Normal_Data[B].x;
		Face.Vector3Normals[1][1] = App->CL_Model->Normal_Data[B].y;
		Face.Vector3Normals[1][2] = App->CL_Model->Normal_Data[B].z;

		Face.Vector3Normals[2][0] = App->CL_Model->Normal_Data[C].x;
		Face.Vector3Normals[2][1] = App->CL_Model->Normal_Data[C].y;
		Face.Vector3Normals[2][2] = App->CL_Model->Normal_Data[C].z;

		Face.groupIndex = App->CL_Model->Face_Data[Count].Group;

		fwrite(&Face, sizeof(Cms3d_triangle_t), 1, WriteMILK);

		Count++;
	}

	return 1;
}
