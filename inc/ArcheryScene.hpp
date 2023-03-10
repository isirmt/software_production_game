#pragma once
#include <GL/glut.h>

#include "2DAssets.hpp"
#include "3DAssets.hpp"
#include "Color255.hpp"
#include "LightManager.hpp"
#include "SceneBase.hpp"
#include "SceneManager.hpp"

namespace Scene {
class ArcheryScene : public SceneBase {
 public:
  // GameScene() {}
  ArcheryScene();
  ~ArcheryScene() {
    delete backButton;
    delete rect;
    delete text;
    delete ruleText;
    delete startButton;
    delete ruleButton;
    delete nImage;
    delete goRect;
    delete quotaImage;
    delete miniuiImage;
    delete ruleBack;
    delete textBack;
    delete line1;
    delete line2;
    delete windInfo;

    for (auto& item : rulePics) {
      delete item;
    }
  }


  void Update() override;
  void Draw() override;
  void KeyboardProc(unsigned char key, int x, int y) override {}
  void MouseProc(int button, int state, int x, int y) override {}
  void MotionProc(int x, int y) override {}
  void PassiveMotionProc(int x, int y) override {}
  void SpecialFuncProc(int key, int x, int y) override {}

  private:
    void RuleMode();

 private:
  float deg;
  Color255 boxAmbient;
  Obj::Sphere sphere;
  Obj::Cube cube;
  Obj::ObjFile stage;
  Obj::Cylinder centerCube;
  Obj::ObjFile arrow;
  Obj::ObjFile bow;
  Obj::Text* text;
  Obj::Text* ruleText;
  Obj::Button* backButton; 
  Obj::Button* startButton;
  Obj::Button* ruleButton;
  Obj::Image* nImage;
  Obj::Image* goRect;
  Obj::Image* quotaImage;
  Obj::Image* miniuiImage;
  Obj::Rectangle* ruleBack;
  Obj::Rectangle* textBack;
  Obj::Rectangle* rect;
  Obj::Rectangle* line1;
  Obj::Rectangle* line2;
  Obj::Image* windInfo;
  bool Mouseflag = false;
  bool isShooting;
  bool flag;
  bool gameStart;
  bool ruleView;
  bool point1;
  bool point2;
  bool point3;
  bool point4;
  bool point5;
  bool point6;
  bool point7;
  bool point8;
  bool point9;
  bool point10;
  float RotX = 0.0;
  float RotY = 0.0;
  float RotZ = 0.0;
  int windDeg = 0.0;
  int windPow = 0.0;
  float windX = 0.0;
  float windZ = 0.0;
  int point = 0;
  int turn = 0;
  int high_point = 0;
  int clearScore = 15;
  float goTimer;
const float goTimerMax = 5.f;

  const PosVec ruleImageOffset =
      PosVec(ApplicationPreference::windowSize.x / 8.f,
              ApplicationPreference::windowSize.y / 8.f);
  const PosVec ruleImageSize =
      PosVec(ApplicationPreference::windowSize.x * 3.f / 4.f,
          ApplicationPreference::windowSize.y * 3.f / 4.f);
  std::vector<Obj::Image*> rulePics;

  const float timerCountMax = 4.f;
  float timerCount;

  const std::string folderName = "minigames/archery/";
};
}  // namespace Scene