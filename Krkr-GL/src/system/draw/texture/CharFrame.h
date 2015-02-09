//
//  CharFrame.h
//  DollEngine
//
//  Created by DollStudio on 14/12/19.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__CharFrame__
#define __DollEngine__CharFrame__

#include "SpriteFrame.h"


class CharFrame:public SpriteFrame
{
public:
    CharFrame();
    ~CharFrame();
    bool initWithConfig(const wstring& str,const wstring& fontName,float fontSize,float outlineSize=0);
    
    static wstring CreateKey(const wstring& str,const wstring& fontName,float fontSize,float outlineSize);
    //    PROPERTY(unsigned char*, Buffer, m_buffer){m_buffer=v;}//图片的数据
    //    PROPERTY(int, Width, m_width){m_width=v;}//图片的宽高
    //    PROPERTY(int, Height, m_height){m_height=v;}
    
    PROPERTY(int, XMin, m_xMin){m_xMin=v;}//左右宽高与orgin的偏移量
    PROPERTY(int, XMax, m_xMax){m_xMax=v;}
    PROPERTY(int, YMin, m_yMin){m_yMin=v;}
    PROPERTY(int, YMax, m_yMax){m_yMax=v;}
    
    PROPERTY(int, Advance, m_advance){m_advance=v;}//字间距
    
    PROPERTY(int, BearingX, m_bearingX){m_bearingX=v;}//图片应该的orgin偏移量
    PROPERTY(int, BearingY, m_bearingY){m_bearingY=v;}
    
    PROPERTY(float , OutlineSize, m_outlineSize){m_outlineSize=v;}
    
};


#endif /* defined(__DollEngine__CharFrame__) */
