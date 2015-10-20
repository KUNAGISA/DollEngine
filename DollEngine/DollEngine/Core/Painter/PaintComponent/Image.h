//
//  Image.h
//  DollEngine
//
//  Created by DollStudio on 15/4/26.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__Image__
#define __DollEngine__Image__

#include "System.h"
#include "ImageInfo.h"
#include "Texture.h"
#include "Transform.h"
#include "PaintProgram.h"

DE_BEGIN

class Image
{
public:
    Image();
    virtual ~Image();
public:
    virtual bool loadImages(const String& path,const String& plist="");
    virtual void freeImage(){SAFF_DELETE(m_displayFrame);}
    void setDrawSize(float w,float h);
    void clipRect(float x,float y,float w,float h);
    void setScale9(float l,float t,float r,float b);
    void setSizeToImageSize();
    void setIsScale9(bool v);
    void setProgram(const String& name);
public:
    void update();
    void updateWithScale9();
    void updateWithFrame();
    void setGradientColor(uint32_t start,uint32_t end,int vector);
    void setOpacity(GLubyte o);
    PROPERTY_RO(bool, Gradient, m_gradient);
    PROPERTY(GLenum, BlendSrc, m_blendSrc){m_blendSrc=v;NEED_REDRAW;}
    PROPERTY(GLenum, BlendDst, m_blendDst){m_blendDst=v;NEED_REDRAW;}
    PROPERTY(ImageInfo*, DisplayFrame, m_displayFrame);
    PROPERTY(PaintProgram*, Program, m_program){m_program=v;NEED_REDRAW;}
    PROPERTY(float, PaintWidth, m_paintWidth){m_paintWidth=v;NEED_REDRAW;}
    PROPERTY(float, PaintHeight, m_paintHeight){m_paintHeight=v;NEED_REDRAW;}
    PROPERTY(bool, FlipY, m_flipY){m_flipY=v;}
    PROPERTY(uint32_t, Color, m_color);
protected:
    void flushPaintConfig(PaintConfig& config);
protected:
    GradientColor m_realColor;
    uint32_t m_endColor;
    GLubyte m_opacity;
    GLubyte m_endOpacity;
};

DE_END

#endif /* defined(__DollEngine__Image__) */
