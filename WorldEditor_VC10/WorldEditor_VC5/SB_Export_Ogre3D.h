#pragma once

//#include "Ogre.h"
//#include "OgreXMLMeshSerializer.h"
//#include "OgreMeshSerializer.h"
//#include "OgreXMLSkeletonSerializer.h"
//#include "OgreSkeletonSerializer.h"
//#include "OgreXMLPrerequisites.h"
//#include "OgreDefaultHardwareBufferManager.h"
//#include "OgreProgressiveMeshGenerator.h"
//#include "OgreDistanceLodStrategy.h"

//using namespace std;
//using namespace Ogre;
//#define MAX_VERTICES 100000
//#define MAX_POLYGONS 100000
//
//typedef struct {
//	vertex_type XMLvertex[MAX_VERTICES];
//	normal_type XMLnormal[MAX_VERTICES];
//	polygon_type XMLpolygon[MAX_POLYGONS];
//	mapcoord_type mapcoord[MAX_VERTICES];
//	int BeenAdded[MAX_VERTICES];
//	int SortedVerticeCount;
//	int SortedPolyCount;
//	int SortedVertIndex[MAX_VERTICES];
//	int SXMLCount;
//	int BoneIndex[MAX_VERTICES];
//
//} XMLStore_Type;
//
//struct XmlOptions
//{
//	String source;
//	String dest;
//	String sourceExt;
//	String destExt;
//	String logFile;
//	bool interactiveMode;
//	unsigned short numLods;
//	Real lodValue;
//	String lodStrategy;
//	Real lodPercent;
//	size_t lodFixed;
//	size_t nuextremityPoints;
//	size_t mergeTexcoordResult;
//	size_t mergeTexcoordToDestroy;
//	bool usePercent;
//	bool generateEdgeLists;
//	bool generateTangents;
//	VertexElementSemantic tangentSemantic;
//	bool tangentUseParity;
//	bool tangentSplitMirrored;
//	bool tangentSplitRotated;
//	bool reorganiseBuffers;
//	bool optimiseAnimations;
//	bool quietMode;
//	bool d3d;
//	bool gl;
//	Serializer::Endian endian;
//};
//
//#define TPACKERROR_OK                0    
//#define TPACKERROR_UNKNOWN           (TPACKERROR_OK - 1)    
//#define TPACKERROR_WRITE             (TPACKERROR_OK - 2)
//#define TPACKERROR_MEMORYALLOCATION  (TPACKERROR_OK - 3)
//#define TPACKERROR_CREATEFILE        (TPACKERROR_OK - 4)

//#pragma pack(1)
//typedef struct TGAHEADER
//{
//	char	IDLength;
//	char	ColorMapType;
//	char	ImageType;
//	Ogre::uint16	CMFirstEntry;
//	Ogre::uint16	CMLength;
//	char	CMEntrySize;
//	Ogre::uint16	Xorigin;
//	Ogre::uint16	Yorigin;
//	Ogre::uint16	Width;
//	Ogre::uint16	Height;
//	char	PixelDepth;
//	char	ImageDescriptor;
//} TGAHEADER;
//#pragma pack()

class WV_Export_Ogre
{
public:
	WV_Export_Ogre();
	~WV_Export_Ogre();

	bool Export_AssimpToOgre(void);
	bool Add_Sub_Folder;
	char NewDirectory[MAX_PATH];
	char Directory_Name[MAX_PATH];

	bool Export_As_RF;

protected:

	bool CreateDirectoryMesh(void);
	bool DecompileTextures(void);
	void CreateMaterialFile(char* MatFileName);
	bool Write_XML_File();
	bool RenderToXML(int GroupIndex);
	bool WriteNewXML(int GroupIndex);
	bool WriteSubMesh(int GroupIndex);
	bool Convert_To_Mesh();
	//XmlOptions parseArgs();
	//void XMLToBinary(XmlOptions opts);

	bool HBITMAP_TO_BmpFile(HBITMAP Bitmap, char* Filename, char* SaveFolder);
	int WriteTGA(const char* pszFile, geBitmap* pBitmap);
	bool Jpg_To_png24(char* File);
	bool Bmp_To_Jpg(char* File);

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

	//MeshSerializer* meshSerializer;
	//XMLMeshSerializer* xmlMeshSerializer;

	//XMLStore_Type * S_XMLStore[1];

	FILE *WritePolyFile;
};

