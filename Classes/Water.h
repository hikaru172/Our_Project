#ifndef __WATER_H__
#define __WATER_H__

#include "cocos2d.h" 

class Water : public cocos2d::Node {
public:
    static Water* create(cocos2d::Vec2, cocos2d::Vec2, std::string);

    virtual bool init(cocos2d::Vec2, cocos2d::Vec2, std::string);
};

#endif //__WATER_H__