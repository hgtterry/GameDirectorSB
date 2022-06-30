#include "stdafx.h"
#include "ME_App.h"
#include "ME_Export_Object.h"


ME_Export_Object::ME_Export_Object()
{
}


ME_Export_Object::~ME_Export_Object()
{
}

// *************************************************************************
// *					Create_ObjectFile Terry Bernie Hazel   		 	   *
// *************************************************************************
bool ME_Export_Object::Create_ObjectFile(void)
{

	strcpy(App->CL_FileIO->BrowserMessage, "Select Folder To Place Object Files a sub folder will be created");
	int Test = App->CL_FileIO->StartBrowser("");

	if (Test == 0)
	{
		return 0;
	}

	strcpy(OutputFolder, "");

	char buff[1024];
	strcpy(buff, App->CL_FileIO->szSelectedDir);
	strcat(buff, "\\");
	strcat(buff, App->CL_Model->JustName);
	strcat(buff, "_Object");
	strcat(buff, "\\");

	strcpy(OutputFolder, buff);

	CreateDirectory(OutputFolder, NULL);

	App->CL_Textures->DecompileTextures(OutputFolder);

	strcpy(Object_FileName, OutputFolder);
	strcat(Object_FileName, App->CL_Model->JustName);
	strcat(Object_FileName, ".obj");

	strcpy(mtl_FileName, OutputFolder);
	strcat(mtl_FileName, App->CL_Model->JustName);
	strcat(mtl_FileName, ".mtl");

	strcpy(Just_mtl_FileName, App->CL_Model->JustName);
	strcat(Just_mtl_FileName, ".mtl");

	Write_ObjectFile();

	WriteMTLFile();

	return 1;
}

// *************************************************************************
// *				Write_ObjectFile Terry Bernie Hazel  				   *
// *************************************************************************
void ME_Export_Object::Write_ObjectFile(void)
{
	Write_OBJECTFILE = 0;

	//	char buf[1024];

	Write_OBJECTFILE = fopen(Object_FileName, "wt");

	if (!Write_OBJECTFILE)
	{
		return;
	}
	if (App->CL_Model->Model_Type == Enums::LoadedFile_Assimp)
	{
		Write_ObjectFile_Commit();
	}

	fclose(Write_OBJECTFILE);
}

