#include "stdafx.h"
#include "ME_App.h"
#include "ME_Dimensions.h"


ME_Dimensions::ME_Dimensions()
{
}


ME_Dimensions::~ME_Dimensions()
{
}

// *************************************************************************
// *	  				Centre_Model_Mid Terry Bernie					   *
// *************************************************************************
void ME_Dimensions::Centre_Model_Mid(void)
{
	if (App->CL_Model->Model_Loaded == 1)
	{
		float X = -App->CL_Model->S_BoundingBox[0]->Centre[0].x;
		float Y = -App->CL_Model->S_BoundingBox[0]->Centre[0].y;
		float Z = -App->CL_Model->S_BoundingBox[0]->Centre[0].z;

		int Count = 0;
		int VertCount = 0;
		int Index = App->CL_Model->Get_Groupt_Count();

		while (Count < Index)
		{
			VertCount = 0;
			while (VertCount < App->CL_Model->Group[Count]->GroupVertCount)
			{
				App->CL_Model->Group[Count]->vertex_Data[VertCount].x += X;
				App->CL_Model->Group[Count]->vertex_Data[VertCount].y += Y;
				App->CL_Model->Group[Count]->vertex_Data[VertCount].z += Z;
				VertCount++;
			}
			Count++;
		}

		App->CL_Model->GetBoundingBoxModel_Update();
		
	}

}