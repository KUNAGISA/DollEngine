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
    
    virtual void setDrawSize(float w,float h);
    virtual void setScale9(float l,float t,float r,float b);
    virtual void setOrginRect(float x,float y,float w,float h);
    float getWidth(){return m_orginRect.width;}
    float getHeight(){return m_orginRect.height;}
    void toTexCoord(GLfloat* v);
    
    PROPERTY(Texture*,Texture,m_texture);
    PROPERTY(bool, IsScale9,m_isScale9){m_isScale9=v;}
    PROPERTY_CONST(Scale9Config, Scale9, m_scale9){m_scale9=v;}
    PROPERTY_CONST(Size, DrawSize,m_drawSize){m_drawSize=v;}
    PROPERTY_CONST(Rect, OrginRect,m_orginRect){m_orginRect=v;}
    
};
DE_END


#endif /* defined(__DollEngine__ImageInfo__) */
