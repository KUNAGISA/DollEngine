//
//  Texture.cpp
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "Texture.h"
#include "IOData.h"
#include "PaintEngine.h"

DE_BEGIN

Texture::Texture()
:m_retainCount(0)
,m_height(0)
,m_textureId(0)
,m_width(0)
{
    
}

Texture::~Texture()
{
    PaintEngine::GetInstance()->removeTexture(this);
    if (m_textureId) {
        PaintEngine::GetInstance()->deleteTexture(1, &m_textureId);
    }
}

bool Texture::initWithImage(PictureData* image)
{
    DrawTexId tex =PaintEngine::GetInstance()->loadTexture(image->getData()->getBuffer(),image->getWidth(),image->getHeight());
    setTextureId(tex);
    setWidth(image->getWidth());
    setHeight(image->getHeight());
    return true;
}

bool Texture::initWithSize(int w,int h)
{
    void* data = malloc(w*h*4);
    if (!data) {
        return false;
    }
    memset(data, 0, w*h*4);
    setTextureId(PaintEngine::GetInstance()->loadTexture(data,w,h));
    setWidth(w);
    setHeight(h);
    free(data);
    return true;
}

void Texture::retain()
{
    m_retainCount++;
}

void Texture::release()
{
    m_retainCount--;
    if (m_retainCount <= 0) {
        delete this;
    }
}

void Texture::bind(GLenum activeId)
{
    if (m_textureId) {
        PaintEngine::GetInstance()->bindTexture(activeId,m_textureId);
    }
}

void Texture::setTextureId(GLuint v)
{
    if (m_textureId) {
        PaintEngine::GetInstance()->deleteTexture(1, &m_textureId);
    }
    m_textureId = v;
}

unsigned char* Texture::getData()
{
    unsigned char* data = new unsigned char[getWidth()*getHeight()*4];
    memset(data, 0, getWidth()*getHeight()*4);
    PaintEngine::GetInstance()->readPixels(0, 0, getWidth(), getHeight(), GL_RGBA, GL_UNSIGNED_BYTE, data);
    return data;
}

DE_END

