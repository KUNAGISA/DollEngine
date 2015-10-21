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
    virtual void freeImage(){SAFF_DELETE(m_info);}
    void setDrawSize(float w,float h);
    void clipRect(float x,float y,float w,float h);
    void setScale9(float l,float t,float r,float b);
    void setSizeToImageSize();
    void setIsScale9(bool v);
    void setProgram(const String& name);
    
    void draw(Transform* trans);
public:
    PROPERTY(GLenum, BlendSrc, m_blendSrc){m_blendSrc=v;NEED_REDRAW;}
    PROPERTY(GLenum, BlendDst, m_blendDst){m_blendDst=v;NEED_REDRAW;}
    PROPERTY(ImageInfo*, Info, m_info);
    PROPERTY(PaintProgram*, Program, m_program){m_program=v;NEED_REDRAW;}
    PROPERTY(bool, FlipX, m_flipX){m_flipX=v;NEED_REDRAW;}
    PROPERTY(bool, FlipY, m_flipY){m_flipY=v;NEED_REDRAW;}
    PROPERTY(uint32_t, StartColor, m_startColor){m_startColor=v;NEED_REDRAW;}
    PROPERTY(uint32_t, EndColor, m_endColor){m_endColor=v;NEED_REDRAW;}
    PROPERTY(GLubyte, StartOpacity, m_startOpacity){m_startOpacity=v;NEED_REDRAW;}
    PROPERTY(GLubyte, EndOpacity, m_endOpacity){m_endOpacity=v;NEED_REDRAW;}
protected:
    void flushPaintConfig(PaintConfig& config);
};

DE_END

#endif /* defined(__DollEngine__Image__) */
