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

@interface AudioPlayer : NSObject

@property (nonatomic)  double fadeTime;
@property (nonatomic)  BOOL loop;
@property (nonatomic)  float volume;

@end

@implementation AudioPlayer
{
    AVAudioPlayer* fore;
    AVAudioPlayer* back;
    NSTimer* fadeTimer;
    
    double startFadeTime;
    float foreStartVolume;
    float foreEndVolume;
    float backStartVolume;
    float backEndVolume;
    BOOL isfading;
}

-(void)setVolume:(float)volume
{
    _volume = volume;
    if (fore) {
        fore.volume = volume;
    }
}

-(void)setLoop:(BOOL)loop
{
    _loop = loop;
    if (fore) {
        fore.numberOfLoops = loop?-1:0;
    }
}

-(BOOL)preload:(NSString*)path
{
    if (back) {
        [back stop];
    }
    DE::String fullpath = DE::Storages::GetInstance()->getFullPath(path.UTF8String);
    if (fullpath.empty()) {
        return NO;
    }
    NSString* url = [NSString stringWithUTF8String:fullpath.c_nstr()];
    //printf("%s\n",fullpath.c_str());
    NSError  *error;
    back = [[AVAudioPlayer alloc]initWithContentsOfURL:[NSURL URLWithString:url] error:&error];
    [back prepareToPlay];
    return NO;
}

-(void)play:(BOOL)isfade
{
    if(fadeTimer){
        [fadeTimer invalidate];
        fadeTimer = nil;
        isfading = NO;
        //printf("[play]isfading=false\n");
    }
    AVAudioPlayer * old = fore;
    fore = back;
    back = old;
    if(isfade){
        if(fore){
            fore.volume = 0;
            [fore play];
            foreStartVolume = 0;
            foreEndVolume = self.volume;
        }
        if(back){
            backStartVolume = back.volume;
            backEndVolume = 0;
        }
        if (fore||back) {
            fadeTimer = [NSTimer scheduledTimerWithTimeInterval:(1/60.0f) target:self selector:@selector(audioFade) userInfo:nil repeats:YES];
            isfading = YES;
            startFadeTime = DE::GetSeconds();
            //printf("[play]isfading=true\n");
        }
    }
    else {
        if (fore) {
            fore.volume = self.volume;
            [fore play];
        }
        if(back){
            [back stop];
            back = nil;
        }
    }
    [self setLoop:self.loop];
}

-(void)stop:(BOOL)isfade
{
    if(fadeTimer){
        [fadeTimer invalidate];
        fadeTimer = nil;
        isfading = NO;
        //printf("[stop]isfading=false\n");
    }
    if (!isfade) {
        if (fore) {
            [fore stop];
        }
        if (back) {
            [back stop];
        }
    }
    else {
        if (fore) {
            foreStartVolume = fore.volume;
            foreEndVolume = 0;
        }
        if(back){
            backStartVolume = back.volume;
            backEndVolume = 0;
        }
        if (fore || back) {
            fadeTimer = [NSTimer scheduledTimerWithTimeInterval:(1/60.0f) target:self selector:@selector(audioFade) userInfo:nil repeats:YES];
            isfading = YES;
            startFadeTime = DE::GetSeconds();
            //printf("[stop]isfading=true\n");
        }
    }
}

-(void)audioFade
{
    double cur = DE::GetSeconds();
    double dt = cur - startFadeTime;
    double p = dt/self.fadeTime;
    if (fore) {
        float v =(foreEndVolume-foreStartVolume)*p+foreStartVolume;
        fore.volume = v;
    }
    if (back) {
        back.volume = (backEndVolume-backStartVolume)*p+backStartVolume;
    }
    if (p>=1) {
        [fadeTimer invalidate];
        if(back){
            [back stop];
            back = nil;
        }
        isfading = NO;
        //printf("[update]isfading=false\n");
    }
}

-(void)dealloc
{
    [self stop:NO];
    fore = nil;
    back = nil;
    //printf("player dealloc\n");
}

@end

DE_BEGIN

static NSMutableSet* s_AVAPlayers = [[NSMutableSet alloc]init];

Audio::Audio()
:m_player(null)
{
    AudioPlayer* player = [[AudioPlayer alloc]init];
    m_player = (__bridge void*)player;
    [s_AVAPlayers addObject:player];
    setFadeTime(0.5f);
    setVolume(100);
    setLoop(false);
}

Audio::~Audio()
{
    if (m_player) {
        AudioPlayer* player = (__bridge AudioPlayer*)m_player;
        [player stop:NO];
        [s_AVAPlayers removeObject:player];
    }
}

bool Audio::preload(const String& path)
{
    AudioPlayer* player = (__bridge AudioPlayer*)m_player;
    BOOL ret = [player preload:[NSString stringWithUTF8String:path.c_nstr()]];
    return ret;
}

void Audio::play(bool isloop, bool isfade)
{
    AudioPlayer* player = (__bridge AudioPlayer*)m_player;
    setLoop(isloop);
    [player play:isfade];
}

void Audio::stop(bool isfade)
{
    AudioPlayer* player = (__bridge AudioPlayer*)m_player;
    [player stop:isfade];
}

void Audio::setLoop(bool v)
{
    m_loop = v;
    AudioPlayer* player = (__bridge AudioPlayer*)m_player;
    player.loop = v;
}

void Audio::setVolume(float v)
{
    m_volume = v;
    AudioPlayer* player = (__bridge AudioPlayer*)m_player;
    player.volume = v/100;
}

void Audio::setFadeTime(float v)
{
    m_fadeTime = v;
    AudioPlayer* player = (__bridge AudioPlayer*)m_player;
    player.fadeTime = v;
}

DE_END