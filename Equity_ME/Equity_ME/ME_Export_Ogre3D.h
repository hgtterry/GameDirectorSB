#pragma once

#include "Ogre.h"
#include "OgreXMLMeshSerializer.h"
#include "OgreMeshSerializer.h"
#include "OgreXMLSkeletonSerializer.h"
#include "OgreSkeletonSerializer.h"
#include "OgreXMLPrerequisites.h"
#include "OgreDefaultHardwareBufferManager.h"
#include "OgreProgressiveMeshGenerator.h"
#include "OgreDistanceLodStrategy.h"

using namespace std;
using namespace Ogre;

#define MAX_VERTICES 100000
#define MAX_POLYGONS 100000

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

struct XmlOptions
{
	String source;
	String dest;
	String sourceExt;
	String destExt;
	String logFile;
	bool interactiveMode;
	unsigned short numLods;
	Real lodValue;
	String lodStrategy;
	Real lodPercent;
	size_t lodFixed;
	size_t nuextremityPoints;
	size_t mergeTexcoordResult;
	size_t mergeTexcoordToDestroy;
	bool usePercent;
	bool generateEdgeLists;
	bool generateTangents;
	VertexElementSemantic tangentSemantic;
	bool tangentUseParity;
	bool tangentSplitMirrored;
	bool tangentSplitRotated;
	bool reorganiseBuffers;
	bool optimiseAnimations;
	bool quietMode;
	bool d3d;
	bool gl;
	Serializer::Endian endian;
};

class ME_Export_Ogre3D
{
public:
	ME_Export_Ogre3D();
	~ME_Export_Ogre3D();

	bool Export_AssimpToOgre(void);

	bool Add_Sub_Folder;
	char NewDirectory[MAX_PATH];
	char Directory_Name[MAX_PATH];

protected:

	bool CreateDirectoryMesh(void);
	bool DecompileTextures(void);
	void CreateMaterialFile(char* MatFileName);
	bool Write_XML_File();
	bool RenderToXML(int GroupIndex);
	bool WriteNewXML(int GroupIndex);
	bool WriteSubMesh(int GroupIndex);
	bool Convert_To_Mesh();
	XmlOptions parseArgs();
	void XMLToBinary(XmlOptions opts);

	char mDecompileFolder[1024];
	char mOgreMeshFileName[255];
	char mOgreScriptFileName[255];
	char mOgreSkellFileName[255];
	char mOgreSkellTagName[255];

	char XmlMeshFileName[256];
	char XmlScriptFileName[256];
	char XmlSkellFileName[256];
	char XmlSkellTagName[256];

	char Source_Path_FileName[1024];
	char Dest_Path_FileName[1024];

	char mCurrentFolder[1024];

	float nx;
	float ny;
	float nz;

	float u;
	float v;

	MeshSerializer* meshSerializer;
	XMLMeshSerializer* xmlMeshSerializer;

	XMLStore_Type * S_XMLStore[1];

	FILE *WritePolyFile;
};

