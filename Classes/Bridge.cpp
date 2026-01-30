#include "Bridge.h"
#include <string>

USING_NS_CC;

Bridge* Bridge::create(Vec2 start_position, Vec2 end_position, std::string sprite_name) {
    Bridge* ret = new Bridge();
    if (ret && ret->init(start_position, end_position, sprite_name)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);

    return nullptr;
}

bool Bridge::init(Vec2 start_position, Vec2 end_position, std::string sprite_name) {
    if (!Node::init()) {
        return false;
    }

    std::string tmp = sprite_name;

    float Xamount = end_position.x - start_position.x + 3.0f; //トータルのブロック数

    for (float i = 0.0f; i < Xamount; i++) {
        if (i == 0.0f) {
            sprite_name.append("_left.png");
        }
        else if (i == Xamount - 1.0f) {
            sprite_name.append("_right.png");
        }
        else {
            sprite_name.append(".png");
        }

        auto sprite = Sprite::create(sprite_name);
        if (sprite_name.find("left") != std::string::npos)
            sprite->setPosition(Vec2(-26.0f, 0.0f));
        else if (sprite_name.find("right") != std::string::npos)
            sprite->setPosition(Vec2(48.0f * (i - 2) + 26.0f, 0.0f));
        else
            sprite->setPosition(Vec2(48.0f * (i - 1) , 0.0f));

        this->addChild(sprite);

        sprite_name = tmp;
    }

    auto Position = Vec2(24.0f + 48.0f * start_position.x, 48.0f * start_position.y);
    this->setPosition(Position);

    auto material = PhysicsMaterial(1.0f, 0.0f, 0.0f);
    auto body = PhysicsBody::createBox(Size(48.0f * (Xamount - 2.0f) + 10.0f, 34.0f), material, Vec2(( (Xamount - 2.0f) / 2.0f) * 48.0f - 24.0f , 0.0f));
    body->setCategoryBitmask(0x80);
    body->setCollisionBitmask(0x01);
    body->setContactTestBitmask(0x01);
    body->setDynamic(false);
    body->setGravityEnable(false);

    this->setPhysicsBody(body);

    return true;
}