//
//  de-painter-paint.h
//  DollEngine
//
//  Created by DollStudio on 15/2/23.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#ifndef __DollEngine__de_painter_paint__
#define __DollEngine__de_painter_paint__

#include "de-functions.h"

NAMESPACE_DE_PAINTER

class SpriteFrame;
class ShaderProgram;
class Transform;
class Paint
{
public:
    Paint();
    virtual ~Paint();
    bool colorRect(int r);
    bool loadImages(const wstring& path);
    void freeImages();
    void trigger();
    PROPERTY(float, ImageWidth, m_imageWidth){m_imageWidth=fmaxf(0,v);}
    PROPERTY(float, ImageHeight, m_imageHeight){m_imageHeight=fmaxf(0,v);}
    PROPERTY(float, Opacity, m_opacity){m_opacity=fminf(1,fmaxf(0,v));}
    PROPERTY(SpriteFrame*, SpriteFrame, m_spriteFrame){m_spriteFrame=v;}
    PROPERTY_CONST(wstring, GraphPath, m_graphPath){m_graphPath=v;}
    PROPERTY(ShaderProgram*, Program, m_program){m_program=v;}
    PROPERTY(bool,Scale9, m_scale9 );
    PROPERTY(float, LeftInside, m_leftInside){m_leftInside=v;}
    PROPERTY(float, TopInside, m_topInside){m_topInside=v;}
    PROPERTY(float, RightInside, m_rightInside){m_rightInside=v;}
    PROPERTY(float, BottomInside, m_bottomInside){m_bottomInside=v;}
protected:
    SpriteFrame* m_scale9Frame[9];
    Transform* m_scale9Trans[9];
    
};

NAMESPACE_DE_END2

#endif /* defined(__DollEngine__de_painter_paint__) */
