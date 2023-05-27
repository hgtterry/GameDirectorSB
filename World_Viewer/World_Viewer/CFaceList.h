#pragma once
class CFaceList
{
public:
	CFaceList();
	~CFaceList();

	FaceList* FaceList_Create(int NumFaces);
	void FaceList_Destroy(FaceList** ppList);

	void FaceList_GetBounds(const FaceList* pList, Box3d* pBounds);
};

