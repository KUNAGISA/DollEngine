//
//  ImageInfo.cpp
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "ImageInfo.h"
#include "PaintEngine.h"
#include "Texture.h"

DE_BEGIN
ImageInfo::ImageInfo()
:m_texture(NULL)
,m_isScale9(false)
{
    
}

ImageInfo::~ImageInfo()
{
    setTexture(NULL);
}

bool ImageInfo::loadWithFile(const String& path, const String& plist)
{
    if(plist.empty()){
        Texture* tex = PaintEngine::GetInstance()->addTexture(path);
        setTexture(tex);
        setDrawSize(tex->getWidth(),tex->getHeight());
        setOrginRect(0,0,tex->getWidth(),tex->getHeight());
    }
    else {
        DM("plist拼接大图尚未支持");
    }
    return false;
}

void ImageInfo::setDrawSize(float w,float h)
{
    m_drawSize.width = w;
    m_drawSize.height = h;
}

void ImageInfo::setScale9(float l,float t,float r,float b)
{
    m_scale9.l = l;
    m_scale9.r = r;
    m_scale9.b = b;
    m_scale9.t = t;
}

void ImageInfo::setOrginRect(float x,float y,float w,float h)
{
    m_orginRect.x = x;
    m_orginRect.y = y;
    m_orginRect.width = w;
    m_orginRect.height = h;
}

void ImageInfo::toDrawData(GLDrawData& data,DrawVertex& vex,bool flipX,bool flipY)
{
    //Vertex
    
    //Color
    
    //UV
    float l=m_orginRect.x/getTexture()->getWidth();
    float r=(m_orginRect.x+m_orginRect.width)/getTexture()->getWidth();
    float t=flipY ?
                (m_orginRect.y+m_orginRect.height)/getTexture()->getHeight():
                m_orginRect.y/getTexture()->getHeight();
    float b=flipY ?
                m_orginRect.y/getTexture()->getHeight():
                (m_orginRect.y+m_orginRect.height)/getTexture()->getHeight();
    
    data.lt.uv.v1 = data.lb.uv.v1 = l;
    data.rt.uv.v1 = data.rb.uv.v1 = r;
    data.lt.uv.v2 = data.rt.uv.v2 = t;
    data.lb.uv.v2 = data.rb.uv.v2 = b;
    
}

void ImageInfo::setTexture(Texture* tex)
{
    if(m_texture) {
        m_texture->release();
    }
    m_texture = tex;
    if(m_texture) {
        m_texture->retain();
        setOrginRect(Rect(0,0,m_texture->getWidth(),m_texture->getHeight()));
    }
}

DE_END
