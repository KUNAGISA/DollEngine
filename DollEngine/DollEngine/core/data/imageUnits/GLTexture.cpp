//
//  GLTexture.cpp
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "GLTexture.h"
#include "GLCache.h"
#include "IOData.h"
#include "GLCanvas.h"

DE_BEGIN

GLTexture::GLTexture()
:m_retainCount(0)
,m_height(0)
,m_textureId(0)
,m_width(0)
{
    
}

GLTexture::~GLTexture()
{
    GLCache::GetInstance()->removeTextureCache(this);
    if (m_textureId) {
        GLCanvas::GetInstance()->deleteTexture(1, &m_textureId);
    }
}

bool GLTexture::initWithImage(ImageData* image)
{
    setTextureId(GLCanvas::GetInstance()->loadTexture(image->getData()->getBuffer(),image->getWidth(),image->getHeight()));
    setWidth(image->getWidth());
    setHeight(image->getHeight());
    return true;
}

bool GLTexture::initWithSize(int w,int h)
{
    void* data = malloc(w*h*4);
    if (!data) {
        return false;
    }
    memset(data, 0, w*h*4);
    setTextureId(GLCanvas::GetInstance()->loadTexture(data,w,h));
    setWidth(w);
    setHeight(h);
    free(data);
    return true;
}

void GLTexture::retain()
{
    m_retainCount++;
}

void GLTexture::release()
{
    m_retainCount--;
    if (m_retainCount <= 0) {
        delete this;
    }
}

void GLTexture::bind(GLenum activeId)
{
    if (m_textureId) {
        GLCanvas::GetInstance()->bindTexture(activeId,m_textureId);
    }
}

void GLTexture::setTextureId(GLuint v)
{
    if (m_textureId) {
        GLCanvas::GetInstance()->deleteTexture(1, &m_textureId);
    }
    m_textureId = v;
}

unsigned char* GLTexture::getData()
{
    unsigned char* data = new unsigned char[getWidth()*getHeight()*4];
    memset(data, 0, getWidth()*getHeight()*4);
    GLCanvas::GetInstance()->readPixels(0, 0, getWidth(), getHeight(), GL_RGBA, GL_UNSIGNED_BYTE, data);
    return data;
}

DE_END

