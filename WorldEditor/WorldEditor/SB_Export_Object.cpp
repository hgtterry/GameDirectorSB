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
#include "SB_Export_Object.h"


SB_Export_Object::SB_Export_Object()
{
}


SB_Export_Object::~SB_Export_Object()
{
}

// *************************************************************************
// *					Create_ObjectFile Terry Bernie Hazel   		 	   *
// *************************************************************************
bool SB_Export_Object::Create_ObjectFile(void)
{
	strcpy(OutputFolder, "");

	char buff[1024];
	strcpy(buff, App->CLSB_Exporter->mFolder_Path);
	strcat(buff, "\\");
	strcat(buff, App->CLSB_Exporter->mDirectory_Name);
	strcat(buff, "\\");

	strcpy(OutputFolder, buff);

	CreateDirectory(OutputFolder, NULL);

	Export_Textures();

	strcpy(Object_FileName, OutputFolder);
	strcat(Object_FileName, App->CLSB_Exporter->mJustName);
	strcat(Object_FileName, ".obj");

	strcpy(mtl_FileName, OutputFolder);
	strcat(mtl_FileName, App->CLSB_Exporter->mJustName);
	strcat(mtl_FileName, ".mtl");

	strcpy(Just_mtl_FileName, App->CLSB_Exporter->mJustName);
	strcat(Just_mtl_FileName, ".mtl");

	Write_ObjectFile();

	WriteMTLFile();

	return 1;
}

// *************************************************************************
// *				Write_ObjectFile Terry Bernie Hazel  				   *
// *************************************************************************
void SB_Export_Object::Write_ObjectFile(void)
{
	Write_OBJECTFILE = 0;

	//	char buf[1024];

	Write_OBJECTFILE = fopen(Object_FileName, "wt");

	if (!Write_OBJECTFILE)
	{
		return;
	}
	if (App->CLSB_Model->Model_Type == Enums::LoadedFile_Assimp)
	{
		Write_ObjectFile_Commit();
	}

	fclose(Write_OBJECTFILE);
}

// *************************************************************************
// *				Write_ObjectFile_Commit Terry Bernie Hazel  		   *
// *************************************************************************
void SB_Export_Object::Write_ObjectFile_Commit(void)
{

	fprintf(Write_OBJECTFILE, "#\n");
	fprintf(Write_OBJECTFILE, "# Wavefront OBJ file\n");
	fprintf(Write_OBJECTFILE, "# Created with Equity_XL\n");
	fprintf(Write_OBJECTFILE, "#\n");
	fprintf(Write_OBJECTFILE, "mtllib %s\n", Just_mtl_FileName);
	fprintf(Write_OBJECTFILE, "%s \n", " ");

	int	VertCount = 0;
	int GroupCount = 0;
	int VertTextCords = 0;
	int VertNormals = 0;
	int FaceCount = 0;
	int FaceIndex = 1;

	int GroupCountTotal = App->CLSB_Model->Get_Groupt_Count();

	//	char GroupName[255];
	char MaterialName[255];

	//--------------------------------------------- Vertices v-

	fprintf(Write_OBJECTFILE, "%s %i\n", "#", App->CLSB_Model->VerticeCount);

	while (GroupCount < GroupCountTotal)
	{
		VertCount = 0;
		while (VertCount < App->CLSB_Model->Group[GroupCount]->GroupVertCount)
		{
			float X = App->CLSB_Model->Group[GroupCount]->vertex_Data[VertCount].x;
			float Y = App->CLSB_Model->Group[GroupCount]->vertex_Data[VertCount].y;
			float Z = App->CLSB_Model->Group[GroupCount]->vertex_Data[VertCount].z;

			fprintf(Write_OBJECTFILE, "v %.06f %.06f %.06f\n", X, Y, Z);

			VertCount++;
		}
		GroupCount++;
	}

	fprintf(Write_OBJECTFILE, "%s \n", " ");

	//--------------------------------------------- Texture Cords vt-

	fprintf(Write_OBJECTFILE, "%s %i\n", "#", App->CLSB_Model->VerticeCount);

	GroupCount = 0;
	
	while (GroupCount < GroupCountTotal)
	{
		VertTextCords = 0;
		while (VertTextCords < App->CLSB_Model->Group[GroupCount]->GroupVertCount)
		{
			float U = App->CLSB_Model->Group[GroupCount]->MapCord_Data[VertTextCords].u;
			float V = App->CLSB_Model->Group[GroupCount]->MapCord_Data[VertTextCords].v;

			fprintf(Write_OBJECTFILE, "vt %.06f %.06f\n", U, V);

			VertTextCords++;
		}
		GroupCount++;
	}

	fprintf(Write_OBJECTFILE, "%s \n", " ");

	//--------------------------------------------- Normals vn-

	fprintf(Write_OBJECTFILE, "%s %i\n", "#", App->CLSB_Model->VerticeCount);

	GroupCount = 0;

	while (GroupCount < GroupCountTotal)
	{
		VertNormals = 0;
		while (VertNormals < App->CLSB_Model->Group[GroupCount]->GroupVertCount)
		{
			float X = App->CLSB_Model->Group[GroupCount]->Normal_Data[VertNormals].x;
			float Y = App->CLSB_Model->Group[GroupCount]->Normal_Data[VertNormals].y;
			float Z = App->CLSB_Model->Group[GroupCount]->Normal_Data[VertNormals].z;

			fprintf(Write_OBJECTFILE, "vn %.06f %.06f %.06f\n", X, Y, Z);

			VertNormals++;
		}
		GroupCount++;
	}

	fprintf(Write_OBJECTFILE, "%s \n", " ");

	GroupCount = 0;
	
	int Offset = 1;
	while (GroupCount < GroupCountTotal)
	{
		FaceCount = 0;
		int LineIndex = 0;

		strcpy(MaterialName, App->CLSB_Model->Group[GroupCount]->MaterialName);
		fprintf(Write_OBJECTFILE, "usemtl %s\n", MaterialName);

		while (FaceCount < App->CLSB_Model->Group[GroupCount]->GroupFaceCount)
		{
			int A0 = App->CLSB_Model->Group[GroupCount]->Face_Data[FaceCount].a + Offset;
			int B0 = App->CLSB_Model->Group[GroupCount]->Face_Data[FaceCount].a + Offset;
			int C0 = App->CLSB_Model->Group[GroupCount]->Face_Data[FaceCount].a + Offset;

			int A1 = App->CLSB_Model->Group[GroupCount]->Face_Data[FaceCount].b + Offset;
			int B1 = App->CLSB_Model->Group[GroupCount]->Face_Data[FaceCount].b + Offset;
			int C1 = App->CLSB_Model->Group[GroupCount]->Face_Data[FaceCount].b + Offset;

			int A2 = App->CLSB_Model->Group[GroupCount]->Face_Data[FaceCount].c + Offset;
			int B2 = App->CLSB_Model->Group[GroupCount]->Face_Data[FaceCount].c + Offset;
			int C2 = App->CLSB_Model->Group[GroupCount]->Face_Data[FaceCount].c + Offset;

			FaceCount++;

			fprintf(Write_OBJECTFILE, "f %i/%i/%i %i/%i/%i %i/%i/%i\n", A0, B0, C0, A1, B1, C1, A2, B2, C2);

		}

		Offset = Offset + App->CLSB_Model->Group[GroupCount]->GroupVertCount;

		fprintf(Write_OBJECTFILE, "%s \n", " ");
		GroupCount++;
	}
}

