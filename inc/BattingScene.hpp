#pragma once
#include <GL/glut.h>

#include <iostream>

#include "2DAssets.hpp"
#include "3DAssets.hpp"
#include "Color255.hpp"
#include "LightManager.hpp"
#include "SceneBase.hpp"
#include "MouseInput.hpp"
#include "SceneManager.hpp"

namespace Scene{
    class BattingScene : public SceneBase {
        public:
            BattingScene();
            inline ~BattingScene(){
                delete backButton;
                delete rect;
                delete text;
            }

            void Update() override;
            void Draw() override;
            void KeyboardProc(unsigned char key, int x, int y) override{}
            void MouseProc(int button, int state, int x, int y) override{}
            void MotionProc(int x, int y) override{}
            void PassiveMotionProc(int x, int y) override{}
            void SpecialFuncProc(int key, int x, int y) override{}

        private:
            void RuleMode();

        private:
            Obj::ObjFile stage;
            Obj::ObjFile bat; 
            Obj::ObjFile player;
            Obj::Sphere ball;
            Obj::ObjFile enemy;
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
            Obj::Null* null;
            const std::string folderName = "minigames/baseball/";
            bool flag;
            bool gameStart;
            bool ruleView;
            int point = 0;
            int strike = 0;
            int high_point = 0;
            int clearScore = 10;
            float goTimer;
            const float goTimerMax = 5.f;
            float batTimer;
            const float batTimerMax = 10.f;
            float watchingCameraDeg;
            bool cameraFlag;
            bool cameraFlag_2;

            const PosVec ruleImageOffset =
                PosVec(ApplicationPreference::windowSize.x / 8.f,
                        ApplicationPreference::windowSize.y / 8.f);
            const PosVec ruleImageSize =
                PosVec(ApplicationPreference::windowSize.x * 3.f / 4.f,
                    ApplicationPreference::windowSize.y * 3.f / 4.f);
            std::vector<Obj::Image*> rulePics;

            PosVec batRatateScale = PosVec(0.5f, 0.f, 0.f);
    };
}