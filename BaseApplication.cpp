/*
-----------------------------------------------------------------------------
Filename:    BaseApplication.cpp
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

#include "BaseApplication.h"

#include <OgreTextureManager.h>

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
#include <macUtils.h>
#endif

// Static Functions
CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID)
{
    switch (buttonID)
    {
    case OIS::MB_Left:
        return CEGUI::LeftButton;
 
    case OIS::MB_Right:
        return CEGUI::RightButton;
 
    case OIS::MB_Middle:
        return CEGUI::MiddleButton;
 
    default:
        return CEGUI::LeftButton;
    }
}

//---------------------------------------------------------------------------
BaseApplication::BaseApplication(void)
    : mRoot(0),
    mCamera1(0),
    mCamera2(0),
    mSceneMgr(0),
    mWindow(0),
    mResourcesCfg(Ogre::StringUtil::BLANK),
    mPluginsCfg(Ogre::StringUtil::BLANK),
    mCursorWasVisible(false),
    mShutDown(false),
    maxRoll(.35),
    maxPitch(.35),
    dPitch1(0),
    dRoll1(0),
    dPitch2(0),
    dRoll2(0),
    mHit(false),
    mHitMaxFrames(500),
    mHitFrames(0),
    mRoundNum(0),
    mInputManager(0),
    mMouse(0),
    mKeyboard(0),
    mOverlaySystem(0),
    mDirection(Ogre::Vector3(0,0,0)),
    mGameState(BaseApplication::STOPPED),
    mGameMode(BaseApplication::IN_MENU),
    mNetRole(-1),
    mTimeToRound(3),
    mWaiting(false)

{
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
    m_ResourcePath = Ogre::macBundlePath() + "/Contents/Resources/";
#else
    m_ResourcePath = "";
#endif
}
//---------------------------------------------------------------------------
BaseApplication::~BaseApplication(void)
{
  if (mOverlaySystem) delete mOverlaySystem;

  // Remove ourself as a Window listener
  Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
  windowClosed(mWindow);
  delete mRoot;
}

//---------------------------------------------------------------------------
bool BaseApplication::configure(void)
{
    // Show the configuration dialog and initialise the system.
    // You can skip this and use root.restoreConfig() to load configuration
    // settings if you were sure there are valid ones saved in ogre.cfg.
    if(mRoot->showConfigDialog())
    {
        // If returned true, user clicked OK so initialise.
        // Here we choose to let the system create a default rendering window by passing 'true'.
        mWindow = mRoot->initialise(true, "TutorialApplication Render Window");

        return true;
    }
    else
    {
        return false;
    }
}
//---------------------------------------------------------------------------
void BaseApplication::chooseSceneManager(void)
{
    // Get the SceneManager, in this case a generic one
    mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);

    // Initialize the OverlaySystem (changed for Ogre 1.9)
    mOverlaySystem = new Ogre::OverlaySystem();
    mSceneMgr->addRenderQueueListener(mOverlaySystem);
}
//---------------------------------------------------------------------------
void BaseApplication::createCamera(void)
{
    // Create the camera1
    mCamera1 = mSceneMgr->createCamera("PlayerCam1");

    mCamera1->setPosition(Ogre::Vector3(0,0,-100));
    mCamera1->lookAt(Ogre::Vector3(0,0,0));
    mCamera1->setNearClipDistance(5);
    mCamera1->setFOVy(Ogre::Radian(Ogre::Degree(90)));

    // Create the camera2
    mCamera2 = mSceneMgr->createCamera("PlayerCam2");

    mCamera2->setPosition(Ogre::Vector3(0,0,100));
    mCamera2->lookAt(Ogre::Vector3(0,0,0));
    mCamera2->setNearClipDistance(5);
    mCamera2->setFOVy(Ogre::Radian(Ogre::Degree(90)));
}
//---------------------------------------------------------------------------
void BaseApplication::createFrameListener(void)
{
    Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
    OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;

    mWindow->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

    mInputManager = OIS::InputManager::createInputSystem(pl);

    mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, true));
    mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject(OIS::OISMouse, true));

    mMouse->setEventCallback(this);
    mKeyboard->setEventCallback(this);

    // Set initial mouse clipping size
    windowResized(mWindow);

    // Register as a Window listener
    Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

    mRoot->addFrameListener(this);
}
//---------------------------------------------------------------------------
void BaseApplication::destroyScene(void)
{
}
//---------------------------------------------------------------------------
void BaseApplication::createViewports(void)
{
    // Create one viewport, entire window
    mViewport = mWindow->addViewport(mCamera1);
    mViewport->setBackgroundColour(Ogre::ColourValue(0,0,0));

    // Alter the cameras aspect ratio to match the viewport
    mCamera1->setAspectRatio(Ogre::Real(mViewport->getActualWidth()) / Ogre::Real(mViewport->getActualHeight()));
    mCamera2->setAspectRatio(Ogre::Real(mViewport->getActualWidth()) / Ogre::Real(mViewport->getActualHeight()));

}
//---------------------------------------------------------------------------
void BaseApplication::setupResources(void)
{
    // Load resource paths from config file
    Ogre::ConfigFile cf;
    cf.load(mResourcesCfg);

    // Go through all sections & settings in the file
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

    Ogre::String secName, typeName, archName;
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
            // OS X does not set the working directory relative to the app.
            // In order to make things portable on OS X we need to provide
            // the loading with it's own bundle path location.
            if (!Ogre::StringUtil::startsWith(archName, "/", false)) // only adjust relative directories
                archName = Ogre::String(Ogre::macBundlePath() + "/" + archName);
#endif

            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                archName, typeName, secName);
        }
    }
}
//---------------------------------------------------------------------------
void BaseApplication::createResourceListener(void)
{
}
//---------------------------------------------------------------------------
void BaseApplication::loadResources(void)
{
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}
//---------------------------------------------------------------------------
void BaseApplication::go(void)
{
#ifdef _DEBUG
#ifndef OGRE_STATIC_LIB
    mResourcesCfg = m_ResourcePath + "resources_d.cfg";
    mPluginsCfg = m_ResourcePath + "plugins_d.cfg";
#else
    mResourcesCfg = "resources_d.cfg";
    mPluginsCfg = "plugins_d.cfg";
#endif
#else
#ifndef OGRE_STATIC_LIB
    mResourcesCfg = m_ResourcePath + "resources.cfg";
    mPluginsCfg = m_ResourcePath + "plugins.cfg";
#else
    mResourcesCfg = "resources.cfg";
    mPluginsCfg = "plugins.cfg";
#endif
#endif

    if (!setup())
        return;

    mRoot->startRendering();

    // Clean up
    destroyScene();
}
//---------------------------------------------------------------------------
bool BaseApplication::setup(void)
{
    mRoot = new Ogre::Root(mPluginsCfg);

    setupResources();

    bool carryOn = configure();
    if (!carryOn) return false;

    chooseSceneManager();
    createCamera();
    createViewports();

    // Set default mipmap level (NB some APIs ignore this)
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

    // Create any resource listeners (for loading screens)
    createResourceListener();
    // Load resources
    loadResources();

    // Init SDL Audio
    mSound = new Sound;

    // Init Bullet Physics
    mPhysics = new Physics(mSound);
    mDebugDraw = new CDebugDraw(mSceneMgr,mPhysics->getDynamicsWorld());

    // Init NetManager
    //initNetwork();
    mNetMgr = new NetManager();

    // Create the scene
    createScene();

    createFrameListener();
    
    return true;
};
//---------------------------------------------------------------------------
bool BaseApplication::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    if(mWindow->isClosed())
        return false;

    if(mShutDown)
        return false;

    // Need to capture/update each device
    mKeyboard->capture();
    mMouse->capture();

    // Inject timestamp to CEGUI system
    CEGUI::System::getSingleton().injectTimePulse(evt.timeSinceLastFrame);

    bool stopped = mGameState == BaseApplication::STOPPED || mGameState == BaseApplication::PAUSED;

    // Wait for client connection
    if(mWaiting) {
        if(mNetMgr->scanForActivity()) {
            mWaiting = false;
            // Show Score Box
            multiScoreBox->show();
            // Set game mode
            mGameMode = BaseApplication::MULTI;
            // Start game
            start();
        }
    }
    // Round start timer
    if(mTimeToRound > 0 && mGameMode == BaseApplication::MULTI) {
        mTimeToRound -= evt.timeSinceLastFrame;
        std::ostringstream strs;
        strs << std::fixed << std::setprecision(1) << mTimeToRound;
        std::string str = strs.str();
        roundTimerLabel->setText("Round starts in " + str);
    }
    if(mTimeToRound <= 0 && stopped && mGameMode == BaseApplication::MULTI) {
        mGameState = BaseApplication::RUNNING;
        roundTimerLabel->hide();
        youMissedLabel->hide();
        youScoredLabel->hide();
        drawLabel->hide();
    }
    
    if(stopped)
        return true;    

    bool isClient = mNetRole == BaseApplication::CLIENT;

    // Set what to update based on client vs server
    Ogre::Node* ballNode = mSceneMgr->getRootSceneNode()->getChild("Ball");
    Ogre::Node* paddleNode = room->getPaddle1()->getNode();
    Ogre::Camera* playerCam = mCamera1;
    if(isClient) {
        paddleNode = room->getPaddle2()->getNode();
        playerCam = mCamera2;
    }
    
    // Update paddle position
    Ogre::Vector3 paddlePosition = paddleNode->getPosition();
    Ogre::Vector3 newDirection = mDirection;
    if(isClient)
        newDirection.x *= -1;
    if((paddlePosition.x <= -70 && newDirection.x < 0) || (paddlePosition.x >= 70 && newDirection.x > 0))
       newDirection.x = 0;
    if((paddlePosition.y <= -85 && newDirection.y < 0) || (paddlePosition.y >= 85 && newDirection.y > 0))
       newDirection.y = 0;
   
/* //old pitch limiter 
    Ogre::Radian newPitch = mPitch;
    Ogre::Real curPitch = paddleNode->getOrientation().getPitch().valueDegrees();
    if(isClient)
        curPitch -= 180;
    if((curPitch <= -115 && newPitch == Ogre::Radian(Ogre::Degree(-.05))) || //up
        (curPitch >= -65 && newPitch == Ogre::Radian(Ogre::Degree(.05))))     //down
        newPitch = 0;

*/
    Ogre::Radian newPitch = mPitch;
    Ogre::Radian newRoll = mRoll;
    if(isClient){
        if((dRoll2 <= -maxRoll && newRoll == Ogre::Radian(Ogre::Degree(-.05))) || //right
                (dRoll2 >= maxRoll && newRoll == Ogre::Radian(Ogre::Degree(.05))))     //left
            newRoll = 0;

        if((dPitch2 <= -maxPitch && newPitch == Ogre::Radian(Ogre::Degree(-.05))) || //right
                (dPitch2 >= maxPitch && newPitch == Ogre::Radian(Ogre::Degree(.05))))     //left
            newPitch = 0;
    }
    else{
        if((dRoll1 <= -maxRoll && newRoll == Ogre::Radian(Ogre::Degree(-.05))) || //right
                (dRoll1 >= maxRoll && newRoll == Ogre::Radian(Ogre::Degree(.05))))     //left
            newRoll = 0;

        if((dPitch1 <= -maxPitch && newPitch == Ogre::Radian(Ogre::Degree(-.05))) || //right
                (dPitch1 >= maxPitch && newPitch == Ogre::Radian(Ogre::Degree(.05))))     //left
            newPitch = 0;
    }

    if(mHit){
        int translate = 50;
        if(isClient)
            translate *= -1;
        if(mHitFrames > mHitMaxFrames/2)
            paddleNode->translate(0, 0, translate * evt.timeSinceLastFrame);
        else 
            paddleNode->translate(0, 0, -translate * evt.timeSinceLastFrame);
        mHitFrames--;
        if(mHitFrames==0)
            mHit = false;
    }
   
    if(isClient){
        dRoll2 += newRoll;
        dPitch2 += newPitch;
    }
    else{
        dRoll1 += newRoll;
        dPitch1 += newPitch;
    }

    paddleNode->translate(newDirection);
    paddleNode->roll(newRoll);
    paddleNode->pitch(newPitch);
   
    playerCam->move(newDirection);
    
    mDirection.x = 0;
    mDirection.y = 0;

    if(mGameMode == BaseApplication::SINGLE) { // Single player updates
        // Update kinematic paddle position in physics sim
        room->getPaddle1()->updateMotionState();
    
        // Update ball through physics sim step
        bool scored = mPhysics->stepSimulation(evt.timeSinceLastFrame);
    
        // Show Physics bounding boxes
        //mDebugDraw->Update();

        btRigidBody* ballRigidBody = room->getBall()->getRigidBody();
        btVector3 ballVelocity = ballRigidBody->getLinearVelocity();
        if(scored) {
            scoreWall->increaseScore();
            updateScoreLabel();
            scoreWall->pickGoal();
            ballRigidBody->applyCentralImpulse(ballVelocity*0.1);
        }
    
        Ogre::Vector3 ballPosition = ballNode->getPosition();
        bool ballStopped = abs(ballVelocity.z()) < 5 && abs(ballVelocity.y()) < 5 && abs(ballVelocity.z() < 5);
        if(ballPosition.z <= -80 || ballStopped) {
            mGameState = BaseApplication::STOPPED;
            gameOver(ballStopped);
        }
    } else { // Multiplayer updates
        if(isClient) { // Client updates
            // TODO rcv packet
            /* shitty pseudo code
            if(packettype == update)
                mSound->play(packet.soundToPlay)
                ballNode->translate(packet.ballx,packet.bally,packet.ballz)
                ballNode->rotate(packet.ballrotw,packet.ballrotx,packet.ballroty,packet.ballrotz)
                Ogre::SceneNode* paddle1node = room->getPaddle1()->getNode();
                paddle1Node->translate(packet.paddlex,packet.paddley,packet.paddlez)
                paddle1Node->rotate(packet.paddlerotw,packet.paddlerotx,packet.paddleroty,packet.paddlerotz)
            else if(packettype == roundover)
                if(server score increase) {
                    youMissedLabel->show();
                    scoreWall->increaseScoreOther();
                    updateScoreLabelOther();
                } else if(client score increase) {
                    youScoredLabel->show();
                    scoreWall->increaseScore();
                    updateScoreLabel();
                    mSound->play(Sound::SOUND_SCORE);
                } else if(no score increase) {
                    drawLabel->show();
                }
                restartRound()
            else if(packettype == gameover)
                if(client win) {
                    youWinLabel->show();
                    scoreWall->increaseScore();
                    updateScoreLabel();
                    mSound->play(Sound::SOUND_SCORE);          
                } else if(server win) {
                    youLoseLabel->show();
                    scoreWall->increaseScoreOther();
                    updateScoreLabelOther();
                }
                endGame()
            */

            // TODO send paddle pos update to server


        } else { // Server updates
            // Update kinematic paddle position in physics sim
            room->getPaddle1()->updateMotionState();
        
            // Update ball through physics sim step
            bool scored = mPhysics->stepSimulation(evt.timeSinceLastFrame);
        
            // Show Physics bounding boxes
            //mDebugDraw->Update();

            if(mNetMgr->scanForActivity()) {
                std::cout << "DATA: " << mNetMgr->tcpClientData[0]->output << "\n";
            }
            btRigidBody* ballRigidBody = room->getBall()->getRigidBody();
            btVector3 ballVelocity = ballRigidBody->getLinearVelocity();

            Ogre::Vector3 ballPosition = ballNode->getPosition();
            bool ballStopped = abs(ballVelocity.z()) < 5 && abs(ballVelocity.y()) < 5 && abs(ballVelocity.z() < 5);
            if(ballPosition.z <= -80 || ballStopped || ballPosition.z >= 80) {
                mGameState = BaseApplication::STOPPED;
                roundOverMulti(ballPosition.z, ballStopped);
            }

            // Build update packet and send to client
            UpdatePacket packet;
            packet.packetType = BaseApplication::PACKET_UPDATE;
            packet.soundToPlay = mSound->soundToPlay;
            packet.ballPos = ballPosition;
            packet.ballRot = ballNode->getOrientation();
            packet.paddlePos = paddleNode->getPosition();
            packet.paddleRot = paddleNode->getOrientation();
            char toSend[sizeof(packet)];
            std::memcpy(&toSend[0],&packet,sizeof(packet));
            mNetMgr->messageClient(PROTOCOL_TCP,0,toSend,sizeof(packet));

            // TODO rcv client packet and update paddle2 pos

            // Reset sound to play
            mSound->soundToPlay = Sound::SOUND_NONE;
        }
    }

    return true;
}
//---------------------------------------------------------------------------
bool BaseApplication::keyPressed( const OIS::KeyEvent &arg )
{
  if (arg.key == OIS::KC_ESCAPE) {
    mShutDown = true;
  }

  return true;
}
//---------------------------------------------------------------------------
bool BaseApplication::keyReleased(const OIS::KeyEvent &arg)
{
    return true;
}
//---------------------------------------------------------------------------
bool BaseApplication::mouseMoved(const OIS::MouseEvent &arg)
{
    CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(arg.state.X.rel, arg.state.Y.rel);
    return true;
}
//---------------------------------------------------------------------------
bool BaseApplication::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
    CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(convertButton(id));
    return true;
}
//---------------------------------------------------------------------------
bool BaseApplication::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
    CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(convertButton(id));
    return true;
}
//---------------------------------------------------------------------------
// Adjust mouse clipping area
void BaseApplication::windowResized(Ogre::RenderWindow* rw)
{
    unsigned int width, height, depth;
    int left, top;
    rw->getMetrics(width, height, depth, left, top);

    const OIS::MouseState &ms = mMouse->getMouseState();
    ms.width = width;
    ms.height = height;
}
//---------------------------------------------------------------------------
// Unattach OIS before window shutdown (very important under Linux)
void BaseApplication::windowClosed(Ogre::RenderWindow* rw)
{
    // Only close for window that created OIS (the main window in these demos)
    if(rw == mWindow)
    {
        if(mInputManager)
        {
            mInputManager->destroyInputObject(mMouse);
            mInputManager->destroyInputObject(mKeyboard);

            OIS::InputManager::destroyInputSystem(mInputManager);
            mInputManager = 0;
        }
    }
}
//---------------------------------------------------------------------------
