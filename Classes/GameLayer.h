#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h" 
#include "Character.h"
#include "Switch.h"
#include "Block.h"

class GameLayer : public cocos2d::Layer {
public:
    //CREATE_FUNCマクロはcreate()に引数を持たせられないので自分で定義
    static GameLayer* createLayer(int);

    virtual bool init(int);

    void update(float);

    void chara_change();

    void setupStage(); // ステージ初期化用

    int getStagenumber();
    float getSumtime();
    bool getStar();

    float _sumTime = 0.0f; // クリアタイム用

    Character* _chara;
    Character* _other;
    Character* _chara1;
    Character* _chara2;

    std::vector<Switch*> _switch;
    std::vector<Block*> _block;

    std::vector<kind_of> _on_switch_kind;

    Node* _stageRoot;

    std::vector<EventKeyboard::KeyCode> _currentKey;
    CharacterInput _input;

private:

    int _stageNumber;

    bool _callstop;
    bool _chara_dead = false;

    bool _leftPressed = false;
    bool _rightPressed = false;
    bool _upPressed = false;
    bool _downPressed = false;
    bool _jumpPressed = false;

    bool _switchPressed = false;

    bool _charafixed = false;
    bool _chara1fixed = false;
    bool _chara2fixed = false;

    bool _charaswitchPressed = false;
    bool _chara1switchPressed = false;
    bool _chara2switchPressed = false;

    bool _pause = false;

    float _diff = 0.0f;
    float _total = 0.0f;
    float _total1 = 0.0f;
    float _total2 = 0.0f;

    bool _isStar = false;

    float _end_point = 0.0f;
};

#endif //__GAME_LAYER_H__