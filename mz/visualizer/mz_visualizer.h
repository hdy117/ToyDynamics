#pragma once

#include <string>
#include <vector>

#include "mz_core/mz_base.h"
#include "mz_core/mz_log.h"

#include "irrlicht/irrlicht.h"

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(lib, "mz_core.lib")
#endif

namespace mz {
	class SIM_API Visualizer {
	public:
		Visualizer();
		virtual ~Visualizer();

		Visualizer(const Visualizer&) = delete;
		Visualizer& operator==(const Visualizer&) = delete;
		Visualizer(const Visualizer&&) = delete;
		Visualizer& operator==(const Visualizer&&) = delete;
	public:
		virtual void initVis();
		virtual void runVis();
		virtual void exitVis();
	public:
		/**
		 * @brief set title of window, must be invoked before initVis
		 * @param title
		*/
		void setTileOfWindow(const std::string& title);

		/**
		 * @brief set camera info, must be invoked before initVis
		*/
		void setCamera(const mz::Vector3& camPosition, const mz::Vector3& camLookTo);

		/**
		 * @brief set root dir of data, must be invoked before initVis
		*/
		void setDataRootDir(const std::string& rootDir);

		/**
		 * @brief join path
		 * @param rootDir 
		 * @param fileName 
		 * @return 
		*/
		std::string joinPath(const std::string& rootDir, const std::string& fileName);

		/**
		 * @brief 
		 * @param meshName 
		 * @param textureName 
		*/
		irr::scene::ISceneNode* loadMesh(const std::string& meshName, const std::string& textureName = "");
	public:
		static void toIrrVec3(const mz::Vector3& vecIn, irr::core::vector3df& vecOut);
	private:
		/**
		 * @brief this device is root object for visualizer. ref https://irrlicht.sourceforge.io/docu/example001.html
		 * @return 
		*/
		bool createDevice();
	protected:
		irr::IrrlichtDevice* m_device;				// root object
		irr::video::IVideoDriver* m_driver;		// graphic driver
		irr::scene::ISceneManager* m_smgr;		// scene manager
		irr::gui::IGUIEnvironment* m_guienv;	// gui env

		irr::core::vector3df m_camPosition, m_camLookTo;
		std::string m_title;

		std::string m_rootDir;
	};
}