#include <Ogre.h>

class Paddle {
protected:
	Ogre::SceneNode* rootNode;

public:
	Paddle(Ogre::SceneManger* scnMgr);
	~Paddle();
	void move(const Ogre::FrameEvent& evt);
}