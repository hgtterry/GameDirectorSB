/*
Copyright (c) 2021 Scene Builder and Equity -- Inflanite Software W.T.Flanigan H.C.Flanigan

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

class EB_Export_Mesh
{
public:
	EB_Export_Mesh();
	~EB_Export_Mesh();

	void XMLToBinary(XmlOptions opts);

	LogManager* logMgr;
	Math* mth;
	LodStrategyManager *lodMgr;
	MaterialManager* matMgr;
	SkeletonManager* skelMgr;
	MeshSerializer* meshSerializer;
	XMLMeshSerializer* xmlMeshSerializer;
	SkeletonSerializer* skeletonSerializer;
	XMLSkeletonSerializer* xmlSkeletonSerializer;
	DefaultHardwareBufferManager *bufferManager;
	MeshManager* meshMgr;
	ResourceGroupManager* rgm;
};

