#ifndef __Goal_h_
#define __Goal_h_

#include <Ogre.h>


class Goal { 
protected: 
    Ogre::SceneNode* goalNode;
    Ogre::Entity* goalEntity;
    bool isActive;

public: 
    Goal(Ogre::SceneManager* scnMgr, double, Ogre::Vector3 pos); 
    void on();
    void off(); 
    Ogre::SceneNode* getNode() { return goalNode; } 
};

#endif
