/*
Copyright (c) 2021 Stage Builder and Equity -- Inflanite Software W.T.Flanigan H.C.Flanigan

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

typedef struct Mvertex_type
{
	float x,y,z;
}Mvertex_type;

class GD_Bt_Render : public btIDebugDraw,public RenderQueueListener
{
	int m_debugMode;

public:
	GD_Bt_Render(void);
	~GD_Bt_Render(void);

	virtual void   drawLine(const btVector3& from, const btVector3& to, const btVector3& fromColor, const btVector3& toColor);

	virtual void   drawLine(const btVector3& from, const btVector3& to, const btVector3& color);

	virtual void   drawSphere(const btVector3& p, btScalar radius, const btVector3& color);

	virtual void   drawTriangle(const btVector3& a, const btVector3& b, const btVector3& c, const btVector3& color, btScalar alpha);

	virtual void   drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color);

	virtual void   reportErrorWarning(const char* warningString);

	virtual void   draw3dText(const btVector3& location, const char* textString);

	virtual void   setDebugMode(int debugMode);

	virtual int  getDebugMode() const;

	inline btVector3 cvt(const Ogre::Vector3 &V){
		return btVector3(V.x, V.y, V.z);
	}

	inline Ogre::Vector3 cvt(const btVector3&V){
		return Ogre::Vector3(V.x(), V.y(), V.z());
	}

	inline btQuaternion cvt(const Ogre::Quaternion &Q)
	{
		return btQuaternion(Q.x, Q.y, Q.z, Q.w);
	};

	inline Ogre::Quaternion cvt(const btQuaternion &Q)
	{
		return Ogre::Quaternion(Q.w(), Q.x(), Q.y(), Q.z());
	};

	void Clear_Debug_Render();
	
	Ogre::Vector3 mfrom;
	Ogre::Vector3 mto;
	Ogre::Vector3 mCfrom;
	Ogre::Vector3 mCto;

	Ogre::ManualObject *mLines;

	Ogre::ManualObject*		btDebug_Manual;
	Ogre::SceneNode*		btDebug_Node;

	Ogre::ColourValue ColourMain;

	bool Render_Debug_Flag; // Stop/Start Render Physics debug shapes [021221]

	std::vector<Mvertex_type> vertex_Colour;
	std::vector<Mvertex_type> vertex_From;
	std::vector<Mvertex_type> vertex_To;

	int V_Count;

protected:

	virtual void renderQueueStarted(Ogre::uint8 queueGroupId, const String& invocation, 
		bool& skipThisInvocation);

	virtual void renderQueueEnded(Ogre::uint8 queueGroupId, const String& invocation, 
		bool& repeatThisInvocation);

	void PreRender();
	void PostRender();
	
	void Render_Debug_Bullet();
	
	bool Render_Debug(void);

	// Clear Debug Render to Zero [021221]

};

