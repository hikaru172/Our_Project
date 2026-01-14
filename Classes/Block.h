#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "cocos2d.h" 
#include "Switch.h"

class Block : public cocos2d::Sprite {
public:
    static Block* create(cocos2d::Vec2, cocos2d::Vec2, std::string);

    virtual bool init(cocos2d::Vec2, cocos2d::Vec2, std::string);

    void setState(State state);

    kind_of get_kind();

private:
    State _state2 = State::Off;
    kind_of _kind2 = kind_of::Normal;
    float _Xamount = 0.0f;
    float _Yamount = 0.0f;
};

#endif //__BLOCK_H__