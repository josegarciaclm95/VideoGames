#include "BasicTutorial7.h"
 
CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID);
CEGUI::Window* quitB;
CEGUI::Window* credits;
CEGUI::Window* madnessText;

//-------------------------------------------------------------------------------------
BasicTutorial7::BasicTutorial7(void)
{
}
//-------------------------------------------------------------------------------------
BasicTutorial7::~BasicTutorial7(void)
{
}
//-------------------------------------------------------------------------------------
void BasicTutorial7::createScene(void)
{
	mRenderer = &CEGUI::OgreRenderer::bootstrapSystem();
	CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
	CEGUI::Font::setDefaultResourceGroup("Fonts");
	CEGUI::Scheme::setDefaultResourceGroup("Schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
	CEGUI::WindowManager::setDefaultResourceGroup("Layouts");

	CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");
	CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
	CEGUI::Window *sheet = wmgr.createWindow("DefaultWindow", "CEGUIDemo/Sheet");
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(sheet);

	quitB = wmgr.createWindow("TaharezLook/Button", "CEGUIDemo/QuitButton");
	quitB->setText("Start game");
	quitB->setSize(CEGUI::USize(CEGUI::UDim(0.2f, 0.0f), CEGUI::UDim(0.067f, 0.0f)));
	quitB->setPosition(CEGUI::UVector2(CEGUI::UDim(0.38f, 0.0f), CEGUI::UDim(0.65f, 0.0f)));

	credits = wmgr.createWindow("TaharezLook/Button", "CEGUIDemo/CreditsButton");
	credits->setText("Credits");
	credits->setSize(CEGUI::USize(CEGUI::UDim(0.2f, 0.0f), CEGUI::UDim(0.067f, 0.0f)));
	credits->setPosition(CEGUI::UVector2(CEGUI::UDim(0.38, 0.0f), CEGUI::UDim(0.75f, 0.0f)));

	madnessText = wmgr.createWindow("TaharezLook/Button", "CEGUIDemo/Sheet/MadnessText");
	madnessText->setText("MADNESS ESCAPE[colour='FFFF0000']");
	madnessText->setSize(CEGUI::USize(CEGUI::UDim(0.35f, 0.0f), CEGUI::UDim(0.35f, 0.0f)));
	madnessText->setPosition(CEGUI::UVector2(CEGUI::UDim(0.30f, 0.0f), CEGUI::UDim(0.20f, 0.0f)));

	sheet->addChild(quitB);
	sheet->addChild(credits);
	sheet->addChild(madnessText);
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(sheet);
	quitB->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&BasicTutorial7::createGame, this));
	//quit->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&BasicTutorial7::quit, this));
	credits->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&BasicTutorial7::showCredits, this));
	/*
	mSceneMgr->setAmbientLight(Ogre::ColourValue(1, 1, 1));
	mSceneMgr->setSkyDome(true, "Examples/CloudySky", 5, 8);
	Ogre::Entity* ogreHead = mSceneMgr->createEntity("Head", "ogrehead.mesh");
	Ogre::SceneNode* headNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, 0, -300));
	headNode->attachObject(ogreHead);

	Ogre::TexturePtr tex = mRoot->getTextureManager()->createManual(
		"RTT",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Ogre::TEX_TYPE_2D,
		512,
		512,
		0,
		Ogre::PF_R8G8B8,
		Ogre::TU_RENDERTARGET);
	Ogre::RenderTexture *rtex = tex->getBuffer()->getRenderTarget();
	
	//Ogre::Camera *cam = mSceneMgr->createCamera("RTTCam");
	//cam->setPosition(100, -100, -400);
	//cam->lookAt(0, 0, -300);
	//Ogre::Viewport *v = rtex->addViewport(cam);
	//v->setOverlaysEnabled(false);
	//v->setClearEveryFrame(true);
	//v->setBackgroundColour(Ogre::ColourValue::Black);
	CEGUI::Texture &guiTex = mRenderer->createTexture("textname", tex);

	const CEGUI::Rectf rect(CEGUI::Vector2f(0.0f, 0.0f), guiTex.getOriginalDataSize());
	CEGUI::BasicImage* image = (CEGUI::BasicImage*)(&CEGUI::ImageManager::getSingleton().create("BasicImage", "RTTImage"));
	image->setTexture(&guiTex);
	image->setArea(rect);
	image->setAutoScaled(CEGUI::ASM_Both);

	CEGUI::Window *si = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/StaticImage", "RTTWindow");
	//si->setSize(CEGUI::UVector2(CEGUI::UDim(0.5f, 0),
	si->setSize(CEGUI::USize(CEGUI::UDim(0.5f, 0),
		CEGUI::UDim(0.4f, 0)));
	si->setPosition(CEGUI::UVector2(CEGUI::UDim(0.5f, 0),
		CEGUI::UDim(0.0f, 0)));
	si->setProperty("Image", "RTTImage");
	sheet->addChild(si);*/
}
//-------------------------------------------------------------------------------------
bool BasicTutorial7::createGame(const CEGUI::EventArgs &e)
{
	quitB->destroy();
	credits->destroy();
	madnessText->destroy();

	mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0f, 1.0f, 1.0f));
	mCamera->setPosition(0, 47, 222);
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
	Ogre::Light* light = mSceneMgr->createLight("MainLight");
	light->setPosition(20.0f, 80.0f, 50.0f);
	return true;
}
//--------------------------------------------------------------------------------------
bool BasicTutorial7::showCredits(const CEGUI::EventArgs & e)
{
	mShutDown = true;
	return true;
}
//-------------------------------------------------------------------------------------
void BasicTutorial7::createFrameListener(void)
{
	Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	mWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	mInputManager = OIS::InputManager::createInputSystem(pl);

	mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, true));
	mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject(OIS::OISMouse, true));

	mMouse->setEventCallback(this);
	mKeyboard->setEventCallback(this);

	//Set initial mouse clipping size
	windowResized(mWindow);

	//Register as a Window listener
	Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

	mRoot->addFrameListener(this);
}
//-------------------------------------------------------------------------------------
bool BasicTutorial7::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	if (mWindow->isClosed())
		return false;

	if (mShutDown)
		return false;

	//Need to capture/update each device
	mKeyboard->capture();
	mMouse->capture();

	//Need to inject timestamps to CEGUI System.
	CEGUI::System::getSingleton().injectTimePulse(evt.timeSinceLastFrame);

	return true;
}
//-------------------------------------------------------------------------------------
bool BasicTutorial7::keyPressed( const OIS::KeyEvent &arg )
{
	CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();
	context.injectKeyDown((CEGUI::Key::Scan)arg.key);
	context.injectChar((CEGUI::Key::Scan)arg.text);
	return true;
}
//-------------------------------------------------------------------------------------
bool BasicTutorial7::keyReleased( const OIS::KeyEvent &arg )
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp((CEGUI::Key::Scan)arg.key);
	return true;
}
//-------------------------------------------------------------------------------------
bool BasicTutorial7::mouseMoved( const OIS::MouseEvent &arg )
{
	CEGUI::GUIContext &sys = CEGUI::System::getSingleton().getDefaultGUIContext();
	sys.injectMouseMove(arg.state.X.rel, arg.state.Y.rel);
	// Scroll wheel.
	if (arg.state.Z.rel)
		sys.injectMouseWheelChange(arg.state.Z.rel / 120.0f);
	return true;
}
//-------------------------------------------------------------------------------------
bool BasicTutorial7::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(convertButton(id));
	return true;
}
//-------------------------------------------------------------------------------------
bool BasicTutorial7::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(convertButton(id));
	return true;
}
//-------------------------------------------------------------------------------------
bool BasicTutorial7::quit(const CEGUI::EventArgs &e)
{
	mShutDown = true;
	return true;
}
//-------------------------------------------------------------------------------------
CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID)
{
	switch (buttonID)
	{
	case OIS::MB_Left:
		return CEGUI::LeftButton;

	case OIS::MB_Right:
		return CEGUI::RightButton;

	case OIS::MB_Middle:
		return CEGUI::MiddleButton;
	default:
		return CEGUI::LeftButton;
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
		BasicTutorial7 app;
 
		try {
			app.go();
		}
		catch (Ogre::Exception& e) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
			MessageBox(NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
			std::cerr << "An exception has occured: " <<
				e.getFullDescription().c_str() << std::endl;
#endif
		}
 
		return 0;
	}
 
#ifdef __cplusplus
}
#endif