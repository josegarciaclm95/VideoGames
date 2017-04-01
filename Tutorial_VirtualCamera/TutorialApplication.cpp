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
	
	rightHandTracker = new vrpn_Tracker_Remote("Right_hand@161.67.196.44:3883");
	rightHandTracker->register_change_handler(this, handleRightHandTracker);
	vrpn_TRACKERCB blank1 = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
	right_data = blank1;
	
	
	leftHandTracker = new vrpn_Tracker_Remote("Left_hand@161.67.196.44:3883");
	leftHandTracker->register_change_handler(this, handleLeftHandTracker);
	vrpn_TRACKERCB blank2 = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
	left_data = blank2;

	/*
	cameraTracker = new vrpn_Tracker_Remote("iotracker@161.67.196.59:3883");
	cameraTracker->register_change_handler(this, handleCameraTracker);
	vrpn_TRACKERCB blank3 = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
	camera_data = blank3;
	*/
	// Set the scene's ambient light
	mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0f, 1.0f, 1.0f));
	//mCamera->setPosition(0, 47, 222);

	/*
	// Create an Entity
	Ogre::Entity* ogreHead = mSceneMgr->createEntity("Head", "ogrehead.mesh");
	// Create a SceneNode and attach the Entity to it
	Ogre::SceneNode* headNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("HeadNode");
	headNode->attachObject(ogreHead);
	*/
	//Left Hand
	Ogre::Entity* leftHandEntity = mSceneMgr->createEntity("hand.mesh");
	Ogre::SceneNode* leftHand = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	leftHand->pitch(Ogre::Degree(180));
	leftHand->yaw(Ogre::Degree(90));
	leftHand->setPosition(Ogre::Vector3(40.0f, 0.0f, 0.0f));
	leftHand->scale(Ogre::Vector3(2.0f, 2.0f, 2.0f));
	leftHand->attachObject(leftHandEntity);

	//Right Hand
	Ogre::Entity* rightHandEntity = mSceneMgr->createEntity("hand.mesh");
	Ogre::SceneNode* rightHand = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	rightHand->pitch(Ogre::Degree(180));
	rightHand->yaw(Ogre::Degree(90));
	//rightHand->pitch(Ogre::Degree(90));
	rightHand->setPosition(Ogre::Vector3(-40.0f, 0.0f, 0.0f));
	//rightHand->pitch(Ogre::Degree(-45));
	rightHand->scale(Ogre::Vector3(2.0f, 2.0f, 2.0f));
	rightHand->attachObject(rightHandEntity);

	OutputDebugString("Hello World");

	Ogre::Entity* ogreEntity3 = mSceneMgr->createEntity("ogrehead.mesh");
	Ogre::SceneNode* ogreNode3 = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	ogreNode3->setPosition(0, -104, 120);
	//ogreNode3->pitch(Ogre::Degree(-45));
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
	Ogre::Camera* newCamera= mSceneMgr->createCamera("NewCam");
	mWindow->getViewport(0)->setCamera(newCamera);
	newCamera->setPosition(Ogre::Vector3(0,0,0));
	newCamera->lookAt(Ogre::Vector3(0,0,-1));
	newCamera->setNearClipDistance(0.1);
	Ogre::SceneNode* hmdNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Ogre::SceneNode* eyeNode = hmdNode->createChildSceneNode();
	eyeNode->translate(0.0, -0.1, 0.05);
	eyeNode->attachObject(newCamera);
	cameraTargetNode = hmdNode;
	*/
	leftTargetNode =  leftHand;
	rightTargetNode = rightHand;
}

//-------------------------------------------------------------------------------------

bool TutorialApplication::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	bool ret = BaseApplication::frameRenderingQueued(evt);

	rightHandTracker->mainloop();
	leftHandTracker->mainloop();
	//cameraTracker->mainloop();
	if(!processUnbufferedInput(evt)) return false;

	return ret;
}
//-------------------------------------------------------------------------------------
bool TutorialApplication::processUnbufferedInput(const Ogre::FrameEvent& evt)
{
	char buffer[256];
	//sprintf(buffer, "Right data %f %f %f\n", right_data.pos[0], right_data.pos[1], right_data.pos[2]);
	//OutputDebugString(buffer);
	char buffer1[256];
	//sprintf(buffer1, "Camera data %f %f %f\n", camera_data.pos[0], camera_data.pos[1], camera_data.pos[2]);
	//OutputDebugString(buffer1);

	//rightTargetNode->setPosition(Ogre::Vector3(right_data.pos[0] * 75, right_data.pos[1] * 75, right_data.pos[2] * 75));
	//rightTargetNode->setOrientation(right_data.quat[3], right_data.quat[0], right_data.quat[1], right_data.quat[2]);
	//leftTargetNode->setPosition(Ogre::Vector3(left_data.pos[0] * 75, left_data.pos[1] * 75, left_data.pos[2] * 75));
	//leftTargetNode->setOrientation(left_data.quat[3], left_data.quat[0], left_data.quat[1], left_data.quat[2]);
	//cameraTargetNode->setPosition(Ogre::Vector3(camera_data.pos[0] * 75, camera_data.pos[1] * 75, camera_data.pos[2] * 75));
	//cameraTargetNode->setOrientation(camera_data.quat[3], camera_data.quat[0], camera_data.quat[1], camera_data.quat[2]);
	return true;
}
//-------------------------------------------------------------------------------------
void VRPN_CALLBACK TutorialApplication::handleRightHandTracker(void* userData, const vrpn_TRACKERCB t)
{
	vrpn_TRACKERCB *pData = &(((TutorialApplication*)userData)->right_data);
	*pData = t;
}
//-------------------------------------------------------------------------------------

void VRPN_CALLBACK TutorialApplication::handleLeftHandTracker(void* userData, const vrpn_TRACKERCB t)
{
	vrpn_TRACKERCB *pData = &(((TutorialApplication*)userData)->left_data);
	*pData = t;
}
//-------------------------------------------------------------------------------------
/*
void VRPN_CALLBACK TutorialApplication::handleCameraTracker(void* userData, const vrpn_TRACKERCB t)
{
	vrpn_TRACKERCB *pData = &(((TutorialApplication*)userData)->camera_data);
	if (t.sensor == 4) {
		*pData = t;
		pData->pos[0] /= 1000.0; // mm to m
		pData->pos[1] /= 1000.0;
		pData->pos[2] /= 1000.0;
	}
}
*/
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
