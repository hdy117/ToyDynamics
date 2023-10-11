#include "mz_visualizer.h"

namespace mz {
	Visualizer::Visualizer() :m_device(nullptr), m_driver(nullptr), m_guienv(nullptr), m_smgr(nullptr) {
	}

	Visualizer::~Visualizer() {
	}

	bool Visualizer::createDevice() {
		/*
			change it to EDT_BURNINGSVIDEO, EDT_NULL, EDT_DIRECT3D8, EDT_DIRECT3D9, or EDT_OPENGL.
			windowSize: Size of the Window or screen in FullScreenMode to be created. In this example we use 640x480.
			bits: Amount of color bits per pixel. This should be 16 or 32. The parameter is often ignored when running in windowed mode.
			fullscreen: Specifies if we want the device to run in fullscreen mode or not.
			stencilbuffer: Specifies if we want to use the stencil buffer (for drawing shadows).
			vsync: Specifies if we want to have vsync enabled, this is only useful in fullscreen mode.
			eventReceiver: An object to receive events. We do not want to use this parameter here, and set it to 0.
		*/
		m_device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(1600, 900), 16,
			false, false, true, 0);

		if (m_device != nullptr) {
			m_driver = m_device->getVideoDriver();
			m_smgr = m_device->getSceneManager();
			m_guienv = m_device->getGUIEnvironment();
		}

		// default camera
		m_camPosition = { 0.0f,30.0f, 30.0f };
		m_camLookTo = { 0.0f,0.0f,0.0f };

		// title
		m_title = "Irrlicht 3D Engine";

		return m_device != nullptr;
	}
	void Visualizer::setTileOfWindow(const std::string& title) {
		m_title = title;
	}
	void Visualizer::toIrrVec3(const mz::Vector3& vecIn, irr::core::vector3df& vecOut) {
		vecOut.X = vecIn[0];
		vecOut.Y = vecIn[1];
		vecOut.Z = vecIn[2];
	}
	void Visualizer::setCamera(const mz::Vector3& camPosition, const mz::Vector3& camLookTo) {
		Visualizer::toIrrVec3(camPosition, m_camPosition);
		Visualizer::toIrrVec3(camLookTo, m_camLookTo);
	}
	void Visualizer::setDataRootDir(const std::string& rootDir) {
		m_rootDir = rootDir;
	}
	std::string Visualizer::joinPath(const std::string& rootDir, const std::string& fileName) {
		return rootDir + "/" + fileName;
	}
	irr::scene::ISceneNode* Visualizer::loadMesh(const std::string& meshName, const std::string& textureName) {
		auto meshAbsPath = joinPath(m_rootDir, meshName);
		irr::scene::IAnimatedMesh* mesh = m_smgr->getMesh(meshAbsPath.c_str());
		if (!mesh) {
			return nullptr;
		}
		irr::scene::IAnimatedMeshSceneNode* node = m_smgr->addAnimatedMeshSceneNode(mesh);
		if (node) {
			auto textureAbsPath = joinPath(m_rootDir, textureName);
			node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
			node->setMD2Animation(irr::scene::EMAT_STAND);
			node->setMaterialTexture(0, m_driver->getTexture(textureAbsPath.c_str()));
		}
	}
	void Visualizer::initVis() {
		// create device
		if (!createDevice()) {
			LOG_ERROR << "unable to create device for Irrlicht.\n";
			throw std::runtime_error("unable to create device for Irrlicht.\n");
		}

		// set title of window
		m_device->setWindowCaption((wchar_t*)(m_title.c_str()));

		// set camera
		m_smgr->addCameraSceneNode(0, m_camPosition, m_camLookTo);
	}
	void Visualizer::runVis() {
		while (m_device->run()) {
			m_driver->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));

			m_smgr->drawAll();
			m_guienv->drawAll();

			m_driver->endScene();
		}
	}
	void Visualizer::exitVis() {
		m_device->drop();
	}
}