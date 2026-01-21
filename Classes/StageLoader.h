#ifndef __STAGE_LOADER_H__
#define __STAGE_LOADER_H__

#include "cocos2d.h"

class StageLoader
{
public:
    static void load(const std::string& jsonFile, cocos2d::Node* stageRoot);
};

#endif //__STAGE_LOADER__