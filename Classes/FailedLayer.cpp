#include "FailedLayer.h"
#include "UILayer.h"
#include "AudioManager.h"
#include "GameLayer.h"
#include "GameScene.h"
#include "StageSelectScene.h"

USING_NS_CC;

bool FailedLayer::init() {
    if (!Layer::init())
        return false;

    int stagenum = dynamic_cast<GameLayer*>(Director::getInstance()->getRunningScene()->getChildByName("GameLayer"))->getStagenumber();
    float time = dynamic_cast<GameLayer*>(Director::getInstance()->getRunningScene()->getChildByName("GameLayer"))->getSumtime();

    //PauseLayer内で全てのタッチ入力を検知することで、Pause中は他のUIに触れないように
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = [&](Touch*, Event*) {
        return true;
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    auto bg = LayerColor::create(Color4B(0, 0, 0, 128));
    this->addChild(bg);

    // 背景
    auto failed = Sprite::create("UI/failed_back.png");
    failed->setPosition(Director::getInstance()->getVisibleSize() / 2.0f);
    this->addChild(failed);
    auto size = failed->getContentSize();
    auto failed1 = Sprite::create("UI/failed_back1.png");
    failed1->setPosition(size / 2.0f);
    failed->addChild(failed1);

    // やり直しボタン
    auto repeat = Sprite::create("UI/clear_button_repeat.png");
    auto repeat_button = Sprite::create("UI/clear_button_repeat_back.png");
    auto repeat_selected_button = Sprite::create("UI/clear_button_repeat_back_selected.png");
    auto button_size = repeat_button->getContentSize();
    repeat->setPosition(button_size / 2.0f);
    auto repeat_Item = MenuItemSprite::create(
        repeat_button,
        repeat_selected_button,
        CC_CALLBACK_1(FailedLayer::onRepeatButtonPressed, this)
    );
    repeat_Item->setPosition(size.width / 5.0f, size.height / 12.0f);
    repeat_Item->addChild(repeat);


    // ステージ選択へボタン
    auto stage = Sprite::create("UI/clear_button_stage.png");
    auto stage_button = Sprite::create("UI/clear_button_stage_back.png");
    auto stage_selected_button = Sprite::create("UI/clear_button_stage_back_selected.png");
    stage->setPosition(button_size / 2.0f);
    auto stage_Item = MenuItemSprite::create(
        stage_button,
        stage_selected_button,
        CC_CALLBACK_1(FailedLayer::onStageButtonPressed, this)
    );
    stage_Item->setPosition(size.width / 5.0f * 4.0f, size.height / 12.0f);
    stage_Item->addChild(stage);

    // ボタン配置
    auto menu = Menu::create(repeat_Item, stage_Item, nullptr);
    menu->setPosition(Vec2::ZERO);
    failed->addChild(menu);

    // ステージ表示
    auto Stage = Label::createWithTTF(StringUtils::format("Stage %d", stagenum), "fonts/RiiPopkkR.otf", 28);
    Stage->setPosition(size.width / 2.0f, size.height / 10.0f * 7.0f);
    failed->addChild(Stage);

    // スコア表示（タイムか何か）
    auto score_back = Sprite::create("UI/clear_score_back.png");
    score_back->setPosition(size.width / 2.0f, size.height / 9.0f * 4.0f);
    failed->addChild(score_back);
    auto score = Label::createWithTTF(StringUtils::format("DEAD TIME : %.2f", time), "fonts/RiiPopkkR.otf", 40);
    score->setPosition(score_back->getContentSize() / 2.0f);
    score_back->addChild(score);

    return true;
}

void FailedLayer::onRepeatButtonPressed(Ref* sender)
{
    dynamic_cast<UILayer*>(Director::getInstance()->getRunningScene()->getChildByName("UILayer"))->endPause();
    AudioManager::resumeBGM();
    auto scene = Director::getInstance()->getRunningScene();
    scene->removeChildByName("FailedLayer");
    dynamic_cast<GameLayer*>(Director::getInstance()->getRunningScene()->getChildByName("GameLayer"))->setupStage();
    scene->getPhysicsWorld()->setSpeed(1);
}

void FailedLayer::onStageButtonPressed(Ref* sender)
{
    auto director = Director::getInstance();
    director->resume();

    auto stageSelectScene = StageSelectScene::createScene();
    director->replaceScene(TransitionFade::create(0.5f, stageSelectScene));
}