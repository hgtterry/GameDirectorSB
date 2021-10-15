#pragma once
class EQ15_Ogre_Import
{
public:
	EQ15_Ogre_Import();
	~EQ15_Ogre_Import();

	bool Load_OgreModel(void);

protected:
	void AddToScene(void);
	void Create_MeshGroups();

	bool Extract_Mesh_Two();

	void Get_SubPoseMeshInstance(Ogre::MeshPtr mesh,
		size_t &vertex_count,
		Ogre::Vector3* &vertices,
		size_t &index_count,
		unsigned long* &indices,
		int SubMesh,
		Ogre::int16* &BoneIndices);
};

