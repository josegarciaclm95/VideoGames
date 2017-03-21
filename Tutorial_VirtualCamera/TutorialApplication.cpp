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
#include <iostream>

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
	/*
	iotracker = new vrpn_Tracker_Remote("iotracker@161.67.196.59:3883");
	iotracker->register_change_handler(this, handleIotracker);
	vrpn_TRACKERCB blank = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
	data = blank;
	*/
	// Set the scene's ambient light
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));
	mCamera->setPosition(0, 47, 222);

	// Create an Entity
	Ogre::Entity* ogreHead = mSceneMgr->createEntity("Head", "ogrehead.mesh");
	// Create a SceneNode and attach the Entity to it
	Ogre::SceneNode* headNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("HeadNode");
	headNode->attachObject(ogreHead);

	//Left Hand
	Ogre::Entity* leftHandEntity = mSceneMgr->createEntity("hand.mesh");
	Ogre::SceneNode* leftHand = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	leftHand->setPosition(20, 104, 0);
	leftHand->attachObject(leftHandEntity);

	//Right Hand
	Ogre::Entity* rightHandEntity = mSceneMgr->createEntity("hand.mesh");
	Ogre::SceneNode* rightHand = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	rightHand->yaw(Ogre::Degree(180));
	rightHand->setPosition(0, 104, -5);
	rightHand->attachObject(rightHandEntity);

	OutputDebugString("Hello World");

	Ogre::Entity* ogreEntity3 = mSceneMgr->createEntity("ogrehead.mesh");
	Ogre::SceneNode* ogreNode3 = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	ogreNode3->setPosition(0, -104, 120);
	ogreNode3->pitch(Ogre::Degree(-45));
	ogreNode3->attachObject(ogreEntity3);
	
	Ogre::Entity* ogreEntity4 = mSceneMgr->createEntity("ogrehead.mesh");
	Ogre::SceneNode* ogreNode4 = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	ogreNode4->setPosition(0, 0, 600);
	ogreNode4->scale(2, 2, 2);
	ogreNode4->yaw(Ogre::Degree(180));
	ogreNode4->attachObject(ogreEntity4);
	/*
	Ogre::Entity* ogreEntity2 = mSceneMgr->createEntity("ogrehead.mesh");
	Ogre::SceneNode* ogreNode2 = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	ogreNode2->setPosition(0, 104, 0);
	ogreNode2->attachObject(ogreEntity2);
	*/
	// Create a Light and set its position
	Ogre::Light* light = mSceneMgr->createLight("MainLight");
	light->setPosition(20.0f, 80.0f, 50.0f);

	//mCamera->setPosition(Ogre::Vector3(0, 0, 8));
	//headNode->scale(0.01, 0.01, 0.01);
	/*
	Ogre::Camera* newCamera = mSceneMgr->createCamera("NewCam");
	mWindow->getViewport(0)->setCamera(newCamera);
	newCamera->setPosition(Ogre::Vector3(0, 0, 0));
	newCamera->lookAt(Ogre::Vector3(0, 0, -1));
	newCamera->setNearClipDistance(0.1);
	Ogre::SceneNode* hmdNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Ogre::SceneNode* eyeNode = hmdNode->createChildSceneNode();
	eyeNode->translate(0.0, -0.1, 0.05);
	eyeNode->attachObject(newCamera);
	targetNode = hmdNode;
	*/
	//targetNode = headNode;
}

//-------------------------------------------------------------------------------------
/*
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
*/
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
