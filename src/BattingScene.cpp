#include "BattingScene.hpp"

#include "StoryScene.hpp"
#include "TitleScene.hpp"

Scene::BattingScene::BattingScene(){
    Camera::SetActive(true);
    SceneBase::SetOrthoCameraWindow();
    Camera::SetAsPerspective(
        ApplicationPreference::windowSize.x / ApplicationPreference::windowSize.y,
        30, 100, 2500, PosVec(2000, 1000, 1), PosVec(500, 0, 0), PosVec(0, 1, 0)
    );
    Camera::SetPerspectiveMode(true);
    Camera::UpdateCamera();

    stage = Obj::ObjFile(PosVec(0.0, 5., 0.0), PosVec(), PosVec(),
                            ApplicationPreference::modelFilePath + folderName +
                                "baseball_stage.obj");
    stage.SetScale(PosVec(100, 100, 100));
    stage.SetShininess(20);
    stage.SetRotate(0, PosVec(0, 1, 0));

    bat = Obj::Cylinder(PosVec(800.0, 80.0, -20.0), PosVec(0.0, 0.0, 0.0), PosVec(0.0, 0.0, 0.0));
    bat.SetAmbient(Color255(100, 75, 80));
    bat.SetDiffuse(Color255(.3f, .3f, .3f));
    bat.SetSpecular(Color255(255, 255, 255, 255));
    bat.SetShininess(20);
    bat.SetScale(PosVec(2, 10, 2));

    player = Obj::ObjFile(PosVec(800.0, 0.0, -50.0), PosVec(0.0, 0.0, 0.0), 
            PosVec(0.0, 0.0, 0.0), ApplicationPreference::modelFilePath + "char/subLeader.obj");
    player.SetScale(PosVec(7, 7, 7));
    player.SetShininess(10);

    ball = Obj::Sphere(PosVec(450.0, -50.0, 0.0), PosVec(0.0, 0.0, 0.0), 
            PosVec(0.0, 0.0, 0.0));
    ball.SetScale(PosVec(3, 3, 3));
    ball.SetAmbient(Color255(250, 250, 250));
    ball.SetDiffuse(Color255(.3, .3, .3));
    ball.SetSpecular(Color255(0, 0, 0));

    enemy = Obj::ObjFile(PosVec(400.0, 0.0, 0.0), PosVec(0.0, 0.0, 0.0), 
            PosVec(0.0, 0.0, 0.0), ApplicationPreference::modelFilePath + "char/Caesar.obj");
    enemy.SetScale(PosVec(7, 7, 7));
    enemy.SetShininess(10);
    enemy.SetRotate(90, PosVec(0, 1, 0));

    flag = false;
    gameStart = false;
    ruleView = false;

    miniuiImage = new Obj::Image(
        PosVec(0, 30), PosVec(75, 190),
        ApplicationPreference::imgFilePath + "minigames/miniui.ppm");
    layer2D.AddObject(miniuiImage);

    Color255 innerCol;
    innerCol = Color255(70, 170, 230);
    startButton = new Obj::Button(PosVec(30, 100), PosVec(50, 50), true, true);
    startButton->SetInnerColor(innerCol, innerCol * 0.8, innerCol * 0.65, innerCol * 0.75);
    startButton->SetOutlineColor(Color255(35, 57, 40), 5.f);
    startButton->SetInnerAnimation(.2f);
    layer2D.AddObject(startButton);

    innerCol = Color255(255, 100, 50);
    backButton = new Obj::Button(PosVec(30, 30), PosVec(50, 50), true, true);
    backButton->SetInnerColor(innerCol, innerCol * 0.8, innerCol * 0.65, innerCol * 0.75);
    backButton->SetOutlineColor(Color255(35, 57, 40), 5.f);
    backButton->SetInnerAnimation(.2f);
    layer2D.AddObject(backButton);

    nImage = new Obj::Image(ruleImageOffset, ruleImageSize,
                ApplicationPreference::imgFilePath + "minigames/gameover.ppm");
                rulePics.emplace_back(nImage);
    nImage = new Obj::Image(
        ruleImageOffset, ruleImageSize,
        ApplicationPreference::imgFilePath + "minigames/quotaAc.ppm");
    rulePics.emplace_back(nImage);
    nImage = new Obj::Image(
        ruleImageOffset, ruleImageSize,
        ApplicationPreference::imgFilePath + "minigames/quotaAc.ppm");
    rulePics.emplace_back(nImage);

    innerCol = Color255("7894DA");
    ruleBack =
        new Obj::Rectangle(PosVec(ruleImageOffset.x - 5, ruleImageOffset.y - 5),
                            PosVec(ruleImageSize.x + 10, ruleImageSize.y + 30));
    ruleBack->SetInnerColor(innerCol);

    ruleText = new Obj::Text(
        PosVec(ruleImageOffset.x + 5.f, ruleImageOffset.y + ruleImageSize.y + 3),
        PosVec(), "ルール説明：次へは画像をクリック！・戻る場合は「ルール」ボタン");
    ruleText->SetInnerColor(Color255(250));

    innerCol = Color255(70, 100, 230);
    ruleButton = new Obj::Button(PosVec(30, 30 + (50 + 20) * 2), PosVec(50, 50), true, true);
    ruleButton->SetInnerColor(innerCol, innerCol * 0.8, innerCol * 0.65, innerCol * 0.75);
    ruleButton->SetOutlineColor(Color255(35, 57, 40), 5.f);
    ruleButton->SetInnerAnimation(.2f);
    layer2D.AddObject(ruleButton);

    innerCol = Color255(70, 170, 230);
    textBack = new Obj::Rectangle(
        PosVec(100, 30), PosVec(ApplicationPreference::windowSize.x - 150, 30));
    textBack->SetInnerColor(innerCol);
    layer2D.AddObject(textBack);

    text = new Obj::Text(PosVec(110, 35), PosVec(), 
                "ボタンをクリックして開始：ストーリーノルマ(" + std::to_string(clearScore) + ")");
    text->SetInnerColor(Color255(250.0, 250.0, 250.0));
    layer2D.AddObject(text);

    innerCol = Color255("#57B7F3");
    rect = new Obj::Rectangle(PosVec(0, 0), PosVec(50, 50), true, false);
    rect->SetInnerColor(innerCol);
    rect->ChangeValueWithAnimation(&rect->GetVectorPointer(VectorType::SIZE)->x, 0.f, 10.f);
    rect->ChangeValueWithAnimation(&rect->GetVectorPointer(VectorType::SIZE)->y, 0.f, 10.f);
    layer2D.AddObject(rect);

    goRect = new Obj::Image(
        PosVec(ApplicationPreference::windowSize.x / 2.f, -100), PosVec(0, 0),
        ApplicationPreference::imgFilePath + "minigames/gameover.ppm");

    innerCol = Color255("#57B7F3");
    quotaImage = new Obj::Image(
        PosVec(-500, 450), PosVec(150, 100),
        ApplicationPreference::imgFilePath + "minigames/quotaAc.ppm");
}

