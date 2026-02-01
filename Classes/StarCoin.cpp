#include "StarCoin.h"
#include "ClearLayer.h"
#include "AudioManager.h"
#include "UILayer.h"

USING_NS_CC;

StarCoin* StarCoin::create(Vec2 position, std::string sprite_name) {
    StarCoin* ret = new StarCoin();
    if (ret && ret->init(position, sprite_name)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);

    return nullptr;
}

bool StarCoin::init(Vec2 position, std::string sprite_name) {

    if (!Sprite::initWithFile(sprite_name)) {
        return false;
    }

    position.x = position.x * 48.0f + 24.0f;
    position.y = position.y * 48.0f + 24.0f;
    this->setPosition(position);

    auto body = PhysicsBody::createBox(Size(12.0f, 12.0f));
    body->setDynamic(false);
    body->setCategoryBitmask(0x100);
    body->setCollisionBitmask(0);
    body->setContactTestBitmask(0x01);
    body->setGravityEnable(false);

    this->setPhysicsBody(body);
    this->setName("Star");

    return true;
}

void StarCoin::getStar() {
    this->removeFromParent();
}