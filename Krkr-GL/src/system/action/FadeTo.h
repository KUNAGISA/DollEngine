//
//  FadeTo.h
//  DollEngine
//
//  Created by DollStudio on 15/1/18.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__FadeTo__
#define __DollEngine__FadeTo__

#include "Action.h"

class FadeTo: public Action
{
public:
    virtual void update();
    PROPERTY(float, BeginOpacity, m_beginOpacity){m_beginOpacity=v;}
    PROPERTY(float, EndOpacity, m_endOpacity){m_endOpacity=v;}
};

#endif /* defined(__DollEngine__FadeTo__) */
