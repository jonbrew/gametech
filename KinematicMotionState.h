#ifndef __KinematicMotionState_h_
#define __KinematicMotionState_h_

#include <Ogre.h>
#include "Physics.h"

class KinematicMotionState : public btMotionState {

protected:
    btTransform mPos;
    Ogre::SceneNode* rootNode;

public:
    KinematicMotionState(const btTransform &initialpos, Ogre::SceneNode* node) { 
        mPos = initialpos;
        rootNode = node;
    }
    void setNode(Ogre::SceneNode *node) { rootNode = node; }
    virtual void getWorldTransform(btTransform &worldTrans) const { worldTrans = mPos; }
    void setKinematicPos() {
        Ogre::Quaternion orientation = rootNode->getOrientation();
        Ogre::Vector3 pos = rootNode->getPosition(); 
        mPos = btTransform(btQuaternion(orientation.x, orientation.y, orientation.z, orientation.w),
                           btVector3(pos.x, pos.y, pos.z));
    }
    virtual void setWorldTransform(const btTransform &worldTrans) { mPos = worldTrans; }
};

#endif