void Scene::BattingScene::Update(){
    layer2D.Collide();

    stage.Update();
    bat.Update();
    player.Update();
    ball.Update();
    enemy.Update();

    if(startButton->GetMouseSelected()){
        startButton->SetMouseOff();
        gameStart = true;
        
        point = 0;
        strike = 0;
        startButton->SetEnabled(false);
        ruleButton->SetEnabled(false);
        text->SetString("得点：" + std::to_string(point) + 
                                "   ストライクカウント：" + std::to_string(strike));

        ruleView = false;
        RuleMode();

        goRect->ChangeValueWithAnimation(
            &goRect->GetVectorPointer(VectorType::SIZE)->x, 1, .3f);
        goRect->ChangeValueWithAnimation(
            &goRect->GetVectorPointer(VectorType::SIZE)->y, 1, .3f);
        goRect->ChangeValueWithAnimation(
            &goRect->GetVectorPointer(VectorType::POS)->x,
            ApplicationPreference::windowSize.x / 2.f, .3f);
        goRect->ChangeValueWithAnimation(
            &goRect->GetVectorPointer(VectorType::POS)->y, -100.f, .3f);
    }

    if(ruleButton->GetMouseSelected()){
        ruleButton->SetMouseOff();
        ruleView = !ruleView;   
        RuleMode();
    }
    if (ruleView) {
        int i = 0;
        for (auto& item : rulePics) {
            if (item->GetMouseSelected()) {
                item->SetMouseOff();
                layer2D.DeleteObject(item);
                if (i == rulePics.size() - 1) {
                layer2D.AddObject(rulePics[0]);
                } else {
                layer2D.AddObject(rulePics[i + 1]);
                }
            }
            i++;
        }
    }

    if(gameStart)
    {
    if (goRect->GetPos().y < -70) layer2D.DeleteObject(goRect);

    if(ball.GetPosition().y < 50.0){
        ball.SetPosition(PosVec(450.0, 50.0, 0.0));
        ball.SetVelocity(PosVec(300, 0, 0));
    }
    
    if(Input::MouseInput::GetClick(GLUT_LEFT_BUTTON) == PressFrame::FIRST && flag){
        bat = Obj::Cylinder(PosVec(800.0, 80.0, -20.0), PosVec(0.0, 0.0, 0.0), PosVec(0.0, 0.0, 0.0));
        bat.SetAmbient(Color255(100, 75, 80));
        bat.SetDiffuse(Color255(.3f, .3f, .3f));
        bat.SetSpecular(Color255(255, 255, 255, 255));
        bat.SetShininess(20);
        bat.SetScale(PosVec(2, 10, 2));

        flag = false;
    }
    else if(Input::MouseInput::GetClick(GLUT_LEFT_BUTTON) == PressFrame::FIRST && !flag){
        bat = Obj::Cylinder(PosVec(800.0, 50.0, 5.0), PosVec(0.0, 0.0, 0.0), PosVec(0.0, 0.0, 0.0));
        bat.SetAmbient(Color255(100, 75, 80));
        bat.SetDiffuse(Color255(.3f, .3f, .3f));
        bat.SetSpecular(Color255(255, 255, 255, 255));
        bat.SetShininess(20);
        bat.SetScale(PosVec(2, 10, 2));
        bat.SetRotate(45, PosVec(1, 1, 0));

        bat = Obj::Cylinder(PosVec(800.0, 40.0, 10.0), PosVec(0.0, 0.0, 0.0), PosVec(0.0, 0.0, 0.0));
        bat.SetAmbient(Color255(100, 75, 80));
        bat.SetDiffuse(Color255(.3f, .3f, .3f));
        bat.SetSpecular(Color255(255, 255, 255, 255));
        bat.SetShininess(20);
        bat.SetScale(PosVec(2, 10, 2));
        bat.SetRotate(90, PosVec(1, 0, 0));

        if(ball.GetPosition().x >= 750.0 && ball.GetPosition().x <= 800.0){
            ball = Obj::Sphere(PosVec(ball.GetPosition()), PosVec(-400.0, 50.0, 0.0), 
                PosVec(0.0, -5.0, 0.0));
            ball.SetScale(PosVec(3, 3, 3));
            ball.SetAmbient(Color255(250, 250, 250));
            ball.SetDiffuse(Color255(.3, .3, .3));
            ball.SetSpecular(Color255(0, 0, 0));
        }

        flag = true;
    }
    
    if(ball.GetPosition().x <= -350.0 || ball.GetPosition().x >= 1200.0){
        if(ball.GetPosition().x >= 1200.0){
            strike++;
            text->SetString("得点：" + std::to_string(point) + 
                                "   ストライクカウント：" + std::to_string(strike));
            if(strike >= 3 ){
                high_point = point;
                text->SetString("OUT!   現在のハイスコア" + std::to_string(high_point));
                gameStart = false;
                startButton->SetEnabled(true);
                ruleButton->SetEnabled(true);


                ball.SetPosition(PosVec(450.0, -50.0, 0.0));
                ball.SetVelocity(PosVec(0, 0, 0));

                if(point >= clearScore && Story::StoryModeManager::GetGameActive()){
                    Story::StoryModeManager::SetGameClear(true);
                    Story::StoryModeManager::SavePlusStep();
                    layer2D.DeleteObject(quotaImage);
                    layer2D.AddObject(quotaImage);
                    startButton->SetEnabled(false);
                    ruleButton->SetEnabled(false);
                    quotaImage->ChangeValueWithAnimation(
                        &quotaImage->GetVectorPointer(VectorType::POS)->x, 30, 3.f);
                }
                else if(Story::StoryModeManager::GetGameActive()){
                    Story::StoryModeManager::SetGameClear(false);
                }

                layer2D.DeleteObject(goRect);
                layer2D.AddObject(goRect);

                goRect->ChangeValueWithAnimation(
                    &goRect->GetVectorPointer(VectorType::SIZE)->x,
                    ApplicationPreference::windowSize.x / 2.f, 5.f);
                goRect->ChangeValueWithAnimation(
                    &goRect->GetVectorPointer(VectorType::SIZE)->y,
                    ApplicationPreference::windowSize.y / 4.f, 5.f);
                goRect->ChangeValueWithAnimation(
                    &goRect->GetVectorPointer(VectorType::POS)->x,
                    ApplicationPreference::windowSize.x / 4.f, 5.f);
                goRect->ChangeValueWithAnimation(
                    &goRect->GetVectorPointer(VectorType::POS)->y,
                    ApplicationPreference::windowSize.y / 4.f, 5.f);
            }
        }
        else if(ball.GetPosition().x <= -350.0){
            point++;
            text->SetString("得点：" + std::to_string(point) + 
                                "   ストライクカウント：" + std::to_string(strike));
        }

        if(strike < 3){
            ball = Obj::Sphere(PosVec(450.0, 50.0, 0.0), PosVec(300.0, 0.0, 0.0), 
                PosVec(0.0, 0.0, 0.0));
            ball.SetScale(PosVec(3, 3, 3));
            ball.SetAmbient(Color255(250, 250, 250));
            ball.SetDiffuse(Color255(.3, .3, .3));
            ball.SetSpecular(Color255(0, 0, 0));
        }
    }
    }

    if (backButton->GetMouseSelected()) {
        backButton->SetMouseOff();
        if(!Story::StoryModeManager::GetGameActive()){
            SceneManager::ChangeScene(new TitleScene());
        }
        else{
            Story::StoryModeManager::SetGameActive(false);
            SceneManager::ChangeScene(new StoryScene());
        }
        return;
    }

    if (Input::MouseInput::GetClick(GLUT_LEFT_BUTTON) >= PressFrame::FIRST) {
    PosVec markSize(50, 50);
    rect->SetPos(PosVec(Input::MouseInput::GetMouse().x - markSize.x / 2.f,
                        Input::MouseInput::GetMouse().y - markSize.y / 2.f));
    rect->SetSize(markSize);
    rect->ChangeValueWithAnimation(
        &rect->GetVectorPointer(VectorType::POS)->x,
        Input::MouseInput::GetMouse().x - markSize.x / 2.f, 5.f);
    rect->ChangeValueWithAnimation(
        &rect->GetVectorPointer(VectorType::POS)->y,
        Input::MouseInput::GetMouse().y - markSize.y / 2.f, 5.f);
    rect->ChangeValueWithAnimation(&rect->GetVectorPointer(VectorType::SIZE)->x,
                                   1.f, 5.f);
    rect->ChangeValueWithAnimation(&rect->GetVectorPointer(VectorType::SIZE)->y,
                                   1.f, 5.f);
    rect->ChangeValueWithAnimation(&rect->GetVectorPointer(VectorType::POS)->x,
                                   Input::MouseInput::GetMouse().x, 5.f);
    rect->ChangeValueWithAnimation(&rect->GetVectorPointer(VectorType::POS)->y,
                                   Input::MouseInput::GetMouse().y, 5.f);
    rect->ChangeValueWithAnimation(&rect->GetVectorPointer(VectorType::SIZE)->x,
                                   0.f, 5.f);
    rect->ChangeValueWithAnimation(&rect->GetVectorPointer(VectorType::SIZE)->y,
                                   0.f, 5.f);
    }

    layer2D.Update();
}

void Scene::BattingScene::RuleMode(){
    if(ruleView){
        if(rulePics.size() != 0){
            layer2D.AddObject(ruleBack);
            layer2D.AddObject(ruleText);
            layer2D.AddObject(rulePics[0]);
        }
        else{
            ruleView = false;
        }
    }
    else{
        for (auto& item : rulePics) {
            layer2D.DeleteObject(item);
        }
        layer2D.DeleteObject(ruleBack);
        layer2D.DeleteObject(ruleText);
    }
}

void Scene::BattingScene::Draw(){
    SceneBase::Set3DDrawMode();
    Camera::SetPerspectiveMode(true);
    Camera::UpdateCamera();

    glPushMatrix();
    stage.Draw();
    bat.Draw();
    player.Draw();
    ball.Draw();
    enemy.Draw();
    glPopMatrix();

    SceneBase::Set2DDrawMode();
    Camera::SetPerspectiveMode(false);
    Camera::UpdateCamera();

    layer2D.Draw();
}