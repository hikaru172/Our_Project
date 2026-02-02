#include "AudioManager.h"

USING_NS_CC;

int AudioManager::_bgmId = AudioEngine::INVALID_AUDIO_ID; 
float AudioManager::_bgmVolume = 0.5f;
float AudioManager::_seVolume = 0.5f;

void AudioManager::playBGM(const std::string& file, bool loop)
{

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
void AudioManager::playSE(const std::string& file){
    AudioEngine::play2d(file, false, _seVolume);
}

void AudioManager::setSEVolume(float volume)
{
    //AudioEngine::setVolume(id, volume) は今流れているidの音量だけを変更するが
    //seの場合は一つ一つの音が短く、全てのse共通で音量管理したいためここでは不要
    _seVolume = volume;
}

float AudioManager::getSEVolume()
{
    return _seVolume;
}