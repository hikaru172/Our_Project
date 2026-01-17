#include "UILayer.h"
#include "GameLayer.h"
#include "PauseLayer.h"
#include "AudioManager.h"

USING_NS_CC;

UILayer* UILayer::createLayer(int stageNumber)
{
    auto layer = UILayer::create(stageNumber);
    return layer;
}

UILayer* UILayer::create(int stageNumber) {
    UILayer* ret = new UILayer();
    if (ret && ret->init(stageNumber)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool UILayer::init(int stageNumber) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto label = Label::createWithTTF(
        StringUtils::format("Stage %d", stageNumber), //文字列をフォーマットする関数
        "fonts/RiiPopkkR.otf",
        32
    );
    label->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label);



    auto normal_Sprite = Sprite::create("UI/stageselect.png");
    auto selected_Sprite = Sprite::create("UI/stageselect2.png");

    //この内部ではSpriteをMenuItemSpriteの子ノードとして追加している
    auto chara_change_Item = MenuItemSprite::create(
        normal_Sprite,
        selected_Sprite,
        CC_CALLBACK_1(UILayer::onButtonPressed, this)
    );
    chara_change_Item->setPosition(Vec2(1200.0f, 670.0f));


    auto repeat_Sprite = Sprite::create("UI/repeat.png");
    auto repeat_selected_Sprite = Sprite::create("UI/repeat2.png");
    auto Repeat_Item = MenuItemSprite::create(
        repeat_Sprite,
        repeat_selected_Sprite,
        CC_CALLBACK_1(UILayer::onRepeatButtonPressed, this)
    );
    Repeat_Item->setPosition(Vec2(90.0f, 690.0f));

    auto pause_Sprite = Sprite::create("UI/pause.png");
    auto pause_selected_Sprite = Sprite::create("UI/pause2.png");
    auto pause_Item = MenuItemSprite::create(
        pause_Sprite,
        pause_selected_Sprite,
        CC_CALLBACK_1(UILayer::onPauseButtonPressed, this)
    );
    pause_Item->setPosition(Vec2(40.0f, 690.0f));



    auto menu = Menu::create(chara_change_Item, Repeat_Item, pause_Item , nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

    return true;
}

void UILayer::onButtonPressed(Ref* sender)
{

    auto gameLayer = dynamic_cast<GameLayer*>(
        this->getParent()->getChildByName("GameLayer")
        );

    if (gameLayer)
    {
        gameLayer->chara_change();
    }
}

void UILayer::onRepeatButtonPressed(Ref* sender)
{

    auto gameLayer = dynamic_cast<GameLayer*>(
        this->getParent()->getChildByName("GameLayer")
        );

    if (gameLayer)
    {
        gameLayer->setupStage();
    }

}

void UILayer::onPauseButtonPressed(Ref* sender)
{

    // ゲーム進行を止める
    Director::getInstance()->pause();
    AudioManager::pauseBGM();

    auto scene = Director::getInstance()->getRunningScene();
    scene->getPhysicsWorld()->setSpeed(0);

    // PauseLayerをSceneに追加
    auto pauseLayer = PauseLayer::create();
    pauseLayer->setName("PauseLayer");

    Director::getInstance()->getRunningScene()->addChild(pauseLayer, 5);
}