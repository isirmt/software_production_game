#pragma once
#include <GL/glut.h>

#include "2DAssets.hpp"
#include "Color255.hpp"
#include "LightManager.hpp"
#include "SceneManager.hpp"
#include "SceneBase.hpp"

namespace Scene {
class LaunchLogoScene : public SceneBase {
 public:
  LaunchLogoScene();
  ~LaunchLogoScene() {
    delete background;
    delete logo;
    delete back;
  }

  void Update() override;
  void Draw() override;
  void KeyboardProc(unsigned char key, int x, int y) override {}
  void MouseProc(int button, int state, int x, int y) override {}
  void MotionProc(int x, int y) override {}
  void PassiveMotionProc(int x, int y) override {}
  void SpecialFuncProc(int key, int x, int y) override {}

 private:
  Obj::Rectangle* background;

  Obj::Image* logo;
  Obj::Image* back;

  int clickCounts;
  float timeleft;

  const std::string folderName = "launch/";
};

}  // namespace Scene