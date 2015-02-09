//
//  FadeTo.h
//  Krkr_GL
//
//  Created by DollStudio on 15/1/18.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __Krkr_GL__FadeTo__
#define __Krkr_GL__FadeTo__

#include "Action.h"

class FadeTo: public Action
{
public:
    virtual void update();
    PROPERTY(float, BeginOpacity, m_beginOpacity){m_beginOpacity=v;}
    PROPERTY(float, EndOpacity, m_endOpacity){m_endOpacity=v;}
};

#endif /* defined(__Krkr_GL__FadeTo__) */
