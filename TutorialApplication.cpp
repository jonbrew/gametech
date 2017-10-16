/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.cpp
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

#include <string> 
#include <sstream>

#include "TutorialApplication.h"

//---------------------------------------------------------------------------
TutorialApplication::TutorialApplication(void)
{
}
//---------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
}

//---------------------------------------------------------------------------
bool TutorialApplication::keyPressed(const OIS::KeyEvent& ke) 
{ 
    
   //change to paddle
    Ogre::Node* paddleNode = mSceneMgr->getRootSceneNode()->getChild("Paddle");
   
    paddleNode = (Ogre::SceneNode*) paddleNode;
    Ogre::Real x = mDirection.x;
    Ogre::Real y = mDirection.y;
    Ogre::Real z = mDirection.z;

    Ogre::Real move = 100;
    switch (ke.key)
    {
        case OIS::KC_ESCAPE: 
            mShutDown = true;
            break;
        case OIS::KC_UP:
            //y += move;
            mPitch = Ogre::Radian(Ogre::Degree(-.1));
            break;
        case OIS::KC_DOWN:
            //y -= move;
            mPitch = Ogre::Radian(Ogre::Degree(.1));
            break;
        case OIS::KC_LEFT:
            //x += move;
            mRoll = Ogre::Radian(Ogre::Degree(.1));
            break;
        case OIS::KC_RIGHT:
            //x -= move;
            mRoll = Ogre::Radian(Ogre::Degree(-.1));
            break;
        case OIS::KC_W:
            y += move;
            mDirection = Ogre::Vector3(x,y,z);
            break;
        case OIS::KC_A:
            x += move;
            mDirection = Ogre::Vector3(x,y,z);
            break;
        case OIS::KC_S:
            y -= move;
            mDirection = Ogre::Vector3(x,y,z);
            break;
        case OIS::KC_D:
            x -= move;
            mDirection = Ogre::Vector3(x,y,z);
            break;
        case OIS::KC_K:
            mRoll = Ogre::Radian(Ogre::Degree(.1));
            break;
        case OIS::KC_L:
            mRoll = Ogre::Radian(Ogre::Degree(-.1));
            break;
        case OIS::KC_H:
            mPitch = Ogre::Radian(Ogre::Degree(.1));
            break;
        case OIS::KC_J:
            mPitch = Ogre::Radian(Ogre::Degree(-.1));
            break;
         case OIS::KC_SPACE:
            if(mHit)
               break;
            mHit = true;
            mHitFrames = mHitMaxFrames;
            break;
        default:
            break;

    }
  return true; 
}
 
bool TutorialApplication::keyReleased(const OIS::KeyEvent& ke) 
{ 
    Ogre::Node* paddleNode = mSceneMgr->getRootSceneNode()->getChild("Paddle");
    paddleNode = (Ogre::SceneNode*) paddleNode;
    Ogre::Real x = mDirection.x;
    Ogre::Real y = mDirection.y;
    Ogre::Real z = mDirection.z;

    Ogre::Real move = 100;
    switch (ke.key)
    {
        case OIS::KC_ESCAPE: 
            mShutDown = true;
            break;
        case OIS::KC_UP:
            mPitch = 0;
            break;
        case OIS::KC_DOWN:
            mPitch = 0;
            break;
        case OIS::KC_LEFT:
            mRoll = 0;
            break;
        case OIS::KC_RIGHT:
            mRoll = 0;
            break;
        case OIS::KC_W:
            y -= move;
            mDirection = Ogre::Vector3(x,y,z);
            break;
        case OIS::KC_A:
            x -= move;
            mDirection = Ogre::Vector3(x,y,z);
            break;
        case OIS::KC_S:
            y += move;
            mDirection = Ogre::Vector3(x,y,z);
            break;
        case OIS::KC_D:
            x += move;
            mDirection = Ogre::Vector3(x,y,z);
            break;
        case OIS::KC_K:
            mRoll = 0;
            break;
        case OIS::KC_L:
            mRoll = 0;
            break;
        case OIS::KC_H:
            mPitch = 0;
            break;
        case OIS::KC_J:
            mPitch = 0;
            break;
        case OIS::KC_SPACE:
            if(mGameState == BaseApplication::STOPPED) {
                startLabel->hide();
                mGameState = BaseApplication::RUNNING;
            }
            break;
        case OIS::KC_R:
            restartGame();
            break;
        default:
            break;

    }
    
  return true; 
}


