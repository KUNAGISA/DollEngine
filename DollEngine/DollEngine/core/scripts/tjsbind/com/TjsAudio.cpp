//
//  TjsAudio.cpp
//  DollEngine
//
//  Created by DollStudio on 15/8/2.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "TjsAudio.h"

NCB_REGISTER_CLASS_DIFFER(Audio, TjsAudio)
{
    TJS_FACTORY_COM
    NCB_METHOD(preload);
    NCB_METHOD(play);
    NCB_METHOD(stop);
    NCB_METHOD(fadeTo);
    NCB_METHOD(pause);
    NCB_METHOD(resume);
    NCB_PROPERTY(loop, getLoop, setLoop);
    NCB_PROPERTY(pan, getPan, setPan);
    NCB_PROPERTY(volume, getVolume, setVolume);
    NCB_PROPERTY(fadeTime, getFadeTime, setFadeTime);
    NCB_PROPERTY_RO(playing, getPlaying);
};
