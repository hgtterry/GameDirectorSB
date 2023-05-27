#pragma once

typedef struct tag_FaceList FaceList;
typedef struct tag_BrushList BrushList;

enum BrushTypeFlags
{
	BRUSH_MULTI = 0x0001,
	BRUSH_LEAF = 0x0002,
	BRUSH_CSG = 0x0004
};

typedef struct BrushTag
{
	struct BrushTag* Prev, * Next;
	FaceList* Faces;			//null if multibrush
	BrushList* BList;			//null if csgbrush
	unsigned long	Flags;
	int				Type;
	int				ModelId;
	int				GroupId;
	geFloat			HullSize;		//for hollows
	Ogre::uint32			Color;
	char* Name;
	Box3d			BoundingBox;
} Brush;

typedef Brush* BrushIterator;

class CBrush
{
public:
	CBrush();
	~CBrush();

	geBoolean Brush_IsDetail(const Brush* b);
	BrushList* BrushList_Create(void);
	BrushList* BrushList_CreateFromFile(Parse3dt* Parser, int VersionMajor, int VersionMinor, const char** Expected);
	Brush* Brush_CreateFromFile(Parse3dt* Parser, int VersionMajor, int VersionMinor, const char** Expected);
	void BrushList_Destroy(BrushList** ppList);
	void BrushList_Append(BrushList* pList, Brush* pBrush);
	void BrushList_DeleteAll(BrushList* pList);
	Brush* BrushList_GetFirst(BrushList* pList, BrushIterator* bi);
	Brush* BrushList_GetNext(BrushIterator* bi);
	Brush* BrushList_GetLast(BrushList* pList, BrushIterator* bi);
	void BrushList_Remove(BrushList* pList, Brush* pBrush);
	void Brush_Destroy(Brush** b);
	Brush* Brush_Create(int Type, const FaceList* fl, const BrushList* BList);
	void Brush_SetName(Brush* b, const char* newname);
	void BrushList_GetBounds(const BrushList* BList, Box3d* pBounds);
	void Brush_Bound(Brush* b);
	void BrushList_MakeHollowsMulti(BrushList* inList);
	void BrushList_InsertAfter(BrushList* pList, Brush* pBMarker, Brush* pBrush);
	void BrushList_Prepend(BrushList* pList, Brush* pBrush);

	int Get_Brush_Count();
	Brush* Get_Brush_ByIndex(int Index);

};

