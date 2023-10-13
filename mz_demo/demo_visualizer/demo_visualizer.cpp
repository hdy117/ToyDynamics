#include "visualizer/mz_visualizer.h"

#ifdef _WIN32
#pragma comment(lib, "mz_core.lib")
#pragma comment(lib, "mz_visualizer.lib")
#endif // _WIN32

/**
 * @brief demo of constant spring, spring connects 2 particles, spring connects anchor and 1 particle
 * @return 
*/
int main() {
  // set log
  FLAGS_v = 1;

  mz::Visualizer visApp;

  std::string sourceCfg = "E:/work/SimReposity/ToyDynamics/bin/resources.cfg";
  visApp.setSourceCfg(sourceCfg);

  visApp.initApp();
  visApp.getRoot()->startRendering();
  visApp.closeApp();

  return 0;
}