/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.cpp
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

#include "TutorialApplication.h"

//---------------------------------------------------------------------------
TutorialApplication::TutorialApplication(void)
{
}
//---------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
}

//---------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{

	Ogre::Camera* newCamera = mSceneMgr->createCamera("NewCam");
	mWindow->getViewport(0)->setCamera(newCamera);
	newCamera->setPosition(Ogre::Vector3(0, 0, 0));
	newCamera->lookAt(Ogre::Vector3(0, 0, -1));
	newCamera->setNearClipDistance(0.1);
	Ogre::SceneNode* camNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	camNode->attachObject(newCamera);
	targetNode = camNode;

	// Set the scene's ambient light
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));

	// Create an Entity
	Ogre::Entity* ogreHead = mSceneMgr->createEntity("Head", "ogrehead.mesh");

	// Create a SceneNode and attach the Entity to it
	Ogre::SceneNode* headNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("HeadNode");
	headNode->attachObject(ogreHead);

	// Create a Light and set its position
	Ogre::Light* light = mSceneMgr->createLight("MainLight");
	light->setPosition(20.0f, 80.0f, 50.0f);

	mCamera->setPosition(Ogre::Vector3(0, 0, 8));
	headNode->scale(0.01, 0.01, 0.01);
	targetNode = headNode;
}

//-------------------------------------------------------------------------------------
bool TutorialApplication::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	bool ret = BaseApplication::frameRenderingQueued(evt);

	iotracker->mainloop();

	if (!processUnbufferedInput(evt)) return false;

	return ret;
}
//-------------------------------------------------------------------------------------
bool TutorialApplication::processUnbufferedInput(const Ogre::FrameEvent& evt)
{
	targetNode->setPosition(Ogre::Vector3(data.pos[0], data.pos[1], data.pos[2]));
	targetNode->setOrientation(data.quat[3], data.quat[0], data.quat[1], data.quat[2]);

	return true;
}
//-------------------------------------------------------------------------------------
void VRPN_CALLBACK TutorialApplication::handleIotracker(void* userData, const vrpn_TRACKERCB t)
{
	vrpn_TRACKERCB *pData = &(((TutorialApplication*)userData)->data);

	if (t.sensor == 3) {
		*pData = t;
		pData->pos[0] /= 1000.0; // mm to m
		pData->pos[1] /= 1000.0;
		pData->pos[2] /= 1000.0;
	}
}
//-------------------------------------------------------------------------------------

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        TutorialApplication app;

        try {
            app.go();
        } catch(Ogre::Exception& e)  {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occurred: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif

//---------------------------------------------------------------------------
