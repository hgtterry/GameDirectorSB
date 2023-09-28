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

#include "stdafx.h"
#include "GD19_App.h"
#include "SB_Picking.h"

SB_Picking::SB_Picking(Ogre::SceneManager* sceneMgr)
{
    mSceneMgr = sceneMgr;

    mRaySceneQuery = mSceneMgr->createRayQuery(Ogre::Ray());
    if (NULL == mRaySceneQuery)
    {
        App->Say("No Ray Query");
        return;
    }
    mRaySceneQuery->setSortByDistance(true);

    pentity = NULL;

    Total_vertex_count = 0;
    Total_index_count = 0;
    Face_Index = 0;
}

SB_Picking::~SB_Picking()
{
    if (mRaySceneQuery != NULL)
    {
        delete mRaySceneQuery;
    }
}

// *************************************************************************
// *		Mouse_Pick_Entity::Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_Picking::Mouse_Pick_Entity()
{
    Total_vertex_count = 0;
    Total_index_count = 0;
    Face_Index = 0;

    HitVertices = Ogre::Vector3(0, 0, 0);

    Ogre::RenderWindow* rw = App->CL_Ogre->mWindow;
    Ogre::Camera* camera = App->CL_Ogre->mCamera;

    ImGuiIO& io = ImGui::GetIO();

    Ogre::Real tx = io.MousePos.x / (Ogre::Real)rw->getWidth();
    Ogre::Real ty = io.MousePos.y / (Ogre::Real)rw->getHeight();

    Ogre::Ray ray = camera->getCameraToViewportRay(tx, ty);

    Ogre::uint32 queryMask = -1;
    Ogre::Vector3 result = Ogre::Vector3(0,0,0);
    Ogre::MovableObject* target = NULL;
    closest_distance = 0;

    Pl_Entity_Name = " ";
    App->CL_Ogre->OgreListener->Selected_Object_Name[0] = 0;

    Ogre::SceneNode* mNode;

    if (raycast(ray, result, target, closest_distance, queryMask))
    {
        //App->Beep_Win();

        mNode = pentity->getParentSceneNode();
        Pl_Entity_Name = pentity->getName();
        
        char buff[255];
        strcpy(buff, Pl_Entity_Name.c_str());

        App->CL_Vm_ImGui->Show_Object_Selection = 1;

        bool test = Ogre::StringUtil::match("Plane0", Pl_Entity_Name, true);
        if (test == 1)
        {
            Pl_Entity_Name = "---------";
        }
        else
        {
            bool test = Ogre::StringUtil::match("Player_1", Pl_Entity_Name, true);
            if (test == 1)
            {
                Pl_Entity_Name = "Player_1";

                return;
            }
            else
            {
                char* pdest;
                int IntNum = 0;
                char buffer[255];

                strcpy(buffer, Pl_Entity_Name.c_str());
                pdest = strstr(buffer, "GDEnt_");
                if (pdest != NULL)
                {
                    sscanf((buffer + 6), "%i", &IntNum);

                    App->SBC_Markers->MarkerBB_Addjust(IntNum);

                    App->CL_Ogre->OgreListener->Selected_Entity_Index = IntNum;
                    strcpy(App->CL_Ogre->OgreListener->Selected_Object_Name, App->SBC_Scene->V_Object[IntNum]->Mesh_Name);

                    App->SBC_FileView->SelectItem(App->SBC_Scene->V_Object[App->CL_Ogre->OgreListener->Selected_Entity_Index]->FileViewItem);

                    return;

                }
            }

        }

    }
    else
    {
        Pl_Entity_Name = "---------";
    }

}

