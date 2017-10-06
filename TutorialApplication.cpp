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
    Ogre::Node* ballNode = mSceneMgr->getRootSceneNode()->getChild(0);
   
    ballNode = (Ogre::SceneNode*) ballNode;
    int x = mDirection.x;
    int y = mDirection.y;
    int z = mDirection.z;
    switch (ke.key)
    {
        case OIS::KC_ESCAPE: 
            mShutDown = true;
            break;
        case OIS::KC_UP:
            y -= 1;
            mDirection = Ogre::Vector3(x,y,z);
            break;
        case OIS::KC_DOWN:
            y += 1;
            mDirection = Ogre::Vector3(x,y,z);
            break;
        case OIS::KC_LEFT:
            x += 1;
            mDirection = Ogre::Vector3(x,y,z);
            break;
        case OIS::KC_RIGHT:
            x -= 1;
            mDirection = Ogre::Vector3(x,y,z);
            break;
        case OIS::KC_W:
            mShutDown = true;
            break;
        case OIS::KC_A:
            mShutDown = true;
            break;
        case OIS::KC_S:
            mShutDown = true;
            break;
        case OIS::KC_D:
            mShutDown = true;
            break;
        default:
            break;

    }
  return true; 
}
 
bool TutorialApplication::keyReleased(const OIS::KeyEvent& ke) 
{ 
    Ogre::Node* ballNode = mSceneMgr->getRootSceneNode()->getChild(0);
    ballNode = (Ogre::SceneNode*) ballNode;
    int x = mDirection.x;
    int y = mDirection.y;
    int z = mDirection.z;
    switch (ke.key)
    {
        case OIS::KC_ESCAPE: 
            mShutDown = true;
            break;
        case OIS::KC_UP:
            y += 1;
            mDirection = Ogre::Vector3(x,y,z);
            break;
        case OIS::KC_DOWN:
            y -= 1;
            mDirection = Ogre::Vector3(x,y,z);
            break;
        case OIS::KC_LEFT:
            x -= 1;
            mDirection = Ogre::Vector3(x,y,z);
            break;
        case OIS::KC_RIGHT:
            x += 1;
            mDirection = Ogre::Vector3(x,y,z);
            break;
        case OIS::KC_W:
            mShutDown = true;
            break;
        case OIS::KC_A:
            mShutDown = true;
            break;
        case OIS::KC_S:
            mShutDown = true;
            break;
        case OIS::KC_D:
            mShutDown = true;
            break;
        default:
            break;

    }
    
  return true; 
}
void TutorialApplication::createScene(void)
{
    mSceneMgr->setAmbientLight(Ogre::ColourValue(.35, .35, .35));
    Ogre::Light* light = mSceneMgr->createLight("MainLight");
    light->setPosition(0, 75, 0);

    Room room(mSceneMgr, 200);
    room.setup();

    scoreWall = room.getScoreWall();
    scoreWall->pickGoal();
}
//---------------------------------------------------------------------------

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
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
