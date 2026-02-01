#ifndef __STAGE_LOADER_H__
#define __STAGE_LOADER_H__

#include "cocos2d.h"

class StageLoader
{
public:
    static void load(const std::string& jsonFile, cocos2d::Node* stageRoot);
    static float timeload(const std::string& jsonFile);
};

#endif //__STAGE_LOADER__