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

class Audio
{
public:
    Audio();
    ~Audio();
    virtual bool preload(const String& path);
    void play(bool isloop,bool isfade);
    void stop(bool isfade);
    PROPERTY(bool, Loop, m_loop);
    PROPERTY(float, Volume, m_volume);
    PROPERTY(float, FadeTime, m_fadeTime);
protected:
    void* m_player;
};

DE_END

#endif /* defined(__DollEngine__Audio__) */
