#include "Block.h"
#include <string>

USING_NS_CC;

Block* Block::create(Vec2 start_position, Vec2 end_position, std::string sprite_name) {
    Block* ret = new Block();
    if (ret && ret->init(start_position, end_position, sprite_name)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);

    return nullptr;
}

bool Block::init(Vec2 start_position, Vec2 end_position, std::string sprite_name) {
    if (!Node::init()) {
        return false;
    }

    float Xamount = end_position.x - start_position.x + 1.0f; //トータルのブロック数
    float Yamount = end_position.y - start_position.y + 1.0f;

    auto material = PhysicsMaterial(1.0f, 0.0f, 0.0f);
    auto body = PhysicsBody::createBox(Size(48.0f * Xamount, 48.0f * Yamount), material, Vec2((Xamount / 2.0f) * 48.0f - 24.0f, (Yamount / 2.0f) * 48.0f - 24.0f));
    body->setDynamic(false);
    body->setCollisionBitmask(0x01);
    body->setContactTestBitmask(0x01);
    body->setEnabled(false);

    auto redpos = sprite_name.find("red");
    if (redpos != std::string::npos) {
        _kind2 = kind_of::Red;
        body->setCategoryBitmask(0x08);
    } 
    //pos = std::string::npos;
    auto bluepos = sprite_name.find("blue");
    if (bluepos != std::string::npos) {
        _kind2 = kind_of::Blue;
        body->setCategoryBitmask(0x08);
    }

    if (bluepos == std::string::npos && redpos == std::string::npos) {
        _kind2 = kind_of::Normal;
        body->setCategoryBitmask(0x02);
    }


    for (float j = 0.0f; j < Yamount; j++) {

        for (float i = 0.0f; i < Xamount; i++) {

            auto sprite = Sprite::create(sprite_name);
            sprite->setName("block_sprite");
            sprite->setPosition(Vec2(48.0f * i, 48.0f * j));
            this->addChild(sprite);

        }
    }

    auto Position = Vec2(24.0f + 48.0 * start_position.x, 24.0f + 48.0f * start_position.y);
    this->setPosition(Position);

    this->setPhysicsBody(body);

    _state2 = State::Off;
    _Xamount = Xamount;
    _Yamount = Yamount;

    return true;
}

void Block::setState(State state) {
    if (_state2 == state) return;

    _state2 = state;

    std::string sprite_name = "Blocks/block";

    if (_state2 == State::Off) {
        sprite_name.append("_trans");
        this->getPhysicsBody()->setEnabled(false);
    }
    else {
        this->getPhysicsBody()->setEnabled(true);
    }

    if (_kind2 == kind_of::Red) {
        sprite_name.append("_red.png");
    }
    else if (_kind2 == kind_of::Blue) {
        sprite_name.append("_blue.png");
    }

    for (auto child : this->getChildren()) //getChildren はVector<Node*>型
    {
        if (auto sprite = dynamic_cast<Sprite*>(child))
        {
            sprite->setTexture(sprite_name);
        }
    }

}

kind_of Block::get_kind() {
    return _kind2;
}