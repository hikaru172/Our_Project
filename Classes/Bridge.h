#ifndef __BRIDGE_H__
#define __BRIDGE_H__

#include "cocos2d.h"

class Bridge : public cocos2d::Node {
public:
    static Bridge* create(cocos2d::Vec2, cocos2d::Vec2, std::string);

    virtual bool init(cocos2d::Vec2, cocos2d::Vec2, std::string);
};

#endif //__BRIDGE_H__