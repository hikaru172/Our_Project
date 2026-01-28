#include "Character.h"
#include "AudioManager.h"
#include "GameLayer.h"
#include "FailedLayer.h"
#include "UILayer.h"

USING_NS_CC;

Character* Character::create(Vec2 position, std::string sprite_name) {
    Character* ret = new Character();
    if (ret && ret->init(position, sprite_name)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);

    return nullptr;
}

bool Character::init(Vec2 position , std::string sprite_name) {

    if (!Sprite::initWithFile(sprite_name)) {
        return false;
    }

    this->setPosition(position);

    auto material = PhysicsMaterial(1.0f, 0.0f, 0.0f);
    auto body = PhysicsBody::createBox(Size(42.0f , 50.0f), material);
    body->setDynamic(true);
    body->setRotationEnable(false);
    body->setCategoryBitmask(0x01);
    body->setCollisionBitmask(0x02 | 0x04 | 0x08);
    body->setContactTestBitmask(0x02 | 0x04 | 0x08 | 0x10 | 0x20 | 0x40);
    body->setVelocityLimit(550.0f);
    this->setPhysicsBody(body);

    auto triangle = Sprite::create("characters/triangle.png");
    auto size = this->getContentSize();
    triangle->setPosition(Vec2(size.width / 2.0f, size.height + 5.0f));
    triangle->setName("triangle");
    this->addChild(triangle);

    size_t pos = sprite_name.find("green");
    if (pos != std::string::npos) {
        initAnimations1();
    }
    else {
        initAnimations2();
        triangle->setVisible(false);
    }

    return true;
}

void Character::initAnimations1() {
    Vector<SpriteFrame*> idleFrames1;
    idleFrames1.pushBack(SpriteFrame::create("Characters/character_green_idle.png", Rect(0, 0, 42, 50)));

    Vector<SpriteFrame*> walkFrames1;
    walkFrames1.pushBack(SpriteFrame::create("Characters/character_green_walk_a.png", Rect(0, 0, 42, 50)));
    walkFrames1.pushBack(SpriteFrame::create("Characters/character_green_walk_b.png", Rect(0, 0, 42, 50)));

    Vector<SpriteFrame*> jumpFrames1;
    jumpFrames1.pushBack(SpriteFrame::create("Characters/character_green_jump.png", Rect(0, 0, 42, 50)));

    Vector<SpriteFrame*> climbFrames1;
    climbFrames1.pushBack(SpriteFrame::create("Characters/character_green_climb_a.png", Rect(0, 0, 42, 50)));
    climbFrames1.pushBack(SpriteFrame::create("Characters/character_green_climb_b.png", Rect(0, 0, 42, 50)));

    Vector<SpriteFrame*> sinkFrames1;
    sinkFrames1.pushBack(SpriteFrame::create("Characters/character_green_hit.png", Rect(0, 0, 42, 50)));
    sinkFrames1.pushBack(SpriteFrame::create("Characters/character_green_hit2.png", Rect(0, 0, 42, 50)));

    auto idleAnimation1 = Animation::createWithSpriteFrames(idleFrames1, 0.5f);
    idleAnimation1->setLoops(-1);

    auto walkAnimation1 = Animation::createWithSpriteFrames(walkFrames1, 0.2f);
    walkAnimation1->setLoops(-1);

    auto jumpAnimation1 = Animation::createWithSpriteFrames(jumpFrames1, 0.2f);
    jumpAnimation1->setLoops(-1);

    auto climbAnimation1 = Animation::createWithSpriteFrames(climbFrames1, 0.2f);
    climbAnimation1->setLoops(-1);

    auto sinkAnimation1 = Animation::createWithSpriteFrames(sinkFrames1, 0.3f);
    sinkAnimation1->setLoops(-1);

    _idleAnim1 = Animate::create(idleAnimation1);
    _walkAnim1 = Animate::create(walkAnimation1);
    _jumpAnim1 = Animate::create(jumpAnimation1);
    _climbAnim1 = Animate::create(climbAnimation1);
    _sinkAnim1 = Animate::create(sinkAnimation1);

    _idleAnim1->retain();
    _walkAnim1->retain();
    _jumpAnim1->retain();
    _climbAnim1->retain();
    _sinkAnim1->retain();

}

