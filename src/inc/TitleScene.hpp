#pragma once
#include "SceneBase.hpp"

namespace Scene
{
    class TitleScene
        : public SceneBase
    {
    public:
        TitleScene() {}
        ~TitleScene() {}

        void Update() override;
        void Draw() override;
        void KeyboardProc(unsigned char key, int x, int y) override {}
        void MouseProc(int button, int state, int x, int y) override {}
        void MotionProc(int x, int y) override {}
        void PassiveMotionProc(int x, int y) override {}
        void SpecialFuncProc(int key, int x, int y) override {}
    };
}