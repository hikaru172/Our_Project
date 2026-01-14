#ifndef __PAUSE_LAYER_H__
#define __PAUSE_LAYER_H__

#include "cocos2d.h"

class PauseLayer : public cocos2d::Layer
{
public:

    CREATE_FUNC(PauseLayer);
    virtual bool init();

    //ˆø”‚Écocos2d::Ref*‚ğ‚½‚¹‚È‚¢‚ÆAŠÖ”‚ğMenuItemSprite::create()‚Ìˆø”‚É‚Å‚«‚È‚¢
    void onResumeButtonPressed(cocos2d::Ref*);
    void onTitleButtonPressed(cocos2d::Ref*);
    void onStageButtonPressed(cocos2d::Ref*);
};

#endif //__PAUSE_LAYER_H__