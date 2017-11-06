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
    virtual bool mouseMoved(const OIS::MouseEvent &arg);

    // GUI components
    CEGUI::Window* sheet;
    CEGUI::Window* startLabel;
    CEGUI::Window* gameOverLabel;
    CEGUI::Window* tooSlowLabel;
    CEGUI::Window* menuButton;
    CEGUI::Window* scoreBox;
    CEGUI::Window* multiScoreBox;
    CEGUI::Window* p1ScoreBox;
    CEGUI::Window* p1ScoreLabel;
    CEGUI::Window* p2ScoreBox;
    CEGUI::Window* p2ScoreLabel;
    CEGUI::Window* scoreLabel;
    CEGUI::Window* mainMenuBox;
    CEGUI::Window* singleButton;
    CEGUI::Window* multiButton;
    CEGUI::Window* mainSoundButton;
    CEGUI::Window* multiMenuBox;
    CEGUI::Window* serverButton;
    CEGUI::Window* clientButton;
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
    bool single(const CEGUI::EventArgs &e);
    bool multi(const CEGUI::EventArgs &e);
    bool server(const CEGUI::EventArgs &e);
    bool client(const CEGUI::EventArgs &e);

    void start(void);
    void updateScoreLabel(void);
    void updateScoreLabelOther(void);
    void gameOver(bool);
    void roundOverMulti(int,bool);
    void restartGame(void);

    // Network functions
    void initNetwork(void);
};

//---------------------------------------------------------------------------

#endif // #ifndef __TutorialApplication_h_

//---------------------------------------------------------------------------
