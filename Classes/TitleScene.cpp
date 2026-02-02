#include "TitleScene.h"
#include "StageSelectScene.h"

USING_NS_CC;

Scene* TitleScene::createScene()
{
    return TitleScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    CCLOG("Error while loading: %s!!!!!!!!!!!!!!!!!!!!!!!!!!\n", filename);
}


bool TitleScene::init()
{
    //親クラスの初期化が失敗したら、自分の初期化も中止
    if (!Scene::init())
    {
        return false;
    }

    //画面サイズ取得
    //visibleSizeは見えている領域の幅と高さ(cocos2d::Size型←ポインタじゃない！)
    auto visibleSize = Director::getInstance()->getVisibleSize();
    //originは見えている画面領域の左下座標(cocos2d::Vec2型←ポインタじゃない！)
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto bg = Sprite::create("BG/title_back.png");
    bg->setPosition(visibleSize / 2.0f);
    this->addChild(bg, 0);

    //スタートボタン
    auto start_label = Label::createWithTTF("START", "fonts/nikumaru.otf", 50);
    start_label->setTextColor(Color4B(60, 60, 60, 255));
    auto startItem = MenuItemLabel::create(
        start_label,
        CC_CALLBACK_1(TitleScene::onStartButtonPressed, this));

    if (startItem == nullptr) {
        problemLoading("'fonts/RiiPopkkR.otf'");
    }
    else {
        startItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 0.2f));
    }

    auto menu = Menu::create(startItem, nullptr); //引数が可変長のため、終端マーカーとしてnullptrを書く
    menu->setPosition(Vec2::ZERO); //Vec2::ZEROはVec2(0,0)のこと
    this->addChild(menu, 1);
    //ここでのthisはTitleScene* のことだが、多態性によってScene*としても扱える


    // ラベル表示
    auto label = Label::createWithTTF("FLIPAIRS", "fonts/nikumaru.otf", 96);
    label->setTextColor(Color4B(0, 0, 0, 255));
    if (label == nullptr) {
        //読み込み失敗時のエラー処理
        problemLoading("'fonts/RiiPopkkR.otf'");
    }
    else {
        // 配置
        label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 0.6f));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    return true;
}

void TitleScene::onStartButtonPressed(Ref* sender)
{

    //遷移
    auto scene = StageSelectScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, scene));

}