// *************************************************************************
// *					             raycast		                	   *
// *************************************************************************
bool SB_Picking::raycast(const Ogre::Ray& ray, Ogre::Vector3& result, Ogre::MovableObject*& target, float& closest_distance, const Ogre::uint32 queryMask)
{
    target = NULL;

    if (mRaySceneQuery != NULL)
    {
        mRaySceneQuery->setRay(ray);
        mRaySceneQuery->setSortByDistance(true);
        mRaySceneQuery->setQueryMask(queryMask);
        // execute the query, returns a vector of hits
        if (mRaySceneQuery->execute().size() <= 0)
        {
            // raycast did not hit an objects bounding box
            return (false);
        }
    }
    else
    {

        App->Say("No Ray Query");
        return (false);
    }

     // at this point we have raycast to a series of different objects bounding boxes.
     // we need to test these different objects to see which is the first polygon hit.
     // there are some minor optimizations (distance based) that mean we wont have to
     // check all of the objects most of the time, but the worst case scenario is that
     // we need to test every triangle of every object.
     //Ogre::Ogre::Real closest_distance = -1.0f;
    closest_distance = -1.0f;
    Ogre::Vector3 closest_result;
    Ogre::RaySceneQueryResult& query_result = mRaySceneQuery->getLastResults();
    for (size_t qr_idx = 0; qr_idx < query_result.size(); qr_idx++)
    {
        // stop checking if we have found a raycast hit that is closer
        // than all remaining entities
        if ((closest_distance >= 0.0f) &&
            (closest_distance < query_result[qr_idx].distance))
        {
            break;
        }

        // only check this result if its a hit against an entity
        if ((query_result[qr_idx].movable != NULL) &&
            (query_result[qr_idx].movable->getMovableType().compare("Entity") == 0))
        {
            // get the entity to check
            pentity = static_cast<Ogre::MovableObject*>(query_result[qr_idx].movable);

        
            // get the mesh information
            GetMeshInformation(((Ogre::Entity*)pentity)->getMesh(),
                pentity->getParentNode()->_getDerivedPosition(),
                pentity->getParentNode()->_getDerivedOrientation(),
                pentity->getParentNode()->_getDerivedScale());

            // test for hitting individual triangles on the mesh
            bool new_closest_found = false;
            for (size_t i = 0; i < Total_index_count; i += 3)
            {
                // check for a hit against this triangle
                std::pair<bool, Ogre::Real> hit = Ogre::Math::intersects(ray, vertices[indices[i]],
                    vertices[indices[i + 1]], vertices[indices[i + 2]], true, false);

                // if it was a hit check if its the closest
                if (hit.first)
                {
                    if ((closest_distance < 0.0f) ||
                        (hit.second < closest_distance))
                    {
                        // this is the closest so far, save it off
                        closest_distance = hit.second;
                        new_closest_found = true;

                        Face_Index = i;
                        App->SBC_Grid->HitVertices[0] = vertices[indices[i]];
                        App->SBC_Grid->HitVertices[1] = vertices[indices[i + 1]];
                        App->SBC_Grid->HitVertices[2] = vertices[indices[i + 2]];
                        App->SBC_Grid->Face_Update2();   
                        App->SBC_Grid->FaceNode->setVisible(true);
                    }
                }
            }

            // free the verticies and indicies memory
            delete[] vertices;
            delete[] indices;

            // if we found a new closest raycast for this object, update the
            // closest_result before moving on to the next object.
            if (new_closest_found)
            {
                target = pentity;
                closest_result = ray.getPoint(closest_distance);
            }
        }
    }

    // return the result
    if (closest_distance >= 0.0f)
    {
        // raycast success
        result = closest_result;
        return (true);
    }
    else
    {
        // raycast failed
        return (false);
    }
}

