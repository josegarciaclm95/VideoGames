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
      Tutorial Framework
      http://www.ogre3d.org/tikiwiki/
-----------------------------------------------------------------------------
*/
#ifndef __TutorialApplication_h_
#define __TutorialApplication_h_

#include "BaseApplication.h"
#include "vrpn_Button.h"

class TutorialApplication : public BaseApplication
{
public:
    TutorialApplication(void);
    virtual ~TutorialApplication(void);

protected:
    virtual void createScene(void);
	// Ogre::FrameListener
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	// VRPN
	static void VRPN_CALLBACK handleButton(void* userData, const vrpn_BUTTONCB b);
	vrpn_Button_Remote* vrpnButton;
};

#endif // #ifndef __TutorialApplication_h_
