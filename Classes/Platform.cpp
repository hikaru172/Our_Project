#include "Platform.h"
#include <string>

USING_NS_CC;

Platform* Platform::create(Vec2 start_position, Vec2 end_position ,std::string sprite_name) {
    Platform* ret = new Platform();
    if (ret && ret->init(start_position, end_position, sprite_name)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);

    return nullptr;
}

bool Platform::init(Vec2 start_position, Vec2 end_position, std::string sprite_name) {
    if (!Node::init()) {
        return false;
    }

    std::string tmp = sprite_name;
    std::string tmp2 = sprite_name;
    float Xamount = end_position.x - start_position.x + 1.0f; //トータルのブロック数
    float Yamount = end_position.y - start_position.y + 1.0f;

    for (float j = 0.0f; j < Yamount; j++) {
        //最上段のときと最下段のときにbottomとtopをつける
        if (j == 0.0f) {
            sprite_name.append("_bottom");
        }
        if (j == Yamount - 1.0f) {
            sprite_name.append("_top");
        }

        tmp2 = sprite_name;

        for (float i = 0.0f; i < Xamount; i++) {
            //右列と左列のときrightとleftつける
            if (i == 0.0f) {
                sprite_name.append("_left");
            }
            if (i == Xamount - 1.0f) {
                sprite_name.append("_right");
            }

            sprite_name.append(".png");

            auto sprite = Sprite::create(sprite_name);
            sprite->setPosition(Vec2(48.0f * i, 48.0f * j));
            this->addChild(sprite);

            sprite_name = tmp2;
        }
        sprite_name = tmp;
    }

    auto Position = Vec2(24.0f + 48.0 * start_position.x, 24.0f + 48.0f * start_position.y);
    this->setPosition(Position);

    
    auto platmaterial = PhysicsMaterial(1.0f, 0.0f, 0.0f);
    auto platbody = PhysicsBody::createBox(Size(48.0f * Xamount , 48.0f * Yamount), platmaterial, Vec2((Xamount/2.0f)* 48.0f - 24.0f , (Yamount / 2.0f) * 48.0f - 24.0f));
    platbody->setDynamic(false);
    platbody->setCategoryBitmask(0x02);
    platbody->setCollisionBitmask(0x01);
    platbody->setContactTestBitmask(0x01);
    this->setPhysicsBody(platbody);
    
    return true;
}