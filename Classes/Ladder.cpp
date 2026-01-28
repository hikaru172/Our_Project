#include "Ladder.h"
#include <string>

USING_NS_CC;

Ladder* Ladder::create(Vec2 start_position, Vec2 end_position, std::string sprite_name) {
    Ladder* ret = new Ladder();
    if (ret && ret->init(start_position, end_position, sprite_name)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);

    return nullptr;
}

bool Ladder::init(Vec2 start_position, Vec2 end_position, std::string sprite_name) {
    if (!Node::init()) {
        return false;
    }

    std::string tmp = sprite_name;
    std::string tmp2 = sprite_name;
    float Xamount = end_position.x - start_position.x + 1.0f; //トータルのブロック数
    float Yamount = end_position.y - start_position.y + 2.0f;

    for (float j = 0.0f; j < Yamount; j++) {
        //最上段のときと最下段のときにbottomとtopをつける
        if (j == 0.0f) {
            sprite_name.append("_bottom");
            /*bottom = true;*/
        }
        else if (j == Yamount - 1.0f) {
            sprite_name.append("_top");
            /*top = true;*/
        }
        else {
            sprite_name.append("_middle");
        }
        tmp2 = sprite_name;

        for (float i = 0.0f; i < Xamount; i++) {
            sprite_name.append(".png");

            /*CCLOG("%s", sprite_name.c_str());*/
            auto sprite = Sprite::create(sprite_name);
            if (sprite_name.find("middle") != std::string::npos)
                sprite->setPosition(Vec2(48.0f * i, 36.0f + 48.0f*(j-1)));
            else if (sprite_name.find("bottom") != std::string::npos)
                sprite->setPosition(Vec2(48.0f * i, 24.0f * j));    //bottomなのでyは一律で0
            else if (sprite_name.find("top") != std::string::npos)
                sprite->setPosition(Vec2(48.0f * i, 72.0f + 48.0f*(j-2)));

            this->addChild(sprite);

            sprite_name = tmp2;
        }
        sprite_name = tmp;
    }

    auto Position = Vec2(24.0f + 48.0f * start_position.x, 12.0f + 48.0f * start_position.y);   
    this->setPosition(Position);

    auto laddermaterial = PhysicsMaterial(1.0f, 0.0f, 0.0f);
    auto ladderbody = PhysicsBody::createBox(Size(2.0f * Xamount, 48.0f + 48.0f * (Yamount - 2)), laddermaterial, Vec2((Xamount / 2.0f) * 48.0f - 24.0f, ((Yamount-1.0f) / 2.0f) * 48.0f - 24.0f));
    ladderbody->setCategoryBitmask(0x10);
    ladderbody->setCollisionBitmask(0x00);
    ladderbody->setContactTestBitmask(0x01);
    ladderbody->setDynamic(false);
    ladderbody->setGravityEnable(false);

    this->setPhysicsBody(ladderbody);

    return true;
}