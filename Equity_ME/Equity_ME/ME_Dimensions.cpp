#include "stdafx.h"
#include "ME_App.h"
#include "ME_Dimensions.h"


ME_Dimensions::ME_Dimensions()
{
	Model_X_Rotation = 90;
	Model_Y_Rotation = 90;
	Model_Z_Rotation = 90;

	Model_X_Position = 1;
	Model_Y_Position = 1;
	Model_Z_Position = 1;

	LockAxis = 0;

	Model_XScale = 0.5;
	Model_YScale = 0.5;
	Model_ZScale = 0.5;
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

// *************************************************************************
// *	  				Centre_Model_Base Terry Bernie					   *
// *************************************************************************
void ME_Dimensions::Centre_Model_Base(void)
{
	if (App->CL_Model->Model_Loaded == 1)
	{

		float X = -App->CL_Model->S_BoundingBox[0]->Centre[0].x;
		float Y = -App->CL_Model->S_BoundingBox[0]->Centre[0].y + App->CL_Model->S_BoundingBox[0]->Size[0].y / 2;
		float Z = -App->CL_Model->S_BoundingBox[0]->Centre[0].z;


		int Count = 0;
		int VertCount = 0;

		int GroupCount = App->CL_Model->Get_Groupt_Count();

		while (Count < GroupCount)
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

// *************************************************************************
// *	  					Rotate_X_Model Terry Bernie					   *
// *************************************************************************
void ME_Dimensions::Rotate_X_Model(float X)
{
	if (App->CL_Model->Model_Loaded == 1)
	{

		Ogre::Vector3 Centre;

		Centre.x = App->CL_Model->S_BoundingBox[0]->Centre[0].x;
		Centre.y = App->CL_Model->S_BoundingBox[0]->Centre[0].y;
		Centre.z = App->CL_Model->S_BoundingBox[0]->Centre[0].z;

		Ogre::Vector3 Rotate;
		Rotate.x = X;
		Rotate.y = 0;
		Rotate.z = 0;

		int Count = 0;
		int VertCount = 0;

		int GroupCount = App->CL_Model->Get_Groupt_Count();

		while (Count < GroupCount)
		{
			VertCount = 0;
			while (VertCount < App->CL_Model->Group[Count]->GroupVertCount)
			{
				Ogre::Vector3 VertPos;
				Ogre::Vector3 RotatedVert;

				VertPos.x = App->CL_Model->Group[Count]->vertex_Data[VertCount].x;
				VertPos.y = App->CL_Model->Group[Count]->vertex_Data[VertCount].y;
				VertPos.z = App->CL_Model->Group[Count]->vertex_Data[VertCount].z;

				if (Rotate.x != 0) // Dont bother if Zero
				{
					RotatedVert = (Ogre::Quaternion(Ogre::Degree(Rotate.x), Ogre::Vector3::UNIT_Y)*(VertPos - Centre));
				}
				else
				{
					RotatedVert = VertPos - Centre;
				}

				RotatedVert += Centre;

				App->CL_Model->Group[Count]->vertex_Data[VertCount].x = RotatedVert.x;
				App->CL_Model->Group[Count]->vertex_Data[VertCount].y = RotatedVert.y;
				App->CL_Model->Group[Count]->vertex_Data[VertCount].z = RotatedVert.z;

				VertCount++;
			}
			Count++;
		}

		App->CL_Model->GetBoundingBoxModel_Update();
	}
}

// *************************************************************************
// *	  				Rotate_Y_Model Terry Bernie						   *
// *************************************************************************
void ME_Dimensions::Rotate_Y_Model(float Y)
{
	if (App->CL_Model->Model_Loaded == 1)
	{
	
		Ogre::Vector3 Centre;

		Centre.x = App->CL_Model->S_BoundingBox[0]->Centre[0].x;
		Centre.y = App->CL_Model->S_BoundingBox[0]->Centre[0].y;
		Centre.z = App->CL_Model->S_BoundingBox[0]->Centre[0].z;

		Ogre::Vector3 Rotate;
		Rotate.x = 0;
		Rotate.y = Y;
		Rotate.z = 0;


		int Count = 0;
		int VertCount = 0;

		int GroupCount = App->CL_Model->Get_Groupt_Count();

		while (Count < GroupCount)
		{
			VertCount = 0;
			while (VertCount < App->CL_Model->Group[Count]->GroupVertCount)
			{
				Ogre::Vector3 VertPos;
				Ogre::Vector3 RotatedVert;

				VertPos.x = App->CL_Model->Group[Count]->vertex_Data[VertCount].x;
				VertPos.y = App->CL_Model->Group[Count]->vertex_Data[VertCount].y;
				VertPos.z = App->CL_Model->Group[Count]->vertex_Data[VertCount].z;

				if (Rotate.y != 0) // Dont bother if Zero
				{
					RotatedVert = (Ogre::Quaternion(Ogre::Degree(Rotate.y), Ogre::Vector3::UNIT_Z)*(VertPos - Centre));
				}
				else
				{
					RotatedVert = VertPos - Centre;
				}

				RotatedVert += Centre;

				App->CL_Model->Group[Count]->vertex_Data[VertCount].x = RotatedVert.x;
				App->CL_Model->Group[Count]->vertex_Data[VertCount].y = RotatedVert.y;
				App->CL_Model->Group[Count]->vertex_Data[VertCount].z = RotatedVert.z;

				VertCount++;
			}
			Count++;
		}
		App->CL_Model->GetBoundingBoxModel_Update();
	}
}

// *************************************************************************
// *	  				Rotate_Z_Model Terry Bernie						   *
// *************************************************************************
void ME_Dimensions::Rotate_Z_Model(float Z)
{
	if (App->CL_Model->Model_Loaded == 1)
	{

		Ogre::Vector3 Centre;

		Centre.x = App->CL_Model->S_BoundingBox[0]->Centre[0].x;
		Centre.y = App->CL_Model->S_BoundingBox[0]->Centre[0].y;
		Centre.z = App->CL_Model->S_BoundingBox[0]->Centre[0].z;

		Ogre::Vector3 Rotate;
		Rotate.x = 0;
		Rotate.y = 0;
		Rotate.z = Z;


		int Count = 0;
		int VertCount = 0;

		int GroupCount = App->CL_Model->Get_Groupt_Count();

		while (Count < GroupCount)
		{
			VertCount = 0;
			while (VertCount < App->CL_Model->Group[Count]->GroupVertCount)
			{
				Ogre::Vector3 VertPos;
				Ogre::Vector3 RotatedVert;

				VertPos.x = App->CL_Model->Group[Count]->vertex_Data[VertCount].x;
				VertPos.y = App->CL_Model->Group[Count]->vertex_Data[VertCount].y;
				VertPos.z = App->CL_Model->Group[Count]->vertex_Data[VertCount].z;

				if (Rotate.z != 0) // Dont bother if Zero
				{
					RotatedVert = (Ogre::Quaternion(Ogre::Degree(Rotate.z), Ogre::Vector3::UNIT_X)*(VertPos - Centre));
				}
				else
				{
					RotatedVert = VertPos - Centre;
				}

				RotatedVert += Centre;

				App->CL_Model->Group[Count]->vertex_Data[VertCount].x = RotatedVert.x;
				App->CL_Model->Group[Count]->vertex_Data[VertCount].y = RotatedVert.y;
				App->CL_Model->Group[Count]->vertex_Data[VertCount].z = RotatedVert.z;

				VertCount++;
			}
			Count++;
		}

		App->CL_Model->GetBoundingBoxModel_Update();
	}
}

// *************************************************************************
// *	  				Translate_Model Terry Bernie					   *
// *************************************************************************
void ME_Dimensions::Translate_Model(float X, float Y, float Z)
{
	if (App->CL_Model->Model_Loaded == 1)
	{
		int Count = 0;
		int VertCount = 0;

		int GroupCount = App->CL_Model->Get_Groupt_Count();

		while (Count < GroupCount)
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

// *************************************************************************
// *	  				Scale_Model Terry Bernie						   *
// *************************************************************************
void ME_Dimensions::Scale_Model(bool Mode, float X, float Y, float Z)
{
	if (LockAxis == 1)
	{
		float Timeser = 1 / Model_XScale;
		Ogre::Vector3 Scale;

		if (Mode == 1)
		{
			Scale.x = Model_XScale * 4;
			Scale.y = Model_YScale * 4;
			Scale.z = Model_ZScale * 4;
		}
		else
		{
			Scale.x = Model_XScale;
			Scale.y = Model_YScale;
			Scale.z = Model_ZScale;
		}

		int Count = 0;
		int VertCount = 0;

		int GroupCount = App->CL_Model->Get_Groupt_Count();

		while (Count < GroupCount)
		{
			VertCount = 0;
			while (VertCount < App->CL_Model->Group[Count]->GroupVertCount)
			{
				App->CL_Model->Group[Count]->vertex_Data[VertCount].x *= Scale.x;
				App->CL_Model->Group[Count]->vertex_Data[VertCount].y *= Scale.y;
				App->CL_Model->Group[Count]->vertex_Data[VertCount].z *= Scale.z;
				VertCount++;
			}
			Count++;
		}

		App->CL_Model->GetBoundingBoxModel_Update();

	}
	else
	{
		Ogre::Vector3 Scale;

		int Count = 0;
		int VertCount = 0;

		int GroupCount = App->CL_Model->Get_Groupt_Count();

		while (Count < GroupCount)
		{
			VertCount = 0;
			while (VertCount <  App->CL_Model->Group[Count]->GroupVertCount)
			{
				App->CL_Model->Group[Count]->vertex_Data[VertCount].x *= X;
				App->CL_Model->Group[Count]->vertex_Data[VertCount].y *= Y;
				App->CL_Model->Group[Count]->vertex_Data[VertCount].z *= Z;
				VertCount++;
			}
			Count++;
		}

		App->CL_Model->GetBoundingBoxModel_Update();
	}
}