/*
Copyright (c) 2022 Equity_ME Model Editor -- Inflanite Software W.T.Flanigan H.C.Flanigan

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
#include "ME_App.h"
#include "ME_OgreListener.h"


ME_OgreListener::ME_OgreListener()
{
	Stop_Ogre = 0;

	View_Height = 0;
	View_Width = 0;
}


ME_OgreListener::~ME_OgreListener()
{
}

// *************************************************************************
// *				frameStarted   Terry Bernie							   *
// *************************************************************************
bool ME_OgreListener::frameStarted(const FrameEvent& evt)
{
	
	App->CL_Ogre->Get_View_Height_Width();

	App->CL_Ogre->m_imgui.NewFrame(evt.timeSinceLastFrame, (float)View_Width, (float)View_Height);

	App->CL_ImGui->Tabs_Render_Camera();
		
	//ImGui::ShowDemoWindow();

	return true;
}

// *************************************************************************
// *				frameEnded   Terry Bernie							   *
// *************************************************************************
bool ME_OgreListener::frameEnded(const FrameEvent& evt)
{

	if (Stop_Ogre == 1)
	{
		return false;
	}

	return true;
}

// *************************************************************************
// *			frameRenderingQueued   Terry Bernie						   *
// *************************************************************************
bool ME_OgreListener::frameRenderingQueued(const FrameEvent& evt)
{
	
	App->CL_Ogre->m_imgui.render();

	return 1;
}
