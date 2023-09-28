#pragma once

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

class SB_Picking
{
public:
	SB_Picking(Ogre::SceneManager* sceneMgr);
	~SB_Picking();

	void SB_Picking::Mouse_Pick_Entity();

	Ogre::String Pl_Entity_Name;
	float closest_distance;

	Ogre::Vector3* vertices;
	Ogre::Vector2* TextCords;
	Ogre::uint32* indices;

	size_t Total_vertex_count;
	size_t Total_index_count;

	int Face_Index;
	int Sub_Mesh_Count;

private:
	bool raycast(const Ogre::Ray& ray, Ogre::Vector3& result, Ogre::MovableObject*& target, float& closest_distance, const Ogre::uint32 queryMask);
	void GetMeshInformation(const Ogre::MeshPtr mesh, const Ogre::Vector3& position, const Ogre::Quaternion& orient, const Ogre::Vector3& scale);
	
	Ogre::SceneManager* mSceneMgr;
	Ogre::RaySceneQuery* mRaySceneQuery;

	Ogre::MovableObject* pentity;

	Ogre::Vector3 HitVertices;
};

