#include "ClearLayer.h"
#include "UILayer.h"
#include "AudioManager.h"
#include "GameLayer.h"
#include "GameScene.h"
#include "StageSelectScene.h"

USING_NS_CC;

bool ClearLayer::init() {
    if (!Layer::init()
        )
        return false;

    _StageNumber = dynamic_cast<GameLayer*>(Director::getInstance()->getRunningScene()->getChildByName("GameLayer"))->getStagenumber();
    float sumTime = dynamic_cast<GameLayer*>(Director::getInstance()->getRunningScene()->getChildByName("GameLayer"))->getSumtime();

    //PauseLayer内で全てのタッチ入力を検知することで、Pause中は他のUIに触れないように
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = [&](Touch*, Event*) {
        return true;
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    auto bg = LayerColor::create(Color4B(0, 0, 0, 128));
    this->addChild(bg);

    // ポップアップ
    auto popup = Label::createWithTTF("CLEAR!", "fonts/RiiPopkkR.otf", 128);
    popup->setPosition(Director::getInstance()->getVisibleSize() / 2.0f);
    this->addChild(popup);
    popup->setScale(0.0f);

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

    clear->setScale(0.0f);

    // スターのアニメーション
    auto star1 = Sprite::create("UI/clear_star1.png");
    star1->setPosition(star1_base->getContentSize() / 2.0f);
    star1_base->addChild(star1);
    star1->setScale(0.0f);
    auto star2 = Sprite::create("UI/clear_star2.png");
    star2->setPosition(star2_base->getContentSize() / 2.0f);
    star2_base->addChild(star2);
    star2->setScale(0.0f);
    auto star3 = Sprite::create("UI/clear_star3.png");
    star3->setPosition(star3_base->getContentSize() / 2.0f);
    star3_base->addChild(star3);
    star3->setScale(0.0f);
    auto popAnim = CallFunc::create([popup]()
        {
            auto popAnim = Sequence::create(ScaleTo::create(0.5f, 1.0f), DelayTime::create(0.5f), FadeOut::create(0.5f), nullptr);
            popup->runAction(popAnim);
        });
    auto clearAnim = CallFunc::create([clear]()
        {
            auto clearAnim = Spawn::create(ScaleTo::create(0.5f, 1.0f), nullptr);
            clear->runAction(clearAnim);
        });
    auto endCallback1 = CallFunc::create([star1]()
        {
            auto rotate1 = RotateBy::create(1.0f, 720);
            auto scaleUp1 = ScaleTo::create(1.0f, 1.0f);
            auto spawn1 = Spawn::create(rotate1, scaleUp1, nullptr);
            star1->runAction(spawn1);
        });
    auto endCallback2 = CallFunc::create([star2]()
        {
            auto rotate2 = RotateBy::create(1.0f, 720);
            auto scaleUp2 = ScaleTo::create(1.0f, 1.0f);
            auto spawn2 = Spawn::create(rotate2, scaleUp2, nullptr);
            star2->runAction(spawn2);
        });
    auto endCallback3 = CallFunc::create([star3]()
        {
            auto rotate3 = RotateBy::create(1.0f, 720);
            auto scaleUp3 = ScaleTo::create(1.0f, 1.0f);
            auto spawn3 = Spawn::create(rotate3, scaleUp3, nullptr);
            star3->runAction(spawn3);
        });
    // ポップアップ->クリア画面出現
    auto sequencePop = Sequence::create(popAnim, DelayTime::create(1.5f), clearAnim, nullptr);
    // スター表示の条件
    auto sequenceStar = Sequence::create(endCallback1, nullptr);
    if (sumTime < 5.0f)
        sequenceStar = Sequence::create(endCallback1, DelayTime::create(1.0f), endCallback3, nullptr);
    if (sumTime < 2.0f)
        sequenceStar = Sequence::create(endCallback1, DelayTime::create(1.0f), endCallback3, DelayTime::create(1.0f), endCallback2, nullptr);

    auto sequence = Sequence::create(sequencePop, DelayTime::create(0.5f), sequenceStar, nullptr);
    this->runAction(sequence);
    
    // ステージ表示
    auto Stage = Label::createWithTTF(StringUtils::format("Stage %d", _StageNumber), "fonts/RiiPopkkR.otf", 28);
    Stage->setPosition(size.width / 2.0f, size.height / 10.0f * 7.0f);
    clear->addChild(Stage);
    
    // スコア表示（タイムか何か）
    auto score_back = Sprite::create("UI/clear_score_back.png");
    score_back->setPosition(size.width / 2.0f, size.height / 9.0f * 4.0f);
    clear->addChild(score_back);
    auto score = Label::createWithTTF(StringUtils::format("CLEAR TIME : %.2f", sumTime), "fonts/RiiPopkkR.otf", 40);
    score->setPosition(score_back->getContentSize() / 2.0f);
    score_back->addChild(score);

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