#pragma once
class ME_Ogre3D
{
public:
	ME_Ogre3D();
	~ME_Ogre3D();

	bool Load_OgreModel(void);

	bool AnimationExtract_Mesh(bool DefaultPose);
	void Get_AnimationInstance(Ogre::MeshPtr mesh, size_t &vertex_count, Ogre::Vector3* &vertices, size_t &index_count,
		unsigned long* &indices,
		int SubMesh,
		bool DefaultPose);

	Ogre::Entity*		OgreModel_Ent;

protected:

	Ogre::SceneNode*	OgreModel_Node;

	void AddToScene(void);
	void Create_MeshGroups();
	bool Extract_Mesh_Two();
	void Get_SubPoseMeshInstance(Ogre::MeshPtr mesh,size_t &vertex_count,Ogre::Vector3* &vertices,size_t &index_count,
		unsigned long* &indices,
		int SubMesh,
		Ogre::int16* &BoneIndices);

	bool NewGet_SubPoseTextureUV(Ogre::MeshPtr mesh, int SubMesh);
	bool NewGet_SubPoseNormals(Ogre::MeshPtr mesh,size_t &vertex_count,Ogre::Vector3* &Normals,int SubMesh);
	bool GetBoneAssignment(Ogre::MeshPtr mesh, int SubMesh, HWND hDlg);
	bool Get_SkeletonInstance(void);
	void Get_BoneNames(void);
	void Get_Motions(void);
	void Get_Textures(void);

	bool NoTexture;
	bool NoMaterialFileFound; // Returns 1 No Material File Found;

	std::vector<Vector2> MeshTextureCoords;

	Ogre::String TempResourceGroup;   // Tempory Reosource Group
};

