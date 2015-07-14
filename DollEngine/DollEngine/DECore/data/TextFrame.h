//
//  TextFrame.h
//  DollEngine
//
//  Created by DollStudio on 15/5/16.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__TextFrame__
#define __DollEngine__TextFrame__

#include "SpriteFrame.h"
#include "FontCache.h"

DE_BEGIN

class TextFrame : public SpriteFrame
{
public:
    TextFrame();
    ~TextFrame();
    PROPERTY(FontData*, Font, m_font){m_font=v;}
};

DE_END

#endif /* defined(__DollEngine__TextFrame__) */
