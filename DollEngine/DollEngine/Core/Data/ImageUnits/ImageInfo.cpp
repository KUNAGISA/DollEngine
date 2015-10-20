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

void ImageInfo::toTexCoord(GLfloat* glCoord)
{
    if (m_texture)
    {
        glCoord[0] = m_orginRect.x/m_texture->getWidth();
        glCoord[1] = m_orginRect.y/m_texture->getHeight();
        glCoord[2] = glCoord[0];
        glCoord[3] = (m_orginRect.x+m_orginRect.height)/m_texture->getHeight();
        glCoord[4] = (m_orginRect.y+m_orginRect.width)/m_texture->getWidth();
        glCoord[5] = glCoord[3];
        glCoord[6] = glCoord[4];
        glCoord[7] = glCoord[1];
    }
    else {
        memset(glCoord,0,sizeof(GLfloat*)*8);
    }
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
