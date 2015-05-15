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

DE_BEGIN

class TextFrame : public SpriteFrame
{
public:
    
    PROPERTY(int, XMin, m_xMin){m_xMin=v;}//左右宽高与orgin的偏移量
    PROPERTY(int, XMax, m_xMax){m_xMax=v;}
    PROPERTY(int, YMin, m_yMin){m_yMin=v;}
    PROPERTY(int, YMax, m_yMax){m_yMax=v;}
    
    PROPERTY(int, Advance, m_advance){m_advance=v;}//字间距
    
    PROPERTY(int, BearingX, m_bearingX){m_bearingX=v;}//图片应该的orgin偏移量
    PROPERTY(int, BearingY, m_bearingY){m_bearingY=v;}
    
    PROPERTY(float , OutlineSize, m_outlineSize){m_outlineSize=v;}
};

DE_END

#endif /* defined(__DollEngine__TextFrame__) */
