//
//  CoreType.h
//  DollEngine
//
//  Created by DollStudio on 15/4/13.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__CoreType__
#define __DollEngine__CoreType__

#include "Macros.h"


DE_BEGIN

class Rect
{
public:
    Rect(float x,float y,float w,float h);
    void set(float x,float y,float w,float h);
    static const Rect& Zero();
    
    
    float x;
    float y;
    float width;
    float height;
};

class GradientColor
{
public:
    GradientColor();
    
    uint32_t begin;
    uint32_t end;
};


DE_END


#endif /* defined(__DollEngine__CoreType__) */
