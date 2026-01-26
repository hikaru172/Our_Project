#include "ClearLayer.h"
#include "UILayer.h"
#include "AudioManager.h"
#include "GameLayer.h"
#include "GameScene.h"
#include "StageSelectScene.h"

USING_NS_CC;

ClearLayer* ClearLayer::createLayer(int stageNumber, float sumTime) {
    ClearLayer* ret = new ClearLayer();
    if (ret && ret->init(stageNumber, sumTime)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);

    return nullptr;
}

bool ClearLayer::init(int stageNumber, float sumTime) {
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

    // 背景
    auto clear = Sprite::create("UI/clear_back.png");
    clear->setPosition(Director::getInstance()->getVisibleSize() / 2.0f);
    this->addChild(clear);
    auto size = clear->getContentSize();
    auto clear1 = Sprite::create("UI/clear_back1.png");
    clear1->setPosition(size / 2.0f);
    clear->addChild(clear1);

    // やり直しボタン
    auto repeat = Sprite::create("UI/clear_button_repeat.png");
    auto repeat_button = Sprite::create("UI/clear_button_repeat_back.png");
    auto repeat_selected_button = Sprite::create("UI/clear_button_repeat_back_selected.png");
    auto button_size = repeat_button->getContentSize();
    repeat->setPosition(button_size / 2.0f);
    auto repeat_Item = MenuItemSprite::create(
        repeat_button,
        repeat_selected_button,
        CC_CALLBACK_1(ClearLayer::onRepeatButtonPressed, this)
    );
    repeat_Item->setPosition(size.width / 5.0f, size.height / 12.0f);
    repeat_Item->addChild(repeat);

    // 次のステージへボタン
    auto next = Sprite::create("UI/clear_button_next.png");
    auto next_button = Sprite::create("UI/clear_button_next_back.png");
    auto next_selected_button = Sprite::create("UI/clear_button_next_back_selected.png");
    next->setPosition(button_size / 2.0f);
    auto next_Item = MenuItemSprite::create(
        next_button,
        next_selected_button,
        CC_CALLBACK_1(ClearLayer::onNextButtonPressed, this)
    );
    next_Item->setPosition(size.width / 2.0f, size.height / 12.0f);
    next_Item->addChild(next);

    // ステージ選択へボタン
    auto stage = Sprite::create("UI/clear_button_stage.png");
    auto stage_button = Sprite::create("UI/clear_button_stage_back.png");
    auto stage_selected_button = Sprite::create("UI/clear_button_stage_back_selected.png");
    stage->setPosition(button_size / 2.0f);
    auto stage_Item = MenuItemSprite::create(
        stage_button,
        stage_selected_button,
        CC_CALLBACK_1(ClearLayer::onStageButtonPressed, this)
    );
    stage_Item->setPosition(size.width / 5.0f * 4.0f, size.height / 12.0f);
    stage_Item->addChild(stage);

    // ボタン配置
    auto menu = Menu::create(repeat_Item, next_Item, stage_Item, nullptr);
    menu->setPosition(Vec2::ZERO);
    clear->addChild(menu);

    // スター
    auto star1_base = Sprite::create("UI/clear_star1_outline.png");
    star1_base->setPosition(size.width / 4.0f, size.height / 10.0f * 9.0f);
    clear->addChild(star1_base);
    auto star2_base = Sprite::create("UI/clear_star2_outline.png");
    star2_base->setPosition(size.width / 2.0f, size.height);
    clear->addChild(star2_base);
    auto star3_base = Sprite::create("UI/clear_star3_outline.png");
    star3_base->setPosition(size.width / 4.0f * 3.0f, size.height / 10.0f * 9.0f);
    clear->addChild(star3_base);

    //auto star1 = Sprite::create("UI/clear_star1.png");
    //star1->setPosition(star1_base->getContentSize() / 2.0f);
    //star1_base->addChild(star1);
    //auto star2 = Sprite::create("UI/clear_star2.png");
    //star2->setPosition(star2_base->getContentSize() / 2.0f);
    //star2_base->addChild(star2);
    //auto star3 = Sprite::create("UI/clear_star3.png");
    //star3->setPosition(star3_base->getContentSize() / 2.0f);
    //star3_base->addChild(star3);
    
    // ステージ表示
    auto Stage = Label::createWithTTF(StringUtils::format("Stage %d", stageNumber), "fonts/RiiPopkkR.otf", 28);
    Stage->setPosition(size.width / 2.0f, size.height / 10.0f * 7.0f);
    clear->addChild(Stage);
    _StageNumber = stageNumber;
    
    // スコア表示（タイムか何か）
    auto score_back = Sprite::create("UI/clear_score_back.png");
    score_back->setPosition(size.width / 2.0f, size.height / 9.0f * 4.0f);
    clear->addChild(score_back);
    auto score = Label::createWithTTF(StringUtils::format("CLEAR TIME : %.2f", sumTime), "fonts/RiiPopkkR.otf", 40);
    score->setPosition(score_back->getContentSize() / 2.0f);
    score_back->addChild(score);

    // 色付きスターをはめ込む動作（スコアによって変化）


    return true;
}

void ClearLayer::onRepeatButtonPressed(Ref* sender)
{
    dynamic_cast<UILayer*>(Director::getInstance()->getRunningScene()->getChildByName("UILayer"))->endPause();
    AudioManager::resumeBGM();
    auto scene = Director::getInstance()->getRunningScene();
    scene->removeChildByName("ClearLayer");
    dynamic_cast<GameLayer*>(Director::getInstance()->getRunningScene()->getChildByName("GameLayer"))->setupStage();
    scene->getPhysicsWorld()->setSpeed(1);
}

void ClearLayer::onNextButtonPressed(Ref* sender)
{
    auto director = Director::getInstance();
    director->resume();

    _StageNumber++;
    auto gameScene = GameScene::createScene(_StageNumber);
    director->replaceScene(TransitionFade::create(0.5f, gameScene));
}

void ClearLayer::onStageButtonPressed(Ref* sender)
{
    auto director = Director::getInstance();
    director->resume();

    auto stageSelectScene = StageSelectScene::createScene();
    director->replaceScene(TransitionFade::create(0.5f, stageSelectScene));
}