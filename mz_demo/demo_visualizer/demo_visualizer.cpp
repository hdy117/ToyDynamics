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
  /*mz::Vector3 camPosition{ 0,30,-40 }, camLookAt{ 0,5,0 };
  camPosition = { -50,50,50 };
  camLookAt = { 0,0,0 };

  vis.setTileOfWindow("MzVisualizer Window");
  vis.setDataRootDir("E:/work/SimReposity/ToyDynamics/bin/data/");
  vis.setCamera(camPosition, camLookAt);

  vis.loadMesh("house/house2.obj");
  vis.loadMesh("FinalBaseMesh.obj");*/

  visApp.initApp();
  visApp.getRoot()->startRendering();
  visApp.closeApp();

  return 0;
}