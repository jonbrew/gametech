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
#include <Ogre.h> 
#include <OgreEntity.h> 
#include <OgreSceneManager.h> 
#include <OISEvents.h> 
#include <OISInputManager.h> 
#include <OISKeyboard.h> 
#include <OISMouse.h> 
#include <OgreRenderWindow.h> 
//#include <SdkTrays.h> 


PlayingField::PlayingField(Ogre::SceneManager* scnMgr) {
    rootNode = scnMgr->getRootSceneNode()->createChildSceneNode("PlayingField");
    Ogre::Plane plane(Ogre::Vector3::UNIT_Y,0);
    Ogre::MeshManager::getSingleton().createPlane(
        "wall",
        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        plane,
        150, 150, 20, 20,
        true,
        1, 5, 5,
        Ogre::Vector3::UNIT_Z);

    

    for (int i = 0; i < 6; i++) {
        wall_entities[i] = scnMgr->createEntity("wall");
        wall_entities[i]->setMaterialName("Examples/BeachStones");
    }

    Ogre::SceneNode* ground = scnMgr->getRootSceneNode()->createChildSceneNode();
    ground->attachObject(wall_entities[0]);

    Ogre::SceneNode* side1 = scnMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, 75, 75));
    side1->pitch(Ogre::Degree(-90));
    side1->attachObject(wall_entities[1]);

    Ogre::SceneNode* side2 = scnMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(75, 75, 0));
    side2->roll(Ogre::Degree(90));
    side2->attachObject(wall_entities[2]);

    Ogre::SceneNode* side3 = scnMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, 75, -75));
    side3->pitch(Ogre::Degree(90));
    side3->attachObject(wall_entities[3]);

    Ogre::SceneNode* side4 = scnMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(-75, 75, 0));
    side4->roll(Ogre::Degree(-90));
    side4->attachObject(wall_entities[4]);

    Ogre::SceneNode* ceiling = scnMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, 150, 0));
    ceiling->pitch(Ogre::Degree(180));
    ceiling->attachObject(wall_entities[5]);

}

void PlayingField::addChild(Ogre::SceneNode* child) {
    rootNode->addChild(child);
}

int PlayingField::getHeight() {
    return 150;
}

int PlayingField::getWidth() {
    return 150;
}

int PlayingField::getLength() {
    return 150;
}


Ball::Ball(Ogre::SceneManager* scnMgr) { 
    Ogre::Entity* ball = scnMgr->createEntity("Sphere", "sphere.mesh"); 
    ball->setMaterialName("Examples/SceneCubeMap2"); 
    ball->setCastShadows(true); 

    rootNode = scnMgr->createSceneNode("Ball"); 
    rootNode->attachObject(ball); 
    rootNode->scale(0.1f,0.1f,0.1f); 
    rootNode->setPosition(Ogre::Vector3(0, 50, 0));
    bRadius = 10.0f; 
    bDirection = Ogre::Vector3(1.0f, 2.0f, 3.0f); 
    bDirection.normalise(); 
    bSpeed = 250.0f; 
} 

void Ball::move(const Ogre::FrameEvent& evt) { 
    Ogre::Vector3 bPosition = rootNode->getPosition(); 
    if (bPosition.y < bRadius && bDirection.y < 0.0f) bDirection.y = -bDirection.y; 
    if (bPosition.y > grounds->getHeight() - bRadius && bDirection.y > 0.0f) bDirection.y = -bDirection.y; 
    if (bPosition.z < -grounds->getLength()/2.0f + bRadius && bDirection.z < 0.0f) bDirection.z = -bDirection.z; 
    if (bPosition.z > grounds->getLength()/2.0f - bRadius && bDirection.z > 0.0f) bDirection.z = -bDirection.z; 
    if (bPosition.x < -grounds->getWidth()/2.0f + bRadius && bDirection.x < 0.0f) bDirection.x = -bDirection.x; 
    if (bPosition.x > grounds->getWidth()/2.0f - bRadius && bDirection.x > 0.0f) bDirection.x = -bDirection.x; 
    rootNode->translate(bSpeed * evt.timeSinceLastFrame * bDirection); 
}


bool TutorialApplication::frameRenderingQueued(const Ogre::FrameEvent& evt) { 
    if(mWindow->isClosed())
        return false;

    if(mShutDown)
        return false;

    // Need to capture/update each device
    mKeyboard->capture();
    mMouse->capture();

    mCameraMan->frameRenderingQueued(evt);
    ball->move(evt);

    return true; 
}


//---------------------------------------------------------------------------
TutorialApplication::TutorialApplication(void)
{
}
//---------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{

}

void TutorialApplication::createCamera() {
    mCamera = mSceneMgr->createCamera("PlayerCam");
    mCamera->setPosition(Ogre::Vector3(0.0f, 0.0f, 0.4f*1000));
    mCamera->lookAt(Ogre::Vector3(0,0,0));
    mCamera->setNearClipDistance(5);
    mCameraMan = new OgreBites::SdkCameraMan(mCamera);

}

void TutorialApplication::createViewports() {
    Ogre::Viewport* vp = mWindow->addViewport(mCamera);
    vp->setBackgroundColour(Ogre::ColourValue(0,0,0));

    mCamera->setAspectRatio(
        Ogre::Real(vp->getActualWidth()) /
        Ogre::Real(vp->getActualHeight())); 
}

//---------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
    // Create your scene here :)
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5f,0.5f,0.5f));
    mCamera->setPosition(0,47,222);

    Ogre::Light* light = mSceneMgr->createLight("MainLight");
    light->setPosition(20.0,80.0,50.0);
    light->setDiffuseColour(0, 0, 4);
    light->setSpecularColour(0,0,1);

    mSceneMgr->setSkyBox(true, "Examples/MorningSkyBox", 5000, false); 
    PlayingField* bCourt = new PlayingField(mSceneMgr); 
    ball = new Ball(mSceneMgr); 
    bCourt->addChild(ball->getNode()); 
    ball->setPlayingField(bCourt);
    
    // Set default mipmap level (note: some APIs ignore this) 
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5); 
    // initialise all resource groups 
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups(); 
    // Create the SceneManager, in this case a generic one 

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
