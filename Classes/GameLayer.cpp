#include "GameLayer.h"
#include "GameScene.h"
#include "Platform.h"
#include "Block.h"
#include "Character.h"
#include "Switch.h"
#include "Ladder.h"
#include "GoalFlag.h"
#include "StageLoader.h"
#include <iostream>
#include <cmath>

USING_NS_CC;

GameLayer* GameLayer::createLayer(int stageNumber) {
    GameLayer* ret = new GameLayer();
    if (ret && ret->init(stageNumber)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);

    return nullptr;
}

bool GameLayer::init(int stageNumber) {
    if (!Layer::init()) {
        return false;
    }

    this->scheduleUpdate();  //これを書かないとupdate()が呼ばれない

    _stageNumber = stageNumber;


    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = [&](PhysicsContact& contact) {

        auto bodyA = contact.getShapeA()->getBody();
        auto bodyB = contact.getShapeB()->getBody();

        PhysicsBody* chara = nullptr;
        PhysicsBody* platform = nullptr;
        PhysicsBody* CB = nullptr;
        PhysicsBody* Switch = nullptr;
        PhysicsBody* Ladder = nullptr;
        PhysicsBody* Flag = nullptr;

        // 衝突情報を取得
        auto contactData = contact.getContactData();
        float normalX = contactData->normal.x; //normalはAがBを押す方向
        float normalY = contactData->normal.y;

        if (bodyA->getCategoryBitmask() == 0x01 && bodyB->getCategoryBitmask() == 0x02){
            chara = bodyA;
			platform = bodyB;
        }
        else if (bodyA->getCategoryBitmask() == 0x02 && bodyB->getCategoryBitmask() == 0x01) {
			chara = bodyB;
			platform = bodyA;
            normalX *= -1.0f;
            normalY *= -1.0f;
        } 
        
        if (bodyA->getCategoryBitmask() == 0x01 && bodyB->getCategoryBitmask() == 0x04) {
            chara = bodyA;
            Switch = bodyB;
        }
        else if (bodyA->getCategoryBitmask() == 0x04 && bodyB->getCategoryBitmask() == 0x01) {
            chara = bodyB;
            Switch = bodyA;
            normalX *= -1;
            normalY *= -1;
        }

        if (bodyA->getCategoryBitmask() == 0x01 && bodyB->getCategoryBitmask() == 0x08) {
            chara = bodyA;
            CB = bodyB;
        }
        else if (bodyA->getCategoryBitmask() == 0x08 && bodyB->getCategoryBitmask() == 0x01) {
            chara = bodyB;
            CB = bodyA;
            normalX *= -1;
            normalY *= -1;
        }

        if (bodyA->getCategoryBitmask() == 0x01 && bodyB->getCategoryBitmask() == 0x16) {
            chara = bodyA;
            Ladder = bodyB;
        }
        else if (bodyA->getCategoryBitmask() == 0x16 && bodyB->getCategoryBitmask() == 0x01) {
            chara = bodyB;
            Ladder = bodyA;
            normalX *= -1;
            normalY *= -1;
        }

        if (bodyA->getCategoryBitmask() == 0x01 && bodyB->getCategoryBitmask() == 0x32) {
            chara = bodyA;
            Flag = bodyB;
        }
        else if (bodyA->getCategoryBitmask() == 0x32 && bodyB->getCategoryBitmask() == 0x01) {
            chara = bodyB;
            Flag = bodyA;
            normalX *= -1;
            normalY *= -1;
        }

        auto vel = chara->getVelocity();

        auto tag = chara->getTag();
        auto charabody = _chara->getPhysicsBody();
        auto otherbody = _other->getPhysicsBody();

        if (Flag) {
            //getNode()はNode*型で返ってくるためキャスト
            auto flag = dynamic_cast<GoalFlag*>(Flag->getNode());
            flag->getFlag(tag);
            return true;
        }

        if (Ladder) {
            _chara->onHitLadder();
            return true;
        }

        if (normalY < -0.5f && chara->getVelocity().y <= 0) { //キャラクターの足と下のオブジェクトが接触
            _chara->onGround();
            CCLOG("onGround");

            chara->setVelocity(Vec2(vel.x, 0.0f));
            if (Switch) {
                _switchPressed = true;
            }
        }

        if (normalX < -0.6f) { //キャラクターの左側と左のオブジェクトが接触
            if (CB && charabody->getTag() == tag)
                _chara->onCBHitLeft();
            else if (CB && otherbody->getTag() == tag)
                _other->onCBHitLeft();
            else if(platform || Switch)
                _chara->onHitLeft();
        }

        if (normalX > 0.6f) { //キャラクターの右側と右のオブジェクトが接触
            if (CB && charabody->getTag() == tag)
                _chara->onCBHitRight();
            else if (CB && otherbody->getTag() == tag)
                _other->onCBHitRight();
            else if (platform || Switch)
                _chara->onHitRight();
        }

        return true; //trueを返すと衝突処理継続
    };

    contactListener->onContactSeparate = [&](PhysicsContact& contact) {

        auto bodyA = contact.getShapeA()->getBody();
        auto bodyB = contact.getShapeB()->getBody();
        PhysicsBody* chara = nullptr;
        PhysicsBody* platform = nullptr;
        PhysicsBody* CB = nullptr;
        PhysicsBody* Switch = nullptr;
        PhysicsBody* Ladder = nullptr;
        PhysicsBody* Flag = nullptr;

        auto contactData = contact.getContactData();
        float normalX = contactData->normal.x;
        float normalY = contactData->normal.y;

        if (bodyA->getCategoryBitmask() == 0x01 && bodyB->getCategoryBitmask() == 0x02) {
            chara = bodyA;
            platform = bodyB;
        }
        else if (bodyA->getCategoryBitmask() == 0x02 && bodyB->getCategoryBitmask() == 0x01) {
            chara = bodyB;
            platform = bodyA;
            normalX *= -1;
            normalY *= -1;
        }
        if (bodyA->getCategoryBitmask() == 0x01 && bodyB->getCategoryBitmask() == 0x04) {
            chara = bodyA;
            Switch = bodyB;
        }
        else if (bodyA->getCategoryBitmask() == 0x04 && bodyB->getCategoryBitmask() == 0x01) {
            chara = bodyB;
            Switch = bodyA;
            normalX *= -1;
            normalY *= -1;
        }

        if (bodyA->getCategoryBitmask() == 0x01 && bodyB->getCategoryBitmask() == 0x08) {
            chara = bodyA;
            CB = bodyB;
        }
        else if (bodyA->getCategoryBitmask() == 0x08 && bodyB->getCategoryBitmask() == 0x01) {
            chara = bodyB;
            CB = bodyA;
            normalX *= -1;
            normalY *= -1;
        }

        if (bodyA->getCategoryBitmask() == 0x01 && bodyB->getCategoryBitmask() == 0x16) {
            chara = bodyA;
            Ladder = bodyB;
        }
        else if (bodyA->getCategoryBitmask() == 0x16 && bodyB->getCategoryBitmask() == 0x01) {
            chara = bodyB;
            Ladder = bodyA;
            normalX *= -1;
            normalY *= -1;
        }

        if (bodyA->getCategoryBitmask() == 0x01 && bodyB->getCategoryBitmask() == 0x32) {
            chara = bodyA;
            Flag = bodyB;
        }
        else if (bodyA->getCategoryBitmask() == 0x32 && bodyB->getCategoryBitmask() == 0x01) {
            chara = bodyB;
            Flag = bodyA;
            normalX *= -1;
            normalY *= -1;
        }

        auto tag = chara->getTag();
        auto charabody = _chara->getPhysicsBody();
        auto otherbody = _other->getPhysicsBody();

        if (Ladder) {
            _chara->onReleaseLadder();
            return true;
        }

        if (normalY < -0.5f) {
            if (!Flag)
                _chara->onReleaseGround();

            if (Switch)
                _switchPressed = false;
        }

        if (normalX < -0.6f) {
            if (CB && charabody->getTag() == tag)
                _chara->onCBReleaseLeft();
            else if(CB && otherbody->getTag() == tag)
                _other->onCBReleaseLeft();
            else
                _chara->onReleaseLeft();
        }
        if (normalX > 0.6f) {
            if (CB && charabody->getTag() == tag)
                _chara->onCBReleaseRight();
            else if (CB && otherbody->getTag() == tag)
                _other->onCBReleaseRight();
            else
                _chara->onReleaseRight();
        }
    };

    //contactlistener登録
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);


    //キー入力listener↓
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* event) { //[]はラムダ式(無名関数)
        if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
            _leftPressed = true;
            _currentKey.push_back(keyCode);
        }
        if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
            _rightPressed = true;
            _currentKey.push_back(keyCode);
        }
        if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW) {
            _upPressed = true;
            _currentKey.push_back(keyCode);
        }
        if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {    //ほかの矢印キーと重ねて押したときにジャンプできない不具合修正のため
            _downPressed = true;
        }
        if (keyCode == EventKeyboard::KeyCode::KEY_SPACE) {
            if (_chara->canJump()) {
                _jumpPressed = true;
            }
        }
        /*_currentKey.push_back(keyCode);*/
    };


    listener->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event* event) {
        if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
            _leftPressed = false;
        if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
            _rightPressed = false;
        if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
            _upPressed = false;
        if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
            _downPressed = false;

        auto it = std::find(_currentKey.begin(), _currentKey.end(), keyCode);
        if (it != _currentKey.end())
            _currentKey.erase(it);

    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


    _stageRoot = Node::create();
    _stageRoot->setPosition(Vec2::ZERO);
    this->addChild(_stageRoot);

    // ステージ初期化処理
    //init()とsetupStage()を分けることで、ステージごとに異なるものはsetupStage()を呼べば初期化できるように
    setupStage();

    return true;
}


