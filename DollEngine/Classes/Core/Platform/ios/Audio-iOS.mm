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
#include "System.h"

DE_BEGIN

Audio::Audio()
:m_object(NULL)
,m_fadeTimerLine(NULL)
,m_loop(false)
,m_muted(false)
,m_position(0)
,m_volume(100)
{
}

Audio::~Audio()
{
    if (m_object) {
        AVAudioPlayer* player = (__bridge AVAudioPlayer*)m_object;
        m_object=NULL;
        [player stop];
        [player release];
    }
}

bool Audio::preload(const String& path)
{
    if (path.empty()) {
        return false;
    }
    String fullPath = Storages::GetInstance()->getFullPath(path);
    if(fullPath.empty()){
        if(path.find(L'.') == String::npos) {
            fullPath = Storages::GetInstance()->getFullPath(path+L".mp3");
            if(fullPath.empty()) {
                fullPath = Storages::GetInstance()->getFullPath(path+L".wav");
                if(fullPath.empty()) {
                    EM(ERROR_FILE_NOT_EXIST,path);
                    return false;
                }
            }
        }
        else {
            EM(ERROR_FILE_NOT_EXIST,path);
            return false;
        }
    }
    if (m_object) {
        AVAudioPlayer* player = (__bridge AVAudioPlayer*)m_object;
        [player stop];
        [player release];
    }
    AVAudioPlayer* player = [[AVAudioPlayer alloc] initWithContentsOfURL:[NSURL URLWithString:[NSString stringWithUTF8String:fullPath.c_nstr()]] error:nil];
    [player stop];
    m_object = (__bridge AVAudioPlayer*)player;
    if (m_object) {
        return true;
    }
    return false;
}

void Audio::play(bool isloop,int fadeMS)
{
    AVAudioPlayer* player = (__bridge AVAudioPlayer*)m_object;
    if(!player){
        return;
    }
    setLoop(isloop);
    setMuted(m_muted);
    setVolume(m_volume);
    [player play];
}

void Audio::stop(int fadeMS)
{
    AVAudioPlayer* player = (__bridge AVAudioPlayer*)m_object;
    if(!player){
        return;
    }
    [player stop];
}

void Audio::setLoop(bool v)
{
    m_loop = v;
    AVAudioPlayer* player = (__bridge AVAudioPlayer*)m_object;
    if(!player){
        return;
    }
    if(v){
        player.numberOfLoops = -1;
    }
    else {
        player.numberOfLoops = 0;
    }
}

void Audio::setVolume(float v)
{
    m_volume = v;
    AVAudioPlayer* player = (__bridge AVAudioPlayer*)m_object;
    if(!player){
        return;
    }
    if (m_muted) {
        player.volume = 0;
    }
    else {
        player.volume = v/100;
    }
}

void Audio::setPosition(int v)
{
    m_position = v;
    AVAudioPlayer* player = (__bridge AVAudioPlayer*)m_object;
    if(!player){
        return;
    }
    player.currentTime = v;
}

void Audio::setMuted(bool v)
{
    m_muted = v;
    AVAudioPlayer* player = (__bridge AVAudioPlayer*)m_object;
    if(!player){
        return;
    }
    if (v) {
        player.volume = 0;
    }
    else {
        player.volume = m_volume/100.0f;
    }
}

void Audio::onMutedChanged(bool v)
{

}

void Audio::onVolumeChanged(bool v)
{

}

void Audio::onPositionChanged(int v)
{

}

void Audio::onPause()
{

}

void Audio::onResume()
{

}

void Audio::onPlay()
{

}

void Audio::onStop()
{

}

DE_END