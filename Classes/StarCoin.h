#ifndef __STAR_H__
#define __STAR_H__

#include "cocos2d.h" 

class StarCoin : public cocos2d::Sprite {
public:

    static StarCoin* create(cocos2d::Vec2, std::string);

    virtual bool init(cocos2d::Vec2, std::string);

    void getStar();
    bool getHold();

    bool _holdStar = false;

};

#endif //__Star_H__