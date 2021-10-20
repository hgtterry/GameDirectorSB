#include "stdafx.h"
#include "GD19_App.h"
#include "SB_XMLConverter.h"

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

using namespace std;
using namespace Ogre;


SB_XMLConverter::SB_XMLConverter()
{
	/*logMgr = 0;
	mth = 0;
	lodMgr = 0;
	matMgr = 0;
	skelMgr = 0;
	meshSerializer = 0;
	xmlMeshSerializer = 0;
	skeletonSerializer = 0;
	xmlSkeletonSerializer = 0;
	bufferManager = 0;
	meshMgr = 0;
	rgm = 0;*/
}


SB_XMLConverter::~SB_XMLConverter()
{
}
