#include "stdafx.h"
#include "GD19_App.h"
#include "VM_File_Equity.h"


VM_File_Equity::VM_File_Equity()
{
}


VM_File_Equity::~VM_File_Equity()
{
}

// *************************************************************************
// *							SaveFile		  			  		 	   *
// *************************************************************************
bool VM_File_Equity::SaveFile(char* Extension, char* Title, char* FileName)
{

	mPath_FileName[0] = 0;
	mFileName[0] = 0;

	strcpy(mPath_FileName, FileName);
	strcpy(mFileName, FileName);

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = App->MainHwnd;
	ofn.hInstance = App->hInst;
	ofn.lpstrFile = mPath_FileName; // Full Path
	ofn.nMaxFile = sizeof(mPath_FileName);
	ofn.lpstrFilter = Extension;
	;
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = mFileName;
	ofn.nMaxFileTitle = sizeof(mFileName); // Just File name
	ofn.lpstrInitialDir = "";
	ofn.lpstrTitle = Title;
	ofn.Flags = OFN_PATHMUSTEXIST |
		OFN_FILEMUSTEXIST |
		OFN_EXPLORER |
		OFN_HIDEREADONLY |
		OFN_OVERWRITEPROMPT;

	if (GetSaveFileName(&ofn) == TRUE)
	{

		return 1;
	}

	return 0;
}

// *************************************************************************
// *						WriteData_File Terry Bernie  				   *
// *************************************************************************
bool VM_File_Equity::WriteData_File()
{
	int Count = 0;
	WriteScene = NULL;

	WriteScene = fopen(mPath_FileName, "wt");
	if (!WriteScene)
	{
		App->Say("Cant Create Save File");
		return 0;
	}

	fprintf(WriteScene, "%s %s\n", "Equity Model Data File", App->CL_Vm_Model->FileName);
	fprintf(WriteScene, "%s\n", " ");

	fprintf(WriteScene, "%s%i\n", "Vertices = ", App->CL_Vm_Model->VerticeCount);
	fprintf(WriteScene, "%s%i\n", "Faces = ", App->CL_Vm_Model->FaceCount);

	fprintf(WriteScene, "%s\n", " ");

	fprintf(WriteScene, "%s%i\n", "Groups = ", App->CL_Vm_Model->GroupCount);


	while (Count<App->CL_Vm_Model->GroupCount)
	{
		fprintf(WriteScene, "%s%i %s\n", "Group ", Count, App->CL_Vm_Model->S_MeshGroup[Count]->GroupName);

		Write_Vertices(Count);
		Write_Face_Indices(Count);

		int GroupVertCount = App->CL_Vm_Model->S_MeshGroup[Count]->GroupFaceCount * 3;
		int GroupFaceCount = App->CL_Vm_Model->S_MeshGroup[Count]->GroupFaceCount ;

		fprintf(WriteScene, "%s %i %s %i\n", "Vertices", GroupVertCount, "Faces", GroupFaceCount);

		fprintf(WriteScene, "%s\n", " ");

		Count++;
	}
	
	Convert_To_GlobalMesh();

	fprintf(WriteScene, "%s\n", " ");
	fprintf(WriteScene, "%s\n", "Global ");


	Write_Global_Vertices();

	fprintf(WriteScene, "%s\n", " ");

	Write_Global_TextIDs();

	fprintf(WriteScene, "%s\n", " ");

	Write_Global_Normals();

	fclose(WriteScene);
	return 1;
}

