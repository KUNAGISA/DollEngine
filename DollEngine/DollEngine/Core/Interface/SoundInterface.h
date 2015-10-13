//
//  SoundInterface.h
//  DollEngine
//
//  Created by DollStudio on 15/10/13.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__SoundInterface__
#define __DollEngine__SoundInterface__

#include "CoreUnits.h"

DE_BEGIN

class SoundInterface
{
public:
    Shared(SoundInterface)
    int preloadSound(const String& path);//加载成功返回soundID
    void play(int bufId,int playId, int fadeTime=0);
    void stop(int bufId);
    void fadeTo(int bufId, int start,int end);
    
};

DE_END

#endif /* defined(__DollEngine__SoundInterface__) */
