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
        default:
            break;

    }
    
  return true; 
}


void TutorialApplication::createScene(void)
{
    srand(time(NULL));
    mSceneMgr->setAmbientLight(Ogre::ColourValue(.35, .35, .35));
    Ogre::Light* light = mSceneMgr->createLight("MainLight");
    light->setPosition(0, 75, 0);

    room = new Room(mSceneMgr, mPhysics, 200);
    room->setup();
    scoreWall = room->getScoreWall();
    scoreWall->pickGoal();

    // mSound->play(Sound::SOUND_HIT);

    Ogre::Node* paddleNode = mSceneMgr->getRootSceneNode()->getChild("Paddle");
    mCamera->lookAt(paddleNode->getPosition());

    setupGUI();
}


void TutorialApplication::setupGUI() {
    gui = new GUI();

    CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();      
    CEGUI::Window* sheet = wmgr.createWindow("DefaultWindow", "CEGUIDemo/Sheet");
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(sheet);

    // Menu
    CEGUI::Window* menu = wmgr.createWindow("Vanilla/Button", "CEGUIDemo/MenuButton");
    menu->setFont("Jura-Regular");
    menu->setText("Menu");
    menu->setSize(CEGUI::USize(CEGUI::UDim(0.1, 0), CEGUI::UDim(0.05, 0)));
    // menu->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&TutorialApplication::quit, this));
    sheet->addChild(menu);

    // Scorebox
    CEGUI::Window* scorebox = wmgr.createWindow("Vanilla/FrameWindow", "CEGUIDemo/ScoreBox");
    scorebox->setFont("Jura-Regular");
    scorebox->setText("SCORE");
    scorebox->setSize(CEGUI::USize(CEGUI::UDim(0.1, 0), CEGUI::UDim(0.125, 0)));
    scorebox->setPosition(CEGUI::UVector2(CEGUI::UDim(0.85, 0), CEGUI::UDim(0.8, 0)));
    CEGUI::Window* scoreLabel = scorebox->createChild("Vanilla/Label", "CEGUIDemo/ScoreBox/ScoreLabel");
    scoreLabel->setFont("Jura-Regular");
    scoreLabel->setText("0");
    scoreLabel->setSize(CEGUI::USize(CEGUI::UDim(1, 0), CEGUI::UDim(0.5, 0)));
    scoreLabel->setPosition(CEGUI::UVector2(CEGUI::UDim(0.02, 0), CEGUI::UDim(0.25, 0)));

    sheet->addChild(scorebox);


    // Quit
    CEGUI::Window* quit = wmgr.createWindow("Vanilla/Button", "CEGUIDemo/QuitButton");
    quit->setFont("Jura-Regular");
    quit->setText("Quit");
    quit->setSize(CEGUI::USize(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
    quit->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&TutorialApplication::quit, this));
    // sheet->addChild(quit);
}


bool TutorialApplication::quit(const CEGUI::EventArgs &e) {
    mShutDown = true;
    return true;
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
