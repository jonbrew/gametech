#ifndef __GUI_h_
#define __GUI_h_

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

class GUI {
public:
	GUI(void);

private:
    CEGUI::OgreRenderer*        mRenderer;

    void initCEGUI(void);
};

#endif
