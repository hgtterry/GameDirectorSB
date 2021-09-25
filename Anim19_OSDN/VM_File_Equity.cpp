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

		Write_All(Count);
		fprintf(WriteScene, "%s\n", " ");
		Count++;
	}
	
	fclose(WriteScene);
	return 1;
}

// *************************************************************************
// *							Write_All Terry Bernie			 		   *
// *************************************************************************
bool VM_File_Equity::Write_All(int Count)
{
	int VertCount = 0;
	int A = 0;
	int B = 0;
	int C = 0;

	if (App->CL_Vm_Model->S_MeshGroup[Count]->MaterialIndex>-1)
	{
		int MatIndex = App->CL_Vm_Model->S_MeshGroup[Count]->MaterialIndex;
		fprintf(WriteScene, "%s%i\n", "Material Index = ", MatIndex);
		
	}
	else
	{
		fprintf(WriteScene, "%s\n", "Material Index = No Material");
	}

	while (VertCount<App->CL_Vm_Model->S_MeshGroup[Count]->GroupFaceCount)
	{
		A = App->CL_Vm_Model->S_MeshGroup[Count]->Face_Data[VertCount].a;
		B = App->CL_Vm_Model->S_MeshGroup[Count]->Face_Data[VertCount].b;
		C = App->CL_Vm_Model->S_MeshGroup[Count]->Face_Data[VertCount].c;

		fprintf(WriteScene, "%s %i %i %i\n", "Face Indices =",A,B,C);

	//	//-----------------------------------------------
	//	glTexCoord2f(App->CL_Vm_Model->S_MeshGroup[Count]->MapCord_Data[A].u, App->CL_Vm_Model->S_MeshGroup[Count]->MapCord_Data[A].v);
	//	glNormal3fv(&App->CL_Vm_Model->S_MeshGroup[Count]->Normal_Data[A].x);
		glVertex3fv(&App->CL_Vm_Model->S_MeshGroup[Count]->vertex_Data[A].x);
		//VertCount++;

		float X, Y, Z;

		X = App->CL_Vm_Model->S_MeshGroup[Count]->vertex_Data[A].x;
		Y = App->CL_Vm_Model->S_MeshGroup[Count]->vertex_Data[A].y;
		Z = App->CL_Vm_Model->S_MeshGroup[Count]->vertex_Data[A].z;
		fprintf(WriteScene, "%s %f %f %f\n", "v =", X, Y, Z);
	//	//-----------------------------------------------
	//	glTexCoord2f(App->CL_Vm_Model->S_MeshGroup[Count]->MapCord_Data[B].u, App->CL_Vm_Model->S_MeshGroup[Count]->MapCord_Data[B].v);
	//	glNormal3fv(&App->CL_Vm_Model->S_MeshGroup[Count]->Normal_Data[B].x);
	//	glVertex3fv(&App->CL_Vm_Model->S_MeshGroup[Count]->vertex_Data[B].x);
		//VertCount++;

		X = App->CL_Vm_Model->S_MeshGroup[Count]->vertex_Data[B].x;
		Y = App->CL_Vm_Model->S_MeshGroup[Count]->vertex_Data[B].y;
		Z = App->CL_Vm_Model->S_MeshGroup[Count]->vertex_Data[B].z;
		fprintf(WriteScene, "%s %f %f %f\n", "v =", X, Y, Z);

		X = App->CL_Vm_Model->S_MeshGroup[Count]->vertex_Data[C].x;
		Y = App->CL_Vm_Model->S_MeshGroup[Count]->vertex_Data[C].y;
		Z = App->CL_Vm_Model->S_MeshGroup[Count]->vertex_Data[C].z;
		fprintf(WriteScene, "%s %f %f %f\n", "v =", X, Y, Z);

	//	//-----------------------------------------------
	//	glTexCoord2f(App->CL_Vm_Model->S_MeshGroup[Count]->MapCord_Data[C].u, App->CL_Vm_Model->S_MeshGroup[Count]->MapCord_Data[C].v);
	//	glNormal3fv(&App->CL_Vm_Model->S_MeshGroup[Count]->Normal_Data[C].x);
	//	glVertex3fv(&App->CL_Vm_Model->S_MeshGroup[Count]->vertex_Data[C].x);
		VertCount++;
		//-----------------------------------------------


	}

	return 1;
}