// *************************************************************************
// *						Write_Vertices Terry Bernie			 		   *
// *************************************************************************
bool VM_File_Equity::Write_Vertices(int Count)
{
	int VertCount = 0;
	int A = 0;
	int B = 0;
	int C = 0;

	while (VertCount<App->CL_Vm_Model->S_MeshGroup[Count]->GroupFaceCount)
	{
		A = App->CL_Vm_Model->S_MeshGroup[Count]->Face_Data[VertCount].a;
		B = App->CL_Vm_Model->S_MeshGroup[Count]->Face_Data[VertCount].b;
		C = App->CL_Vm_Model->S_MeshGroup[Count]->Face_Data[VertCount].c;

		float X, Y, Z;

		X = App->CL_Vm_Model->S_MeshGroup[Count]->vertex_Data[A].x;
		Y = App->CL_Vm_Model->S_MeshGroup[Count]->vertex_Data[A].y;
		Z = App->CL_Vm_Model->S_MeshGroup[Count]->vertex_Data[A].z;
		fprintf(WriteScene, "%s %f %f %f\n", "v =", X, Y, Z);
	
		X = App->CL_Vm_Model->S_MeshGroup[Count]->vertex_Data[B].x;
		Y = App->CL_Vm_Model->S_MeshGroup[Count]->vertex_Data[B].y;
		Z = App->CL_Vm_Model->S_MeshGroup[Count]->vertex_Data[B].z;
		fprintf(WriteScene, "%s %f %f %f\n", "v =", X, Y, Z);

		X = App->CL_Vm_Model->S_MeshGroup[Count]->vertex_Data[C].x;
		Y = App->CL_Vm_Model->S_MeshGroup[Count]->vertex_Data[C].y;
		Z = App->CL_Vm_Model->S_MeshGroup[Count]->vertex_Data[C].z;
		fprintf(WriteScene, "%s %f %f %f\n", "v =", X, Y, Z);

		VertCount++;
		
	}

	return 1;
}

// *************************************************************************
// *					Write_Face_Indices Terry Bernie			 		   *
// *************************************************************************
bool VM_File_Equity::Write_Face_Indices(int Count)
{
	int FaceCount = 0;
	int A = 0;
	int B = 0;
	int C = 0;

	while (FaceCount<App->CL_Vm_Model->S_MeshGroup[Count]->GroupFaceCount)
	{
		A = App->CL_Vm_Model->S_MeshGroup[Count]->Face_Data[FaceCount].a;
		B = App->CL_Vm_Model->S_MeshGroup[Count]->Face_Data[FaceCount].b;
		C = App->CL_Vm_Model->S_MeshGroup[Count]->Face_Data[FaceCount].c;

		fprintf(WriteScene, "%s %i %i %i\n", "Face Indices =",A,B,C);

		FaceCount++;
	}

	return 1;
}

// *************************************************************************
// *					Convert_To_GlobalMesh  Terry Bernie   	  	 	   *
// *************************************************************************
void VM_File_Equity::Convert_To_GlobalMesh(void)
{
	int Count = 0;
	int GroupVertCount = 0;
	int GroupFaceCount = 0;
	int VC = 0;

	int Offset = 0;

	App->CL_Vm_Model->vertex_Data.resize(App->CL_Vm_Model->VerticeCount);
	App->CL_Vm_Model->Face_Data.resize(App->CL_Vm_Model->FaceCount);

	App->CL_Vm_Model->Normal_Data.resize(App->CL_Vm_Model->VerticeCount);
	App->CL_Vm_Model->MapCord_Data.resize(App->CL_Vm_Model->VerticeCount);
	App->CL_Vm_Model->MatIndex_Data.resize(App->CL_Vm_Model->FaceCount);

	while (Count < App->CL_Vm_Model->GroupCount)
	{
		GroupVertCount = 0;

		while (GroupVertCount < App->CL_Vm_Model->S_MeshGroup[Count]->GroupVertCount)
		{
			App->CL_Vm_Model->vertex_Data[VC].x = App->CL_Vm_Model->S_MeshGroup[Count]->vertex_Data[GroupVertCount].x;
			App->CL_Vm_Model->vertex_Data[VC].y = App->CL_Vm_Model->S_MeshGroup[Count]->vertex_Data[GroupVertCount].y;
			App->CL_Vm_Model->vertex_Data[VC].z = App->CL_Vm_Model->S_MeshGroup[Count]->vertex_Data[GroupVertCount].z;

			/*if (App->CL_Model_Data->ItsAnOgreModel == 1)
			{
			App->CL_Model_Data->BoneIndex_Data[VC].Index = App->CL_Model_Data->S_MeshGroup[Count]->BoneIndex_Data[GroupVertCount].Index;
			}*/

			App->CL_Vm_Model->MapCord_Data[VC].u = App->CL_Vm_Model->S_MeshGroup[Count]->MapCord_Data[GroupVertCount].u;
			App->CL_Vm_Model->MapCord_Data[VC].v = App->CL_Vm_Model->S_MeshGroup[Count]->MapCord_Data[GroupVertCount].v;

			App->CL_Vm_Model->Normal_Data[VC].x = App->CL_Vm_Model->S_MeshGroup[Count]->Normal_Data[GroupVertCount].x;
			App->CL_Vm_Model->Normal_Data[VC].y = App->CL_Vm_Model->S_MeshGroup[Count]->Normal_Data[GroupVertCount].y;
			App->CL_Vm_Model->Normal_Data[VC].z = App->CL_Vm_Model->S_MeshGroup[Count]->Normal_Data[GroupVertCount].z;

			VC++;

			GroupVertCount++;
		}

		Count++;
	}


	VC = 0;
	Count = 0;
	int mFaceCount = 0;
	while (Count < App->CL_Vm_Model->GroupCount)
	{
		mFaceCount = 0;
		while (mFaceCount < App->CL_Vm_Model->S_MeshGroup[Count]->GroupFaceCount)
		{

			App->CL_Vm_Model->Face_Data[VC].Group = Count;

			App->CL_Vm_Model->Face_Data[VC].a = App->CL_Vm_Model->S_MeshGroup[Count]->Face_Data[mFaceCount].a + Offset;
			App->CL_Vm_Model->Face_Data[VC].b = App->CL_Vm_Model->S_MeshGroup[Count]->Face_Data[mFaceCount].b + Offset;
			App->CL_Vm_Model->Face_Data[VC].c = App->CL_Vm_Model->S_MeshGroup[Count]->Face_Data[mFaceCount].c + Offset;

			VC++;
			mFaceCount++;
		}

		Offset = Offset + App->CL_Vm_Model->S_MeshGroup[Count]->GroupVertCount;
		Count++;

	}


	VC = 0;
	Count = 0;
	while (Count < App->CL_Vm_Model->GroupCount)
	{
		GroupFaceCount = 0;

		while (GroupFaceCount < App->CL_Vm_Model->S_MeshGroup[Count]->GroupFaceCount)
		{
			App->CL_Vm_Model->MatIndex_Data[VC] = App->CL_Vm_Model->S_MeshGroup[Count]->MaterialIndex;

			VC++;
			GroupFaceCount++;
		}

		Count++;
	}
}

