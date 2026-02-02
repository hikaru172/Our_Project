#ifndef __GOALFLAG_H__
#define __GOALFLAG_H__

#include "cocos2d.h" 

class GoalFlag : public cocos2d::Sprite {
public:

    static GoalFlag* create(cocos2d::Vec2, std::string);

    virtual bool init(cocos2d::Vec2, std::string);

    void getFlag(int, cocos2d::Node*);

};

#endif //__GOALFLAG_H__