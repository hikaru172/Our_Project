#include "cocos2d.h"
#include "audio/include/AudioEngine.h"
#include <string>

class AudioManager
{
public:
    static void playBGM(const std::string&, bool);
    static void stopBGM();
    static void pauseBGM();
    static void resumeBGM();

    static void setBGMVolume(float);
    static float getBGMVolume();

    static void playSE(const std::string&);
    static void setSEVolume(float);
    static float getSEVolume();

private:
    static int _bgmId;
    static float _bgmVolume;
    static float _seVolume;
};