void TutorialApplication::createScene(void)
{
    //srand(time(NULL));
    mSceneMgr->setAmbientLight(Ogre::ColourValue(.35, .35, .35));
    Ogre::Light* light = mSceneMgr->createLight("MainLight");
    light->setPosition(0, 75, 0);

    room = new Room(mSceneMgr, mPhysics, 200);
    room->setup();
    scoreWall = room->getScoreWall();
    scoreWall->pickGoal();
    Ogre::Node* paddleNode = mSceneMgr->getRootSceneNode()->getChild("Paddle");
    mCamera->lookAt(paddleNode->getPosition());

    setupGUI();
}


void TutorialApplication::setupGUI() {
    gui = new GUI();

    CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();      
    sheet = wmgr.createWindow("DefaultWindow", "CEGUIDemo/Sheet");
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(sheet);

    // Start Label
    startLabel = wmgr.createWindow("Vanilla/Label", "CEGUIDemo/StartLabel");
    startLabel->setFont("Jura-Regular");
    startLabel->setText("Press SPACEBAR to start");
    startLabel->setSize(CEGUI::USize(CEGUI::UDim(0.3, 0), CEGUI::UDim(0.1, 0)));
    startLabel->setPosition(CEGUI::UVector2(CEGUI::UDim(0.35, 0), CEGUI::UDim(0.45, 0)));
    sheet->addChild(startLabel);

    // Game Over Label
    gameOverLabel = wmgr.createWindow("Vanilla/Label", "CEGUIDemo/GameOverLabel");
    gameOverLabel->setFont("Jura-Regular");
    gameOverLabel->setText("Press R to restart");
    gameOverLabel->setSize(CEGUI::USize(CEGUI::UDim(0.3, 0), CEGUI::UDim(0.1, 0)));
    gameOverLabel->setPosition(CEGUI::UVector2(CEGUI::UDim(0.35, 0), CEGUI::UDim(0.45, 0)));
    gameOverLabel->hide();
    sheet->addChild(gameOverLabel);

    // Menu Button
    menuButton = wmgr.createWindow("Vanilla/Button", "CEGUIDemo/MenuButton");
    menuButton->setFont("Jura-Regular");
    menuButton->setText("Menu");
    menuButton->setSize(CEGUI::USize(CEGUI::UDim(0.1, 0), CEGUI::UDim(0.05, 0)));
    menuButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&TutorialApplication::menu, this));
    sheet->addChild(menuButton);

    // Score Box
    scoreBox = wmgr.createWindow("Vanilla/FrameWindow", "CEGUIDemo/ScoreBox");
    scoreBox->setFont("Jura-Regular");
    scoreBox->setText("SCORE");
    scoreBox->setSize(CEGUI::USize(CEGUI::UDim(0.1, 0), CEGUI::UDim(0.125, 0)));
    scoreBox->setPosition(CEGUI::UVector2(CEGUI::UDim(0.85, 0), CEGUI::UDim(0.8, 0)));
    scoreLabel = scoreBox->createChild("Vanilla/Label", "CEGUIDemo/ScoreBox/ScoreLabel");
    scoreLabel->setFont("Jura-Regular");
    scoreLabel->setText("0");
    scoreLabel->setSize(CEGUI::USize(CEGUI::UDim(1, 0), CEGUI::UDim(0.5, 0)));
    scoreLabel->setPosition(CEGUI::UVector2(CEGUI::UDim(0.02, 0), CEGUI::UDim(0.25, 0)));
    sheet->addChild(scoreBox);

    // Menu
    menuBox = wmgr.createWindow("Vanilla/FrameWindow", "CEGUIDemo/Menu");
    menuBox->setFont("Jura-Regular");
    menuBox->setText("Menu");
    menuBox->setSize(CEGUI::USize(CEGUI::UDim(0.2, 0), CEGUI::UDim(0.6, 0)));
    menuBox->setPosition(CEGUI::UVector2(CEGUI::UDim(0.4, 0), CEGUI::UDim(0.2, 0)));
    menuBox->hide();

    // Resume Button
    resumeButton = menuBox->createChild("Vanilla/Button", "CEGUIDemo/Menu/QuitButton");
    resumeButton->setFont("Jura-Regular");
    resumeButton->setText("Resume");
    resumeButton->setSize(CEGUI::USize(CEGUI::UDim(0.8, 0), CEGUI::UDim(0.1, 0)));
    resumeButton->setPosition(CEGUI::UVector2(CEGUI::UDim(0.1, 0), CEGUI::UDim(0.1, 0)));
    resumeButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&TutorialApplication::resume, this));

    // Toggle Sound Button
    soundButton = menuBox->createChild("Vanilla/Button", "CEGUIDemo/Menu/SoundButton");
    soundButton->setFont("Jura-Regular");
    soundButton->setText("Sound Off");
    soundButton->setSize(CEGUI::USize(CEGUI::UDim(0.8, 0), CEGUI::UDim(0.1, 0)));
    soundButton->setPosition(CEGUI::UVector2(CEGUI::UDim(0.1, 0), CEGUI::UDim(0.3, 0)));
    soundButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&TutorialApplication::sound, this));

    // Restart Button
    restartButton = menuBox->createChild("Vanilla/Button", "CEGUIDemo/Menu/RestartButton");
    restartButton->setFont("Jura-Regular");
    restartButton->setText("Restart");
    restartButton->setSize(CEGUI::USize(CEGUI::UDim(0.8, 0), CEGUI::UDim(0.1, 0)));
    restartButton->setPosition(CEGUI::UVector2(CEGUI::UDim(0.1, 0), CEGUI::UDim(0.5, 0)));
    restartButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&TutorialApplication::restart, this));

    // Quit Button
    quitButton = menuBox->createChild("Vanilla/Button", "CEGUIDemo/Menu/QuitButton");
    quitButton->setFont("Jura-Regular");
    quitButton->setText("Quit");
    quitButton->setSize(CEGUI::USize(CEGUI::UDim(0.8, 0), CEGUI::UDim(0.1, 0)));
    quitButton->setPosition(CEGUI::UVector2(CEGUI::UDim(0.1, 0), CEGUI::UDim(0.7, 0)));
    quitButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&TutorialApplication::quit, this));

    sheet->addChild(menuBox);
}