// *************************************************************************
// *					      GetMeshInformation		              	   *
// *************************************************************************
void SB_Picking::GetMeshInformation(const Ogre::MeshPtr mesh, const Ogre::Vector3& position,const Ogre::Quaternion& orient,const Ogre::Vector3& scale)
{
    bool added_shared = false;
    size_t current_offset = 0;
    size_t shared_offset = 0;
    size_t next_offset = 0;
    size_t index_offset = 0;

    Total_vertex_count = Total_index_count = 0;

    // Calculate how many vertices and indices we're going to need
    for (unsigned short i = 0; i < mesh->getNumSubMeshes(); ++i)
    {
        Ogre::SubMesh* submesh = mesh->getSubMesh(i);

        // We only need to add the shared vertices once
        if (submesh->useSharedVertices)
        {
            if (!added_shared)
            {
                Total_vertex_count += mesh->sharedVertexData->vertexCount;
                added_shared = true;
            }
        }
        else
        {
            Total_vertex_count += submesh->vertexData->vertexCount;
        }

        // Add the indices
        Total_index_count += submesh->indexData->indexCount;
    }


    // Allocate space for the vertices and indices
    vertices = new Ogre::Vector3[Total_vertex_count];
    indices = new Ogre::uint32[Total_index_count];
    TextCords = new Ogre::Vector2[Total_vertex_count];

    added_shared = false;

    // Run through the submeshes again, adding the data into the arrays
    for (unsigned short i = 0; i < mesh->getNumSubMeshes(); ++i)
    {
        Ogre::SubMesh* submesh = mesh->getSubMesh(i);

        Ogre::VertexData* vertex_data = submesh->useSharedVertices ? mesh->sharedVertexData : submesh->vertexData;

        if ((!submesh->useSharedVertices) || (submesh->useSharedVertices && !added_shared))
        {
            if (submesh->useSharedVertices)
            {
                added_shared = true;
                shared_offset = current_offset;
            }

            const Ogre::VertexElement* posElem =
                vertex_data->vertexDeclaration->findElementBySemantic(Ogre::VES_POSITION);

            Ogre::HardwareVertexBufferSharedPtr vbuf =
                vertex_data->vertexBufferBinding->getBuffer(posElem->getSource());

            unsigned char* vertex =
                static_cast<unsigned char*>(vbuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));

            // There is _no_ baseVertexPointerToElement() which takes an Ogre::Ogre::Real or a double
            //  as second argument. So make it float, to avoid trouble when Ogre::Ogre::Real will
            //  be comiled/typedefed as double:
            //      Ogre::Ogre::Real* pOgre::Real;
            float* pReal;

            for (size_t j = 0; j < vertex_data->vertexCount; ++j, vertex += vbuf->getVertexSize())
            {
                posElem->baseVertexPointerToElement(vertex, &pReal);

                Ogre::Vector3 pt(pReal[0], pReal[1], pReal[2]);

                vertices[current_offset + j] = (orient * (pt * scale)) + position;
            }

            vbuf->unlock();
            next_offset += vertex_data->vertexCount;
        }


        Ogre::IndexData* index_data = submesh->indexData;
        size_t numTris = index_data->indexCount / 3;
        Ogre::HardwareIndexBufferSharedPtr ibuf = index_data->indexBuffer;

        bool use32bitindexes = (ibuf->getType() == Ogre::HardwareIndexBuffer::IT_32BIT);

        Ogre::uint32* pLong = static_cast<Ogre::uint32*>(ibuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
        unsigned short* pShort = reinterpret_cast<unsigned short*>(pLong);


        size_t offset = (submesh->useSharedVertices) ? shared_offset : current_offset;

        if (use32bitindexes)
        {
            for (size_t k = 0; k < numTris * 3; ++k)
            {
                indices[index_offset++] = pLong[k] + static_cast<Ogre::uint32>(offset);
            }
        }
        else
        {
            for (size_t k = 0; k < numTris * 3; ++k)
            {
                indices[index_offset++] = static_cast<Ogre::uint32>(pShort[k]) +
                    static_cast<Ogre::uint32>(offset);
            }
        }

        ibuf->unlock();
        current_offset = next_offset;
    }

    // Texture Cords UVS
    int textoffsset = 0;

    for (unsigned short i = 0; i < mesh->getNumSubMeshes(); ++i)
    {
        Ogre::SubMesh* submesh = mesh->getSubMesh(i);

        Ogre::VertexData* vertex_data = submesh->useSharedVertices ? mesh->sharedVertexData : submesh->vertexData;

        if ((!submesh->useSharedVertices) || (submesh->useSharedVertices && !added_shared))
        {
            if (submesh->useSharedVertices)
            {
                added_shared = true;
                shared_offset = current_offset;
            }

            const Ogre::VertexElement* texElem = vertex_data->vertexDeclaration->findElementBySemantic(Ogre::VES_TEXTURE_COORDINATES);

            Ogre::HardwareVertexBufferSharedPtr vbufText =
                vertex_data->vertexBufferBinding->getBuffer(texElem->getSource());

            byte* vertexText = (byte*)vbufText->lock(Ogre::HardwareBuffer::HBL_NORMAL);
            float* pRealText;

            for (ulong j = 0; j < vertex_data->vertexCount; ++j, vertexText += vbufText->getVertexSize())
            {
                texElem->baseVertexPointerToElement(vertexText, &pRealText);
                TextCords[textoffsset].x = pRealText[0];
                TextCords[textoffsset].y = pRealText[1];

                textoffsset++;
            }

            vbufText->unlock();
        }
    }
       
}
