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
        setPaintSize(tex->getWidth(),tex->getHeight());
        setOrginRect(0,0,tex->getWidth(),tex->getHeight());
        return true;
    }
    else {
        DM("plist拼接大图尚未支持");
    }
    return false;
}

bool ImageInfo::loadWithSize(int w,int h,int r)
{
    Texture* tex = PaintEngine::GetInstance()->addTexture(r);
    if(!tex) {
        return false;
    }
    setTexture(tex);
    setPaintSize(w,h);
    setOrginRect(0,0,tex->getWidth(),tex->getHeight());
    return true;
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

void ImageInfo::toDrawData(GLDrawData& data,Transform* trans,bool flipX,bool flipY)
{
    //Vertex
    data.lb.vertex.v1 = data.lt.vertex.v1 = m_paintPos.x;
    data.rb.vertex.v2 = data.lb.vertex.v2 = m_paintPos.y;
    data.rb.vertex.v1 = data.rt.vertex.v1 = m_paintPos.x+m_paintSize.width;
    data.lt.vertex.v2 = data.rt.vertex.v2 = m_paintPos.y+m_paintSize.height;
    if (trans) {
        trans->transTo(data.lb.vertex.v1, data.lb.vertex.v2, &data.lb.vertex);
        trans->transTo(data.lt.vertex.v1, data.lt.vertex.v2, &data.lt.vertex);
        trans->transTo(data.rb.vertex.v1, data.rb.vertex.v2, &data.rb.vertex);
        trans->transTo(data.rt.vertex.v1, data.rt.vertex.v2, &data.rt.vertex);
    }
    
    //Color
    GLfloat c[4];
    m_color.start.toColorF(c);
    c[0] *= c[3];c[1] *= c[3];c[2] *= c[3];
    memcpy(&data.lt.color, c, sizeof(GLV4F));
    memcpy(&data.rt.color, c, sizeof(GLV4F));
    m_color.end.toColorF(c);
    c[0] *= c[3];c[1] *= c[3];c[2] *= c[3];
    memcpy(&data.lb.color, c, sizeof(GLV4F));
    memcpy(&data.rb.color, c, sizeof(GLV4F));
    
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

void ImageInfo::setColor(uint32_t start,uint32_t end,GLubyte so,GLubyte eo)
{
    m_color.start.setRGB(start);
    m_color.start.a = so;
    m_color.end.setRGB(end);
    m_color.end.a = eo;
}
DE_END
