/*
Copyright (c) 2023 World Editor -- HGT Software W.T.Flanigan H.C.Flanigan

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
#include "AB_App.h"
#include "SB_Export_Milkshape.h"

SB_Export_Milkshape::SB_Export_Milkshape()
{
	OutputFolder[0] = 0;
	Text_FileName[0] = 0;
	MaterialName[0] = 0;

	WriteMILK = nullptr;
}

SB_Export_Milkshape::~SB_Export_Milkshape()
{
}

// *************************************************************************
// *			Export_To_Milk:- Terry and Hazel Flanigan 2023             *
// *************************************************************************
bool SB_Export_Milkshape::Export_To_Milk(bool DoMotions)
{
	strcpy(App->CLSB_FileIO->BrowserMessage, "Select Folder To Place Milk Files a sub folder will be created");
	int Test = App->CLSB_FileIO->StartBrowser("");

	if (Test == 0)
	{
		return 0;
	}

	OutputFolder[0] = 0;

	char buff[1024];
	strcpy(buff, App->CLSB_FileIO->szSelectedDir);
	strcat(buff, "\\");
	strcat(buff, App->CLSB_Model->JustName);
	strcat(buff, "_Milkshape");
	strcat(buff, "\\");

	strcpy(OutputFolder, buff);

	CreateDirectory(OutputFolder, NULL);


	if (App->CLSB_Model->Model_Type == Enums::LoadedFile_Assimp)
	{
		//App->CL_Textures->DecompileTextures(OutputFolder);

		Write_MILK_File();
	}

	//CleanUp();

	return 1;
}

// *************************************************************************
// *			Write_MILKFile:- Terry and Hazel Flanigan 2023	 		   *
// *************************************************************************
bool SB_Export_Milkshape::Write_MILK_File(void)
{
	char buf[244];
	strcpy(buf, OutputFolder);
	strcat(buf, "\\");
	strcat(buf, App->CLSB_Model->JustName);
	strcat(buf, ".ms3d");

	WriteMILK = fopen(buf, "wb");
	if (!WriteMILK)
	{
		return 0;
	}

	word Zero = 0;

	Write_MILK_Header();

	float mFrames = 0;
	float CurrentTime = 0;

	int TotalFrames = 0;

	Convert_To_GlobalMesh();

	

	Write_MILK_Mesh();
	Write_MILK_Groups();
	Write_MILK_Texures();

	fwrite(&mFrames, sizeof(float), 1, WriteMILK);
	fwrite(&CurrentTime, sizeof(float), 1, WriteMILK);
	fwrite(&TotalFrames, sizeof(int), 1, WriteMILK);

	fwrite(&Zero, sizeof(word), 1, WriteMILK);

	fclose(WriteMILK);

	return 1;
}

// *************************************************************************
// *		Write_MILKHeader:- Terry and Hazel Flanigan 2023		 	   *
// *************************************************************************
void SB_Export_Milkshape::Write_MILK_Header(void)
{
	Cms3d_header_t header;

	strcpy(header.id, "MS3D000000");
	header.version = 4;
	fwrite(&header, sizeof(Cms3d_header_t), 1, WriteMILK);
}

// *************************************************************************
// *		Convert_To_GlobalMesh:- Terry and Hazel Flanigan 2023  	 	   *
// *************************************************************************
void SB_Export_Milkshape::Convert_To_GlobalMesh(void)
{
	int Count = 0;
	int GroupVertCount = 0;
	int GroupFaceCount = 0;
	int VC = 0;

	int Offset = 0;

	vertex_Data.resize(App->CLSB_Model->VerticeCount);
	Face_Data.resize(1000);// App->CLSB_Model->FaceCount);

	Normal_Data.resize(App->CLSB_Model->VerticeCount);
	MapCord_Data.resize(App->CLSB_Model->VerticeCount);
	MatIndex_Data.resize(App->CLSB_Model->VerticeCount);

	while (Count < App->CLSB_Model->GroupCount)
	{
		GroupVertCount = 0;

		while (GroupVertCount < App->CLSB_Model->Group[Count]->GroupVertCount)
		{
			vertex_Data[VC].x = App->CLSB_Model->Group[Count]->vertex_Data[GroupVertCount].x;
			vertex_Data[VC].y = App->CLSB_Model->Group[Count]->vertex_Data[GroupVertCount].y;
			vertex_Data[VC].z = App->CLSB_Model->Group[Count]->vertex_Data[GroupVertCount].z;

			MapCord_Data[VC].u = App->CLSB_Model->Group[Count]->MapCord_Data[GroupVertCount].u;
			MapCord_Data[VC].v = App->CLSB_Model->Group[Count]->MapCord_Data[GroupVertCount].v;

			Normal_Data[VC].x = App->CLSB_Model->Group[Count]->Normal_Data[GroupVertCount].x;
			Normal_Data[VC].y = App->CLSB_Model->Group[Count]->Normal_Data[GroupVertCount].y;
			Normal_Data[VC].z = App->CLSB_Model->Group[Count]->Normal_Data[GroupVertCount].z;

			VC++;

			GroupVertCount++;
		}

		Count++;
	}

	VC = 0;
	Count = 0;
	int mFaceCount = 0;
	while (Count < App->CLSB_Model->GroupCount)
	{
		mFaceCount = 0;
		while (mFaceCount < App->CLSB_Model->Group[Count]->GroupFaceCount)
		{

			Face_Data[VC].Group = Count;

			Face_Data[VC].a = App->CLSB_Model->Group[Count]->Face_Data[mFaceCount].a + Offset;
			Face_Data[VC].b = App->CLSB_Model->Group[Count]->Face_Data[mFaceCount].b + Offset;
			Face_Data[VC].c = App->CLSB_Model->Group[Count]->Face_Data[mFaceCount].c + Offset;

			VC++;
			mFaceCount++;
		}

		Offset = Offset + App->CLSB_Model->Group[Count]->GroupVertCount;
		Count++;

	}

	VC = 0;
	Count = 0;
	while (Count < App->CLSB_Model->GroupCount)
	{
		GroupFaceCount = 0;

		while (GroupFaceCount < App->CLSB_Model->Group[Count]->GroupFaceCount)
		{
			MatIndex_Data[VC] = App->CLSB_Model->Group[Count]->MaterialIndex;

			VC++;
			GroupFaceCount++;
		}

		Count++;
	}
}

// *************************************************************************
// *			WriteMILKMesh:- Terry and Hazel Flanigan 2023		 	   *
// *************************************************************************
bool SB_Export_Milkshape::Write_MILK_Mesh(void)
{

	word numMesh = App->CLSB_Model->VerticeCount;

	fwrite(&numMesh, 2, 1, WriteMILK);

	//-------------------------------------------- Vertices
	Cms3d_Vector3_t Mesh;

	int Count = 0;
	while (Count < App->CLSB_Model->VerticeCount)
	{
		Mesh.Vector3[0] = vertex_Data[Count].x;
		Mesh.Vector3[1] = vertex_Data[Count].y;
		Mesh.Vector3[2] = vertex_Data[Count].z;;

		Mesh.flags = 0;

		Mesh.jointId = -1;

		Mesh.referenceCount = 0;

		fwrite(&Mesh, sizeof(Cms3d_Vector3_t), 1, WriteMILK);
		Count++;
	}

	//-------------------------------------------- Faces
	word numFaces = App->CLSB_Model->FaceCount;

	fwrite(&numFaces, 2, 1, WriteMILK);

	Cms3d_triangle_t Face;
	Count = 0;

	//App->Say_Int(App->CL_Model_Data->FaceCount);

	while (Count < App->CLSB_Model->FaceCount)
	{
		int A = Face_Data[Count].a;
		int B = Face_Data[Count].b;
		int C = Face_Data[Count].c;

		Face.Vector3Indices[0] = Face_Data[Count].a;
		Face.Vector3Indices[1] = Face_Data[Count].b;
		Face.Vector3Indices[2] = Face_Data[Count].c;

		Face.flags = 0;

		// 3 Face UVs for Face
		Face.s[0] = MapCord_Data[A].u;
		Face.t[0] = 1 - MapCord_Data[A].v;

		Face.s[1] = MapCord_Data[B].u;
		Face.t[1] = 1 - MapCord_Data[B].v;

		Face.s[2] = MapCord_Data[C].u;
		Face.t[2] = 1 - MapCord_Data[C].v;


		// 3 Face Normals for Face
		Face.Vector3Normals[0][0] = Normal_Data[A].x;
		Face.Vector3Normals[0][1] = Normal_Data[A].y;
		Face.Vector3Normals[0][2] = Normal_Data[A].z;

		Face.Vector3Normals[1][0] = Normal_Data[B].x;
		Face.Vector3Normals[1][1] = Normal_Data[B].y;
		Face.Vector3Normals[1][2] = Normal_Data[B].z;

		Face.Vector3Normals[2][0] = Normal_Data[C].x;
		Face.Vector3Normals[2][1] = Normal_Data[C].y;
		Face.Vector3Normals[2][2] = Normal_Data[C].z;

		Face.groupIndex = Face_Data[Count].Group;

		fwrite(&Face, sizeof(Cms3d_triangle_t), 1, WriteMILK);

		Count++;
	}

	return 1;
}

// *************************************************************************
// *			WriteMILKGroups:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool SB_Export_Milkshape::Write_MILK_Groups(void)
{

	Sort_Groups();
	Debug
	word numGroups = App->CLSB_Model->Get_Groupt_Count();

	fwrite(&numGroups, 2, 1, WriteMILK);

	int Count = 0;
	int GroupCount = App->CLSB_Model->Get_Groupt_Count();
	while (Count < GroupCount)
	{
		fwrite(&TGroup[Count]->flags, sizeof(byte), 1, WriteMILK);
		fwrite(&TGroup[Count]->name, sizeof(char), 32, WriteMILK);
		fwrite(&TGroup[Count]->numtriangles, sizeof(word), 1, WriteMILK);

		for (int j = 0; j < TGroup[Count]->numtriangles; j++)
		{
			fwrite(&TGroup[Count]->triangleIndices[j], 2, 1, WriteMILK);
		}

		fwrite(&TGroup[Count]->materialIndex, 1, 1, WriteMILK);

		Count++;
	}

	return 1;
}

// *************************************************************************
// *				SortGroups:- Terry and Hazel Flanigan 2023   		   *
// *************************************************************************
bool SB_Export_Milkshape::Sort_Groups(void)
{
	int IndiceCount = 0;
	int VertCount = 0;
	int Count = 0;
	int GroupCount = App->CLSB_Model->Get_Groupt_Count();

	while (Count < GroupCount)
	{
		TGroup[Count] = new Cms3d_group_t;
		TGroup[Count]->flags = 0;
		TGroup[Count]->materialIndex = -1;// App->CLSB_Model->Group[Count]->MaterialIndex;// -1;Count;//-1;
		strcpy(TGroup[Count]->name, App->CLSB_Model->Group[Count]->GroupName);

		VertCount = 0;
		IndiceCount = 0;

		while (VertCount < App->CLSB_Model->Group[Count]->GroupFaceCount)
		{

			TGroup[Count]->triangleIndices[IndiceCount] = App->CLSB_Model->Group[Count]->FaceIndex_Data[VertCount].Index;

			IndiceCount++;
			VertCount++;
		}

		TGroup[Count]->numtriangles = IndiceCount;

		Count++;
	}

	return 1;
}

// *************************************************************************
// *		WriteMILKTexures:- Terry and Hazel Flanigan 2023		 	   *
// *************************************************************************
bool SB_Export_Milkshape::Write_MILK_Texures(void)
{
	word numMaterials = App->CLSB_Model->Get_Groupt_Count();

	fwrite(&numMaterials, 2, 1, WriteMILK);

	Cms3d_material_t mat;

	int Count = 0;
	int MatCount = App->CLSB_Model->Get_Groupt_Count();

	while (Count < MatCount)
	{
		Get_Material_Name(Count);
		strcpy(mat.name, MaterialName);
		SetVec4(mat.diffuse, 1, 1, 1, 1);
		SetVec4(mat.ambient, 1, 1, 1, 1);
		SetVec4(mat.specular, 0, 0, 0, 1);
		SetVec4(mat.emissive, 0, 0, 0, 1);
		mat.shininess = 0;
		mat.transparency = 1;
		mat.mode = 0;


		int Len = strlen(Text_FileName);
		Text_FileName[Len - 4] = 0;
		strcat(Text_FileName, ".jpg");

		strcpy(mat.texture, Text_FileName);
		strcpy(mat.alphamap, "");

		fwrite(&mat, sizeof(Cms3d_material_t), 1, WriteMILK);
		Count++;
	}
	return 1;
}

// *************************************************************************
// *			GetMaterialName:- Terry and Hazel Flanigan 2023		 	   *
// *************************************************************************
bool SB_Export_Milkshape::Get_Material_Name(int Loop)
{

	strcpy(MaterialName, App->CLSB_Model->Group[Loop]->MaterialName);
	strcpy(Text_FileName, App->CLSB_Model->Group[Loop]->Text_FileName);
	return 1;
}

// *************************************************************************
// *			SetVec4:- Terry and Hazel Flanigan 2023  				   *
// *************************************************************************
inline void SB_Export_Milkshape::SetVec4(float* target, float x, float y, float z, float w)
{
	target[0] = x;
	target[1] = y;
	target[2] = z;
	target[3] = w;
}