void Character::initAnimations2() {

    Vector<SpriteFrame*> idleFrames2;
    idleFrames2.pushBack(SpriteFrame::create("Characters/character_beige_idle.png", Rect(0, 0, 42, 50)));

    Vector<SpriteFrame*> walkFrames2;
    walkFrames2.pushBack(SpriteFrame::create("Characters/character_beige_walk_a.png", Rect(0, 0, 42, 50)));
    walkFrames2.pushBack(SpriteFrame::create("Characters/character_beige_walk_b.png", Rect(0, 0, 42, 50)));

    Vector<SpriteFrame*> jumpFrames2;
    jumpFrames2.pushBack(SpriteFrame::create("Characters/character_beige_jump.png", Rect(0, 0, 42, 50)));

    Vector<SpriteFrame*> climbFrames2;
    climbFrames2.pushBack(SpriteFrame::create("Characters/character_beige_climb_a.png", Rect(0, 0, 42, 50)));
    climbFrames2.pushBack(SpriteFrame::create("Characters/character_beige_climb_b.png", Rect(0, 0, 42, 50)));

    Vector<SpriteFrame*> sinkFrames2;
    sinkFrames2.pushBack(SpriteFrame::create("Characters/character_beige_hit.png", Rect(0, 0, 42, 50)));
    sinkFrames2.pushBack(SpriteFrame::create("Characters/character_beige_hit2.png", Rect(0, 0, 42, 50)));

    auto idleAnimation2 = Animation::createWithSpriteFrames(idleFrames2, 0.5f);
    idleAnimation2->setLoops(-1);

    auto walkAnimation2 = Animation::createWithSpriteFrames(walkFrames2, 0.2f);
    walkAnimation2->setLoops(-1);

    auto jumpAnimation2 = Animation::createWithSpriteFrames(jumpFrames2, 0.2f);
    jumpAnimation2->setLoops(-1);

    auto climbAnimation2 = Animation::createWithSpriteFrames(climbFrames2, 0.2f);
    climbAnimation2->setLoops(-1);

    auto sinkAnimation2 = Animation::createWithSpriteFrames(sinkFrames2, 0.3f);
    sinkAnimation2->setLoops(-1);

    _idleAnim2 = Animate::create(idleAnimation2);
    _walkAnim2 = Animate::create(walkAnimation2);
    _jumpAnim2 = Animate::create(jumpAnimation2);
    _climbAnim2 = Animate::create(climbAnimation2);
    _sinkAnim2 = Animate::create(sinkAnimation2);

    _idleAnim2->retain();
    _walkAnim2->retain();
    _jumpAnim2->retain();
    _climbAnim2->retain();
    _sinkAnim2->retain();

}

void Character::changeAnimation(AnimState state) {

    stopAllActions();

    auto chara_tag = this->getTag();
    auto idleAnim = _idleAnim1;
    auto walkAnim = _walkAnim1;
    auto jumpAnim = _jumpAnim1;
    auto climbAnim = _climbAnim1;

    if (chara_tag == 2) {
        idleAnim = _idleAnim2;
        walkAnim = _walkAnim2;
        jumpAnim = _jumpAnim2;
        climbAnim = _climbAnim2;
    }


    switch (state) {
    case AnimState::Idle:
        runAction(idleAnim);
        break;

    case AnimState::Walk:
        runAction(walkAnim);
        break;

    case AnimState::Jump:
        runAction(jumpAnim);
        break;

    case AnimState::Climb:
        runAction(climbAnim);
        break;
    }

}


void Character::update(float dt, const CharacterInput& input, const std::vector<EventKeyboard::KeyCode>& currentKey) {

    auto body = this->getPhysicsBody();
    Vec2 vel = body->getVelocity();
    float speed = 200.0f;

    if (currentKey.empty()) {
        vel.x = 0;
        if (_state != AnimState::Jump) {
            _state = AnimState::Idle;
        }
    }
    else if (currentKey.back() == EventKeyboard::KeyCode::KEY_LEFT_ARROW && input.left && !(_leftlimited || _CBleftlimited)) {
        vel.x = -speed;
        setFlippedX(true);
        if (!_jumplimited)
            _state = AnimState::Walk;
        else if (_climblimited)
            _state = AnimState::Jump;
    }
    else if (currentKey.back() == EventKeyboard::KeyCode::KEY_RIGHT_ARROW && input.right && !(_rightlimited || _CBrightlimited)) {
        vel.x = speed;
        setFlippedX(false);
        if (!_jumplimited)
            _state = AnimState::Walk;
        else if (_climblimited)
            _state = AnimState::Jump;
    }
    else if (currentKey.back() == EventKeyboard::KeyCode::KEY_UP_ARROW && input.up && !_climblimited) {
        auto pos = this->getPositionX();
        int x;
        x = pos / 48.0f;
        this->setPositionX(48.0f * x + 24.0f);
        vel.x = 0;
        vel.y = speed;
        _state = AnimState::Climb;
    }
    else if ((input.left || input.right) && (_leftlimited || _CBleftlimited || _rightlimited || _CBrightlimited)) { //左右でlimitedがかかっているときにも_stateをWalkさせるようにするため
        vel.x = 0;  //これがなくても速度ほぼ0になってるが,念のため書いてる
        _state = AnimState::Walk;
    }
    else if (input.up && _climblimited) {
        if (_state == AnimState::Walk) {
            _state = AnimState::Walk;   //そのまま
            if (!input.right && !input.left) {
                vel.x = 0.0f;
                _state = AnimState::Idle;
            }
        }
        else if (_state == AnimState::Jump) {
            _state = AnimState::Jump;   //そのまま
        }
    }


    if (input.jump && !_jumplimited) {
        vel.y = 500.0f;
        _state = AnimState::Jump;
    }

    /*CCLOG("vel.x %f", vel.x);*/
    body->setVelocity(vel);

    if (_state != _prevState) {
        changeAnimation(_state);
        _prevState = _state;
    }

}

