ACLOCAL_AMFLAGS= -I m4
noinst_HEADERS= BaseApplication.h TutorialApplication.h Ball.h Wall.h Room.h Goal.h ScoreWall.h Paddle.h Sound.h Physics.h KinematicMotionState.h GUI.h NetManager.h

bin_PROGRAMS= OgreApp
CEGUI_OGRE_CFLAGS= -pthread -I/lusr/opt/cegui-0.8.7/include/cegui-0 -I/usr/include/OGRE
CEGUI_OGRE_LIBS= -L/lusr/opt/cegui-0.8.7/lib -lCEGUIOgreRenderer-0 -lOgreMain -lpthread -lCEGUIBase-0 
OgreApp_CPPFLAGS= -I$(top_srcdir)
OgreApp_SOURCES= BaseApplication.cpp TutorialApplication.cpp Ball.cpp Wall.cpp Room.cpp Goal.cpp ScoreWall.cpp Paddle.cpp Sound.cpp Physics.cpp GUI.cpp NetManager.cpp
OgreApp_CXXFLAGS= -I/usr/include/OGRE -pthread $(OIS_CFLAGS) $(bullet_CFLAGS) $(CEGUI_CFLAGS) $(CEGUI_OGRE_CFLAGS) -lSDL_net
OgreApp_LDADD= -L/usr/lib/x86_64-linux-gnu/OGRE-1.9.0 -lSDL -lSDL_mixer -lOgreMain -lpthread $(OIS_LIBS) $(bullet_LIBS) $(CEGUI_LIBS) $(CEGUI_OGRE_LIBS)
OgreApp_LDFLAGS= -lOgreOverlay -lboost_system

EXTRA_DIST= buildit makeit
AUTOMAKE_OPTIONS= foreign
