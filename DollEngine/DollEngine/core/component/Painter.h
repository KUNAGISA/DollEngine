//
//  Painter.h
//  DollEngine
//
//  Created by DollStudio on 15/4/26.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__Painter__
#define __DollEngine__Painter__

#include "Component.h"
#include "SpriteFrame.h"
#include "GLTexture.h"
#include "Transform.h"
#include "GLProgram.h"
#include "Application.h"

DE_BEGIN

class Painter : public virtual Component
{
public:
    Painter();
    ~Painter();
public:
    bool loadImages(const string& path,const string& plist="");
    bool loadSize(int w,int h,int r);
    void setPaintSizeToImageSize();
public:
    void update();
    void updateWithFrame();
    void setColor(uint32_t color);
    void setGradientColor(uint32_t start,uint32_t end,bool isHorizontal);
    void setOpacity(GLubyte o);
    PROPERTY(bool, Scale9, m_scale9){m_scale9=v;NEED_REDRAW;}
    PROPERTY(bool, ColorRect, m_colorRect){m_colorRect=v;NEED_REDRAW;}
    PROPERTY(bool, Gradient, m_gradient){m_gradient=v;NEED_REDRAW;}
    PROPERTY(GLenum, BlendSrc, m_blendSrc){m_blendSrc=v;NEED_REDRAW;}
    PROPERTY(GLenum, BlendDst, m_blendDst){m_blendDst=v;NEED_REDRAW;}
    PROPERTY(SpriteFrame*, DisplayFrame, m_displayFrame);
    PROPERTY(GLProgram*, Program, m_program){m_program=v;NEED_REDRAW;}
    PROPERTY(GradientColor*, Color, m_color){m_color=v;NEED_REDRAW;}
    PROPERTY(float, PaintWidth, m_paintWidth){m_paintWidth=v;NEED_REDRAW;}
    PROPERTY(float, PaintHeight, m_paintHeight){m_paintHeight=v;NEED_REDRAW;}
};

DE_END

#endif /* defined(__DollEngine__Painter__) */
