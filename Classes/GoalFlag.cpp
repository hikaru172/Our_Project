#include "GoalFlag.h"
#include "ClearLayer.h"
#include "AudioManager.h"
#include "UILayer.h"

USING_NS_CC;

GoalFlag* GoalFlag::create(Vec2 position, std::string sprite_name) {
    GoalFlag* ret = new GoalFlag();
    if (ret && ret->init(position, sprite_name)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);

    return nullptr;
}

bool GoalFlag::init(Vec2 position, std::string sprite_name) {

    if (!Sprite::initWithFile(sprite_name)) {
        return false;
    }

    position.x = position.x * 48.0f + 24.0f;
    position.y = position.y * 48.0f + 24.0f;
    this->setPosition(position);

    auto body = PhysicsBody::createBox(Size(12.0f, 12.0f));
    body->setDynamic(false);
    body->setCategoryBitmask(0x20);
    body->setCollisionBitmask(0);
    body->setContactTestBitmask(0x01);
    body->setGravityEnable(false);

    size_t pos = sprite_name.find("green");
    if (pos != std::string::npos) {
        body->setTag(1);
    }
    else {
        body->setTag(2);
    }

    this->setPhysicsBody(body);
    this->setName("Flag");

    return true;
}

void GoalFlag::getFlag(int charatag, cocos2d::Node* stageRoot, int stageNumber, float sumTime) {
    int tag = this->getPhysicsBody()->getTag();
    if(tag == charatag)
        this->removeFromParent();

    auto item = stageRoot->getChildByName("Flag");
    if (!item) { //Flag‚ğ2‚ÂŠl“¾‚µ‚½‚Æ‚« 
        /*Director::getInstance()->end();*/

        // ƒQ[ƒ€is‚ğ~‚ß‚é
        dynamic_cast<UILayer*>(Director::getInstance()->getRunningScene()->getChildByName("UILayer"))->startPause();
        AudioManager::pauseBGM();   // ¡‚Ì‚Æ‚±‚ë‚Í~‚ß‚Ä‚¨‚­iŒã‚©‚ç’²®—\’èj
        auto scene = Director::getInstance()->getRunningScene();
        scene->getPhysicsWorld()->setSpeed(0);
        // ClearLayer‚ğScene‚É’Ç‰Á
        auto clearLayer = ClearLayer::createLayer(stageNumber, sumTime);
        clearLayer->setName("ClearLayer");

        Director::getInstance()->getRunningScene()->addChild(clearLayer, 5);
    }
}