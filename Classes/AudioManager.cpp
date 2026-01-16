#include "AudioManager.h"

USING_NS_CC;

int AudioManager::_bgmId = AudioEngine::INVALID_AUDIO_ID; 
float AudioManager::_bgmVolume = 0.2f;

void AudioManager::playBGM(const std::string& file, bool loop)
{

    AudioEngine::lazyInit();

    //stopやplay2dなどのメソッドを呼ぶとき、この条件を用いることで安全に管理している
    if (_bgmId != AudioEngine::INVALID_AUDIO_ID)
    {
        AudioEngine::stop(_bgmId);
        _bgmId = AudioEngine::INVALID_AUDIO_ID;
    }

    //play2d()で再生するとその再生してる音のid(int型)を返す
    //再生していない音のidはINVALID_AUDIO_IDにする
    _bgmId = AudioEngine::play2d(file, loop, _bgmVolume);
}

void AudioManager::stopBGM()
{
    if (_bgmId != AudioEngine::INVALID_AUDIO_ID)
    {
        AudioEngine::stop(_bgmId);
        _bgmId = AudioEngine::INVALID_AUDIO_ID;
    }
}

void AudioManager::pauseBGM()
{
    if (_bgmId != AudioEngine::INVALID_AUDIO_ID)
        AudioEngine::pause(_bgmId);
}

void AudioManager::resumeBGM()
{
    if (_bgmId != AudioEngine::INVALID_AUDIO_ID)
        AudioEngine::resume(_bgmId);
}

void AudioManager::setBGMVolume(float volume)
{
    _bgmVolume = volume;
    if (_bgmId != AudioEngine::INVALID_AUDIO_ID)
        AudioEngine::setVolume(_bgmId, volume);
}

float AudioManager::getBGMVolume()
{
    return _bgmVolume;
}

//SEはBGMや他SEと音が重なる可能性があるため、_bgmId!= AudioEngine::INVALID_AUDIO_ID のチェックはしていない
//もしサウンドによって必要になった時は、_seIdをメンバ変数として用意して同様に実装する
void AudioManager::playSE(const std::string& file, float volume){
    AudioEngine::play2d(file, false, volume);
}
