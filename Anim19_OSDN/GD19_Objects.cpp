#include "StdAfx.h"
#include "GD19_App.h"
#include "GD19_Objects.h"

GD19_Objects::GD19_Objects(void)
{
	Init_Object();

}

GD19_Objects::~GD19_Objects(void)
{

}

// *************************************************************************
// *	  					Init_Object Terry							   *
// *************************************************************************
bool GD19_Objects::Init_Object(void)
{
	strcpy(Name, "None");
	strcpy(MeshName, "None");
	strcpy(MeshName_FullPath, "None");

	// Actor Scale ------------------------------------------------------
	Mesh_Scale.x = 1;
	Mesh_Scale.y = 1;
	Mesh_Scale.z = 1;

	// Actor Pos
	Mesh_Pos.x = 0;
	Mesh_Pos.y = 0;
	Mesh_Pos.z = 0;

	// Actor Rotation
	Mesh_Rot.x = 0;
	Mesh_Rot.y = 0;
	Mesh_Rot.z = 0;

	// Actor Quat
	Mesh_Quat.w = 1;
	Mesh_Quat.x = 0;
	Mesh_Quat.y = 0;
	Mesh_Quat.z = 0;

	// Physics Scale ------------------------------------------------------
	Physics_Scale.x = 1;
	Physics_Scale.y = 1;
	Physics_Scale.z = 1;

	// Physics Pos
	Physics_Pos.x = 0;
	Physics_Pos.y = 0;
	Physics_Pos.z = 0;

	// Physics Rotation
	Physics_Rot.x = 0;
	Physics_Rot.y = 0;
	Physics_Rot.z = 0;

	// Physics Size
	Physics_Size.x = 0;
	Physics_Size.y = 0;
	Physics_Size.z = 0;

	// Physics Quat
	Physics_Quat.w = 1;
	Physics_Quat.x = 0;
	Physics_Quat.y = 0;
	Physics_Quat.z = 0;
	Physics_Valid = 0;


	Usage = Enums::Usage_None;

	// Object Folder
	Folder = Enums::Folder_None;

	// Object Shape
	Shape = -1;

	// Flag it is valid
	Deleted = 0;

	Show_Debug = 0;
	bt_body = NULL;
	IsInCollision = 0;

	HasSound = 0;

	ListViewItem = NULL;

	Object_ID = 0; // THis Needs Checking

	Sound_ID_v2 = 0;
	Play_v2 = 1;

	Ogre_Particle = nullptr;

	OgreNode = nullptr;
	OgreEntity = nullptr;
	return 1;
}


