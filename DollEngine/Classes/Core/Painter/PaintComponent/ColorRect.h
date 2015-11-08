//
//  ColorRect.h
//  DollEngine
//
//  Created by DollStudio on 15/4/26.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__ColorRect__
#define __DollEngine__ColorRect__

#include "Image.h"

DE_BEGIN

class ColorRect : public Image
{
public:
    ColorRect();
    virtual ~ColorRect();
public:
    bool loadSize(int w,int h,int r);
    
    PROPERTY(int,R,m_r);
};

DE_END

#endif /* defined(__DollEngine__ColorRect__) */
