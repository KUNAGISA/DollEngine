//
//  Audio.cpp
//  DollEngine
//
//  Created by DollStudio on 15/8/2.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include <AVFoundation/AVFoundation.h>
#include "Audio.h"
#include "Storages.h"

DE_BEGIN

static NSMutableSet* s_AVAPlayers = [[NSMutableSet alloc]init];

Audio::Audio()
:m_loop(false)
,m_player(null)
,m_playing(false)
,m_volume(100)
,m_prePlayer(null)
,m_fadeTime(0.5f)
,m_pan(0)
{
    setCompName("Audio");
    setType(COMP_UPDATE);
    setEnabled(false);
}

Audio::~Audio()
{
    if (m_player) {
        AVAudioPlayer* player = (__bridge AVAudioPlayer*)m_player;
        [player stop];
        [s_AVAPlayers removeObject:player];
    }
    if (m_prePlayer) {
        AVAudioPlayer* player = (__bridge AVAudioPlayer*)m_prePlayer;
        [player stop];
        [s_AVAPlayers removeObject:player];
    }
}

bool Audio::preload(const string &path)
{
    string fullpath = Storages::GetInstance()->getFullPath(path);
    if (fullpath == "") {
        return false;
    }
    AVAudioPlayer* player=nil;
    if (m_prePlayer) {
        player = (__bridge AVAudioPlayer*)m_prePlayer;
        [s_AVAPlayers removeObject:player];
        m_prePlayer = null;
    }
    player = [[AVAudioPlayer alloc]initWithContentsOfURL:[NSURL URLWithString:[NSString stringWithUTF8String:fullpath.c_str()]] error:nil];
    if (player) {
        [player prepareToPlay];
        [player stop];
        m_prePlayer = (__bridge void*)player;
        [s_AVAPlayers addObject:player];
        return true;
    }
    else {
        return false;
    }
}

void Audio::update()
{
    map<void*,AudioFadeData> tmp = m_fadeData;
    for (auto iter = tmp.begin();
         iter != tmp.end(); ++iter)
    {
        AudioFadeData& data = iter->second;
        AVAudioPlayer* player=(__bridge AVAudioPlayer*)iter->first;
        float dt = getTime()/data.time;
        bool isrelease = false;
        if (dt >= 1) {
            dt = 1;
            if (data.autorelease == true) {
                isrelease = true;
            }
        }
        float v = (data.end-data.start)*dt + data.start;
        player.volume = v/100;
        if(isrelease){
            [player stop];
            [s_AVAPlayers removeObject:player];
            m_fadeData.erase(iter->first);
        }
    }
    if (m_fadeData.size() == 0) {
        setEnabled(false);
    }
}

void Audio::play(bool isloop, bool isfade)
{
    switchAudio(isfade);
    setLoop(isloop);
    setPan(m_pan);
    m_playing = true;
}

void Audio::switchAudio(bool isfade)
{
    if (m_fadeTime < 1/60.0f) {
        isfade = false;
    }
    if (m_fadeData.size() > 0) {
        for (auto iter = m_fadeData.begin();
             iter != m_fadeData.end(); ++iter)
        {
            AVAudioPlayer* audio = (__bridge AVAudioPlayer*)iter->first;
            [audio stop];
            if (m_player != iter->first && m_prePlayer != iter->first) {
                [s_AVAPlayers removeObject:audio];
            }
        }
        m_fadeData.clear();
        setEnabled(false);
    }
    
    AVAudioPlayer* audioIn=(__bridge AVAudioPlayer*)m_prePlayer;
    AVAudioPlayer* audioOut=(__bridge AVAudioPlayer*)m_player;
    if (isfade) {
        if (m_prePlayer) {
            AudioFadeData cfgin;
            cfgin.autorelease = false;
            cfgin.time = m_fadeTime;
            cfgin.start = 0;
            cfgin.end = m_volume;
            audioIn.volume = 0;
            [audioIn play];
            m_fadeData[m_prePlayer] = cfgin;
        }
        if (m_player) {
            AudioFadeData cfgout;
            cfgout.autorelease = true;
            cfgout.time = m_fadeTime;
            cfgout.start = audioOut.volume*100;
            cfgout.end = 0;
            m_fadeData[m_player] = cfgout;
        }
        m_player = m_prePlayer;
        m_prePlayer = null;
        setEnabled(true);
    }
    else {
        if (m_player) {
            [audioOut stop];
            [s_AVAPlayers removeObject:audioOut];
        }
        if (m_prePlayer) {
            audioIn.volume = m_volume/100;
            [audioIn play];
        }
        m_player = m_prePlayer;
        m_prePlayer = null;
    }
}

void Audio::stop(bool isfade)
{
    if (m_fadeTime < 1/60.0f) {
        isfade = false;
    }
    AVAudioPlayer* audioIn=(__bridge AVAudioPlayer*)m_prePlayer;
    [s_AVAPlayers removeObject:audioIn];
    switchAudio(isfade);
    m_playing = false;
}

void Audio::fadeTo(float vol)
{
    setEnabled(false);
    m_fadeData.clear();
    if (m_player) {
        AudioFadeData config;
        config.time = m_fadeTime;
        config.start = m_volume;
        config.end = vol;
        config.autorelease = false;
        m_fadeData[m_player] = config;
        setEnabled(true);
        m_volume = vol;
    }
}

void Audio::pause()
{
    if (m_player) {
        AVAudioPlayer* player= (__bridge AVAudioPlayer*)m_player;
        [player pause];
        m_playing = false;
    }
}

void Audio::resume()
{
    if (m_player) {
        AVAudioPlayer* player= (__bridge AVAudioPlayer*)m_player;
        [player play];
        m_playing = true;
    }
}

void Audio::setLoop(bool v)
{
    m_loop = v;
    if (m_player) {
        AVAudioPlayer* player= (__bridge AVAudioPlayer*)m_player;
        player.numberOfLoops = v?-1:0;
    }
}

void Audio::setVolume(float v)
{
    m_volume = v;
    if (m_player) {
        AVAudioPlayer* player= (__bridge AVAudioPlayer*)m_player;
        player.volume = v/100;
    }
}

void Audio::setPan(float v)
{
    m_pan = v;
    if (m_player) {
        AVAudioPlayer* player= (__bridge AVAudioPlayer*)m_player;
        player.pan = v;
    }
}

DE_END