#pragma once
#include <GL/glut.h>
#include <sys/stat.h>

#include <iostream>
#include <map>
#include <sstream>

#include "2DAssets.hpp"
#include "3DAssets.hpp"
#include "Color255.hpp"
#include "DataStore.hpp"
#include "LightManager.hpp"
#include "MapRelativeData.hpp"
#include "SceneBase.hpp"
#include "SceneManager.hpp"
#include "StoryData.hpp"
#include "StoryProgressData.hpp"
#include "picojson.hpp"

namespace Scene {
class StoryScene : public SceneBase {
 public:
  StoryScene();
  ~StoryScene() {
    delete nowStage;
    delete nowLeft;
    delete nowRight;
    delete buttonFrame;
    delete speakerFrame;
    delete speakerText;
    delete storyText;
    delete nowChapter;
  }

  void Update() override;
  void Draw() override;
  void KeyboardProc(unsigned char key, int x, int y) override {}
  void MouseProc(int button, int state, int x, int y) override {}
  void MotionProc(int x, int y) override {}
  void PassiveMotionProc(int x, int y) override {}
  void SpecialFuncProc(int key, int x, int y) override {}

 private:
  void StoreChapter();

  picojson::array storyArray;  // json内容格納変数

  Story::StoryProgress storyProgress;

  Obj::ObjFile* nowStage;
  Obj::ObjFile* nowLeft;
  Obj::ObjFile* nowRight;

  Obj::Button* buttonFrame;
  Obj::Rectangle* speakerFrame;

  Obj::Text* speakerText;
  Obj::Text* storyText;

  Obj::Button* button;

  Story::Chapter* nowChapter;

  std::map<std::string, MapRelative> mapRelatives;

  const std::string folderName = "title/";
  const std::string talksFilePath = "story/talks.json";
  const std::string relativeStageFilePath = "relative/modelName.json";
  const std::string storyProgressFilePath = "story/progress.dat";

  const std::string stageFolderName = "story/";
};

}  // namespace Scene