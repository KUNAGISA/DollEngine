//
//  TjsAudio.h
//  DollEngine
//
//  Created by DollStudio on 15/8/2.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__TjsAudio__
#define __DollEngine__TjsAudio__

#include "TjsCOM.h"
#include "Audio.h"

TJS_NCB(Audio){}

bool preload(tTJSVariant v){
    TJS_STRING(v, str);
    return Audio::preload(str);
}
};

#endif /* defined(__DollEngine__TjsAudio__) */
