#include "stdafx.h"
#include "GD19_App.h"
#include "Base_Area.h"


Base_Area::Base_Area()
{
	Area_Ent =	nullptr;
	Area_Node = nullptr;

	mObject =	nullptr;
	mShape =	nullptr;

	/*strcpy(Name, "None");
	strcpy(MeshName, "None");
	strcpy(MeshName_FullPath, "None");*/

	// Actor Scale ------------------------------------------------------
	//Mesh_Scale.x = 1;
	//Mesh_Scale.y = 1;
	//Mesh_Scale.z = 1;

	//// Actor Pos
	//Mesh_Pos.x = 0;
	//Mesh_Pos.y = 0;
	//Mesh_Pos.z = 0;

	//// Actor Rotation
	//Mesh_Rot.x = 0;
	//Mesh_Rot.y = 0;
	//Mesh_Rot.z = 0;

	//// Actor Quat
	//Mesh_Quat.w = 1;
	//Mesh_Quat.x = 0;
	//Mesh_Quat.y = 0;
	//Mesh_Quat.z = 0;

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
	/*Physics_Size.x = 0;
	Physics_Size.y = 0;
	Physics_Size.z = 0;*/

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
	/*Deleted = 0;

	Show_Debug = 0;
	bt_body = NULL;
	IsInCollision = 0;

	Triggered = 0;

	HasSound = 0;*/

	/*strcpy(Entity[0].mTextItem, "Welcome");
	strcpy(Entity[0].Stock_mName, "None");
	Entity[0].Stock_mIndex = 0;

	Re_Trigger = 1;

	ListViewItem = NULL;*/

	Object_ID = 0; // THis Needs Checking

	/*Sound_ID_v2 = 0;
	Play_v2 = 1;

	Ogre_Particle = nullptr;

	OgreNode = nullptr;
	OgreEntity = nullptr;*/
}


Base_Area::~Base_Area()
{
}

// *************************************************************************
//						create_New_TrimeshTerry Bernie					   *
// *************************************************************************
btBvhTriangleMeshShape* Base_Area::create_New_Trimesh(Ogre::Entity* ent)
{
	int Index = App->SBC_Scene->Area_Count;

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

		//App->Say("here");
	}

	const bool useQuantizedAABB = true;
	btBvhTriangleMeshShape* mShape = new btBvhTriangleMeshShape(triMesh, false, true);
	//mShape->buildOptimizedBvh();

	float x = Area_Node->getPosition().x;
	float y = Area_Node->getPosition().y;
	float z = Area_Node->getPosition().z;

	Physics_Pos = Ogre::Vector3(x, y, z);
	Physics_Rot = Ogre::Vector3(0, 0, 0);
	Physics_Quat = Ogre::Quaternion(1, 0, 0, 0);

	btVector3 inertia(0, 0, 0);
	mShape->calculateLocalInertia(0.0, inertia);

	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setRotation(btQuaternion(0.0f, 0.0f, 0.0f, 1));
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

	mObject = new btRigidBody(rigidBodyCI);
	mObject->clearForces();
	mObject->setLinearVelocity(btVector3(0, 0, 0));
	mObject->setAngularVelocity(btVector3(0, 0, 0));
	mObject->setWorldTransform(startTransform);

	mObject->setCustomDebugColor(btVector3(0, 1, 1));
	int f = mObject->getCollisionFlags();
	mObject->setCollisionFlags(f | btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);

	Type = Enums::Bullet_Type_Static;
	Shape = Enums::Shape_TriMesh;


	mObject->setUserIndex(123);
	mObject->setUserIndex2(Index);

	Collect_Object_Data();

	App->Cl_Bullet->dynamicsWorld->addRigidBody(mObject);

	Physics_Valid = 1;
	return mShape;
}

// *************************************************************************
//						Collect_Object_Data Terry Bernie				   *
// *************************************************************************
void Base_Area::Collect_Object_Data(void)
{
	int Index = App->SBC_Scene->Area_Count;

	float x = 0;
	float y = 0;
	float z = 0;

	x = mObject->getWorldTransform().getOrigin().getX();
	y = mObject->getWorldTransform().getOrigin().getY();
	z = mObject->getWorldTransform().getOrigin().getZ();

	Physics_Pos.x = x;
	Physics_Pos.y = y;
	Physics_Pos.z = z;

	x = mObject->getCollisionShape()->getLocalScaling().getX();
	y = mObject->getCollisionShape()->getLocalScaling().getY();
	z = mObject->getCollisionShape()->getLocalScaling().getZ();

	Physics_Scale.x = x;
	Physics_Scale.y = y;
	Physics_Scale.z = z;
}
