#include "StageLoader.h"
#include "json/document.h"
#include "platform/CCFileUtils.h"

#include "Platform.h"
#include "Block.h"
#include "Switch.h"
#include "Ladder.h"
#include "GoalFlag.h"
#include "Water.h"
#include "Bridge.h"
#include "StarCoin.h"

USING_NS_CC;
using namespace rapidjson;

void StageLoader::load(const std::string& jsonFile, Node* stageRoot)
{
    //FileUtils内のgetStringFromFile()メソッドにより、jsonファイル全体を 1つの文字列にする
    std::string jsonStr = FileUtils::getInstance()->getStringFromFile(jsonFile);

    Document doc; //docは親子関係の一番上にあるrootノード
    doc.Parse(jsonStr.c_str()); //メモリ上にノードを生成し、親子関係を構築

    if (!doc.IsObject() || !doc.HasMember("objects"))
        return;

    //JSONオブジェクトの中から"objects" というキーを持つValue(jsonの一要素)への参照
    // []はキーを持つValueを指す
    //参照(&)は別名をつけるだけで中身はそのもの
    const auto& objects = doc["objects"];
    for (auto& obj : objects.GetArray()) //objects配列内のオブジェクトを1つずつ参照
    {
        std::string type = obj["type"].GetString();
        std::string image = obj["image"].GetString();

        if (type == "Water") {
            Vec2 start(
                obj["start"][0].GetFloat(),
                obj["start"][1].GetFloat()
            );
            Vec2 end(
                obj["end"][0].GetFloat(),
                obj["end"][1].GetFloat()
            );

            auto water = Water::create(start, end, image);
            stageRoot->addChild(water);
        }
        else if (type == "Platform")
        {
            Vec2 start(
                obj["start"][0].GetFloat(),
                obj["start"][1].GetFloat()
            );
            Vec2 end(
                obj["end"][0].GetFloat(),
                obj["end"][1].GetFloat()
            );

            auto platform = Platform::create(start, end, image);
            stageRoot->addChild(platform);
        }
        else if (type == "Block")
        {
            Vec2 start(
                obj["start"][0].GetFloat(),
                obj["start"][1].GetFloat()
            );
            Vec2 end(
                obj["end"][0].GetFloat(),
                obj["end"][1].GetFloat()
            );

            auto block = Block::create(start, end, image);
            stageRoot->addChild(block);
        }
        else if (type == "Switch")
        {
            Vec2 pos(
                obj["position"][0].GetFloat(),
                obj["position"][1].GetFloat()
            );

            auto Switch = Switch::create(pos, image);
            stageRoot->addChild(Switch);
        }
        else if (type == "Ladder")
        {
            Vec2 start(
                obj["start"][0].GetFloat(),
                obj["start"][1].GetFloat()
            );
            Vec2 end(
                obj["end"][0].GetFloat(),
                obj["end"][1].GetFloat()
            );

            auto ladder = Ladder::create(start, end, image);
            stageRoot->addChild(ladder);
        }
        else if (type == "GoalFlag")
        {
            Vec2 pos(
                obj["position"][0].GetFloat(),
                obj["position"][1].GetFloat()
            );

            auto flag = GoalFlag::create(pos, image);
            stageRoot->addChild(flag);
        }
        else if (type == "Bridge")
        {
            Vec2 start(
                obj["start"][0].GetFloat(),
                obj["start"][1].GetFloat()
            );
            Vec2 end(
                obj["end"][0].GetFloat(),
                obj["end"][1].GetFloat()
            );

            auto Bridge = Bridge::create(start, end, image);
            stageRoot->addChild(Bridge);
        }
        else if (type == "StarCoin")
        {
            Vec2 pos(
                obj["position"][0].GetFloat(),
                obj["position"][1].GetFloat()
            );

            auto star = StarCoin::create(pos, image);
            stageRoot->addChild(star);
        }
    }
}

float StageLoader::timeload(const std::string& jsonFile) {
    std::string jsonStr = FileUtils::getInstance()->getStringFromFile(jsonFile);

    Document doc; //docは親子関係の一番上にあるrootノード
    doc.Parse(jsonStr.c_str()); //メモリ上にノードを生成し、親子関係を構築

    float clearTime = 0.0f;

    if (doc.HasMember("clear_time") && doc["clear_time"].IsNumber())
    {
        clearTime = doc["clear_time"].GetFloat();
    }
    return clearTime;
}

float StageLoader::endload(const std::string& jsonFile) {
    std::string jsonStr = FileUtils::getInstance()->getStringFromFile(jsonFile);

    Document doc;
    doc.Parse(jsonStr.c_str());

    float endpoint = 0.0f;

    if (doc.HasMember("end_point") && doc["end_point"].IsNumber())
    {
        endpoint = doc["end_point"].GetFloat();
    }
    return endpoint;
}
