#ifndef __LADDER_H__
#define __LADDER_H__

#include "cocos2d.h"

class Ladder : public cocos2d::Node {
public:
    static Ladder* create(cocos2d::Vec2, cocos2d::Vec2, std::string);

    virtual bool init(cocos2d::Vec2, cocos2d::Vec2, std::string);
};

#endif //__LADDER_H__