// *************************************************************************
// *					Write_Global_Vertices Terry Bernie					   *
// *************************************************************************
bool VM_File_Equity::Write_Global_Vertices()
{
	int VerticeCount = 0;
	float X, Y, Z;

	while (VerticeCount<App->CL_Vm_Model->VerticeCount)
	{

		X = App->CL_Vm_Model->vertex_Data[VerticeCount].x;
		Y = App->CL_Vm_Model->vertex_Data[VerticeCount].y;
		Z = App->CL_Vm_Model->vertex_Data[VerticeCount].z;
		fprintf(WriteScene, "%s %f %f %f\n", "v", X, Y, Z);

		VerticeCount++;
	}

	fprintf(WriteScene, "%s %d %s\n", "#", App->CL_Vm_Model->VerticeCount,"vertices");
	return 1;
}

// *************************************************************************
// *					Write_Global_TextIDs Terry Bernie				   *
// *************************************************************************
bool VM_File_Equity::Write_Global_TextIDs()
{
	int VerticeCount = 0;
	float U, V;

	while (VerticeCount<App->CL_Vm_Model->VerticeCount)
	{

		U = App->CL_Vm_Model->MapCord_Data[VerticeCount].u;
		V = App->CL_Vm_Model->MapCord_Data[VerticeCount].v;

		fprintf(WriteScene, "%s %f %f\n", "vt", U, V);

		VerticeCount++;
	}

	fprintf(WriteScene, "%s %d %s\n", "#", App->CL_Vm_Model->VerticeCount, "texture coordinates");

	return 1;
}

// *************************************************************************
// *					Write_Global_Normals Terry Bernie				   *
// *************************************************************************
bool VM_File_Equity::Write_Global_Normals()
{
	int VerticeCount = 0;
	float X,Y,Z;

	while (VerticeCount<App->CL_Vm_Model->VerticeCount)
	{
		X = App->CL_Vm_Model->Normal_Data[VerticeCount].x;
		Y = App->CL_Vm_Model->Normal_Data[VerticeCount].y;
		Z = App->CL_Vm_Model->Normal_Data[VerticeCount].z;

		fprintf(WriteScene, "%s %f %f %f\n", "vn", X, Y, Z);

		VerticeCount++;
	}

	fprintf(WriteScene, "%s %d %s\n", "#", App->CL_Vm_Model->VerticeCount, "normals");
	
	return 1;
}