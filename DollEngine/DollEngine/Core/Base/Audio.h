#ifndef AUDIO_H
#define AUDIO_H

#include "CoreUnits.h"


DE_BEGIN

class Audio
{
public:
    Audio();
    ~Audio();
    
    bool preload(const String& path);
    void play(bool isloop,int fadeMS);
    void stop(int fadeMS);
    void pause();
    void resume();
    void fadeTo(int tarVol);
public:
    bool getPlaying();
    PROPERTY(bool, Loop, m_loop);
    PROPERTY(float, Volume, m_volume);
    PROPERTY(bool, Muted,m_muted);
    
public:
    virtual void onMutedChanged(bool v);
protected:
    void* m_object;
};

DE_END

#endif // AUDIO_H