// *************************************************************************
// *				Write_ObjectFile_Commit Terry Bernie Hazel  		   *
// *************************************************************************
void ME_Export_Object::Write_ObjectFile_Commit(void)
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

	int GroupCountTotal = App->CL_Model->Get_Groupt_Count();

	//	char GroupName[255];
	char MaterialName[255];

	//--------------------------------------------- Vertices v-

	fprintf(Write_OBJECTFILE, "%s %i\n", "#", App->CL_Model->VerticeCount);

	while (GroupCount < GroupCountTotal)
	{
		VertCount = 0;
		while (VertCount < App->CL_Model->Group[GroupCount]->GroupVertCount)
		{
			float X = App->CL_Model->Group[GroupCount]->vertex_Data[VertCount].x;
			float Y = App->CL_Model->Group[GroupCount]->vertex_Data[VertCount].y;
			float Z = App->CL_Model->Group[GroupCount]->vertex_Data[VertCount].z;

			fprintf(Write_OBJECTFILE, "v %.06f %.06f %.06f\n", X, Y, Z);

			VertCount++;
		}
		GroupCount++;
	}

	fprintf(Write_OBJECTFILE, "%s \n", " ");

	//--------------------------------------------- Texture Cords vt-

	fprintf(Write_OBJECTFILE, "%s %i\n", "#", App->CL_Model->VerticeCount);

	GroupCount = 0;
	
	while (GroupCount < GroupCountTotal)
	{
		VertTextCords = 0;
		while (VertTextCords < App->CL_Model->Group[GroupCount]->GroupVertCount)
		{
			float U = App->CL_Model->Group[GroupCount]->MapCord_Data[VertTextCords].u;
			float V = App->CL_Model->Group[GroupCount]->MapCord_Data[VertTextCords].v;

			fprintf(Write_OBJECTFILE, "vt %.06f %.06f\n", U, V);

			VertTextCords++;
		}
		GroupCount++;
	}

	fprintf(Write_OBJECTFILE, "%s \n", " ");

	//--------------------------------------------- Normals vn-

	fprintf(Write_OBJECTFILE, "%s %i\n", "#", App->CL_Model->VerticeCount);

	GroupCount = 0;

	while (GroupCount < GroupCountTotal)
	{
		VertNormals = 0;
		while (VertNormals < App->CL_Model->Group[GroupCount]->GroupVertCount)
		{
			float X = App->CL_Model->Group[GroupCount]->Normal_Data[VertNormals].x;
			float Y = App->CL_Model->Group[GroupCount]->Normal_Data[VertNormals].y;
			float Z = App->CL_Model->Group[GroupCount]->Normal_Data[VertNormals].z;

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

		strcpy(MaterialName, App->CL_Model->Group[GroupCount]->MaterialName);
		fprintf(Write_OBJECTFILE, "usemtl %s\n", MaterialName);

		while (FaceCount < App->CL_Model->Group[GroupCount]->GroupFaceCount)
		{
			int A0 = App->CL_Model->Group[GroupCount]->Face_Data[FaceCount].a + Offset;
			int B0 = App->CL_Model->Group[GroupCount]->Face_Data[FaceCount].a + Offset;
			int C0 = App->CL_Model->Group[GroupCount]->Face_Data[FaceCount].a + Offset;

			int A1 = App->CL_Model->Group[GroupCount]->Face_Data[FaceCount].b + Offset;
			int B1 = App->CL_Model->Group[GroupCount]->Face_Data[FaceCount].b + Offset;
			int C1 = App->CL_Model->Group[GroupCount]->Face_Data[FaceCount].b + Offset;

			int A2 = App->CL_Model->Group[GroupCount]->Face_Data[FaceCount].c + Offset;
			int B2 = App->CL_Model->Group[GroupCount]->Face_Data[FaceCount].c + Offset;
			int C2 = App->CL_Model->Group[GroupCount]->Face_Data[FaceCount].c + Offset;

			FaceCount++;

			fprintf(Write_OBJECTFILE, "f %i/%i/%i %i/%i/%i %i/%i/%i\n", A0, B0, C0, A1, B1, C1, A2, B2, C2);

		}

		Offset = Offset + App->CL_Model->Group[GroupCount]->GroupVertCount;

		fprintf(Write_OBJECTFILE, "%s \n", " ");
		GroupCount++;
	}
}

// *************************************************************************
// *					WriteMTLFile Terry Bernie Hazel 		   	   	   *
// *************************************************************************
bool ME_Export_Object::WriteMTLFile(void)
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
	int GroupCountTotal = App->CL_Model->Get_Groupt_Count();

	while (GroupCount < GroupCountTotal)
	{
		strcpy(buf, App->CL_Model->Group[GroupCount]->MaterialName);
		fprintf(Write_MTLFile, "newmtl %s\n", buf);

		fprintf(Write_MTLFile, "illum 2\n");
		fprintf(Write_MTLFile, "Kd 0.800000 0.800000 0.800000\n");
		fprintf(Write_MTLFile, "Ka 0.200000 0.200000 0.200000\n");
		fprintf(Write_MTLFile, "Ks 0.000000 0.000000 0.000000\n");
		fprintf(Write_MTLFile, "Ke 0.000000 0.000000 0.000000\n");
		fprintf(Write_MTLFile, "Ns 0.000000\n");

		strcpy(buf, App->CL_Model->Group[GroupCount]->Text_FileName);
		int Len = strlen(buf);
		buf[Len - 4] = 0;
		strcat(buf, ".jpg");

		fprintf(Write_MTLFile, "map_Kd %s\n", buf);

		fprintf(Write_MTLFile, "%s \n", " ");

		GroupCount++;
	}

	fclose(Write_MTLFile);

	return 1;
}