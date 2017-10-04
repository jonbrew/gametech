#include <Ogre.h>

class Goal { 
    protected: 
        Ogre::SceneNode* rootNode;
        bool isActive;

    public: 
        Goal(Ogre::SceneManager* scnMgr, Ogre::Vector3 pos); 
        void on();
        void off(); 
        Ogre::SceneNode* getNode() { return rootNode; } 
};