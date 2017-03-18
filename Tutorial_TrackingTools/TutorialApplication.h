/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.h
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

#ifndef __TutorialApplication_h_
#define __TutorialApplication_h_

#include "BaseApplication.h"
#include "vrpn_Tracker.h"

//---------------------------------------------------------------------------

class TutorialApplication : public BaseApplication
{
public:
	TutorialApplication(void);
	virtual ~TutorialApplication(void);

protected:
	virtual void createScene(void);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

private:
	bool processUnbufferedInput(const Ogre::FrameEvent& evt);
	static void VRPN_CALLBACK handleRightHandTracker(void* userData, const vrpn_TRACKERCB t);

	vrpn_Tracker_Remote* rightHandTracker;
	vrpn_TRACKERCB data;
	Ogre::SceneNode* targetNode;
};

//---------------------------------------------------------------------------

#endif // #ifndef __TutorialApplication_h_

//---------------------------------------------------------------------------