bool TutorialApplication::menu(const CEGUI::EventArgs &e) {
    // Show menu
    menuBox->show();

    // Pause game
    mGameState = BaseApplication::PAUSED;
    return true;
}

bool TutorialApplication::sound(const CEGUI::EventArgs &e) {
    // Toggle sound
    mSound->toggle();

    // Change text
    if(mSound->getIsOn()) {
        soundButton->setText("Sound Off");
    }
    else {
        soundButton->setText("Sound On");
    }

    return true;
}


bool TutorialApplication::resume(const CEGUI::EventArgs &e) {
    // Hide menu
    menuBox->hide();

    // Resume game
    mGameState = BaseApplication::RUNNING;
    return true;
}

bool TutorialApplication::restart(const CEGUI::EventArgs &e) {
    restartGame();
    // Hide Menu
    menuBox->hide();
    return true;
}

bool TutorialApplication::quit(const CEGUI::EventArgs &e) {
    mShutDown = true;
    return true;
}

void TutorialApplication::updateScoreLabel() {
    int score = scoreWall->getScore();
    std::stringstream ss;
    ss << score;
    scoreLabel->setText(ss.str());
}

void TutorialApplication::restartGame() {
    // Stop game
    mGameState = BaseApplication::STOPPED;
    // Reset score
    scoreWall->resetScore();
    updateScoreLabel();
    // Reset room
    room->reset();
    // Show label
    startLabel->show();
}

void TutorialApplication::gameOver() {
    // Show label
    gameOverLabel->show();
}

//---------------------------------------------------------------------------

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"Button
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        TutorialApplication app;

        try {
            app.go();
        } catch(Ogre::Exception& e)  {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occurred: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif

//---------------------------------------------------------------------------