void Character::onGround() {
    _jumplimited = false;
    if (_state == AnimState::Jump) {
        _state = AnimState::Idle;
    }
}

void Character::onHitLeft() {
    _leftlimited = true;
}

void Character::onCBHitLeft() {
    _CBleftlimited = true;
}

void Character::onHitRight() {
    _rightlimited = true;
}

void Character::onCBHitRight() {
    _CBrightlimited = true;
}

void Character::onHitLadder() {
    _climblimited = false;
}

void Character::onReleaseLeft() {
    _leftlimited = false;
}

void Character::onCBReleaseLeft() {
    _CBleftlimited = false;
}

void Character::onReleaseRight() {
    _rightlimited = false;
}
void Character::onCBReleaseRight() {
    _CBrightlimited = false;
}

void Character::onReleaseGround() {
    _jumplimited = true;
}

void Character::onReleaseLadder() {
    _climblimited = true;
}

bool Character::canMoveLeft() const {
    return !(_leftlimited || _CBleftlimited);
}

bool Character::canMoveRight() const {
    return !(_rightlimited || _CBrightlimited);
}

bool Character::canJump() const {
    return !_jumplimited;
}

void Character::reset_flip() {
    setFlippedX(false);
}

void Character::setTriangle() {
    auto triangle = this->getChildByName("triangle");
    triangle->setVisible(true);
}

void Character::removeTriangle() {
    auto triangle = this->getChildByName("triangle");
    triangle->setVisible(false);
}

void Character::onEnterWater()
{
    if (_iswater)
        return;

    _iswater = true;

    //操作・物理を止める
    this->stopAllActions();
    this->getPhysicsBody()->setVelocity(Vec2::ZERO);
    this->getPhysicsBody()->setGravityEnable(false);

    auto up = MoveBy::create(0.5f, Vec2(0, 15));
    auto down = MoveBy::create(0.5f, Vec2(0, -20));

    auto sink = MoveBy::create(0.5f, Vec2(0, -50));

    auto endCallback = CallFunc::create([this]()
        {
            std::string sound_name = "Sounds/";
            auto tag = this->getTag();
            if (tag == 1)
                sound_name.append("chara1_failed.mp3");
            else if (tag == 2)
                sound_name.append("chara2_failed.mp3");

            this->removeChildByName("triangle");
            this->runAction(MoveBy::create(1.0f,Vec2(0,-100)));
            this->runAction(FadeOut::create(0.5f));

            AudioManager::playSE(sound_name);

            dynamic_cast<UILayer*>(Director::getInstance()->getRunningScene()->getChildByName("UILayer"))->startPause();
            AudioManager::pauseBGM();   // 今のところは止めておく（後から調整予定）
            auto scene = Director::getInstance()->getRunningScene();
            scene->getPhysicsWorld()->setSpeed(0);
            auto failed = FailedLayer::create();
            failed->setName("FailedLayer");
            Director::getInstance()->getRunningScene()->addChild(failed, 5);
        });

    auto tag = this->getTag();
    if(tag == 1)
        this->runAction(_sinkAnim1);
    else if(tag == 2)
        this->runAction(_sinkAnim2);

    //アニメーションが終わった後の処理をコールバック関数としてSequenceに入れるために、上で処理をまとめて書いている
    auto seq = Sequence::create(down, up , down , sink, endCallback, nullptr);
    this->runAction(seq);
}

bool Character::iswater() {
    return _iswater;
}

Character::~Character() {
    CC_SAFE_RELEASE(_idleAnim1);
    CC_SAFE_RELEASE(_walkAnim1);
    CC_SAFE_RELEASE(_jumpAnim1);
    CC_SAFE_RELEASE(_idleAnim2);
    CC_SAFE_RELEASE(_walkAnim2);
    CC_SAFE_RELEASE(_jumpAnim2);
    CC_SAFE_RELEASE(_sinkAnim1);
    CC_SAFE_RELEASE(_sinkAnim2);
}