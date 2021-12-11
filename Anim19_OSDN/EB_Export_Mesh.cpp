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

#include "stdafx.h"
#include "GD19_App.h"

#include "Ogre.h"
#include "OgreXMLMeshSerializer.h"
#include "OgreMeshSerializer.h"
#include "OgreXMLSkeletonSerializer.h"
#include "OgreSkeletonSerializer.h"
#include "OgreXMLPrerequisites.h"
#include "OgreDefaultHardwareBufferManager.h"
#include "OgreProgressiveMeshGenerator.h"
#include "OgreDistanceLodStrategy.h"
#include <iostream>
#include <sys/stat.h>

#include "EB_Export_Mesh.h"

using namespace std;
using namespace Ogre;

EB_Export_Mesh::EB_Export_Mesh()
{
}


EB_Export_Mesh::~EB_Export_Mesh()
{
}

// *************************************************************************
// *	  					 XMLToBinary	Terry Bernie				   *
// *************************************************************************
void EB_Export_Mesh::XMLToBinary(XmlOptions opts)
{

	// Read root element and decide from there what type
	String response;
	TiXmlDocument* doc = new TiXmlDocument(opts.source.c_str());
	// Some double-parsing here but never mind
	if (!doc->LoadFile())
	{
		delete doc;
		exit(1);
	}
	TiXmlElement* root = doc->RootElement();
	if (!_stricmp(root->Value(), "mesh"))
	{
		delete doc;
		MeshPtr newMesh = MeshManager::getSingleton().createManual("conversion",
			ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
		VertexElementType colourElementType;
		if (opts.d3d)
			colourElementType = VET_COLOUR_ARGB;
		else
			colourElementType = VET_COLOUR_ABGR;

		xmlMeshSerializer->importMesh(opts.source, colourElementType, newMesh.getPointer());

		// Re-jig the buffers?
		// Make sure animation types are up to date first
		newMesh->_determineAnimationTypes();
		if (opts.reorganiseBuffers)
		{

			// Shared geometry
			if (newMesh->sharedVertexData)
			{
				// Automatic
				VertexDeclaration* newDcl =
					newMesh->sharedVertexData->vertexDeclaration->getAutoOrganisedDeclaration(
						newMesh->hasSkeleton(), newMesh->hasVertexAnimation(), newMesh->getSharedVertexDataAnimationIncludesNormals());
				if (*newDcl != *(newMesh->sharedVertexData->vertexDeclaration))
				{
					// Usages don't matter here since we're onlly exporting
					BufferUsageList bufferUsages;
					for (size_t u = 0; u <= newDcl->getMaxSource(); ++u)
						bufferUsages.push_back(HardwareBuffer::HBU_STATIC_WRITE_ONLY);
					newMesh->sharedVertexData->reorganiseBuffers(newDcl, bufferUsages);
				}
			}
			// Dedicated geometry
			Mesh::SubMeshIterator smIt = newMesh->getSubMeshIterator();
			while (smIt.hasMoreElements())
			{
				SubMesh* sm = smIt.getNext();
				if (!sm->useSharedVertices)
				{
					const bool hasVertexAnim = sm->getVertexAnimationType() != Ogre::VAT_NONE;

					// Automatic
					VertexDeclaration* newDcl =
						sm->vertexData->vertexDeclaration->getAutoOrganisedDeclaration(
							newMesh->hasSkeleton(), hasVertexAnim, sm->getVertexAnimationIncludesNormals());
					if (*newDcl != *(sm->vertexData->vertexDeclaration))
					{
						// Usages don't matter here since we're onlly exporting
						BufferUsageList bufferUsages;
						for (size_t u = 0; u <= newDcl->getMaxSource(); ++u)
							bufferUsages.push_back(HardwareBuffer::HBU_STATIC_WRITE_ONLY);
						sm->vertexData->reorganiseBuffers(newDcl, bufferUsages);
					}
				}
			}

		}

		// Prompt for LOD generation?
		bool genLod = false;
		bool askLodDtls = false;
		if (!opts.interactiveMode) // derive from params if in batch mode
		{
			askLodDtls = false;
			if (opts.numLods == 0)
			{
				genLod = false;
			}
			else
			{
				genLod = true;
			}
		}
		else if (opts.numLods == 0) // otherwise only ask if not specified on command line
		{
			if (newMesh->getNumLodLevels() > 1)
			{

				while (response == "")
				{
					cin >> response;
					StringUtil::toLowerCase(response);
					if (response == "u")
					{
						// Do nothing
					}
					else if (response == "d")
					{
						newMesh->removeLodLevels();
					}
					else if (response == "r")
					{
						genLod = true;
						askLodDtls = true;

					}
					else
					{

						response = "";
					}
				}// while response == ""
			}
			else // no existing LOD
			{
				std::cout << "\nWould you like to generate LOD information? (y/n) ";
				while (response == "")
				{
					cin >> response;
					StringUtil::toLowerCase(response);
					if (response == "n")
					{
						// Do nothing
					}
					else if (response == "y")
					{
						genLod = true;
						askLodDtls = true;
					}
					else
					{

						response = "";
					}
				}
			}
		}

		if (genLod)
		{
			unsigned short numLod;
			LodConfig lodConfig;
			lodConfig.levels.clear();
			lodConfig.mesh = newMesh->clone(newMesh->getName());
			lodConfig.strategy = DistanceLodSphereStrategy::getSingletonPtr();

			LodLevel lodLevel;
			lodLevel.reductionMethod = LodLevel::VRM_PROPORTIONAL;

			if (askLodDtls)
			{
				cout << "\nHow many extra LOD levels would you like to generate? ";
				cin >> numLod;

				cout << "\nWhat LOD strategy should be used? ";
				cin >> opts.lodStrategy;

				cout << "\nWhat unit of reduction would you like to use:" <<
					"\n(f)ixed or (p)roportional? ";
				response = "";
				while (response == "") {
					cin >> response;
					StringUtil::toLowerCase(response);
					if (response == "f")
					{
						lodLevel.reductionMethod = LodLevel::VRM_CONSTANT;

					}
					else if (response == "p")
					{
						lodLevel.reductionMethod = LodLevel::VRM_PROPORTIONAL;

					}
					else {

						response = "";
					}
				}
				cin >> lodLevel.reductionValue;
				if (lodLevel.reductionMethod == LodLevel::VRM_PROPORTIONAL)
				{
					// Percentage -> parametric
					lodLevel.reductionValue *= 0.01f;
				}



				for (unsigned short iLod = 0; iLod < numLod; ++iLod)
				{

					lodConfig.levels.push_back(lodLevel);
				}
			}
			else
			{
				numLod = opts.numLods;
				lodLevel.reductionMethod = opts.usePercent ?
					LodLevel::VRM_PROPORTIONAL : LodLevel::VRM_CONSTANT;
				if (opts.usePercent)
				{
					lodLevel.reductionValue = opts.lodPercent * 0.01f;
				}
				else
				{
					lodLevel.reductionValue = (Ogre::Real)opts.lodFixed;
				}
				Real currDist = 0;
				for (unsigned short iLod = 0; iLod < numLod; ++iLod)
				{
					currDist += opts.lodValue;
					Real currDistSq = Ogre::Math::Sqr(currDist);
					lodLevel.distance = currDistSq;
					lodConfig.levels.push_back(lodLevel);
				}

			}

			newMesh->setLodStrategy(LodStrategyManager::getSingleton().getStrategy(opts.lodStrategy));
			ProgressiveMeshGenerator pm;
			pm.generateLodLevels(lodConfig);
		}

		if (opts.interactiveMode)
		{

			while (response == "")
			{
				cin >> response;
				StringUtil::toLowerCase(response);
				if (response == "y")
				{
					// Do nothing
				}
				else if (response == "n")
				{
					opts.generateEdgeLists = false;
				}
				else
				{

					response = "";
				}
			}



			while (response == "")
			{
				cin >> response;
				StringUtil::toLowerCase(response);
				if (response == "y")
				{
					opts.generateTangents = true;
				}
				else if (response == "n")
				{
					// Do nothing
				}
				else
				{

					response = "";
				}
			}
		}

		if (opts.generateEdgeLists)
		{
			if (!opts.quietMode)
			{

			}
			newMesh->buildEdgeList();
		}

		if (opts.generateTangents)
		{
			unsigned short srcTex, destTex;
			if (!opts.quietMode)
			{

			}
			bool existing;
			try {
				existing = newMesh->suggestTangentVectorBuildParams(opts.tangentSemantic, srcTex, destTex);
			}
			catch (Exception &e) {
				std::cerr << "WARNING: While checking for existing tangents: " << e.getFullDescription() << std::endl;
				std::cerr << "NOTE: Tangents were NOT generated for this mesh!" << std::endl;
				existing = false;
				opts.generateTangents = false;
			}
			if (existing)
			{

				while (response == "")
				{
					cin >> response;
					StringUtil::toLowerCase(response);
					if (response == "y")
					{
						// Do nothing
					}
					else if (response == "n")
					{
						opts.generateTangents = false;
					}
					else
					{
						std::cout << "Did not understand \"" << response << "\" please try again:" << std::endl;
						response = "";
					}
				}

			}
			if (opts.generateTangents)
			{
				if (!opts.quietMode)
				{

				}
				newMesh->buildTangentVectors(opts.tangentSemantic, srcTex, destTex,
					opts.tangentSplitMirrored, opts.tangentSplitRotated, opts.tangentUseParity);
			}
		}

		if (opts.mergeTexcoordResult != opts.mergeTexcoordToDestroy)
		{
			newMesh->mergeAdjacentTexcoords(opts.mergeTexcoordResult, opts.mergeTexcoordToDestroy);
		}

		if (opts.nuextremityPoints)
		{
			Mesh::SubMeshIterator smIt = newMesh->getSubMeshIterator();
			while (smIt.hasMoreElements())
			{
				SubMesh* sm = smIt.getNext();
				sm->generateExtremes(opts.nuextremityPoints);
			}
		}

		meshSerializer->exportMesh(newMesh.getPointer(), opts.dest, opts.endian);

		// Clean up the conversion mesh
		MeshManager::getSingleton().remove("conversion");
	}
	else if (!_stricmp(root->Value(), "skeleton"))
	{
		delete doc;
		SkeletonPtr newSkel = SkeletonManager::getSingleton().create("conversion",
			ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
		xmlSkeletonSerializer->importSkeleton(opts.source, newSkel.getPointer());
		if (opts.optimiseAnimations)
		{
			newSkel->optimiseAllAnimations();
		}
		skeletonSerializer->exportSkeleton(newSkel.getPointer(), opts.dest, SKELETON_VERSION_LATEST, opts.endian);

		// Clean up the conversion skeleton
		SkeletonManager::getSingleton().remove("conversion");
	}
	else
	{
		delete doc;
	}

}
