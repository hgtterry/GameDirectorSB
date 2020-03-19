#pragma once

#include <imgui.h>
#include <OgreCommon.h>

#include <OgreRenderQueueListener.h>
#include <OgreTexture.h>
#include "OgrePrerequisites.h"
#include "OgreRenderable.h"
#include <OgreRenderOperation.h>

class OgreImGui
{
public:

    OgreImGui();

    void Init(Ogre::SceneManager* mgr, HWND OgreWin);

    //Inherited from OIS::MouseListener
    bool mouseMoved();
    bool mousePressed();
    bool mouseReleased();

    //Inherited from OIS::KeyListener
    virtual bool keyPressed();
    virtual bool keyReleased();

    void render();
    void NewFrame(float deltaTime, float displayWidth, float displayHeight);
	HWND mOgreWin;
	
private:

    class ImGUIRenderable : public Ogre::Renderable
    {
    public:
        ImGUIRenderable();
        virtual ~ImGUIRenderable();

        void updateVertexData(const ImDrawVert* vtxBuf, const ImDrawIdx* idxBuf, unsigned int vtxCount, unsigned int idxCount);
        Ogre::Real getSquaredViewDepth(const Ogre::Camera* cam) const   { (void)cam; return 0; }

        void setMaterial( const Ogre::String& matName );
        void setMaterial(const Ogre::MaterialPtr & material);
        virtual const Ogre::MaterialPtr& getMaterial(void) const override;
        virtual void getWorldTransforms( Ogre::Matrix4* xform ) const override;
        virtual void getRenderOperation( Ogre::RenderOperation& op ) override;
        virtual const Ogre::LightList& getLights(void) const override;

        int                      mVertexBufferSize;
        int                      mIndexBufferSize;

    private:
        void initImGUIRenderable(void);

        Ogre::MaterialPtr mMaterial;
        Ogre::RenderOperation mRenderOp;
    };

    void createFontTexture();
    void createMaterial();

    Ogre::SceneManager*         mSceneMgr;
    Ogre::Pass*                 mPass;
    Ogre::TexturePtr            mFontTex;

};

