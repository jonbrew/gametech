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
#include <OgreMeshManager.h>

//---------------------------------------------------------------------------
TutorialApplication::TutorialApplication(void)
{
}
//---------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
}

//---------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
    mSceneMgr->setAmbientLight(Ogre::ColourValue(.35, .35, .35));
    Ogre::Light* light = mSceneMgr->createLight("MainLight");
    light->setPosition(0, 75, 0);

    createWalls(200);
    Ball* ball = new Ball(mSceneMgr);
    Ogre::Entity* ballEntity = mSceneMgr->createEntity("sphere.mesh"); 
    //ball->setMaterialName("BallColor/CubeMap"); 
    ballEntity->setCastShadows(true);
    Ogre::SceneNode* ballNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("ball"); 
    ballNode->attachObject(ballEntity);
    ballNode->scale(0.1,0.1,0.1); 
    ballNode->setPosition(0,0,0);

}

void TutorialApplication::createWalls(int wallSize)
{
    // Create plane and mesh
    Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingleton().createPlane(
        "planeMesh",
        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        plane, 
        wallSize, wallSize, 20, 20, 
        true, 
        1, 5, 5, 
        Ogre::Vector3::UNIT_Z);
    Ogre::Entity* groundEntity = mSceneMgr->createEntity("planeMesh");
    groundEntity->setCastShadows(false);
    groundEntity->setMaterialName("Examples/Rockwall");
    
    // Create SceneNodes
    Ogre::SceneNode *groundNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    Ogre::SceneNode *ceilingNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    Ogre::SceneNode *rightNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    Ogre::SceneNode *leftNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    Ogre::SceneNode *frontNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    Ogre::SceneNode *backNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    
    // Attach entities to Nodes and move to position
    groundNode->attachObject(groundEntity);
    groundNode->translate(Ogre::Vector3(0,-wallSize/2,0));
    ceilingNode->attachObject(groundEntity->clone("ceilingEntity"));
    ceilingNode->roll(Ogre::Radian(Ogre::Degree(180)));
    ceilingNode->translate(Ogre::Vector3(0,wallSize/2,0));
    rightNode->attachObject(groundEntity->clone("rightEntity"));
    rightNode->roll(Ogre::Radian(Ogre::Degree(-90)));
    rightNode->yaw(Ogre::Radian(Ogre::Degree(90)));
    rightNode->translate(Ogre::Vector3(-wallSize/2,0,0));
    leftNode->attachObject(groundEntity->clone("leftEntity"));
    leftNode->roll(Ogre::Radian(Ogre::Degree(90)));
    leftNode->yaw(Ogre::Radian(Ogre::Degree(90)));
    leftNode->translate(Ogre::Vector3(wallSize/2,0,0));
    frontNode->attachObject(groundEntity->clone("frontEntity"));
    frontNode->pitch(Ogre::Radian(Ogre::Degree(-90)));
    frontNode->translate(Ogre::Vector3(0,0,wallSize/2));
    backNode->attachObject(groundEntity->clone("backEntity"));
    backNode->pitch(Ogre::Radian(Ogre::Degree(90)));
    backNode->translate(Ogre::Vector3(0,0,-wallSize/2));
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
