//
//  FadeTo.cpp
//  DollEngine
//
//  Created by DollStudio on 15/1/18.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "FadeTo.h"

void FadeTo::update()
{
    if (getTarget())
    {
        getTarget()->setOpacity(_Lerp(m_beginOpacity,m_endOpacity));
    }
}