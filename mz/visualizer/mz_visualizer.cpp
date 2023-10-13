#include "mz_visualizer.h"

namespace mz {
	Visualizer::Visualizer() : OgreBites::ApplicationContext("Demo App") {
	}

	Visualizer::~Visualizer() {
	}

	void Visualizer::loadSourceCfg() {
		Ogre::ConfigFile cf;
		cf.load(m_sourcePath);

		Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
		Ogre::String secName, typeName, archName;

		while (seci.hasMoreElements())
		{
			secName = seci.peekNextKey();
			Ogre::ConfigFile::SettingsMultiMap* settings = seci.getNext();
			Ogre::ConfigFile::SettingsMultiMap::iterator i;

			for (i = settings->begin(); i != settings->end(); ++i)
			{
				typeName = i->first;
				archName = i->second;
				Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
			}
		}

		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	}

	void Visualizer::setup() {
		OgreBites::ApplicationContext::setup();
		addInputListener(this);

		// load from source.cfg
		loadSourceCfg();

		// get a pointer to the already created root
		Ogre::Root* root = getRoot();
		Ogre::SceneManager* scnMgr = root->createSceneManager();

		// register our scene with the RTSS
		Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
		shadergen->addSceneManager(scnMgr);

		// without light we would just get a black screen    
		Ogre::Light* light = scnMgr->createLight("MainLight");
		Ogre::SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
		lightNode->setPosition(0, 10, 15);
		lightNode->attachObject(light);

		// also need to tell where we are
		Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
		camNode->setPosition(0, 0, 140);
		camNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);

		// create the camera
		Ogre::Camera* cam = scnMgr->createCamera("myCam");
		cam->setNearClipDistance(5); // specific to this sample
		cam->setAutoAspectRatio(true);
		camNode->attachObject(cam);

		// and tell it to render into the main window
		getRenderWindow()->addViewport(cam);

		// finally something to render
		Ogre::Entity* ent = scnMgr->createEntity("ogrehead.mesh");
		Ogre::SceneNode* node = scnMgr->getRootSceneNode()->createChildSceneNode();
		node->attachObject(ent);
		node->scale(Ogre::Vector3(0.6, 0.6, 0.6));
	}
	
	void Visualizer::setTileOfWindow(const std::string& title) {
		m_title = title;
	}
	
	void Visualizer::setCamera(const mz::Vector3& camPosition, const mz::Vector3& camLookAt) {

	}
	
	void Visualizer::setSourceCfg(const std::string& sourceCfgFile) {
		m_sourcePath = sourceCfgFile;
	}

	std::string Visualizer::joinPath(const std::string& rootDir, const std::string& fileName) {
		return rootDir + "/" + fileName;
	}

	void Visualizer::drawGrid(float gridSize, float unitSize) {
		/*for (float x = -gridSize / 2; x <= gridSize / 2; x += unitSize) {
			m_driver->draw3DLine(irr::core::vector3df(x, -gridSize / 2, 0), irr::core::vector3df(x, gridSize / 2, 0), color);
			m_driver->draw3DLine(irr::core::vector3df(-gridSize / 2, x, 0), irr::core::vector3df(gridSize / 2, x, 0), color);
		}*/
	}

	void Visualizer::drawAxis(float axisLength) {
		//// Draw X-axis (red)
		//m_driver->draw3DLine(irr::core::vector3df(0, 0, 0), irr::core::vector3df(axisLength, 0, 0), irr::video::SColor(255, 255, 0, 0));

		//// Draw Y-axis (green)
		//m_driver->draw3DLine(irr::core::vector3df(0, 0, 0), irr::core::vector3df(0, axisLength, 0), irr::video::SColor(255, 0, 255, 0));

		//// Draw Z-axis (blue)
		//m_driver->draw3DLine(irr::core::vector3df(0, 0, 0), irr::core::vector3df(0, 0, axisLength), irr::video::SColor(255, 0, 0, 255));
	}
}