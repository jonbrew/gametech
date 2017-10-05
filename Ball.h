#include <Ogre.h>

class Ball { 
    protected:
        Ogre::SceneManager* sceneMgr;
        Ogre::SceneNode* rootNode; 
        Ogre::Real bRadius; 
        Ogre::Vector3 bDirection; 
        Ogre::Real bSpeed;
    public: 
        Ball(Ogre::SceneManager* scnMgr);
        void createBall(void);
        void move(const Ogre::FrameEvent& evt); 
        Ogre::SceneNode* getNode(void) { return rootNode; } 
};