// *************************************************************************
//							createTrimeshTerry Bernie					   *
// *************************************************************************
btBvhTriangleMeshShape* GD19_Objects::createTrimesh(Ogre::Entity* ent, int Object_Index)
{
	int Index = Object_Index;

	// Get the mesh from the entity
	Ogre::MeshPtr myMesh = ent->getMesh();
	Ogre::Mesh::SubMeshIterator SubMeshIter = myMesh->getSubMeshIterator();

	// Create the triangle mesh
	btTriangleMesh* triMesh = NULL;
	btVector3 vert0, vert1, vert2;
	int i = 0;

	while (SubMeshIter.hasMoreElements())
	{
		i = 0;
		Ogre::SubMesh* subMesh = SubMeshIter.getNext();
		Ogre::IndexData* indexData = subMesh->indexData;
		Ogre::VertexData* vertexData = subMesh->vertexData;

		// -------------------------------------------------------
		// Get the position element
		const Ogre::VertexElement* posElem = vertexData->vertexDeclaration->findElementBySemantic(Ogre::VES_POSITION);
		// Get a pointer to the vertex buffer
		Ogre::HardwareVertexBufferSharedPtr vBuffer = vertexData->vertexBufferBinding->getBuffer(posElem->getSource());
		// Get a pointer to the index buffer
		Ogre::HardwareIndexBufferSharedPtr iBuffer = indexData->indexBuffer;

		// -------------------------------------------------------
		// The vertices and indices used to create the triangle mesh
		std::vector<Ogre::Vector3> vertices;
		vertices.reserve(vertexData->vertexCount);
		std::vector<unsigned long> indices;
		indices.reserve(indexData->indexCount);

		// -------------------------------------------------------
		// Lock the Vertex Buffer (READ ONLY)
		unsigned char* vertex = static_cast<unsigned char*> (vBuffer->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
		float* pReal = NULL;

		for (size_t j = 0; j < vertexData->vertexCount; ++j, vertex += vBuffer->getVertexSize()) {
			posElem->baseVertexPointerToElement(vertex, &pReal);
			Ogre::Vector3 pt(pReal[0], pReal[1], pReal[2]);

			vertices.push_back(pt);
		}
		vBuffer->unlock();
		// -------------------------------------------------------
		bool use32bitindexes = (iBuffer->getType() == Ogre::HardwareIndexBuffer::IT_32BIT);

		// -------------------------------------------------------
		// Lock the Index Buffer (READ ONLY)
		unsigned long* pLong = static_cast<unsigned long*> (iBuffer->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
		unsigned short* pShort = reinterpret_cast<unsigned short*> (pLong);

		if (use32bitindexes) {
			for (size_t k = 0; k < indexData->indexCount; ++k) {
				//
				indices.push_back(pLong[k]);
			}
		}
		else {
			for (size_t k = 0; k < indexData->indexCount; ++k) {
				//
				indices.push_back(static_cast<unsigned long> (pShort[k]));
			}
		}
		iBuffer->unlock();

		// -------------------------------------------------------
		// We now have vertices and indices ready to go
		// ----

		if (triMesh == nullptr)
		{
			triMesh = new btTriangleMesh(use32bitindexes);
		}

		for (size_t y = 0; y < indexData->indexCount / 3; y++) {
			// Set each vertex
			vert0.setValue(vertices[indices[i]].x, vertices[indices[i]].y, vertices[indices[i]].z);
			vert1.setValue(vertices[indices[i + 1]].x, vertices[indices[i + 1]].y, vertices[indices[i + 1]].z);
			vert2.setValue(vertices[indices[i + 2]].x, vertices[indices[i + 2]].y, vertices[indices[i + 2]].z);

			// Add the triangle into the triangle mesh
			triMesh->addTriangle(vert0, vert1, vert2);

			// Increase index count
			i += 3;
		}
	}

	const bool useQuantizedAABB = true;
	btBvhTriangleMeshShape* mShape = new btBvhTriangleMeshShape(triMesh, false, true);
	//mShape->buildOptimizedBvh();

	float x = Mesh_Pos.x;
	float y = Mesh_Pos.y;
	float z = Mesh_Pos.z;

	//------------ Rotation
	float rw = Physics_Quat.w;
	float rx = Physics_Quat.x;
	float ry = Physics_Quat.y;
	float rz = Physics_Quat.z;

	btVector3 inertia(0, 0, 0);
	mShape->calculateLocalInertia(0.0, inertia);

	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setRotation(btQuaternion(rx, ry, rz, rw));
	btVector3 initialPosition(x, y, z);
	startTransform.setOrigin(initialPosition);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

	//myMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));

	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI
	(
		0,  // mass
		myMotionState,// initial position
		mShape,      // collision shape of body
		inertia   // local inertia
	);

	bt_body = new btRigidBody(rigidBodyCI);
	bt_body->clearForces();
	bt_body->setLinearVelocity(btVector3(0, 0, 0));
	bt_body->setAngularVelocity(btVector3(0, 0, 0));
	bt_body->setWorldTransform(startTransform);

	bt_body->setCustomDebugColor(btVector3(0, 1, 1));
	int f = bt_body->getCollisionFlags();
	bt_body->setCollisionFlags(f | btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);

	bt_body->setUserIndex(123);
	bt_body->setUserIndex2(Index);

	App->Cl_Bullet->dynamicsWorld->addRigidBody(bt_body);

	return mShape;
}

// *************************************************************************
//						Set_Physics_PosRot Terry Bernie					   *
// *************************************************************************
btTransform GD19_Objects::Set_Physics_PosRot(void)
{
	btTransform startTransform;
	startTransform.setIdentity();

	//------------ Position
	float x = Physics_Pos.x;
	float y = Physics_Pos.y;
	float z = Physics_Pos.z;
	startTransform.setOrigin(btVector3(x, y, z));

	//------------ Rotation
	float rw = Physics_Quat.w;
	float rx = Physics_Quat.x;
	float ry = Physics_Quat.y;
	float rz = Physics_Quat.z;
	startTransform.setRotation(btQuaternion(rx, ry, rz, rw));

	return startTransform;
}

// *************************************************************************
//						Set_Physics_Scale Terry Bernie					   *
// *************************************************************************
void GD19_Objects::Set_Physics_Scale(void)
{
	//------------ Scale
	float sx = Physics_Scale.x;
	float sy = Physics_Scale.y;
	float sz = Physics_Scale.z;
	bt_body->getCollisionShape()->setLocalScaling(btVector3(sx, sy, sz));
}

// *************************************************************************
// *	  				GetPlacement Terry Bernie						   *
// *************************************************************************
Ogre::Vector3 GD19_Objects::GetPlacement(void)
{

	Ogre::Vector3 Placement;
	Ogre::Vector3 CamPos;
	Ogre::Quaternion CamRot;
	Ogre::Radian mYaw;
	Ogre::Vector3 mDirection;

	/*if (App->A_Player_C->CameraMode == Enums::CamDetached ||
		App->A_Player_C->CameraMode == Enums::CamFirst)
	{*/
	CamPos = App->Cl19_Ogre->mCamera->getPosition();
	mYaw = App->Cl19_Ogre->mCamera->getOrientation().getYaw();

	/*}
	else
	{
		CamPos = App->A_Player_C->gCharacter->getPosition();
		mYaw = App->A_Player_C->gCharacter->mNode->getSceneNode()->getOrientation().getYaw();
	}*/

	App->Cl19_Ogre->PlacementCam->setPosition(CamPos);

	CamRot = Ogre::Quaternion::IDENTITY;
	App->Cl19_Ogre->PlacementCam->setOrientation(CamRot);
	App->Cl19_Ogre->PlacementCam->yaw(mYaw);

	Ogre::Vector3 TranslateVector = Ogre::Vector3::ZERO;

	float Radius = OgreNode->getAttachedObject(0)->getBoundingRadius();
	Radius = (Radius * 7) + 2;

	/*if (App->A_Player_C->CameraMode == Enums::CamDetached ||
		App->A_Player_C->CameraMode == Enums::CamFirst)
	{*/
	TranslateVector.z = -6;//Radius;
/*}
else
{
	TranslateVector.z = Radius;
}*/
	CamPos = App->Cl19_Ogre->mCamera->getPosition();

	App->Cl19_Ogre->PlacementCam->moveRelative(TranslateVector);

	Placement = App->Cl19_Ogre->PlacementCam->getPosition();
	Placement.y = CamPos.y - 3; // = Placement.y - (float)13.5 / 2;

	return Placement;
}

// *************************************************************************
//						Collect_Object_Data Terry Bernie				   *
// *************************************************************************
void GD19_Objects::Collect_Object_Data(void)
{
	/*int Index = App->Cl_Scene_Data->ObjectCount;

	float x = 0;
	float y = 0;
	float z = 0;

	x = bt_body->getWorldTransform().getOrigin().getX();
	y = bt_body->getWorldTransform().getOrigin().getY();
	z = bt_body->getWorldTransform().getOrigin().getZ();

	Physics_Pos.x = x;
	Physics_Pos.y = y;
	Physics_Pos.z = z;

	x = bt_body->getCollisionShape()->getLocalScaling().getX();
	y = bt_body->getCollisionShape()->getLocalScaling().getY();
	z = bt_body->getCollisionShape()->getLocalScaling().getZ();

	Physics_Scale.x = x;
	Physics_Scale.y = y;
	Physics_Scale.z = z;*/
}

// *************************************************************************
//					Get_BoundingBox_World_Centre Terry Bernie			   *
// *************************************************************************
Ogre::Vector3 GD19_Objects::Get_BoundingBox_World_Centre(void)
{
	AxisAlignedBox worldAAB = OgreEntity->getBoundingBox();
	worldAAB.transformAffine(OgreNode->_getFullTransform());
	Ogre::Vector3 Centre = worldAAB.getCenter();

	return Centre;
}


