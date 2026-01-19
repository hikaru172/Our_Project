#include "PauseLayer.h"
#include "TitleScene.h"
#include "StageSelectScene.h"
#include "AudioManager.h"

USING_NS_CC;

bool PauseLayer::init() {
    if (!Layer::init()
        )
        return false;

    //PauseLayer内で全てのタッチ入力を検知することで、Pause中は他のUIに触れないように
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = [&](Touch*, Event*) {
        return true;
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    auto bg = LayerColor::create(Color4B(0, 0, 0, 128));
    this->addChild(bg);

    auto pause = Sprite::create("UI/pause_back.png");
    pause->setPosition(Director::getInstance()->getVisibleSize() / 2.0f);
    this->addChild(pause);

    auto size = pause->getContentSize();
    auto x_button = Sprite::create("UI/red_button.png");
    auto x_selected_button = Sprite::create("UI/red_button.png");
    auto resume_Item = MenuItemSprite::create(
        x_button,
        x_selected_button,
        CC_CALLBACK_1(PauseLayer::onResumeButtonPressed, this)
    );
    resume_Item->setPosition(size);
    auto x_mark = Sprite::create("UI/icon_cross.png");
    x_mark->setPosition(x_button->getContentSize() / 2.0f);
    resume_Item->addChild(x_mark);
    
    auto button = Sprite::create("UI/blue_rectangle_button.png");
    auto selected_button = Sprite::create("UI/blue_rectangle_button2.png");
    auto title_Item = MenuItemSprite::create(
        button,
        selected_button,
        CC_CALLBACK_1(PauseLayer::onTitleButtonPressed, this)
    );
    title_Item->setPosition(Vec2(size.width/ 2.0f, 50.0f));
    auto title_label = Label::createWithTTF(u8"タイトルへ", "fonts/RiiPopkkR.otf", 28);
    title_label->setPosition(button->getContentSize() / 2);
    title_Item->addChild(title_label);

    auto button2 = Sprite::create("UI/blue_rectangle_button.png");
    auto selected_button2 = Sprite::create("UI/blue_rectangle_button2.png");
    auto stage_Item = MenuItemSprite::create(
        button2,
        selected_button2,
        CC_CALLBACK_1(PauseLayer::onStageButtonPressed, this)
    );
    stage_Item->setPosition(Vec2(size.width / 2.0f, 150.0f));
    auto stage_label = Label::createWithTTF(u8"ステージ選択へ", "fonts/RiiPopkkR.otf", 28);
    stage_label->setPosition(button2->getContentSize() / 2);
    stage_Item->addChild(stage_label);




    auto base_sound = Sprite::create("UI/slide_horizontal_grey_bar.png");
    auto base_bar_edge = Sprite::create("UI/slide_horizontal_grey_circle.png");
    auto base_bar_edge2 = Sprite::create("UI/slide_horizontal_grey_circle2.png");
    auto real_sound = Sprite::create("UI/slide_horizontal_color_bar.png");
    auto real_bar_edge = Sprite::create("UI/slide_horizontal_color_circle.png");
    auto hangle_sound = Sprite::create("UI/slide_hangle.png");
    auto size_base = base_sound->getContentSize();
    auto size_base_edge = base_bar_edge->getContentSize();
    auto percent = AudioManager::getBGMVolume();

    base_sound->setPosition(Vec2(size.width / 2.0f, 250.0f));
    base_bar_edge->setPosition(Vec2(0.0f, size_base.height / 2.0f));
    base_bar_edge2->setPosition(Vec2(264.0f, size_base.height / 2.0f));
    pause->addChild(base_sound);
    base_sound->addChild(base_bar_edge);
    base_sound->addChild(base_bar_edge2);

    real_sound->setAnchorPoint(Vec2(0.0f, 0.5f)); // 左中央
    real_sound->setScaleX(percent);
    real_sound->setPosition(Vec2(0.0f, size_base.height / 2.0f));
    real_bar_edge->setPosition(Vec2(0.0f, size_base.height / 2.0f));
    base_sound->addChild(real_sound);
    base_sound->addChild(real_bar_edge);


    hangle_sound->setPosition(size_base.width * percent, size_base.height / 2.0f);
    base_sound->addChild(hangle_sound);

    auto sound_listener = EventListenerTouchOneByOne::create();
    sound_listener->setSwallowTouches(true);
    sound_listener->onTouchBegan = [=](Touch* touch, Event* event) {
        Vec2 pos = base_sound->convertToNodeSpace(touch->getLocation());
        Rect rect = Rect(-size_base_edge.width / 2.0f, 0, size_base.width + size_base_edge.width, size_base.height);
        CCLOG("posX = %f", pos.x);
        /*return rect.containsPoint(pos);*/
        if (rect.containsPoint(pos)) {
            float minX = 0.0f;
            float maxX = size_base.width;
            pos.x = clampf(pos.x, minX, maxX);
            hangle_sound->setPositionX(pos.x);
            auto percent = (pos.x) / (size_base.width);
            real_sound->setScaleX(percent);
            AudioManager::setBGMVolume(percent);

            return true;  // このノードがタッチを取る
        }
        return false;
    };
    sound_listener->onTouchMoved = [=](Touch* touch, Event* event) {
        float minX = 0.0f;
        float maxX = size_base.width;

        Vec2 localPos = base_sound->convertToNodeSpace(touch->getLocation());
        localPos.x = clampf(localPos.x, minX, maxX);

        hangle_sound->setPositionX(localPos.x);

        // 値に変換（0〜1）
        auto percent = (localPos.x - minX) / (maxX - minX);

        real_sound->setScaleX(percent);

        CCLOG("percent = %f", percent);

        // ここで音量などを変更
         /*AudioEngine::setVolume(id, percent);*/
        AudioManager::setBGMVolume(percent);
    };
    sound_listener->onTouchEnded = [=](Touch* touch, Event* event) {
        //CCLOG("drag end");
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(sound_listener, hangle_sound);





    auto menu = Menu::create(resume_Item, stage_Item, title_Item,  nullptr);
    menu->setPosition(Vec2::ZERO);
    pause->addChild(menu);

    return true;
}

void PauseLayer::onResumeButtonPressed(Ref* sender) {
    Director::getInstance()->resume();
    AudioManager::resumeBGM();
    auto scene = Director::getInstance()->getRunningScene();
    scene->removeChildByName("PauseLayer");
    scene->getPhysicsWorld()->setSpeed(1);
}

void PauseLayer::onTitleButtonPressed(Ref* sender) {
    auto director = Director::getInstance();

    director->resume();
    this->removeFromParent();

    auto titleScene = TitleScene::createScene();
    director->replaceScene(TransitionFade::create(0.5f, titleScene));
}

void PauseLayer::onStageButtonPressed(Ref* sender) {
    auto director = Director::getInstance();

    director->resume();
    this->removeFromParent();

    auto stageSelectScene = StageSelectScene::createScene();
    director->replaceScene(TransitionFade::create(0.5f, stageSelectScene));
}

void PauseLayer::onArrangeSound(Ref* sender) {

}