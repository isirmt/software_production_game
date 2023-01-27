#pragma once
#include <GL/glut.h>

#include "2DAssets.hpp"
#include "3DAssets.hpp"
#include "Color255.hpp"
#include "LightManager.hpp"
#include "SceneBase.hpp"

namespace Scene {
class ArcheryScene : public SceneBase {
 public:
  // GameScene() {}
  ArcheryScene();
  ~ArcheryScene() {}

  void Update() override;
  void Draw() override;
  void KeyboardProc(unsigned char key, int x, int y) override {}
  void MouseProc(int button, int state, int x, int y) override {}
  void MotionProc(int x, int y) override {}
  void PassiveMotionProc(int x, int y) override {}
  void SpecialFuncProc(int key, int x, int y) override {}

 private:
  float deg;
  Color255 boxAmbient;
  Obj::Sphere sphere;
  Obj::Cube cube;
  Obj::ObjFile stage;
  Obj::Cylinder centerCube;
  Obj::ObjFile arrow;
  Obj::ObjFile bow;
  Obj::Button* backbutton;
  bool Mouseflag;

  const std::string folderName = "minigames/archery/";
};
}  // namespace Scene