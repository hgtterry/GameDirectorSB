/*
Copyright (c) 2023 World Editor -- HGT Software W.T.Flanigan H.C.Flanigan

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software. If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.

3. This notice may not be removed or altered from any source
distribution.
*/

#pragma once

#include "OgreXMLMeshSerializer.h"

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

class SB_Export_Ogre3D
{
public:
	SB_Export_Ogre3D(void);
	~SB_Export_Ogre3D(void);

	bool Export_AssimpToOgre(void);

	bool Add_Sub_Folder;
	char NewDirectory[MAX_PATH];
	char Directory_Name[MAX_PATH];

private:

	bool CreateDirectoryMesh(void);

	bool DecompileTextures(void);
	bool DecompileTextures_TXL(void);

	void CreateMaterialFile(char* MatFileName);

	bool Write_XML_File();
	bool Write_WE_XML_File();

	bool RenderToXML(int GroupIndex);
	bool Render_WE_ToXML(int GroupIndex);

	bool WriteNewXML(int GroupIndex);
	bool WriteSubMesh(int GroupIndex);
	bool Convert_To_Mesh();
	void XMLToBinary(XmlOptions opts);
	XmlOptions parseArgs();

	char mDecompileFolder[MAX_PATH];
	char mOgreMeshFileName[MAX_PATH];
	char mOgreScriptFileName[MAX_PATH];
	char mOgreSkellFileName[MAX_PATH];
	char mOgreSkellTagName[MAX_PATH];

	char XmlMeshFileName[MAX_PATH];
	char XmlScriptFileName[MAX_PATH];
	char XmlSkellFileName[MAX_PATH];
	char XmlSkellTagName[MAX_PATH];

	char Source_Path_FileName[MAX_PATH];
	char Dest_Path_FileName[MAX_PATH];

	char mCurrentFolder[MAX_PATH];

	char mSelected_Directory[MAX_PATH];

	float nx;
	float ny;
	float nz;

	float u;
	float v;

	XMLStore_Type* S_XMLStore[1];
	
	MeshSerializer* meshSerializer;
	XMLMeshSerializer* xmlMeshSerializer;

	FILE* WritePolyFile;
};

