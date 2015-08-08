//
//  Audio.h
//  DollEngine
//
//  Created by DollStudio on 15/8/2.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__Audio__
#define __DollEngine__Audio__

#include "Timer.h"

DE_BEGIN

struct AudioFadeData
{
    bool autorelease;
    float time;
    float start;
    float end;
};

class Audio :public Timer
{
public:
    Audio();
    ~Audio();
    virtual bool preload(const string& path);
    void play(bool isloop,bool isfade);
    void switchAudio(bool isfade);
    void stop(bool isfade);
    void fadeTo(float vol);
    void pause();
    void resume();
    void update();
    PROPERTY(float, Pan, m_pan);
    PROPERTY(bool, Loop, m_loop);
    PROPERTY_RO(bool, Playing, m_playing);
    PROPERTY(float, Volume, m_volume);
    PROPERTY(float, FadeTime, m_fadeTime){m_fadeTime=v;}
protected:
    void* m_player;
    void* m_prePlayer;
    map<void*,AudioFadeData> m_fadeData;
};

DE_END

#endif /* defined(__DollEngine__Audio__) */
