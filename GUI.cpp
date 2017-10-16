#include "GUI.h"

GUI::GUI() {
    mRenderer = &CEGUI::OgreRenderer::bootstrapSystem();

    initCEGUI();
}

void GUI::initCEGUI() {
	CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
    CEGUI::Font::setDefaultResourceGroup("Fonts");
    CEGUI::Scheme::setDefaultResourceGroup("Schemes");
    CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
    CEGUI::WindowManager::setDefaultResourceGroup("Layouts");

    // Pick scheme and set defaults
    CEGUI::SchemeManager::getSingleton().createFromFile("VanillaSkin.scheme");
    CEGUI::FontManager::getSingleton().createFreeTypeFont("Jura-Regular", 20, true, "Jura-Regular.ttf", "Fonts");
    CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("Vanilla-Images/MouseArrow");
}
