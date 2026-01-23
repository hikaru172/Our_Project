#ifndef __PAUSE_LAYER_H__
#define __PAUSE_LAYER_H__

#include "cocos2d.h"

class PauseLayer : public cocos2d::Layer
{
public:

    CREATE_FUNC(PauseLayer);
    virtual bool init();

    //引数(cocos2d::Ref*型)を持たせないと、関数をMenuItemSprite::create()の引数にできない
    void onResumeButtonPressed(cocos2d::Ref*);
    void onTitleButtonPressed(cocos2d::Ref*);
    void onStageButtonPressed(cocos2d::Ref*);
};

#endif //__PAUSE_LAYER_H__