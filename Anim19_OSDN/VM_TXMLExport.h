// TXMLExport.h: interface for the TXMLExport class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TXMLEXPORT_H__09CFE2AF_FA7A_4A4F_9A9C_6B5A90092AC3__INCLUDED_)
#define AFX_TXMLEXPORT_H__09CFE2AF_FA7A_4A4F_9A9C_6B5A90092AC3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct {
	vertex_type XMLvertex[MAX_VERTICES];
	normal_type XMLnormal[MAX_VERTICES];
	polygon_type XMLpolygon[MAX_POLYGONS];
	mapcoord_type mapcoord[MAX_VERTICES];
	int BeenAdded[MAX_VERTICES];
	int SortedVerticeCount;
	int SortedPolyCount;
	int SortedVertIndex[MAX_VERTICES];
	int SXMLCount;
	int BoneIndex[MAX_VERTICES];

} XMLStore_Type;

class VM_XMLExport  
{

private:
bool WriteScript(int LFormat);
bool WriteBoneMatrix();
bool GetBoneMatrix(int Count);
bool WriteHiracy();
bool CreateHiracyLists();
bool RenderToXML();
bool CreateDirectory();
bool WriteNewXML();
bool WriteSubMesh();
bool WriteSkellFile();
bool DirectoryControl();
bool CreateDirectoryMesh();

bool GetTexureInfoIndex(char *LTexture);
bool WriteBoneAssigenment();
bool DecompileTextures(int LFormat);
bool WriteMotion(int lMotionCount);

bool GetFrameMatrix();
bool GetRootMatrix();


FILE *WriteSFile;
FILE *WritePolyFile;
FILE *WriteSkFile;

float nx;
float ny;
float nz;

float u;
float v;

public:
	VM_XMLExport();
	virtual ~VM_XMLExport();

	bool StartRenderToXML(int LTextureFormat);
	bool StartRenderToMesh(int LTextureFormat);
	char *GetTexture(int Index);

	char DecompileFolder[1024];
	char XmlMeshFileName[256];
	char XmlScriptFileName[256];
	char XmlSkellFileName[256];
	char XmlSkellTagName[256];

	char OgreMeshFileName[256];
	char OgreScriptFileName[256];
	char OgreSkellFileName[256];
	char OgreSkellTagName[256];

	char OgreSkellMeshDir[256];
	char OgreScriptDir[256];
	char OgreTextureDir[256];

	int TextureNum;
	int DoSkell;
	int DoMotion;
	int DoBoneAssignment;
	int DontCopy;
	int XMLScale;

	int DeleteXML;
	int DeleteMesh;
	
	int Test;
	
	geXForm3d SPosNewMatric;
	geXForm3d SRotNewMatric;

	XMLStore_Type * S_XMLStore[1];

};

#endif // !defined(AFX_TXMLEXPORT_H__09CFE2AF_FA7A_4A4F_9A9C_6B5A90092AC3__INCLUDED_)
