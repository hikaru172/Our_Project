#ifndef __FAILED_LAYER_H__
#define __FAILED_LAYER_H__

#include "cocos2d.h"

class FailedLayer : public cocos2d::Layer
{
public:

	virtual bool init();

	void onRepeatButtonPressed(cocos2d::Ref*);
	void onStageButtonPressed(cocos2d::Ref*);

	CREATE_FUNC(FailedLayer);
};

#endif //__FAILED_LAYER_H__