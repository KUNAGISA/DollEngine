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
    virtual bool loadImages(const string& path,const string& plist="");
    bool loadSize(int w,int h,int r);
    virtual void setSizeToImageSize();
public:
    void update();
    void updateWithScale9();
    void updateWithFrame();
    void setColor(uint32_t color);
    void setGradientColor(uint32_t start,uint32_t end,int vector);
    void setOpacity(GLubyte o);
    PROPERTY(bool, Scale9, m_scale9){m_scale9=v;NEED_REDRAW;}
    PROPERTY(float, Scale9L, m_scale9L){m_scale9L=v;NEED_REDRAW;}
    PROPERTY(float, Scale9T, m_scale9T){m_scale9T=v;NEED_REDRAW;}
    PROPERTY(float, Scale9R, m_scale9R){m_scale9R=v;NEED_REDRAW;}
    PROPERTY(float, Scale9B, m_scale9B){m_scale9B=v;NEED_REDRAW;}
    PROPERTY_RO(bool, ColorRect, m_colorRect);
    PROPERTY_RO(bool, Gradient, m_gradient);
    PROPERTY(GLenum, BlendSrc, m_blendSrc){m_blendSrc=v;NEED_REDRAW;}
    PROPERTY(GLenum, BlendDst, m_blendDst){m_blendDst=v;NEED_REDRAW;}
    PROPERTY(SpriteFrame*, DisplayFrame, m_displayFrame);
    PROPERTY(GLProgram*, Program, m_program){m_program=v;NEED_REDRAW;}
    PROPERTY(float, PaintWidth, m_paintWidth){m_paintWidth=v;NEED_REDRAW;}
    PROPERTY(float, PaintHeight, m_paintHeight){m_paintHeight=v;NEED_REDRAW;}
    PROPERTY(bool, FlipY, m_flipY){m_flipY=v;}
    
protected:
    void flushPaintConfig(PaintConfig& config);
protected:
    GradientColor* m_color;
};

DE_END

#endif /* defined(__DollEngine__Painter__) */
