#ifndef __CLEAR_LAYER_H__
#define __CLEAR_LAYER_H__

#include "cocos2d.h"

class ClearLayer : public cocos2d::Layer
{
public:

	static ClearLayer* createLayer(int, float);
	
	virtual bool init(int, float);

	int _StageNumber = 0;

	void onRepeatButtonPressed(cocos2d::Ref*);
	void onNextButtonPressed(cocos2d::Ref*);
	void onStageButtonPressed(cocos2d::Ref*);
};

#endif //__PAUSE_LAYER_H__