//
//  de-types.h
//  DollEngine
//
//  Created by DollStudio on 15/2/13.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#ifndef DollEngine_de_types_h
#define DollEngine_de_types_h


#include "de-macros.h"


struct DERect
{
    DERect():left(0),top(0),width(0),height(0){}
    DERect(float x,float y,float w,float h):left(x),top(y),width(w),height(h){}
    float left;
    float top;
    float width;
    float height;
};

#endif
