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
    TJS_FACTORY
    NCB_METHOD(preload);
    NCB_METHOD(play);
    NCB_METHOD(pause);
    NCB_METHOD(resume);
    NCB_METHOD(stop);
    NCB_PROPERTY(loop, getLoop, setLoop);
    NCB_PROPERTY(volume, getVolume, setVolume);
};
