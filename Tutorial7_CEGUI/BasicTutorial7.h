#include "BaseApplication.h"
 
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h> //from 0.8 it's just Ogre/Renderer.h
 
class BasicTutorial7 : public BaseApplication
{
public:
    BasicTutorial7(void);
    virtual ~BasicTutorial7(void);
 
protected:
    CEGUI::OgreRenderer* mRenderer;
    virtual void createScene(void); 
    virtual void createFrameListener(void);
    // Ogre::FrameListener
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
 
    // OIS::KeyListener
    virtual bool keyPressed( const OIS::KeyEvent &arg );
    virtual bool keyReleased( const OIS::KeyEvent &arg );
    // OIS::MouseListener
    virtual bool mouseMoved( const OIS::MouseEvent &arg );
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
 
	bool createGame(const CEGUI::EventArgs &e);
	bool showCredits(const CEGUI::EventArgs &e);
    bool quit(const CEGUI::EventArgs &e);
};