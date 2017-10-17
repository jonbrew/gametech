/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.h
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/
Tutorial Framework (for Ogre 1.9)
http://www.ogre3d.org/wiki/
-----------------------------------------------------------------------------
*/

#ifndef __TutorialApplication_h_
#define __TutorialApplication_h_

#include "BaseApplication.h"
#include "Room.h"
#include "Paddle.h"

//---------------------------------------------------------------------------

class TutorialApplication : public BaseApplication
{
public:
    TutorialApplication(void);
    virtual ~TutorialApplication(void);

protected:
    virtual void createScene(void);
    virtual bool keyPressed(const OIS::KeyEvent& ke);
    virtual bool keyReleased(const OIS::KeyEvent& ke);

    // GUI components
    CEGUI::Window* sheet;
    CEGUI::Window* startLabel;
    CEGUI::Window* gameOverLabel;
    CEGUI::Window* tooSlowLabel;
    CEGUI::Window* youMissedLabel;
    CEGUI::Window* menuButton;
    CEGUI::Window* scoreBox;
    CEGUI::Window* scoreLabel;
    CEGUI::Window* menuBox;
    CEGUI::Window* quitButton;
    CEGUI::Window* resumeButton;
    CEGUI::Window* restartButton;
    CEGUI::Window* soundButton;
    
    // CEGUI
    void setupGUI(void);

    // GUI Events
    bool start(const CEGUI::EventArgs &e);
    bool menu(const CEGUI::EventArgs &e);
    bool sound(const CEGUI::EventArgs &e);
    bool restart(const CEGUI::EventArgs &e);
    bool resume(const CEGUI::EventArgs &e);
    bool quit(const CEGUI::EventArgs &e);

    void updateScoreLabel(void);
    void gameOver(bool);
    void restartGame(void);
};

//---------------------------------------------------------------------------

#endif // #ifndef __TutorialApplication_h_

//---------------------------------------------------------------------------
