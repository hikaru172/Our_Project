#include "Water.h"
#include <string>

USING_NS_CC;

Water* Water::create(Vec2 start_position, Vec2 end_position, std::string sprite_name) {
    Water* ret = new Water();
    if (ret && ret->init(start_position, end_position, sprite_name)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);

    return nullptr;
}

bool Water::init(Vec2 start_position, Vec2 end_position, std::string sprite_name) {
    if (!Node::init()) {
        return false;
    }

    std::string tmp = sprite_name;
    float Xamount = end_position.x - start_position.x + 1.0f; //ƒg[ƒ^ƒ‹‚ÌƒuƒƒbƒN”
    float Yamount = end_position.y - start_position.y + 1.0f;

    for (float j = 0.0f; j < Yamount; j++) {

        if (j == Yamount - 1.0f) {
            sprite_name.append("_top");
        }

        sprite_name.append(".png");

        for (float i = 0.0f; i < Xamount; i++) {

            auto sprite = Sprite::create(sprite_name);
            sprite->setPosition(Vec2(48.0f * i, 48.0f * j));
            this->addChild(sprite);

        }
        sprite_name = tmp;
    }

    auto Position = Vec2(24.0f + 48.0 * start_position.x, 24.0f + 48.0f * start_position.y);
    this->setPosition(Position);


    auto material = PhysicsMaterial(1.0f, 0.0f, 0.0f);
    auto body = PhysicsBody::createBox(Size(48.0f * Xamount, 48.0f * Yamount - 24.0f), material, Vec2((Xamount / 2.0f) * 48.0f - 24.0f, (Yamount / 2.0f) * 48.0f - 24.0f));
    body->setDynamic(false);
    body->setCategoryBitmask(0x40);
    body->setCollisionBitmask(0x00);
    body->setContactTestBitmask(0x01);
    this->setPhysicsBody(body);

    auto left = MoveBy::create(1.5f, Vec2(-30, 0));
    auto right = MoveBy::create(1.5f, Vec2(30, 0));

    auto wave = RepeatForever::create(
        Sequence::create(
            EaseSineInOut::create(left), 
            EaseSineInOut::create(right),
            nullptr
        )
    );

    this->runAction(wave);

    return true;
}