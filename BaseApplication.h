/*
-----------------------------------------------------------------------------
Filename:    BaseApplication.h
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

#ifndef __BaseApplication_h_
#define __BaseApplication_h_

#include "ScoreWall.h"
#include "Room.h"
#include "Sound.h"
#include "Physics.h"
#include "GUI.h"
#include "NetManager.h"
#include "DebugDraw.hpp"

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>
#include <OgreMeshManager.h>

#include <OgreWindowEventUtilities.h>
#include <OgreFrameListener.h>
#include <Overlay/OgreOverlaySystem.h>

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
#  include <OIS/OISEvents.h>
#  include <OIS/OISInputManager.h>
#  include <OIS/OISKeyboard.h>
#  include <OIS/OISMouse.h>

#else
#  include <OISEvents.h>
#  include <OISInputManager.h>
#  include <OISKeyboard.h>
#  include <OISMouse.h>

#endif

#ifdef OGRE_STATIC_LIB
#  define OGRE_STATIC_GL
#  if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#    define OGRE_STATIC_Direct3D9
// D3D10 will only work on vista, so be careful about statically linking
#    if OGRE_USE_D3D10
#      define OGRE_STATIC_Direct3D10
#    endif
#  endif
#  define OGRE_STATIC_BSPSceneManager
#  define OGRE_STATIC_ParticleFX
#  define OGRE_STATIC_CgProgramManager
#  ifdef OGRE_USE_PCZ
#    define OGRE_STATIC_PCZSceneManager
#    define OGRE_STATIC_OctreeZone
#  else
#    define OGRE_STATIC_OctreeSceneManager
#  endif
#  include "OgreStaticPluginLoader.h"
#endif

//---------------------------------------------------------------------------

class BaseApplication : public Ogre::FrameListener, public Ogre::WindowEventListener, public OIS::KeyListener, public OIS::MouseListener
{
public:
    BaseApplication(void);
    virtual ~BaseApplication(void);

    virtual void go(void);

protected:
    virtual bool setup();
    virtual bool configure(void);
    virtual void chooseSceneManager(void);
    virtual void createCamera(void);
    virtual void createFrameListener(void);
    virtual void createScene(void) = 0; // Override me!
    virtual void destroyScene(void);
    virtual void createViewports(void);
    virtual void setupResources(void);
    virtual void createResourceListener(void);
    virtual void loadResources(void);
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

    virtual bool keyPressed(const OIS::KeyEvent &arg);
    virtual bool keyReleased(const OIS::KeyEvent &arg);
    virtual bool mouseMoved(const OIS::MouseEvent &arg);
    virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
    virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

    // Adjust mouse clipping area
    virtual void windowResized(Ogre::RenderWindow* rw);
    // Unattach OIS before window shutdown (very important under Linux)
    virtual void windowClosed(Ogre::RenderWindow* rw);
    Ogre::Root*                 mRoot;
    Ogre::Camera*               mCamera1;
    Ogre::Camera*               mCamera2;
    Ogre::SceneManager*         mSceneMgr;
    Ogre::RenderWindow*         mWindow;
    Ogre::Viewport*             mViewport;
    Ogre::String                mResourcesCfg;
    Ogre::String                mPluginsCfg;
    
    Ogre::Vector3               mDirection;
    Ogre::Radian                mRoll;
    Ogre::Radian                mPitch;

    Ogre::Radian                maxRoll;
    Ogre::Radian                maxPitch;

    Ogre::Radian                dRoll1;
    Ogre::Radian                dPitch1;
    Ogre::Radian                dRoll2;
    Ogre::Radian                dPitch2;


    Ogre::OverlaySystem*        mOverlaySystem;

    bool                        mCursorWasVisible;	// Was cursor visible before dialog appeared?
    bool                        mShutDown;
    bool                        mHit;
    bool                        mWaiting;
    int                         mHitMaxFrames;
    int                         mHitFrames;
    int                         mRoundNum;
    int                         mLivesNum;
    double                      mTimeToRound;
    CEGUI::Window*              roundTimerLabel;
    CEGUI::Window*              youMissedLabel;
    CEGUI::Window*              youScoredLabel;
    CEGUI::Window*              drawLabel;
    CEGUI::Window*              youWinLabel;
    CEGUI::Window*              youLoseLabel;
    CEGUI::Window*              multiScoreBox;
    CEGUI::Window*              waitingBox;
    CEGUI::Window*              ipLabel;




    //OIS Input devices
    OIS::InputManager*          mInputManager;
    OIS::Mouse*                 mMouse;
    OIS::Keyboard*              mKeyboard;

    // SDL Sound controller
    Sound*                      mSound;

    // Bullet Physics controller
    Physics*                    mPhysics;

    // Debug Drawer for Physics bounding boxes
    CDebugDraw*                 mDebugDraw;

    // Networking Manager
    NetManager*                 mNetMgr;

    // Added for Mac compatibility
    Ogre::String                m_ResourcePath;

    // Game components
    Room*                       room;
    ScoreWall*                  scoreWall;
    virtual void updateScoreLabel(void) = 0;
    virtual void updateScoreLabelOther(void) = 0;

    // GUI component
    GUI*                        gui;

    // Game State
    static const int            STOPPED = 0;
    static const int            RUNNING = 1;
    static const int            PAUSED = 2;
    static const int            ROUND_END = 3;

    int                         mGameState;
    virtual void gameOver(bool) = 0;
    virtual void roundOverMulti(int,bool) = 0;

    // Game Mode
    static const int            SINGLE = 0;
    static const int            MULTI = 1;
    static const int            IN_MENU = 2;

    int                         mGameMode;

    // Networking Role
    static const int            CLIENT = 0;
    static const int            SERVER = 1;

    int                         mNetRole;

    // Packet Types
    static const int            PACKET_UPDATE = 0;
    static const int            PACKET_ROUND = 1;
    static const int            PACKET_GAME = 2;

    // Score Types
    static const int            SCORE_SERVER = 0;
    static const int            SCORE_CLIENT = 1;
    static const int            SCORE_DRAW = 2;

    struct UpdatePacket {
        int packetType;
        int soundToPlay;
        int scoreType;
        Ogre::Vector3 ballPos;
        Ogre::Quaternion ballRot;
        Ogre::Vector3 paddlePos;
        Ogre::Quaternion paddleRot;
    };
    UpdatePacket                clientPacketBuffer;
    UpdatePacket                clientPacket;

    virtual void start(void) = 0;
    

#ifdef OGRE_STATIC_LIB
    Ogre::StaticPluginLoader m_StaticPluginLoader;
#endif
};

//---------------------------------------------------------------------------

#endif // #ifndef __BaseApplication_h_

//---------------------------------------------------------------------------