void GameLayer::setupStage() {
    if (_stageRoot->getChildrenCount() != 0) {
        _stageRoot->removeAllChildrenWithCleanup(true);
    }

    _chara1 = Character::create(Vec2(120.0f, 280.0f), "characters/character_green_idle.png");
    _chara2 = Character::create(Vec2(70.0f, 280.0f), "characters/character_beige_idle.png");
    _stageRoot->addChild(_chara1, 1);
    _stageRoot->addChild(_chara2, 0);

    _chara1->reset_flip();
    _chara2->reset_flip();


    _chara = _chara1;
    _other = _chara2;
    _chara->setTag(1);

    _chara->getPhysicsBody()->setTag(1);
    _other->getPhysicsBody()->setTag(2);

    _total = 0.0f;
    _total1 = 0.0f;
    _total2 = 0.0f;

    _charafixed = false;
    _chara1fixed = false;
    _chara2fixed = false;

    _charaswitchPressed = false;
    _chara1switchPressed = false;
    _chara2switchPressed = false;

    //ここから下にステージごとのオブジェクト配置処理を追加していく

    StageLoader::load("stage_info/stage1.json", _stageRoot);
    _block = dynamic_cast<Block*>(_stageRoot->getChildByName("block"));
    _switch = dynamic_cast<Switch*>(_stageRoot->getChildByName("switch"));
    _ladder = dynamic_cast<Ladder*>(_stageRoot->getChildByName("ladder"));
    _flag = dynamic_cast<GoalFlag*>(_stageRoot->getChildByName("flag"));

}



