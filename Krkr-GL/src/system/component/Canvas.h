//
//  Canvas.h
//  DollEngine
//
//  Created by DollStudio on 14/11/23.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__Canvas__
#define __DollEngine__Canvas__

#include "COM.h"
#include "ShaderProgram.h"
#include "SpriteFrame.h"
#include "Transform.h"

class Canvas : public COM
{
public:
    Canvas();
    virtual ~Canvas();
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

#endif /* defined(__DollEngine__Canvas__) */
