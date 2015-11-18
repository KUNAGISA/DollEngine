//
//  ImageInfo.h
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__ImageInfo__
#define __DollEngine__ImageInfo__

#include "Texture.h"

DE_BEGIN

class ImageInfo
{
public:
    ImageInfo();
    ~ImageInfo();
    
    bool loadWithFile(const String& path, const String& plist="");
    bool loadWithSize(int w,int h,int r);
    
    void resetPaintSize();
    virtual void setPaintSize(float w,float h){m_paintSize.width = w;m_paintSize.height = h;}
    virtual void setScale9(float l,float t,float r,float b);
    virtual void setOrginRect(float x,float y,float w,float h);
    float getPaintWidth(){return m_paintSize.width;}
    float getPaintHeight(){return m_paintSize.height;}
    void clipRect(float x,float y,float w,float h);
    void toDrawData(GLDrawData& data,Transform* trans,bool flipX=false,bool flipY=false);
    void setColor(uint32_t start,uint32_t end,GLubyte so,GLubyte eo);
    
    PROPERTY(Texture*,Texture,m_texture);
    PROPERTY(bool, IsScale9,m_isScale9){m_isScale9=v;}
    PROPERTY_CONST(Scale9Config, Scale9, m_scale9){m_scale9=v;}
    PROPERTY_CONST(Size, PaintSize,m_paintSize){m_paintSize=v;}
    PROPERTY_CONST(Rect, ClipRect,m_clipRect){m_clipRect=v;}
    PROPERTY_CONST(Rect, OrginRect,m_orginRect){
        m_orginRect=v;
        m_clipRect.x = 0;
        m_clipRect.y = 0;
        m_clipRect.width = m_orginRect.width;
        m_clipRect.height = m_orginRect.height;
    }
    PROPERTY_CONST(GradientColor, Color,m_color){m_color=v;}
    
};
DE_END


#endif /* defined(__DollEngine__ImageInfo__) */