void GameLayer::update(float dt){

    CharacterInput input;
    input.left = _leftPressed;
    input.right = _rightPressed;
    input.jump = _jumpPressed;
    input.up = _upPressed;
    input.down = _downPressed;

    _chara->update(dt, input, _currentKey);
    _jumpPressed = false;

    float screenHalf = Director::getInstance()->getVisibleSize().width * 0.5f;
    float charaX = _chara->getPositionX();
    float speed = 200.0f;

    if (_total * speed > 0.0f) {
        _total = 0.0f;
        this->setPositionX(0.0f);
    }
    else {
        this->setPositionX(_total * speed);
    }

    if (_switchPressed || _charaswitchPressed) {
        _switch->setState(State::On);
        _block->setState(State::On);
    }
    else {
        _chara->onCBReleaseLeft();
        _chara->onCBReleaseRight();
        _switch->setState(State::Off);
        _block->setState(State::Off);
    }

    auto item = _stageRoot->getChildByName("Flag");
    //if (!item) //Flagを2つ獲得したとき
    //    Director::getInstance()->end();

    if (charaX > screenHalf) {
        if (_currentKey.empty()) {
            return;
        }
        else if (_currentKey.back() == EventKeyboard::KeyCode::KEY_LEFT_ARROW && _chara->canMoveLeft()) {
            _total += dt;
        }
        else if (_currentKey.back() == EventKeyboard::KeyCode::KEY_RIGHT_ARROW && _chara->canMoveRight()) {
            _total -= dt;
        }
    }
}


void GameLayer::chara_change() {
    auto now_chara_num = _chara->getTag();

    float screenHalf = Director::getInstance()->getVisibleSize().width * 0.5f;

    if (now_chara_num == 1) {
        _chara1 = _chara;
        _other = _chara1;
        _chara = _chara2;
        _chara->setTag(2);
        _total1 = _total;
        _total = _total2;
        _chara1fixed = _charafixed;
        _charafixed = _chara2fixed;
        _chara1->removeTriangle();
        _chara2->setTriangle();
        _chara1->setLocalZOrder(0);
        _chara2->setLocalZOrder(1); //数字大きいほど手前に来る
        _chara1switchPressed = _switchPressed;
        _charaswitchPressed = _chara1switchPressed;
        _switchPressed = _chara2switchPressed;

    }
    else if (now_chara_num == 2) {
        _chara2 = _chara;
        _other = _chara2;
        _chara = _chara1;
        _chara->setTag(1);
        _total2 = _total;
        _total = _total1;
        _chara2fixed = _charafixed;
        _charafixed = _chara1fixed;
        _chara2->removeTriangle();
        _chara1->setTriangle();
        _chara2->setLocalZOrder(0);
        _chara1->setLocalZOrder(1);
        _chara2switchPressed = _switchPressed;
        _charaswitchPressed = _chara2switchPressed;
        _switchPressed = _chara1switchPressed;
    }

}