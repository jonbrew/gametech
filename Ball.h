#include <Ogre.h>

class Ball { 
    protected: 
        Ogre::SceneNode* rootNode; 
        Ogre::Real bRadius; 
        Ogre::Vector3 bDirection; 
        Ogre::Real bSpeed; 
    public: 
        Ball(Ogre::SceneManager* scnMgr); 
        ~Ball(); 
        void move(const Ogre::FrameEvent& evt); 
        Ogre::SceneNode* getNode() { return rootNode; } 
};