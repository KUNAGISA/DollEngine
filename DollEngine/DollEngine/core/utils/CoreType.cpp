//
//  CoreType.cpp
//  DollEngine
//
//  Created by DollStudio on 15/4/13.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "CoreType.h"

DE_BEGIN

static Rect s_rect_zero = Rect(0,0,0,0);

Rect::Rect(float x,float y,float w,float h)
{
    set(x,y,w,h);
}

void Rect::set(float x,float y,float w,float h)
{
    this->x = x;
    this->y = y;
    this->width = w;
    this->height = h;
}

const Rect& Rect::Zero()
{
    return s_rect_zero;
}

GradientColor::GradientColor()
{
    begin = 0xffffffff;
    end = begin;
}

DE_END
