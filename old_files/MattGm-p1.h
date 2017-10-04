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
#include <OgreRoot.h>
#include <SdkCameraMan.h>
#include <OIS/OISEvents.h>
#include <OIS/OISInputManager.h>
#include <OIS/OISKeyboard.h>
#include <OIS/OISMouse.h>

//---------------------------------------------------------------------------
class PlayingField {
protected:
    Ogre::SceneNode* rootNode;

public:
    Ogre::Entity* wall_entities[6];
    PlayingField(Ogre::SceneManager* scnMgr);
    ~PlayingField();
    void addChild(Ogre::SceneNode* child);
    int getHeight();
    int getWidth();
    int getLength();

};

class Ball { 
    protected: 
        Ogre::SceneNode* rootNode; 
        Ogre::Real bRadius; 
        Ogre::Vector3 bDirection; 
        Ogre::Real bSpeed; 
        PlayingField* grounds; 
    public: 
        Ball(Ogre::SceneManager* scnMgr); 
        ~Ball(); 
        void move(const Ogre::FrameEvent& evt); 
        Ogre::SceneNode* getNode() { return rootNode; } 
        void setPlayingField(PlayingField * pf) { grounds = pf; } 
};


class TutorialApplication : public BaseApplication
{
protected:
	Ball* ball;
	OgreBites::SdkCameraMan* mCameraMan;

public:
    TutorialApplication(void);
    virtual ~TutorialApplication(void);

protected:
    virtual void createScene(void);
    virtual void createCamera();
    virtual void createViewports();
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& fe);
};

//---------------------------------------------------------------------------

#endif // #ifndef __TutorialApplication_h_

//---------------------------------------------------------------------------
