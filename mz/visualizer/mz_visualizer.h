#pragma once

#include <string>
#include <vector>
#include <codecvt>

#include "mz_core/mz_base.h"
#include "mz_core/mz_log.h"

#include <Ogre.h>
#include <OgreApplicationContext.h>
#include <OgreInput.h>
#include <OgreRTShaderSystem.h>
#include <OgreShaderGenerator.h>

#ifdef _MSC_VER
#pragma comment(lib, "mz_core.lib")
#endif

namespace mz {
	class SIM_API Visualizer : public OgreBites::ApplicationContext, public OgreBites::InputListener {
	public:
		Visualizer();
		virtual ~Visualizer();
	public:
		virtual void setup() override;
	public:
		/**
		 * @brief set title of window, must be invoked before setup
		 * @param title
		*/
		void setTileOfWindow(const std::string& title);

		/**
		 * @brief set camera info, must be invoked before setup
		*/
		void setCamera(const mz::Vector3& camPosition, const mz::Vector3& camLookAt);

		/**
		 * @brief set source.cfg file path
		 * @param sourceCfgFile 
		*/
		void setSourceCfg(const std::string& sourceCfgFile);

		/**
		 * @brief load source.cfg
		*/
		void loadSourceCfg();

		/**
		 * @brief join path
		 * @param rootDir 
		 * @param fileName 
		 * @return 
		*/
		std::string joinPath(const std::string& rootDir, const std::string& fileName);

		/**
		 * @brief draw grids
		 * @param gridSize 
		 * @param unitSize 
		*/
		void drawGrid(float gridSize, float unitSize);
		
		/**
		 * @brief draw axis of X,Y,Z
		 * @param axisLength 
		*/
		void drawAxis(float axisLength = 1.0f);
	protected:
		mz::Vector3 m_camPosition, m_camLookTo;
		std::string m_title;

		std::string m_sourcePath;
	};
}