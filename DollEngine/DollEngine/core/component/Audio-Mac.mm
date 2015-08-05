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
    AVAudioPlayer* player=nil;
    if (m_fadeTime < 1/60.0f) {
        isfade = false;
    }
    if (m_prePlayer) {
        //当存在prePlayer的时候说明这时候是切换声音
        stop(isfade);
        m_player = m_prePlayer;
        m_prePlayer = null;
    }
    setEnabled(false);
    m_fadeData.clear();
    if (m_player) {
        player = (__bridge AVAudioPlayer*)m_player;
        setLoop(isloop);
        setPan(m_pan);
        if(isfade) {
            AudioFadeData config;
            config.time = m_fadeTime;
            config.startTime = -1;
            config.start = 0;
            config.end = m_volume;
            config.autorelease = false;
            player.volume = 0;
            [player play];
            m_fadeData[m_player] = config;
            setEnabled(true);
        }
        else {
            player.volume = m_volume;
            [player play];
            setEnabled(false);
        }
        m_playing = true;
    }
    else {
        Debug::throwMsg("音频文件未加载");
        m_playing = false;
    }
}

void Audio::stop(bool isfade)
{
    if (m_fadeTime < 1/60.0f) {
        isfade = false;
    }
    setEnabled(false);
    m_fadeData.clear();
    AVAudioPlayer* player=nil;
    if (m_player) {
        player = (__bridge AVAudioPlayer*)m_player;
        if(isfade) {
            AudioFadeData config;
            config.time = m_fadeTime;
            config.startTime = -1;
            config.start = player.volume*100;
            config.end = 0;
            config.autorelease = true;
            m_fadeData[m_player] = config;
            setEnabled(true);
        }
        else {
            [player stop];
            [s_AVAPlayers removeObject:player];
            setEnabled(false);
        }
        m_player = null;
    }
    m_playing = false;
}

void Audio::fadeTo(float vol)
{
    setEnabled(false);
    m_fadeData.clear();
    if (m_player) {
        AudioFadeData config;
        config.time = m_fadeTime;
        config.startTime = -1;
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