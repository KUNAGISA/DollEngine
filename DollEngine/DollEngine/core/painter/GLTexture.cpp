//
//  GLTexture.cpp
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "GLTexture.h"
#include "GLCache.h"

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
        glDeleteTextures(1, &m_textureId);
    }
}

bool GLTexture::initWithImage(ImageData* image)
{
    glGenTextures(1,&m_textureId);
    glBindTexture(GL_TEXTURE_2D,m_textureId);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, image->getWidth(), image->getHeight(), 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image->getData()->getBuffer() );
    setWidth(image->getWidth());
    setHeight(image->getHeight());
    CHECK_GL_ERROR;
    return true;
}

bool GLTexture::initWithSize(int w,int h)
{
    void* data = malloc(w*h*4);
    if (!data) {
        return false;
    }
    memset(data, 0, w*h*4);
    glGenTextures(1, &m_textureId);
    glBindTexture(GL_TEXTURE_2D,m_textureId);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, data );
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
        glActiveTexture(activeId);
        glBindTexture(GL_TEXTURE_2D, m_textureId);
        CHECK_GL_ERROR;
    }
}

void GLTexture::setTextureId(GLuint v)
{
    if (m_textureId) {
        glDeleteTextures(1, &m_textureId);
    }
    m_textureId = v;
}

unsigned char* GLTexture::getData()
{
    unsigned char* data = new unsigned char[getWidth()*getHeight()*4];
    memset(data, 0, getWidth()*getHeight()*4);
    glReadPixels(0, 0, getWidth(), getHeight(), GL_RGBA, GL_UNSIGNED_BYTE, data);
    CHECK_GL_ERROR;
    return data;
}

DE_END