// *************************************************************************
// *					WriteMTLFile Terry Bernie Hazel 		   	   	   *
// *************************************************************************
bool SB_Export_Object::WriteMTLFile(void)
{
	Write_MTLFile = 0;

	char buf[1024];

	Write_MTLFile = fopen(mtl_FileName, "wt");

	if (!Write_MTLFile)
	{
		return 0;
	}

	fprintf(Write_MTLFile, "#\n");
	fprintf(Write_MTLFile, "# Wavefront material file\n");
	fprintf(Write_MTLFile, "# Created with Equity_XL\n");
	fprintf(Write_MTLFile, "#\n");
	fprintf(Write_MTLFile, "%s \n", " ");

	int GroupCount = 0;
	int GroupCountTotal = App->CLSB_Model->Get_Groupt_Count();

	while (GroupCount < GroupCountTotal)
	{
		strcpy(buf, App->CLSB_Model->Group[GroupCount]->MaterialName);
		fprintf(Write_MTLFile, "newmtl %s\n", buf);

		fprintf(Write_MTLFile, "illum 2\n");
		fprintf(Write_MTLFile, "Kd 0.800000 0.800000 0.800000\n");
		fprintf(Write_MTLFile, "Ka 0.200000 0.200000 0.200000\n");
		fprintf(Write_MTLFile, "Ks 0.000000 0.000000 0.000000\n");
		fprintf(Write_MTLFile, "Ke 0.000000 0.000000 0.000000\n");
		fprintf(Write_MTLFile, "Ns 0.000000\n");

		strcpy(buf, App->CLSB_Model->Group[GroupCount]->Text_FileName);
		
		fprintf(Write_MTLFile, "map_Kd %s\n", buf);

		fprintf(Write_MTLFile, "%s \n", " ");

		GroupCount++;
	}

	fclose(Write_MTLFile);

	return 1;
}

// *************************************************************************
// *					Export_Textures Terry Bernie Hazel 		   	   	   *
// *************************************************************************
bool SB_Export_Object::Export_Textures(void)
{
	char buf[MAX_PATH];

	int GroupCount = 0;
	int GroupCountTotal = App->CLSB_Model->Get_Groupt_Count();

	while (GroupCount < GroupCountTotal)
	{
		strcpy(buf, App->CLSB_Model->Group[GroupCount]->Text_FileName);
		int Len = strlen(buf);
		buf[Len - 4] = 0;

		App->CLSB_Textures->Extract_TXL_Texture(buf, OutputFolder);
		
		GroupCount++;
	}

	return 1;
}