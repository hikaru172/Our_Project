#include "PauseLayer.h"
#include "TitleScene.h"
#include "StageSelectScene.h"
#include "AudioManager.h"

USING_NS_CC;

bool PauseLayer::init() {
    if (!Layer::init())
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