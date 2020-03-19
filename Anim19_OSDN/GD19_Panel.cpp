/*
	Copyright (c) GD10 (GameDirector) 2019 Inflanite Software W.T.Flanigan H.C.Flanigan B.Parkin

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

#include "StdAfx.h"
#include "GD19_App.h"
#include "GD19_Panel.h"

GD19_Panel::GD19_Panel(char* PanelName, char* OverlayName, char* TextAreaName)
{
	overlay = nullptr;
	panel = nullptr;
	textArea = nullptr;
	LoadingText = nullptr;

	strcpy(mOverlayName, PanelName);
	strcpy(mTextAreaName, OverlayName);
	strcpy(mPanel_Name, PanelName);

	strcpy(mText,"Welcome."); // Test

	strcpy(mFont_Name, "MyFont"); // Test
	
	Font_Size = 48;

	Red = 0;
	Green = 0;
	Blue = 1.0;

	mText_Pos_X = 55;
	mText_Pos_Y = 30;

	mPanel_Pos_X = -150;
	mPanel_Pos_Y = 50;

	mPanel_Width = 300;
	mPanel_Height = 100;

	CreateTextOverlay(PanelName, OverlayName, TextAreaName);

}

GD19_Panel::~GD19_Panel(void)
{
}

// *************************************************************************
// *					CreateTextOverlay (Terry Bernie)				   *
// *************************************************************************
bool GD19_Panel::CreateTextOverlay(char* Name, char* OverlayName, char* TextAreaName)
{
	//  Creation 
	OverlayManager& overlayManager = OverlayManager::getSingleton();

	panel = static_cast <BorderPanelOverlayElement*> (overlayManager.createOverlayElement("BorderPanel", Name));

	panel->setMetricsMode(Ogre::GMM_PIXELS);
	panel->setPosition(mPanel_Pos_X, mPanel_Pos_Y);
	panel->setDimensions(mPanel_Width, mPanel_Height);
	panel->setHorizontalAlignment(GHA_CENTER);
	panel->setVerticalAlignment(GVA_TOP);
	panel->setColour(ColourValue(1.0, 0.0, 0.0));
	panel->setCaption("Test");
	panel->setMaterialName("Core/PhysicsStatsBlockBorder");
	panel->setBorderSize(4, 4, 4, 4);
	panel->setBorderMaterialName("Core/StatsBlockBorder");
	panel->show();

	// Create a text area
	textArea = static_cast<TextAreaOverlayElement*>(overlayManager.createOverlayElement("TextArea", TextAreaName));
	textArea->setMetricsMode(Ogre::GMM_PIXELS);
	textArea->setPosition(mText_Pos_X, mText_Pos_Y);
	textArea->setDimensions(100, 100);
	textArea->setCharHeight(Ogre::Real(Font_Size));
	textArea->setFontName(mFont_Name);
	textArea->setColour(ColourValue(Red,Green,Blue));
	textArea->setCaption(mText);

	//// Create a text area
	//LoadingText = static_cast<TextAreaOverlayElement*>(overlayManager.createOverlayElement("TextArea", "TextAreaName2"));

	//LoadingText->setMetricsMode(Ogre::GMM_PIXELS);
	//LoadingText->setPosition(-130, 300);
	//LoadingText->setDimensions(100, 100);
	//LoadingText->setCaption("Loading Poo Please Wait");
	//LoadingText->setCharHeight(36);
	//LoadingText->setFontName("BlueHighway");
	//LoadingText->setColour(ColourValue(0.0, 1.0, 0.0));
	//LoadingText->hide();
	//LoadingText->show();

	//// Create an overlay, and add the panel
	overlay = overlayManager.create(OverlayName);
	overlay->add2D(panel);
	//overlay->scroll(0, 0.5);

	//// Add the text area to the panel
	panel->addChild(textArea);
	
	overlay->hide();

	return 1;
}
