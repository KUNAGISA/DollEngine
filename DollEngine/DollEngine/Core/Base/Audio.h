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
    void fadeTo(float dut,int tarVol);
public:
    bool getPlaying();
    PROPERTY(int, Loop, m_loop);
    PROPERTY(float, Volume, m_volume);
    PROPERTY(bool, Muted,m_muted);
    PROPERTY(int, Position,m_position);
public:
    virtual void onMutedChanged(bool v);
    virtual void onVolumeChanged(bool v);
    virtual void onPositionChanged(int v);
    virtual void onPause();
    virtual void onResume();
    virtual void onPlay();
    virtual void onStop();
protected:
    void* m_object;
    void* m_fadeTimerLine;
    String m_fullPath;
};

DE_END

#endif // AUDIO_H
